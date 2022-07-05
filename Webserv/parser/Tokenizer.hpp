#if !defined(TOKENIZER_HPP)
#define TOKENIZER_HPP

#include "Utils.hpp"

//////////////////////////////////////////////////
// Tokenizer class
//////////////////////////////////////////////////
class Tokenizer
{
private:
	std::string _input;
	size_t _pos;
	std::vector<std::string> _specs;

public:
	Tokenizer();
	Tokenizer(std::string);
	~Tokenizer();

	void fill_specs();

	bool is_EOF();
	bool has_next();
	Token next_token();
	std::string match(std::string, std::string);
};

#endif // TOKENIZER_HPP
