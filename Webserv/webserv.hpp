#if !defined(WEBSERV_HPP)
#define WEBSERV_HPP

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

#include <signal.h>
#include "handler/handler.hpp"

// TOOLS
void setup_config_file(int, char **, std::string &);
void read_config_file(std::string &);
void exit_err(std::string &);

#endif // WEBSERV_HPP

// () = include()
// webserv ( handler ( Handle_request_response ( Parser ) ) )
