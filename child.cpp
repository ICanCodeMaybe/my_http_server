// the child's "main"
#include "child.h"

#include "include/stream_server.h"
#include "log.h"

#include <cstring>
#include <iostream>
#include <string.h>

#include "handle_req.h"

Stream_ser* ch_server;
struct connection* ch_conn;
struct response ch_resp;

int MAX_BUFFSIZE = 1024;
char* buff;
char* resp_buff; 

void get_request();

void child(Stream_ser* server, struct connection conn){
	buff = new char[MAX_BUFFSIZE];

	ch_server = server;
	ch_conn = new connection;
	*ch_conn = conn;

	CON_LOG("HELLO");

	while(1){
		if(buff != nullptr){
			memset(buff, 0, MAX_BUFFSIZE - 1);
		}
	
		get_request();
		CON_LOG(buff);

		ch_resp = parase(buff);
		int resp_size;
		CON_WARN_LOG("HEE");
		resp_buff = get_response(ch_resp, &resp_size);
		CON_LOG(resp_buff);

		int sent = ch_server->Send(*ch_conn, resp_buff, resp_size);
		CON_LOG("Bytes sent: " << sent);

	}

	delete ch_conn;
	exit(0);
}

void get_request(){
	int bytes_recv = ch_server->Recv(*ch_conn, buff, MAX_BUFFSIZE);
	buff[bytes_recv] = '\0';

}
