#include "Parser.hpp"

//////////////////////////////////////////////////
// Parser class
//////////////////////////////////////////////////
Parser::Parser() {}
Parser::Parser(std::string config_file)
{
	_config_file = config_file;
	_tokenizer = Tokenizer(_config_file);
	_lookahead = _tokenizer.next_token();
	while (_lookahead.get_type() == "server")
		_servers.push_back(server());
	post_checking();
}
Parser::~Parser() {}

Token Parser::eat(std::string token_type)
{
	Token token = _lookahead;

	if (token.get_type() == "NULL")
		throw std::string("Unexpected end of file");
	if (token.get_type() != token_type)
		throw std::string("Unexpected token: " + token.get_value());
	_lookahead = _tokenizer.next_token();

	return token;
}

Server Parser::server()
{
	Server server;

	eat("server");
	eat("{");
	while (_lookahead.get_value() != "}")
		server_directives(server);
	eat("}");
	return server;
}
void Parser::server_directives(Server &server)
{
	if (_lookahead.get_type() == "host")
	{
		eat("host");
		if (_lookahead.get_type() == "string" || _lookahead.get_type() == "ipv4")
		{
			server.set_host(_lookahead.get_value());
			eat(_lookahead.get_type());
		}
		eat(";");
	}
	else if (_lookahead.get_type() == "port")
	{
		eat("port");
		if (_lookahead.get_type() == "number")
		{
			server.set_port(_lookahead.get_value());
			eat(_lookahead.get_type());
		}
		eat(";");
	}
	else if (_lookahead.get_type() == "server_name")
	{
		eat("server_name");
		while (_lookahead.get_type() != ";" && _lookahead.get_type() == "string")
		{
			server.add_server_name(_lookahead.get_value());
			eat(_lookahead.get_type());
		}
		eat(";");
	}
	else if (_lookahead.get_type() == "error_page")
	{
		eat("error_page");
		if (_lookahead.get_type() == "number")
		{
			server.add_error_page(_lookahead.get_value());
			eat(_lookahead.get_type());
			if (_lookahead.get_type() == "uri")
				server.add_error_page(_lookahead.get_value());
			eat("uri");
		}
		eat(";");
	}
	else if (_lookahead.get_type() == "client_max_body_size")
	{
		eat("client_max_body_size");
		if (_lookahead.get_type() == "number")
		{
			server.set_client_max_body_size(_lookahead.get_value());
			eat(_lookahead.get_type());
		}
		eat(";");
	}
	else if (_lookahead.get_type() == "location")
		server.add_location(location());
	else
		throw std::string("Unexpected token: " + _lookahead.get_value());
}

Location Parser::location()
{
	Location location;

	eat("location");
	if (_lookahead.get_type() == "uri")
	{
		location.set_uri(_lookahead.get_value());
		eat(_lookahead.get_type());
	}
	eat("{");
	while (_lookahead.get_value() != "}")
		location_directives(location);
	eat("}");
	return location;
}
void Parser::location_directives(Location &location)
{
	if (_lookahead.get_type() == "root")
	{
		eat("root");
		if (_lookahead.get_type() == "uri")
			location.set_root(_lookahead.get_value());
		eat("uri");
		eat(";");
	}
	else if (_lookahead.get_type() == "index")
	{
		eat("index");
		if (_lookahead.get_type() == "string")
			location.set_index(_lookahead.get_value());
		eat("string");
		eat(";");
	}
	else if (_lookahead.get_type() == "allow_methods")
	{
		eat("allow_methods");
		while (_lookahead.get_value() != ";" && _lookahead.get_type() == "string")
		{
			if (_lookahead.get_value() != "GET" && _lookahead.get_value() != "POST" && _lookahead.get_value() != "DELETE")
				throw std::string("Unexpected token: " + _lookahead.get_value());
			location.add_allow_methods(_lookahead.get_value());
			eat(_lookahead.get_type());
		}
		eat(";");
	}
	else if (_lookahead.get_type() == "redirect")
	{
		eat("redirect");
		if (_lookahead.get_type() == "uri")
			location.set_redirect(_lookahead.get_value());
		eat("uri");
		eat(";");
	}
	else if (_lookahead.get_type() == "upload")
	{
		eat("upload");
		if (_lookahead.get_type() == "uri")
			location.set_upload(_lookahead.get_value());
		eat("uri");
		eat(";");
	}
	else if (_lookahead.get_type() == "autoindex")
	{
		eat("autoindex");
		if (_lookahead.get_type() == "string")
			location.set_autoindex(_lookahead.get_value());
		eat("string");
		eat(";");
	}
	else if (_lookahead.get_type() == "cgi")
	{
		eat("cgi");
		if (_lookahead.get_type() == "string")
		{
			location.add_cgi(_lookahead.get_value());
			eat(_lookahead.get_type());
			if (_lookahead.get_type() == "uri")
				location.add_cgi(_lookahead.get_value());
			eat("uri");
		}
		eat(";");
	}
	else
		throw std::string("Unexpected token: " + _lookahead.get_value());
}

void Parser::post_checking()
{
	std::vector<short> ports;
	std::vector<Server>::iterator it = _servers.begin();

	for (; it != _servers.end(); it++)
	{
		ports.push_back(it->get_port());

		std::vector<Location> locations = it->get_locations();
		if (!locations.size())
			throw std::string("\033[0;31mError: \033[0mat least one location is required\n");
		std::vector<Location>::iterator it2 = locations.begin();
		for (; it2 != locations.end(); it2++)
			if (it2->get_uri() == "NULL" || it2->get_root() == "NULL")
				throw std::string("\033[0;31mError: \033[0mlocation uri and root are necessary\n");
	}
	// checking for duplicate ports
	std::sort(ports.begin(), ports.end());
	std::vector<short>::iterator dup = std::unique(ports.begin(), ports.end());
	if (dup != ports.end())
		throw std::string("\033[0;31mError: \033[0mduplicate ports aren't allowed\n");
}

std::vector<Server> Parser::get_servers() const { return _servers; }
