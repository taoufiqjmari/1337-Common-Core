#include "Handle_request_response.hpp"

//////////////////////////////////////////////////
// Request
//////////////////////////////////////////////////
int Handle_request_response::recv_request(int fd, Server &server)
{
	/// if server doesn't exist, add it to the map
	if (requests.find(fd) == requests.end())
	{
		requests[fd].first = Request();
		requests[fd].second = Response();
	}

	char temp[BUFFER_SIZE];
	long read = recv(fd, temp, BUFFER_SIZE - 1, 0);

	if (read <= 0)
	{
		requests.erase(fd);
		return FAILED;
	}
	else
	{
		temp[read] = '\0';
		std::string received(temp, read);
		// recv header
		if (!requests[fd].first.get_header_status())
		{
			size_t header_end = received.find("\r\n\r\n");
			if (header_end == std::string::npos)
			{
				requests[fd].first.set_temp_header(requests[fd].first.get_temp_header() + received);
				return CHUNCKED;
			}
			else
			{
				received = requests[fd].first.get_temp_header() + received;
				requests[fd].first.set_header_status(READ);
			}
		}

		// parse header
		if (requests[fd].first.get_header_status() < PARSED)
		{
			int first_line_status = request_first_line(fd, received, server);
			if (first_line_status)
			{
				requests[fd].first.set_status_code(first_line_status);
				return DONE;
			}
			std::string host_port = find_value("Host:", received);
			requests[fd].first.set_host(split_string(host_port, ":")[0]);
			requests[fd].first.set_port(split_string(host_port, ":")[1]);
			requests[fd].first.set_connection(find_value("Connection:", received));
			if (requests[fd].first.get_connection() == "NULL")
				requests[fd].first.set_connection("keep-alive");
			requests[fd].first.set_transfer_encoding(find_value("Transfer-Encoding:", received));
			if (requests[fd].first.get_transfer_encoding() != "NULL" && requests[fd].first.get_transfer_encoding() != "chunked")
			{
				requests[fd].first.set_status_code(NOT_IMPLEMENTED);
				return DONE;
			}
			requests[fd].first.set_content_length(find_value("Content-Length:", received));
			if (requests[fd].first.get_content_length() > server.get_client_max_body_size())
			{
				requests[fd].first.set_status_code(PAYLOAD_TOO_LARGE);
				return DONE;
			}
			requests[fd].first.set_content_type(find_value("Content-Type:", received));
			if (!fix_path(requests[fd].first))
			{
				requests[fd].first.set_status_code(NOT_IMPLEMENTED);
				return DONE;
			}
			requests[fd].first.set_cookie(find_value("Cookie:", received));
			requests[fd].first.set_header_status(PARSED);
		}

		if (requests[fd].first.get_method() == "GET")
			return Handle_request_response::get_handle(fd);
		if (requests[fd].first.get_method() == "POST")
			return Handle_request_response::post_handle(fd, received, read);
		else
			return Handle_request_response::delete_handle(fd);
	}
}
int Handle_request_response::get_handle(int fd)
{
	// create root
	std::string cmd = "mkdir -p " + requests[fd].first.get_location().get_root().substr(1);
	if (system(cmd.c_str()) < 0)
	{
		requests.erase(fd);
		return FAILED;
	}

	struct stat info;
	std::string path = requests[fd].first.get_path();
	std::string ext = ext_from_path(path);
	if (stat(path.c_str(), &info) != 0)
	{
		// request resource not found
		requests[fd].first.set_status_code(NOT_FOUND);
		return DONE;
	}
	else if (S_ISREG(info.st_mode))
	{
		// is registery
		std::vector<std::string> cgi = requests[fd].first.get_location().get_cgi();
		std::vector<std::string>::iterator it;

		// running CGI code here
		if ((it = find(cgi.begin(), cgi.end(), ext)) != cgi.end())
		{
			requests[fd].second.set_cgi(*it++);
			requests[fd].second.set_cgi_path(*it);
			requests[fd].first.mycgi.run(fd);
			requests[fd].first.set_cgi(true);
		}
		else
			requests[fd].second.set_content_length(info.st_size);
		return DONE;
	}
	else // if (S_ISDIR(info.st_mode))
	{
		// is directory
		std::string index = requests[fd].first.get_location().get_index();
		if (index != "NULL")
		{
			// if there is an index file
			std::string index_path = path + "/" + index;
			struct stat index_info;
			if (stat(index_path.c_str(), &index_info) == 0 && S_ISREG(index_info.st_mode))
			{
				requests[fd].first.set_path(index_path);
				return get_handle(fd);
			}
			else
				requests[fd].first.set_status_code(NOT_FOUND);
		}
		else
		{
			// if autoindex is on
			if (requests[fd].first.get_location().get_autoindex() == "on")
				requests[fd].second.set_autoindex(true);
			else
				requests[fd].first.set_status_code(FORBIDDEN);
		}
		return DONE;
	}
}
int Handle_request_response::post_handle(int fd, std::string &received, int read)
{
	if (requests[fd].first.get_header_status() == PARSED)
	{
		received = received.substr(received.find("\r\n\r\n") + 4);
		requests[fd].first.set_read_bytes(received.size());
		requests[fd].first.set_header_status(FULLY_PARSED);

		// create folder to upload to
		requests[fd].first.set_path_to_upload("mkdir -p " + requests[fd].first.get_location().get_upload().substr(1));
		if (system(requests[fd].first.get_path_to_upload().c_str()) < 0)
		{
			requests.erase(fd);
			return FAILED;
		}
		requests[fd].first.set_path_to_upload(requests[fd].first.get_location().get_upload().substr(1) + "/" + generate_random_name() + extension_maker(requests[fd].first.get_content_type()));
	}
	else if (requests[fd].first.get_transfer_encoding() != "chunked") // counting not needed in case of chunked
		requests[fd].first.set_read_bytes(requests[fd].first.get_read_bytes() + read);

	if (requests[fd].first.get_transfer_encoding() == "chunked")
	{
		size_t endline_pos;
		requests[fd].first.set_chunked_temp(requests[fd].first.get_chunked_temp() + received);
		endline_pos = requests[fd].first.get_chunked_temp().find("\r\n");

		while (endline_pos != std::string::npos)
		{
			if (requests[fd].first.get_chunked_bytes() == -1)
			{
				requests[fd].first.set_chunked_bytes(hex_to_dec(requests[fd].first.get_chunked_temp().substr(0, endline_pos)));
				if (!requests[fd].first.get_chunked_bytes())
				{
					requests[fd].first.set_status_code(NO_CONTENT);
					return DONE;
				}
				requests[fd].first.set_chunked_temp(requests[fd].first.get_chunked_temp().substr(endline_pos + 2));
				endline_pos = requests[fd].first.get_chunked_temp().find("\r\n");
			}
			else
			{
				size_t chunked_bytes = requests[fd].first.get_chunked_bytes();
				if (requests[fd].first.get_chunked_temp().size() >= chunked_bytes)
				{
					std::ofstream upload_file(requests[fd].first.get_path_to_upload(), std::ios::out | std::ios::app);
					upload_file << requests[fd].first.get_chunked_temp().substr(0, chunked_bytes);
					upload_file.close();
					requests[fd].first.set_chunked_temp(requests[fd].first.get_chunked_temp().substr(chunked_bytes + 2));
					requests[fd].first.set_chunked_bytes(-1);
					endline_pos = requests[fd].first.get_chunked_temp().find("\r\n");
				}
				else
					break;
			}
		}
		return CHUNKED;
	}
	else
	{
		std::ofstream upload_file(requests[fd].first.get_path_to_upload(), std::ios::out | std::ios::app);
		upload_file << received;
		upload_file.close();

		if (requests[fd].first.get_read_bytes() < requests[fd].first.get_content_length())
			return CHUNCKED;
	}
	// CGI Handling
	std::string ext = ext_from_path(requests[fd].first.get_path());
	std::vector<std::string> cgi = requests[fd].first.get_location().get_cgi();
	std::vector<std::string>::iterator it;

	// running CGI code here
	if ((it = find(cgi.begin(), cgi.end(), ext)) != cgi.end())
	{
		requests[fd].second.set_cgi(*it++);
		requests[fd].second.set_cgi_path(*it);
		requests[fd].first.mycgi.run(fd);
		requests[fd].first.set_cgi(true);
	}
	else
		requests[fd].first.set_status_code(NO_CONTENT);
	return DONE;
}
int Handle_request_response::delete_handle(int fd)
{
	struct stat statbuf;
	std::string path = requests[fd].first.get_path();
	std::string path_to_delete;

	if (stat(path.c_str(), &statbuf) != 0)
	{
		requests[fd].first.set_status_code(NOT_FOUND);
		return DONE;
	}
	else if (S_ISREG(statbuf.st_mode))
		path_to_delete = "rm -f " + path;
	else if (S_ISDIR(statbuf.st_mode))
		path_to_delete = "rm -rf " + path;

	if (S_IWUSR & statbuf.st_mode)
	{
		if (!system(path_to_delete.c_str()))
			requests[fd].first.set_status_code(NO_CONTENT);
		else
			requests[fd].first.set_status_code(INTERNAL_SERVER_ERROR);
	}
	else
		requests[fd].first.set_status_code(FORBIDDEN);
	return DONE;
}

//////////////////////////////////////////////////
// Request tools
//////////////////////////////////////////////////
int Handle_request_response::request_first_line(int fd, std::string received, Server &server)
{
	size_t pos;
	size_t end_pos;

	if ((pos = received.find("GET")) == std::string::npos)
		if ((pos = received.find("POST")) == std::string::npos)
			if ((pos = received.find("DELETE")) == std::string::npos)
				return NOT_IMPLEMENTED;
	if ((end_pos = received.find("\r\n", pos)) == std::string::npos)
		return BAD_REQUEST;

	std::vector<std::string> splitted_first_line = split_string(received.substr(pos, end_pos - pos), " ");
	requests[fd].first.set_location(right_location(fd, splitted_first_line[1], server));
	if (requests[fd].first.get_location().get_uri() == "NULL")
		return NOT_FOUND;

	if (is_method_allowed(requests[fd].first.get_location(), splitted_first_line[0]))
		requests[fd].first.set_method(splitted_first_line[0]);
	else
		return METHOD_NOT_ALLOWED;
	if (!requests[fd].first.get_path().size())
	{
		if (splitted_first_line[1].size() <= 1024)
			requests[fd].first.set_path(splitted_first_line[1]);
		else
			return REQUEST_URI_TOO_LONG;
	}
	return 0;
}
std::string Handle_request_response::find_value(std::string key, std::string received)
{
	size_t pos = received.find(key);
	size_t end_pos = received.find("\r\n", pos);
	if (pos == std::string::npos || end_pos == std::string::npos)
		return "NULL";

	std::string whole_line;
	whole_line = received.substr(pos, end_pos - pos);
	std::vector<std::string> splitted_line = split_string(whole_line, " ");
	return splitted_line[1];
}
Location Handle_request_response::right_location(int fd, std::string path, Server &server)
{
	Location location;

	do
	{
		location = wanted_location(path, server);

		if (location.get_uri() == "NULL")
		{
			size_t pos = path.find_last_of("/");
			if (pos != std::string::npos)
				path = path.substr(0, pos);
		}
		else
			break;
	} while (path.size());

	// if location isn't found, use root location
	// if no root location is found an empty location is returned
	if (location.get_uri() == "NULL")
		location = wanted_location("/", server);

	// redirection
	if (location.get_uri() != "NULL" && location.get_redirect() != "NULL")
	{
		requests[fd].first.set_path(location.get_redirect());
		requests[fd].first.set_status_code(MOVED_PERMANENTLY);
		return right_location(fd, location.get_redirect(), server);
	}

	return location;
}
Location Handle_request_response::wanted_location(std::string path, Server &server)
{
	std::vector<Location> locations = server.get_locations();
	std::vector<Location>::iterator it = locations.begin();

	while (it != locations.end())
	{
		if (it->get_uri() == path)
			return *it;
		it++;
	}
	return Location();
}
bool Handle_request_response::is_method_allowed(Location location, std::string method)
{
	std::vector<std::string> allow_methods = location.get_allow_methods();
	if (std::count(allow_methods.begin(), allow_methods.end(), method))
		return true;
	return false;
}
bool Handle_request_response::fix_path(Request &request)
{
	Location location = request.get_location();

	// if location accept POST and doesn't have upload directive is concidered an error
	if (request.get_method() == "POST" && request.get_location().get_upload() == "NULL")
		return false;

	std::string uri = request.get_method() == "POST" ? location.get_upload().substr(1) : location.get_root().substr(1);
	size_t route_size = location.get_uri().size();

	// uri.size() == 1 => "/"
	route_size = route_size == 1 ? 0 : route_size;
	if (location.get_uri() != request.get_path())
		request.set_path(uri + request.get_path().substr(route_size));
	else
		request.set_path(uri + request.get_path().substr(route_size) + '/');
	return true;
}
std::vector<std::string> Handle_request_response::split_string(std::string str, std::string delimiter)
{
	size_t pos;
	std::string token;
	std::vector<std::string> final_vector;

	while ((pos = str.find(delimiter)) != std::string::npos)
	{
		token = str.substr(0, pos);
		final_vector.push_back(token);
		str.erase(0, pos + delimiter.length());
	}
	final_vector.push_back(str);
	return final_vector;
}
std::string Handle_request_response::generate_random_name()
{
	std::string random_name;

	srand(time(0));
	random_name = "file_" + int_to_str(rand());
	return random_name;
}
int Handle_request_response::str_to_int(std::string str)
{
	std::stringstream ss;
	int i;

	ss << str;
	ss >> i;
	return i;
}
int Handle_request_response::hex_to_dec(std::string hex_val)
{
	int base = 1;
	int dec_val = 0;

	for (int i = hex_val.size() - 1; i >= 0; i--)
	{
		if (hex_val[i] >= '0' && hex_val[i] <= '9')
			dec_val += (int(hex_val[i]) - 48) * base;
		else if (hex_val[i] >= 'a' && hex_val[i] <= 'f')
			dec_val += (int(hex_val[i]) - 87) * base;
		base = base * 16;
	}
	return dec_val;
}
