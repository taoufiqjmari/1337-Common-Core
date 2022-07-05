#include "Handle_request_response.hpp"

//////////////////////////////////////////////////
// Request class
//////////////////////////////////////////////////
Request::Request()
{
	_method = "NULL";
	_path = "";
	_connection = "keep-alive";
	_content_length = 0;
	_content_type = "";
	_transfer_encoding = "NULL";
	_temp_header = "";
	_status_code = 200;
	_header_status = RECEIVE;
	_read_bytes = 0;
	_path_to_upload = "";
	_chunked_bytes = -1;
	_chunked_temp = "";
	_cookie = "";
	_cgi = false;
}

void Request::set_method(std::string method) { this->_method = method; }
void Request::set_path(std::string path) { this->_path = path; }
void Request::set_host(std::string host) { this->_host = host; }
void Request::set_port(std::string port) { this->_port = port; }
void Request::set_connection(std::string connection) { this->_connection = connection; }
void Request::set_content_length(std::string content_length) { this->_content_length = atoi(content_length.c_str()); }
void Request::set_content_type(std::string content_type) { this->_content_type = content_type; }
void Request::set_transfer_encoding(std::string transfer_encoding) { this->_transfer_encoding = transfer_encoding; }
void Request::set_temp_header(std::string temp_header) { this->_temp_header = temp_header; }
void Request::set_location(Location location) { this->_location = location; }
void Request::set_status_code(short status_code) { this->_status_code = status_code; }
void Request::set_header_status(short header_status) { this->_header_status = header_status; }
void Request::set_read_bytes(size_t read_bytes) { this->_read_bytes = read_bytes; }
void Request::set_path_to_upload(std::string path_to_upload) { this->_path_to_upload = path_to_upload; }
void Request::set_chunked_bytes(long chunked_bytes) { this->_chunked_bytes = chunked_bytes; }
void Request::set_chunked_temp(std::string chunked_temp) { this->_chunked_temp = chunked_temp; }
void Request::set_cookie(std::string cookie) { this->_cookie = cookie; }
void Request::set_cgi(bool cgi) { this->_cgi = cgi; }
std::string Request::get_method() const { return _method; }
std::string Request::get_path() const { return _path; }
std::string Request::get_host() const { return _host; }
std::string Request::get_port() const { return _port; }
std::string Request::get_connection() const { return _connection; }
size_t Request::get_content_length() const { return _content_length; }
std::string Request::get_content_type() const { return _content_type; }
std::string Request::get_transfer_encoding() const { return _transfer_encoding; }
std::string Request::get_temp_header() const { return _temp_header; }
Location Request::get_location() const { return _location; }
short Request::get_status_code() const { return _status_code; }
short Request::get_header_status() const { return _header_status; }
size_t Request::get_read_bytes() const { return _read_bytes; }
std::string Request::get_path_to_upload() const { return _path_to_upload; }
long Request::get_chunked_bytes() const { return _chunked_bytes; }
std::string Request::get_chunked_temp() const { return _chunked_temp; }
std::string Request::get_cookie() const { return _cookie; }
bool Request::get_cgi() const { return _cgi; }

void Request::clear_request()
{
	_method = "NULL";
	_path = "";
	_connection = "NULL";
	_content_length = 0;
	_content_type = "";
	_transfer_encoding = "NULL";
	_temp_header = "";
	_status_code = 200;
	_header_status = RECEIVE;
	_read_bytes = 0;
	_path_to_upload = "";
	_chunked_bytes = -1;
	_chunked_temp = "";
	_cookie = "";
	_cgi = false;
}

//////////////////////////////////////////////////
// Response class
//////////////////////////////////////////////////
Response::Response()
{
	_header = "";
	_header_sent = HEADER_NOT_SENT;
	_cgi = "";
	_cgi_path = "";
	_autoindex = false;
	_content_length = 0;
	_sent_sofar = 0;
}

void Response::set_header(std::string header) { this->_header = header; }
void Response::set_header_sent(bool header_sent) { this->_header_sent = header_sent; }
void Response::set_cgi(std::string cgi) { this->_cgi = cgi; }
void Response::set_cgi_path(std::string cgi_path) { this->_cgi_path = cgi_path; }
void Response::set_autoindex(bool autoindex) { this->_autoindex = autoindex; }
void Response::set_content_length(unsigned long content_length) { this->_content_length = content_length; }
void Response::set_sent_sofar(unsigned long sent_sofar) { this->_sent_sofar = sent_sofar; }
std::string Response::get_header() const { return _header; }
bool Response::get_header_sent() const { return _header_sent; }
std::string Response::get_cgi() const { return _cgi; }
std::string Response::get_cgi_path() const { return _cgi_path; }
bool Response::get_autoindex() const { return _autoindex; }
unsigned long Response::get_content_length() const { return _content_length; }
unsigned long Response::get_sent_sofar() const { return _sent_sofar; }

void Response::clear_response()
{
	_header = "";
	_header_sent = HEADER_NOT_SENT;
	_cgi = "";
	_cgi_path = "";
	_autoindex = false;
	_content_length = 0;
	_sent_sofar = 0;
}

//////////////////////////////////////////////////
// Handle_request_response class
//////////////////////////////////////////////////
Handle_request_response::Handle_request_response() {}

Handle_request_response handler;
