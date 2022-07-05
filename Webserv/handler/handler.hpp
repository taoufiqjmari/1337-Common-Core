#ifndef HANDLER_HPP
#define HANDLER_HPP

#include <arpa/inet.h> // htons(3), htonl(3), ntohs(3), ntohl(3)
#include <poll.h>      // poll(2)
// #include <sys/epoll.h> // epoll(7), epoll_create(2), epoll_ctl(2), epoll_wait(2)
#include <sys/event.h>  // kqueue(2)
#include <sys/select.h> // select(2)
#include <sys/time.h>   // kqueue(2)
#include <sys/types.h>  // kqueue(2)

#include "../handle_request_response/Handle_request_response.hpp"

class SocketMaker
{
public:
    int _socket;
    Server &server;
    const std::vector<Location> location;
    SocketMaker(Server &serv);
    ~SocketMaker();
};
extern std::vector<SocketMaker> srv;
extern std::map<int, int> cli_srv;

void looper(std::vector<Server> servers);
int set_servers(fd_set &rd, fd_set &wr);
void ReadyToRead(int &fd, fd_set &rd, fd_set &wr, int &max_fd);
void ReadyToWrite(int &fd, fd_set &rd, fd_set &wr, int &max_fd);
bool isserver(const int &fd);
Server &search_server(const int &fd);

#endif