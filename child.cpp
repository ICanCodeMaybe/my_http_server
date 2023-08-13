// the child's "main"
#include "child.h"

#include "include/stream_server.h"
#include "log.h"

#include <cstring>
#include <iostream>
#include <string.h>

Stream_ser* ch_server;
struct connection* ch_conn;

void get_request();

void child(Stream_ser* server, struct connection conn){
	ch_server = server;
	ch_conn = new connection;
	*ch_conn = conn;

	CON_LOG("HELLO");
	get_request();

	delete ch_conn;
	exit(0);
}

void get_request(){
	int MAX_BUFFSIZE = 1024;
	char buff[MAX_BUFFSIZE];

	int bytes_recv = ch_server->Recv(*ch_conn, buff, MAX_BUFFSIZE);
	buff[bytes_recv] = '\0';

	CON_LOG("HERE");

	std::cout << buff << "\n";
}
