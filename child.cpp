// the child's "main"
#include "child.h"

#include "include/stream_server.h"
#include "log.h"

#include <cstring>
#include <iostream>
#include <ostream>
#include <string.h>
#include <vector>

#include "handle_req.h"

Stream_ser* ch_server;
struct connection* ch_conn;
struct response ch_resp;

std::string buff;

void get_request();

void child(Stream_ser* server, struct connection conn){
	ch_server = server;
	ch_conn = new connection;
	*ch_conn = conn;

	CON_LOG("HELLO");

	while(1){
		//clearing the buffer
		buff.clear();
		std::vector<char> resp_buff;

		get_request();
		CON_LOG("REQUEST - ");
		for(char ch : buff){
			std::cout << ch;
		}
		//parese the request
		parase(buff, ch_resp);
		
		//generating the response
		get_response(resp_buff, ch_resp);
		
		for(char ch : resp_buff){
			std::cout << ch;
		}
		
		int resp_size = resp_buff.size();

		char* resp_send = new char[resp_size];
		std::copy(resp_buff.begin(), resp_buff.end(), resp_send);
		int sent = ch_server->Send(*ch_conn, resp_send, resp_size);
		delete[] resp_send;

		CON_LOG("Bytes sent: " << sent << "Response size: " << resp_size);

	}

	delete ch_conn;
	exit(0);
}

void get_request(){
	int MAX_BUF_SIZE = 1024;
	char buffer[MAX_BUF_SIZE];
	
	int bytes_recv = ch_server->Recv(*ch_conn, buffer, MAX_BUF_SIZE);
	buffer[bytes_recv] = '\0';

	int i = 0;
	while(i <= bytes_recv){
		buff.push_back(buffer[i]);
		i++;
	}

}

