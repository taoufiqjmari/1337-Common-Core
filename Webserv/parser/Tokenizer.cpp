#include "Tokenizer.hpp"

//////////////////////////////////////////////////
// Tokenizer class
//////////////////////////////////////////////////
Tokenizer::Tokenizer() {}
Tokenizer::Tokenizer(std::string input)
	: _input(input), _pos(0) { fill_specs(); }
Tokenizer::~Tokenizer() {}

void Tokenizer::fill_specs()
{
	_specs.push_back("whitespace");
	_specs.push_back("comment");

	_specs.push_back("{");
	_specs.push_back("}");
	_specs.push_back(";");

	_specs.push_back("server");
	_specs.push_back("host");
	_specs.push_back("port");
	_specs.push_back("server_name");
	_specs.push_back("error_page");
	_specs.push_back("client_max_body_size");

	_specs.push_back("location");
	_specs.push_back("root");
	_specs.push_back("index");
	_specs.push_back("allow_methods");
	_specs.push_back("redirect");
	_specs.push_back("upload");
	_specs.push_back("autoindex");
	_specs.push_back("cgi");

	_specs.push_back("ipv4");
	_specs.push_back("uri");
	_specs.push_back("number");
	_specs.push_back("string");
}

bool Tokenizer::is_EOF() { return _pos >= _input.length(); }
bool Tokenizer::has_next() { return _pos < _input.length(); }
Token Tokenizer::next_token()
{
	if (!has_next())
		return Token("NULL", "NULL");

	std::string string = _input.substr(_pos);

	std::vector<std::string>::iterator it = _specs.begin();
	for (; it != _specs.end(); it++)
	{
		std::string tokenValue = match(*it, string);
		if (tokenValue == "NULL")
			continue;

		// Should skip token e.g. whitespace or comment
		if (*it == "whitespace" || *it == "comment")
			return Tokenizer::next_token();

		return Token(*it, tokenValue);
	}
	throw std::string("Invalid token");
}
std::string Tokenizer::match(std::string regexp, std::string string)
{
	static Regex regex;

	std::string matched = regex.match(regexp, string);
	if (matched == "NULL")
		return "NULL";
	_pos += matched.length();
	return matched;
}
