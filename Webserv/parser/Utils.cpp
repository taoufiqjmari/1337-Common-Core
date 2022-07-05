#include "Utils.hpp"

//////////////////////////////////////////////////
// Token class
//////////////////////////////////////////////////
Token::Token() {}
Token::Token(std::string type, std::string value) : _type(type), _value(value) {}
Token::Token(const Token &token) : _type(token._type), _value(token._value) {}
Token::~Token() {}

Token &Token::operator=(const Token &token)
{
	_type = token._type;
	_value = token._value;
	return *this;
}

void Token::set_type(std::string type) { _type = type; }
void Token::set_value(std::string value) { _value = value; }

std::string Token::get_type() const { return _type; }
std::string Token::get_value() const { return _value; }

//////////////////////////////////////////////////
// Regex class
//////////////////////////////////////////////////
Regex::Regex() {}
Regex::~Regex() {}

std::string Regex::match(std::string &regex, std::string &string)
{
	if (regex == "whitespace")
		return match_whitespace(string);
	else if (regex == "comment")
		return match_comment(string);

	else if (regex == "{")
		return match_start_block(string);
	else if (regex == "}")
		return match_end_block(string);
	else if (regex == ";")
		return match_semicolon(string);

	else if (regex == "server")
		return match_server(string);
	else if (regex == "host")
		return match_host(string);
	else if (regex == "port")
		return match_port(string);
	else if (regex == "server_name")
		return match_server_name(string);
	else if (regex == "error_page")
		return match_error_page(string);
	else if (regex == "client_max_body_size")
		return match_client_max_body_size(string);

	else if (regex == "location")
		return match_location(string);
	else if (regex == "root")
		return match_root(string);
	else if (regex == "index")
		return match_index(string);
	else if (regex == "allow_methods")
		return match_allow_methods(string);
	else if (regex == "redirect")
		return match_redirect(string);
	else if (regex == "upload")
		return match_upload(string);
	else if (regex == "autoindex")
		return match_autoindex(string);
	else if (regex == "cgi")
		return match_cgi(string);

	else if (regex == "ipv4")
		return match_ipv4(string);
	else if (regex == "uri")
		return match_uri(string);
	else if (regex == "number")
		return match_number(string);
	else if (regex == "string")
		return match_string(string);
	else
		return "NULL";
}

std::string Regex::match_whitespace(std::string &string)
{
	if (isspace(string[0]))
	{
		std::string::size_type pos = string.find_first_not_of(" \t\n");
		return string.substr(0, pos); // if pos != string::npos it returns until no more whitespace else it returns the whole string
	}
	return "NULL";
}
std::string Regex::match_comment(std::string &string)
{
	if (string[0] == '#')
	{
		std::string::size_type pos = string.find("\n");
		return string.substr(0, pos);
	}
	return "NULL";
}

std::string Regex::match_start_block(std::string &string)
{
	return string[0] == '{' ? "{" : "NULL";
}
std::string Regex::match_end_block(std::string &string)
{
	return string[0] == '}' ? "}" : "NULL";
}
std::string Regex::match_semicolon(std::string &string)
{
	return string[0] == ';' ? ";" : "NULL";
}

static std::string match_keyword(std::string &string, std::string keyword, int len)
{
	std::string from_string = string.substr(0, len);
	return (from_string == keyword && isspace(string[len])) ? keyword : "NULL";
}
std::string Regex::match_server(std::string &string)
{
	return match_keyword(string, "server", 6);
}
std::string Regex::match_host(std::string &string)
{
	return match_keyword(string, "host", 4);
}
std::string Regex::match_port(std::string &string)
{
	return match_keyword(string, "port", 4);
}
std::string Regex::match_server_name(std::string &string)
{
	return match_keyword(string, "server_name", 11);
}
std::string Regex::match_error_page(std::string &string)
{
	return match_keyword(string, "error_page", 10);
}
std::string Regex::match_client_max_body_size(std::string &string)
{
	return match_keyword(string, "client_max_body_size", 20);
}

std::string Regex::match_location(std::string &string)
{
	return match_keyword(string, "location", 8);
}
std::string Regex::match_root(std::string &string)
{
	return match_keyword(string, "root", 4);
}
std::string Regex::match_index(std::string &string)
{
	return match_keyword(string, "index", 5);
}
std::string Regex::match_allow_methods(std::string &string)
{
	return match_keyword(string, "allow_methods", 13);
}
std::string Regex::match_redirect(std::string &string)
{
	return match_keyword(string, "redirect", 8);
}
std::string Regex::match_upload(std::string &string)
{
	return match_keyword(string, "upload", 6);
}
std::string Regex::match_autoindex(std::string &string)
{
	return match_keyword(string, "autoindex", 9);
}
std::string Regex::match_cgi(std::string &string)
{
	return match_keyword(string, "cgi", 3);
}

std::string Regex::match_ipv4(std::string &string)
{
	if (isdigit(string[0]))
	{
		std::string::size_type pos = string.find_first_not_of(".0123456789");
		if (pos != std::string::npos)
		{
			std::string address = string.substr(0, pos);
			return address.find(".") != std::string::npos ? address : "NULL"; // if there is no dot, it isn't an ipv4 address
		}
		else
			throw std::string("Syntax error: file only ends with '}' or comment or whitespace");
	}
	return "NULL";
}
std::string Regex::match_uri(std::string &string)
{
	if (string[0] == '/')
	{
		std::string::size_type pos = string.find_first_not_of("-./0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ_abcdefghijklmnopqrstuvwxyz");
		if (pos != std::string::npos)
			return string.substr(0, pos);
		else
			throw std::string("Syntax error: file only ends with '}' or comment or whitespace");
	}
	return "NULL";
}
std::string Regex::match_number(std::string &string)
{
	if (isdigit(string[0]))
	{
		std::string::size_type pos = string.find_first_not_of("0123456789");
		if (pos != std::string::npos)
			return string.substr(0, pos);
		else
			throw std::string("Syntax error: file only ends with '}' or comment or whitespace");
	}
	return "NULL";
}
std::string Regex::match_string(std::string &string)
{
	if (string[0] == '"')
	{
		std::string::size_type pos = string.find("\"", 1);
		if (pos != std::string::npos)
			return string.substr(0, pos + 1);
		else
			throw std::string("Syntax error: missing closing quote");
	}
	else if (string[0] == '\'')
	{
		std::string::size_type pos = string.find("\'", 1);
		if (pos != std::string::npos)
			return string.substr(0, pos + 1);
		else
			throw std::string("Syntax error: missing closing quote");
	}
	else if (isalpha(string[0]) || string[0] == '_')
	{
		std::string::size_type pos = string.find_first_not_of(".0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ_abcdefghijklmnopqrstuvwxyz");
		if (pos != std::string::npos)
			return string.substr(0, pos);
		else
			throw std::string("Syntax error: file only ends with '}' or comment or whitespace");
	}
	return "NULL";
}

//////////////////////////////////////////////////
// Location class
//////////////////////////////////////////////////
Location::Location()
{
	this->_uri = "NULL";
	this->_root = "NULL";
	this->_index = "NULL";
	this->_autoindex = "off";
	this->_upload = "NULL";
	this->_redirect = "NULL";
}
Location::Location(const Location &src) { *this = src; }
Location::~Location() {}

Location &Location::operator=(const Location &src)
{
	this->_uri = src._uri;
	this->_root = src._root;
	this->_index = src._index;
	this->_allow_methods = src._allow_methods;
	this->_redirect = src._redirect;
	this->_upload = src._upload;
	this->_autoindex = src._autoindex;
	this->_cgi = src._cgi;
	return *this;
}

void Location::set_uri(std::string uri) { _uri = uri; }
void Location::set_root(std::string root) { _root = root; }
void Location::set_index(std::string index) { _index = index; }
void Location::add_allow_methods(std::string allow_methods) { _allow_methods.push_back(allow_methods); }
void Location::set_redirect(std::string redirect) { _redirect = redirect; }
void Location::add_cgi(std::string cgi) { _cgi.push_back(cgi); }
void Location::set_upload(std::string upload) { _upload = upload; }
void Location::set_autoindex(std::string autoindex) { _autoindex = autoindex; }

std::string Location::get_uri() const { return _uri; }
std::string Location::get_root() const { return _root; }
std::string Location::get_index() const { return _index; }
std::vector<std::string> Location::get_allow_methods() const { return _allow_methods; }
std::string Location::get_redirect() const { return _redirect; }
std::vector<std::string> Location::get_cgi() const { return _cgi; }
std::string Location::get_upload() const { return _upload; }
std::string Location::get_autoindex() const { return _autoindex; }

//////////////////////////////////////////////////
// Server class
//////////////////////////////////////////////////
Server::Server()
{
	this->_host = "0.0.0.0";
	this->_port = 8080;
	this->_client_max_body_size = 0;
}
Server::Server(const Server &src) { *this = src; }
Server::~Server() {}

Server &Server::operator=(const Server &src)
{
	this->_host = src._host;
	this->_port = src._port;
	this->_server_name = src._server_name;
	this->_error_page = src._error_page;
	this->_client_max_body_size = src._client_max_body_size;
	this->_locations = src._locations;
	return *this;
}

void Server::set_host(std::string host) { _host = host; }
void Server::set_port(std::string port)
{
	std::string::iterator it = port.begin();
	while (it != port.end())
	{
		if (!isdigit(*it))
			throw std::string("Syntax error: port must be a number");
		it++;
	}
	_port = atoi(port.c_str());
}
void Server::add_server_name(std::string server_name) { _server_name.push_back(server_name); }
void Server::add_error_page(std::string error_page) { _error_page.push_back(error_page); }
void Server::set_client_max_body_size(std::string client_max_body_size) { _client_max_body_size = atoi(client_max_body_size.c_str()); }
void Server::add_location(Location location) { _locations.push_back(location); }

std::string Server::get_host() const { return _host; }
short Server::get_port() const { return _port; }
std::vector<std::string> Server::get_server_name() const { return _server_name; }
std::vector<std::string> Server::get_error_page() const { return _error_page; }
size_t Server::get_client_max_body_size() const { return _client_max_body_size; }
std::vector<Location> Server::get_locations() const { return _locations; }

//////////////////////////////////////////////////
// Print servers function
//////////////////////////////////////////////////
void print_vector(std::vector<std::string> vector)
{
	for (std::vector<std::string>::iterator it = vector.begin(); it != vector.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl;
}
void print_servers(std::vector<Server> &servers)
{
	std::vector<Server>::iterator it = servers.begin();

	int i = 1;
	while (it != servers.end())
	{
		std::vector<Location> locations = it->get_locations();
		std::vector<Location>::iterator it2 = locations.begin();

		std::cout << "____________________SERVER " << i << "____________________" << std::endl;
		std::cout << "host:			" << it->get_host() << std::endl;
		std::cout << "port:			" << it->get_port() << std::endl;
		std::cout << "server name:		";
		print_vector(it->get_server_name());
		std::cout << "error_page:		";
		print_vector(it->get_error_page());
		std::cout << "client_max_body_size:	" << it->get_client_max_body_size() << std::endl;

		int j = 1;
		while (it2 != locations.end())
		{
			std::cout << "----------------------------------------" << std::endl;
			std::cout << "location: " << j << std::endl;
			std::cout << "	uri:			" << it2->get_uri() << std::endl;
			std::cout << "	root:			" << it2->get_root() << std::endl;
			std::cout << "	index:			" << it2->get_index() << std::endl;
			std::cout << "	allow_methods:		";
			print_vector(it2->get_allow_methods());
			std::cout << "	redirect:		" << it2->get_redirect() << std::endl;
			std::cout << "	upload:		" << it2->get_upload() << std::endl;
			std::cout << "	autoindex:		" << it2->get_autoindex() << std::endl;
			std::cout << "	cgi:		";
			print_vector(it2->get_cgi());

			j++;
			it2++;
		}

		std::cout << "____________________SERVER " << i << "____________________" << std::endl;
		std::cout << std::endl
				  << std::endl;
		i++;
		it++;
	}
}
