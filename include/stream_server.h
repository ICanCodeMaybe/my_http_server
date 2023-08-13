#ifndef STREAM_SERVER
#define STREAM_SERVER

#include <iostream>
#include <cstring>
#include <netdb.h>
#include <string>
#include <sys/socket.h>
#include <unistd.h>

struct connection{
	struct sockaddr_storage host_addr;
	socklen_t addr_size = sizeof host_addr;
	int fd;
};

class Stream_ser{
public:
	const char* PORT;
	const int BACKLOG;
	int success = 0;
public:
	//init - getaddrinfo(), socket(), bind(), listen()
	Stream_ser(const char* PORT, int BACKLOG);

	//accept(), send()
	int Send(struct connection conn, void* data, int lenght);
	int Recv(connection conn, void* buffer, int MAX_BUFFSIZE);

	struct connection Accept();

	std::string GetMyIP(); //TODO
	std::string GetHostIP();
	
private:
	int m_status, m_fd, m_new_fd;
	socklen_t m_new_size;
	struct addrinfo m_hints, *m_res, *m_p;
	struct sockaddr_storage m_new_addr;
	
	
};
#endif
