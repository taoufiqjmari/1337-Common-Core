#include "handler.hpp"

std::vector<SocketMaker> srv;
std::map<int, int> cli_srv;

SocketMaker::~SocketMaker() {}
SocketMaker::SocketMaker(Server &serv) : server(serv), location(serv.get_locations())
{
	struct sockaddr_in address;

	memset(&address, 0, sizeof(address));
	address.sin_family = AF_INET;
	address.sin_port = htons(serv.get_port());
	address.sin_addr.s_addr = inet_addr((serv.get_host()).c_str());

	if ((_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		throw std::string("failed socket");
	if (fcntl(_socket, F_SETFL, O_NONBLOCK))
		throw std::string("failed fcntl");

	int bool_opt(1);
	if (setsockopt(_socket, SOL_SOCKET, SO_REUSEADDR, &bool_opt, sizeof(bool_opt)))
		throw std::string("failed socketoptions");

	if (bind(_socket, (sockaddr *)&address, sizeof(address)))
		throw std::string("failed bind socket");

	if (listen(_socket, 1024))
		throw std::string("failed listening to socket");
}

int set_servers(fd_set &rd, fd_set &wr)
{
	int max_fd(0);

	FD_ZERO(&rd);
	FD_ZERO(&wr);
	for (size_t i = 0; i < srv.size(); i++)
	{
		FD_SET(srv[i]._socket, &rd);
		max_fd = max_fd < srv[i]._socket ? srv[i]._socket : max_fd;
	}
	return (max_fd);
}

bool isserver(const int &fd)
{
	for (size_t i(0); i < srv.size(); i++)
	{
		if (srv[i]._socket == fd)
			return (true);
	}
	return (false);
}

Server &search_server(const int &fd)
{
	for (size_t i(0); i < srv.size(); i++)
	{
		if (srv[i]._socket == fd)
			return (srv[i].server);
	}
	return (srv[0].server);
}

void ReadyToRead(int &fd, fd_set &rd, fd_set &wr, int &max_fd)
{
	// PRINT(fd);
	if (isserver(fd))
	{
		int client;
		if ((client = accept(fd, NULL, NULL)) < 0)
			return;
		fcntl(client, F_SETFL, O_NONBLOCK);
		cli_srv[client] = fd;
		FD_SET(client, &rd);
		max_fd = max_fd < client ? client : max_fd;
	}
	else
	{
		switch (handler.recv_request(fd, search_server(cli_srv[fd])))
		{
		case FAILED:
			FD_CLR(fd, &rd);
			cli_srv.erase(fd);
			close(fd);
			fd == max_fd ? max_fd-- : 0;
			break;
		case DONE:
			FD_CLR(fd, &rd);
			FD_SET(fd, &wr);
			break;
		}
	}
}
void ReadyToWrite(int &fd, fd_set &rd, fd_set &wr, int &max_fd)
{

	// PRINT(fd);
	switch (handler.send_response(fd, search_server(cli_srv[fd])))
	{
	case KILL_CONNECTION:
		FD_CLR(fd, &wr);
		cli_srv.erase(fd);
		close(fd);
		fd == max_fd ? max_fd-- : 0;
		break;
	case KEEP_ALIVE:
		FD_CLR(fd, &wr);
		FD_SET(fd, &rd);
		break;
	}
}

void looper(std::vector<Server> servers)
{
	for (size_t i(0); i < servers.size(); i++)
	{
		try
		{
			srv.push_back(SocketMaker(servers[i]));
		}
		catch (const std::string &e)
		{
			PRINT_ERR(e);
			for (size_t j(0); j < srv.size(); j++)
				close(srv[j]._socket);
			srv.clear();
			return;
		}
	}
	fd_set rd, wr;
	fd_set tmp_rd, tmp_wr;
	int max_fd = set_servers(rd, wr);
	while (1)
	{
		FD_COPY(&rd, &tmp_rd);
		FD_COPY(&wr, &tmp_wr);
		for (size_t i = 0; i < srv.size(); i++)
			FD_SET(srv[i]._socket, &rd);
		if (select(max_fd + 1, &tmp_rd, &tmp_wr, NULL, NULL) < 1)
			continue;
		for (int i(0); i <= max_fd; i++)
		{
			if (FD_ISSET(i, &tmp_rd))
				ReadyToRead(i, rd, wr, max_fd);
			if (FD_ISSET(i, &tmp_wr))
				ReadyToWrite(i, rd, wr, max_fd);
		}
	}
}
