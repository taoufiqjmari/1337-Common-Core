#if !defined(HANDLE_REQUEST_RESPONSE_HPP)
#define HANDLE_REQUEST_RESPONSE_HPP

#define PRINT_ERR(err) std::cerr << err << std::endl
#define PRINT(msg) std::cout << msg << std::endl

// Status Codes
/// 2xx Succesful
#define OK 200
#define CREATED 201
#define NO_CONTENT 204
/// 3xx Redirection
#define MOVED_PERMANENTLY 301
#define FOUND 302
#define SEE_OTHER 303
#define NOT_MODIFIED 304
#define TEMPORARY_REDIRECT 307
#define PERMANENT_REDIRECT 308
/// 4xx Client Error
#define BAD_REQUEST 400
#define UNAUTHORIZED 401
#define FORBIDDEN 403
#define NOT_FOUND 404
#define METHOD_NOT_ALLOWED 405
#define PAYLOAD_TOO_LARGE 413
#define REQUEST_URI_TOO_LONG 414
/// 5xx Server Error
#define INTERNAL_SERVER_ERROR 500
#define NOT_IMPLEMENTED 501

// header and body status
#define RECEIVE 0
#define READ 1
#define PARSED 2
#define FULLY_PARSED 3

// Request
#define FAILED -1
#define CHUNCKED 0
#define DONE 1

// Response
#define HEADER_NOT_SENT 0
#define HEADER_SENT 1
#define KILL_CONNECTION -1
#define CHUNKED 0
#define KEEP_ALIVE 1

#include "../parser/Parser.hpp"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sstream>
#include <map>
#include <sys/socket.h> // socket(2), accept(2), listen(2), send(2), recv(2), bind(2), connect(2), inet_addr(3), setsockopt(2), getsockname(2)
#include <sys/stat.h>	// stat(2)
#include <dirent.h>
#include <sys/types.h>

#define BUFFER_SIZE 1025

//////////////////////////////////////////////////
// CGI class
//////////////////////////////////////////////////

class cgi
{
private:
	int _status;
	std::string outfile;
	int infd;
	int outfd;
	int pid;
	int fd;
	char *args[3];

	int	MakeRespFile(int &fd);
	int checktype(std::string path);
	void SetCgiEnv();
	void execute_cgi();
public:
	cgi();
	~cgi();

	void run(int fd);
	int GetStatus();
	std::string &GetOutFile();
};

//////////////////////////////////////////////////
// Request class
//////////////////////////////////////////////////
class Request
{
private:
	std::string _method;
	std::string _path;
	std::string _host;
	std::string _port;
	std::string _connection;
	size_t _content_length;
	std::string _content_type;
	std::string _transfer_encoding;
	std::string _temp_header;
	Location _location;
	short _status_code;
	short _header_status;
	size_t _read_bytes;
	std::string _path_to_upload;
	long _chunked_bytes;
	std::string _chunked_temp;
	std::string _cookie;
	bool _cgi;

public:
	Request();
	cgi mycgi;

	void set_method(std::string);
	void set_path(std::string);
	void set_host(std::string);
	void set_port(std::string);
	void set_connection(std::string);
	void set_content_length(std::string);
	void set_content_type(std::string);
	void set_transfer_encoding(std::string);
	void set_temp_header(std::string);
	void set_location(Location);
	void set_status_code(short);
	void set_header_status(short);
	void set_read_bytes(size_t);
	void set_path_to_upload(std::string);
	void set_chunked_bytes(long);
	void set_chunked_temp(std::string);
	void set_cookie(std::string);
	void set_cgi(bool);
	std::string get_method() const;
	std::string get_path() const;
	std::string get_host() const;
	std::string get_port() const;
	std::string get_connection() const;
	size_t get_content_length() const;
	std::string get_content_type() const;
	std::string get_transfer_encoding() const;
	std::string get_temp_header() const;
	Location get_location() const;
	short get_header_status() const;
	short get_status_code() const;
	size_t get_read_bytes() const;
	std::string get_path_to_upload() const;
	long get_chunked_bytes() const;
	std::string get_chunked_temp() const;
	std::string get_cookie() const;
	bool get_cgi() const;

	void clear_request();
};

//////////////////////////////////////////////////
// Handle_request_response class
//////////////////////////////////////////////////
class Response
{
private:
	std::string _header;
	bool _header_sent;
	std::string _cgi;
	std::string _cgi_path;
	bool _autoindex;
	unsigned long _content_length;
	unsigned long _sent_sofar;

public:
	Response();

	void set_header(std::string);
	void set_header_sent(bool);
	void set_cgi(std::string);
	void set_cgi_path(std::string);
	void set_autoindex(bool);
	void set_content_length(unsigned long);
	void set_sent_sofar(unsigned long);
	std::string get_header() const;
	bool get_header_sent() const;
	std::string get_cgi() const;
	std::string get_cgi_path() const;
	bool get_autoindex() const;
	unsigned long get_content_length() const;
	unsigned long get_sent_sofar() const;

	void clear_response();
};

//////////////////////////////////////////////////
// Handle_request_response class
//////////////////////////////////////////////////
class Handle_request_response
{
private:
	std::map<int, std::pair<Request, Response> > requests;

public:
	Handle_request_response();

	int recv_request(int, Server &);
	int get_handle(int);
	int post_handle(int, std::string &, int);
	int delete_handle(int);

	int request_first_line(int, std::string, Server &);
	std::string find_value(std::string, std::string);
	Location right_location(int, std::string, Server &);
	Location wanted_location(std::string, Server &);
	bool is_method_allowed(Location, std::string);
	bool fix_path(Request &);
	std::vector<std::string> split_string(std::string, std::string);
	std::string generate_random_name();
	int str_to_int(std::string);
	int hex_to_dec(std::string);

	int send_response(int, Server &);
	std::string header_maker(short);
	std::string status_code_maker(short);
	std::string content_type_maker(std::string);
	std::string extension_maker(std::string);
	std::string ext_from_path(std::string);
	std::string autoindex_maker(int);
	std::string error_page_maker(short);
	int clear(int, std::string);
	bool send_string(int, std::string);
	std::string defined_error_page_found(std::vector<std::string> &, short);
	std::string int_to_str(int);

	friend class cgi;
};

extern Handle_request_response handler;

#endif // HANDLE_REQUEST_RESPONSE_HPP
