#include "Handle_request_response.hpp"

//////////////////////////////////////////////////
// CGI class
//////////////////////////////////////////////////
int cgi::MakeRespFile(int &fd)
{
	std::stringstream s;
	std::string tmp;
	s << fd, s >> tmp;
	int ret = open(("/tmp/CgiResp" + tmp).c_str(), O_CREAT | O_WRONLY | O_TRUNC, 0777);
	outfile = "/tmp/CgiResp" + tmp;
	return (ret);
}
int cgi::checktype(std::string path)
{
	struct stat s;
	if (stat(path.c_str(), &s))
		return (0);
	if (S_ISDIR(s.st_mode))
		return (2);
	if (!S_ISREG(s.st_mode))
		return (0);
	if (!(s.st_mode & S_IXUSR))
		return (0);
	return (1);
}
void cgi::SetCgiEnv()
{
	setenv("GATEWAY_INTERFACE", "CGI/1.1", 1);
	setenv("SERVER_PROTOCOL", "HTTP/1.1", 1);
	setenv("REDIRECT_STATUS", "200", 1);
	setenv("SCRIPT_NAME", (char *)handler.requests[fd].first.get_path().c_str(), 1);
	setenv("REQUEST_METHOD", handler.requests[fd].first.get_method().c_str(), 1);
	setenv("CONTENT_TYPE", handler.requests[fd].first.get_content_type().c_str(), 1);
	if (handler.requests[fd].first.get_method() == "GET")
	{
		setenv("QUERY_STRING", "", 1);
		setenv("CONTENT_LENGTH", "", 1);
	}
	else if (handler.requests[fd].first.get_method() == "POST")
	{
		infd = open(handler.requests[fd].first.get_path_to_upload().c_str(), O_RDONLY, 0666);
		std::stringstream s;
		std::string tmp;
		s << handler.requests[fd].first.get_content_length(), s >> tmp;
		setenv("QUERY_STRING", "", 1);
		setenv("CONTENT_LENGTH", "tmp", 1);
	}
}
void cgi::execute_cgi()
{
	pid = fork();
	if (pid < 0)
		return;
	if (pid == 0)
	{
		SetCgiEnv();
		dup2(infd, 0);
		dup2(outfd, 1);
		execv(args[0], args);
		exit(1);
	}
}

cgi::cgi() {}
cgi::~cgi() {}

void cgi::run(int fds)
{
	infd = 0;
	fd = fds;
	_status = 0;
	outfd = MakeRespFile(fd);
	if (outfd < 0 || checktype(handler.requests[fd].second.get_cgi_path()) != 1)
	{
		_status = 500;
		return;
	}
	std::string cgipsth = handler.requests[fd].second.get_cgi_path();
	std::string inputfile = handler.requests[fd].first.get_path();
	args[0] = (char *)cgipsth.data();
	args[1] = (char *)inputfile.data();
	args[2] = NULL;
	execute_cgi();
}
int cgi::GetStatus()
{
	int Stat;
	int ret;

	if (_status)
		return (_status);
	ret = waitpid(pid, &Stat, WNOHANG);
	if (!ret)
		return (0); // not finished
	if (infd > 0)
		close(infd);
	close(outfd);
	if (ret == pid)
		return (1); // done
	return (500);	// server error
}
std::string &cgi::GetOutFile() { return (outfile); }
