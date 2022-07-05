#include "Handle_request_response.hpp"

//////////////////////////////////////////////////
// Response
//////////////////////////////////////////////////
int Handle_request_response::send_response(int fd, Server &server)
{
	// For CGI
	if (requests[fd].first.get_cgi())
	{
		int cgi_status = requests[fd].first.mycgi.GetStatus();

		if (!cgi_status)
			return CHUNKED;
		else if (cgi_status == 1)
		{
			std::string response;
			std::ifstream file(requests[fd].first.mycgi.GetOutFile());
			if (file.good())
			{
				std::stringstream buffer;
				buffer << file.rdbuf();
				response = buffer.str();
				if (!send_string(fd, buffer.str()))
				{
					requests.erase(fd);
					return FAILED;
				}
				return clear(fd, requests[fd].first.get_connection());
			}
			else
			{
				requests[fd].first.set_status_code(500);
				requests[fd].first.set_cgi(false);
				return send_response(fd, server);
			}
		}
		requests[fd].first.set_status_code(500);
		requests[fd].first.set_cgi(false);
		return send_response(fd, server);
	}
	if (requests[fd].first.get_status_code() != 200 && requests[fd].first.get_status_code() != 204
		&& requests[fd].first.get_status_code() != 301)
	{
		std::string error_page;
		std::vector<std::string> defined_error_pages = server.get_error_page();
		std::string error_html = defined_error_page_found(defined_error_pages, requests[fd].first.get_status_code());
		if (!error_html.size())
			error_html = error_page_maker(requests[fd].first.get_status_code());

		error_page += "HTTP/1.1 " + status_code_maker(requests[fd].first.get_status_code());
		error_page += "Content-Type: text/html\r\n";
		error_page += "Content-Length: " + int_to_str(error_html.size()) + "\r\n\r\n";
		error_page += error_html;
		if (!send_string(fd, error_page))
		{
			requests.erase(fd);
			return FAILED;
		}
		return clear(fd, requests[fd].first.get_connection());
	}
	// autoindex pre processing
	std::string autoindex_file;
	if (requests[fd].second.get_autoindex() == true)
	{
		autoindex_file = autoindex_maker(fd);
		requests[fd].second.set_content_length(autoindex_file.size());
	}
	// send header
	if (!requests[fd].second.get_header_sent())
	{
		if (requests[fd].second.get_header().size() == 0)
			requests[fd].second.set_header(header_maker(fd));
		if (!send_string(fd, requests[fd].second.get_header()))
		{
			requests.erase(fd);
			return FAILED;
		}
		requests[fd].second.set_header_sent(HEADER_SENT);
		return CHUNKED;
	}
	// send body in case of GET request
	else if (requests[fd].first.get_method() == "GET")
	{
		// send body code
		if (requests[fd].second.get_autoindex() == true)
		{
			if (!send_string(fd, autoindex_file))
			{
				requests.erase(fd);
				return FAILED;
			}
		}
		else
		{
			std::ifstream requested_file(requests[fd].first.get_path());
			char buffer[BUFFER_SIZE] = {[0 ... BUFFER_SIZE - 1] = 0};
			long read;

			if (requests[fd].second.get_content_length() - requests[fd].second.get_sent_sofar())
			{
				requested_file.seekg(requests[fd].second.get_sent_sofar());
				requested_file.read(buffer, BUFFER_SIZE - 1);
				read = requested_file.gcount();
				buffer[read] = '\0';

				long sent = send(fd, buffer, read, 0);
				if (sent < 0)
				{
					requests.erase(fd);
					return FAILED;
				}
				requests[fd].second.set_sent_sofar(requests[fd].second.get_sent_sofar() + sent);
				requested_file.close();
				return CHUNCKED;
			}
		}
		return clear(fd, requests[fd].first.get_connection());
	}
	else
		return clear(fd, requests[fd].first.get_connection());
}

//////////////////////////////////////////////////
// Response tools
//////////////////////////////////////////////////
std::string Handle_request_response::header_maker(short fd)
{
	std::string header;

	header = "HTTP/1.1 " + status_code_maker(requests[fd].first.get_status_code());
	header += "Connection: " + requests[fd].first.get_connection() + "\r\n";
	if (requests[fd].first.get_method() == "GET")
	{
		header += "Content-Length: ";
		header += int_to_str(requests[fd].second.get_content_length()) + "\r\n";
		if (requests[fd].second.get_autoindex())
			header += "Content-Type: text/html\r\n";
		else
			header += content_type_maker(ext_from_path(requests[fd].first.get_path()));
	}
	header += "Set-Cookie: user1=tjmari\r\nSet-Cookie: user2=mmarzouk\r\n";
	header += "\r\n";
	return header;
}
std::string Handle_request_response::status_code_maker(short status_code)
{
	switch (status_code)
	{
	case OK:
		return "200 OK\r\n";
		break;
	case CREATED:
		return "201 Created\r\n";
		break;
	case NO_CONTENT:
		return "204 No Content\r\n";
		break;
	case MOVED_PERMANENTLY:
		return "301 Moved Permanently\r\n";
		break;
	case FOUND:
		return "302 Found\r\n";
		break;
	case TEMPORARY_REDIRECT:
		return "307 Temporary Redirect\r\n";
		break;
	case PERMANENT_REDIRECT:
		return "308 Permanent Redirect\r\n";
		break;
	case BAD_REQUEST:
		return "400 Bad Request\r\n";
		break;
	case FORBIDDEN:
		return "403 Forbidden\r\n";
		break;
	case NOT_FOUND:
		return "404 Not Found\r\n";
		break;
	case METHOD_NOT_ALLOWED:
		return "405 Method Not Allowed\r\n";
		break;
	case PAYLOAD_TOO_LARGE:
		return "413 Payload Too Large\r\n";
		break;
	case REQUEST_URI_TOO_LONG:
		return "414 URI Too Long\r\n";
		break;
	case INTERNAL_SERVER_ERROR:
		return "500 Internal Server Error\r\n";
		break;
	case NOT_IMPLEMENTED:
		return "501 Not Implemented\r\n";
		break;
	default:
		return int_to_str(status_code);
	}
}
std::string Handle_request_response::content_type_maker(std::string ext)
{
	std::string base("Content-Type: ");

	if (ext == "html" || ext == "htm")
		return base + "text/html\r\n";
	else if (ext == "css")
		return base + "text/css\r\n";
	else if (ext == "xml")
		return base + "text/xml\r\n";
	else if (ext == "gif")
		return base + "image/gif\r\n";
	else if (ext == "jpeg" || ext == "jpg")
		return base + "image/jpeg\r\n";
	else if (ext == "js")
		return base + "application/javascript\r\n";
	else if (ext == "txt")
		return base + "text/plain\r\n";
	else if (ext == "png")
		return base + "image/png\r\n";
	else if (ext == "svg" || ext == "svgz")
		return base + "image/svg+xml\r\n";
	else if (ext == "ico")
		return base + "image/x-icon\r\n";
	else if (ext == "json")
		return base + "application/json\r\n";
	else if (ext == "pdf")
		return base + "application/pdf\r\n";
	else if (ext == "csv")
		return base + "text/csv\r\n";
	else if (ext == "ppt")
		return base + "application/vnd.ms-powerpoint\r\n";
	else if (ext == "zip")
		return base + "application/zip\r\n";
	else if (ext == "mp3")
		return base + "audio/mpeg\r\n";
	else if (ext == "mp4")
		return base + "video/mp4\r\n";
	return base + "application/octet-stream\r\n";
}
std::string Handle_request_response::extension_maker(std::string type)
{
	if (type == "text/html")
		return ".html";
	else if (type == "text/css")
		return ".css";
	else if (type == "text/xml")
		return ".xml";
	else if (type == "image/gif")
		return ".gif";
	else if (type == "image/jpeg")
		return ".jpeg";
	else if (type == "application/javascript")
		return ".js";
	else if (type == "text/plain")
		return ".txt";
	else if (type == "image/png")
		return ".png";
	else if (type == "image/svg+xml")
		return ".svg";
	else if (type == "image/x-icon")
		return ".ico";
	else if (type == "application/json")
		return ".json";
	else if (type == "application/pdf")
		return ".pdf";
	else if (type == "text/csv")
		return ".csv";
	else if (type == "application/vnd.ms-powerpoint")
		return ".ppt";
	else if (type == "application/zip")
		return ".zip";
	else if (type == "audio/mpeg")
		return ".mp3";
	else if (type == "video/mp4")
		return ".mp4";
	return "";
}
std::string Handle_request_response::ext_from_path(std::string path)
{
	size_t dot_pos = path.find_last_of(".");
	if (dot_pos != std::string::npos)
		return path.substr(++dot_pos);
	return "";
}
std::string Handle_request_response::autoindex_maker(int fd)
{
	DIR *dr;
	struct dirent *en;

	std::string autoindex_file;
	autoindex_file = "\
	<!DOCTYPE html>\n\
	<html lang=\"en\">\n\
		<head>\n\
			<meta charset=\"UTF-8\">\n\
			<title>Index</title>\n\
		</head>\n\
		<body>\n\
		<h1>Index</h1>\n\
		<hr>\n<ul>\n";

	dr = opendir(requests[fd].first.get_path().c_str());
	while ((en = readdir(dr)) != NULL)
	{
		if (!strcmp(en->d_name, "."))
			continue;
		else if (!strcmp(en->d_name, ".."))
			autoindex_file += "\t\t<li><a href=\"..\">..</a></li>\n";
		else
		{
			autoindex_file += "\t\t<li><a href=\"http://";
			autoindex_file += requests[fd].first.get_host() + ":" + requests[fd].first.get_port();
			autoindex_file += requests[fd].first.get_path().substr(requests[fd].first.get_path().find("/"));
			autoindex_file += requests[fd].first.get_path().back() != '/' ? "/" : "";
			autoindex_file += en->d_name;
			autoindex_file += "\">";
			autoindex_file += en->d_name;
			autoindex_file += "</a></li>\n";
		}
	}
	autoindex_file += "\t</ul>\n</body>\n</html>";
	closedir(dr);
	return autoindex_file;
}
std::string Handle_request_response::error_page_maker(short status_code)
{
	std::string error_page;

	error_page = "\
	<!DOCTYPE html>\n\
	<html lang=\"en\">\n\
		<head>\n\
			<meta charset=\"UTF-8\">\n\
			<title>Error Page</title>\n\
		</head>\n\
		<body>\n\
		<h1>\n";
	error_page += status_code_maker(status_code);
	error_page += "</h1>\n</body>\n</html>\n";
	return error_page;
}
int Handle_request_response::clear(int fd, std::string connection)
{
	requests[fd].first.clear_request();
	requests[fd].second.clear_response();

	if (connection == "keep-alive")
		return KEEP_ALIVE;
	else
		return KILL_CONNECTION;
}
bool Handle_request_response::send_string(int fd, std::string to_send)
{
	size_t len = to_send.size();
	size_t total_send = 0;

	do
	{
		long sent = send(fd, to_send.c_str(), to_send.size(), 0);
		if (sent < 0)
			return false;
		to_send = to_send.substr(sent);
		total_send += sent;
	} while (total_send < len);
	return true;
}
std::string Handle_request_response::defined_error_page_found(std::vector<std::string> &defined_error_pages, short status_code)
{
	std::vector<std::string>::iterator it;
	it = find(defined_error_pages.begin(), defined_error_pages.end(), int_to_str(status_code));
	if (it != defined_error_pages.end())
	{
		std::string error_page = *(++it);
		std::ifstream file(error_page.substr(1));
		if (file.good())
		{
			std::stringstream buffer;
			buffer << file.rdbuf();
			return buffer.str();
		}
	}
	return "";
}
std::string Handle_request_response::int_to_str(int i)
{
	std::stringstream ss;
	std::string str;

	ss << i;
	ss >> str;
	return str;
}
