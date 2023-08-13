#include "stream_server.h"


Stream_ser::Stream_ser(const char* port, int BACKLOG)
	:PORT(port), BACKLOG(BACKLOG)
{
	memset(&m_hints, 0, sizeof(addrinfo));
	m_hints.ai_family = AF_UNSPEC;
	m_hints.ai_socktype = SOCK_STREAM;
	m_hints.ai_flags = AI_PASSIVE;

	m_status = getaddrinfo(NULL, PORT, &m_hints, &m_res);
	if(m_status != 0){
		std::cout << "Error::STREAM_SERVER::GET_ADDR_INFO()\n";
		success = -1;
	}

	//socket and binding, yay
	for(m_p = m_res; m_p != NULL; m_p = m_p->ai_next){
		m_fd = socket(m_p->ai_family, m_p->ai_socktype, m_p->ai_protocol);
		if(m_fd == -1){
			std::cout << "STREAM_SERVER::SOCKET()\n";
			continue;
		}

		m_status = bind(m_fd, m_p->ai_addr, m_p->ai_addrlen);
		if(m_status == -1){
			std::cout << "STREAM_SERVER::BIND()\n";
			continue;
		}
		break;
	}
	
	if(m_p == NULL){
		std::cout << "ERROR::STREAM_SERVER::FAILED_TO_BIND()\n";
		success = -2;
	}
	
	//listen kid
	m_status = listen(m_fd, BACKLOG);
	if(m_status == -1){
		std::cout << "ERROR::STREAM_SERVER::LISTEN()\n";
		success = -3;
	}

}

int Stream_ser::Send(struct connection conn, void* data, int length){
	m_status = send(conn.fd, data, length, 0);
	if(m_status != length){
		std::cout << "WARNING::STREAM_SERVER::SEND()\n";
	}
	return m_status;
};

struct connection Stream_ser::Accept(){
	struct connection conn;
	conn.fd = accept(m_fd, (struct sockaddr*)&conn.host_addr, &conn.addr_size);
	if(conn.fd == -1){
		std::cout << "ERROR::STREAM_SERVER::ACCEPT()\n";
	}


	return conn;
}

int Stream_ser::Recv(connection conn, void *buffer, int MAX_BUFFSIZE){
	m_status = recv(conn.fd, buffer, MAX_BUFFSIZE, 0);
	if(m_status == -1){
		std::cout << "ERROR::STREAM_SERVER::RECV()\n";
	}
	return m_status;
}



