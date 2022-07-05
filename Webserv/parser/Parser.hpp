#if !defined(PARSER_HPP)
#define PARSER_HPP

#include "Tokenizer.hpp"

//////////////////////////////////////////////////
// Parser class
//////////////////////////////////////////////////
class Parser
{
private:
	std::string _config_file;
	Tokenizer _tokenizer;
	Token _lookahead;
	std::vector<Server> _servers;

public:
	Parser();
	Parser(std::string);
	~Parser();

	Token eat(std::string);

	Server server();
	void server_directives(Server &);
	Location location();
	void location_directives(Location &);
	void post_checking();

	std::vector<Server> get_servers() const;
};

#endif // PARSER_HPP
