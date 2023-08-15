#include <csignal>
#include <iostream>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "child.h"
#include "include/stream_server.h"

#include "log.h"

pid_t child_pid;
bool should_close = false;

Stream_ser* server;
struct connection conn;

void handle_signals(int signum);

int main(int argc, char** argv){
	std::cout << "Hello there!\n";

	struct sigaction sa;
	sa.sa_handler = handle_signals;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART | SA_NOMASK;

	sigaction(SIGCHLD, &sa, NULL);
	sigaction(SIGINT, &sa, NULL);

	server = new Stream_ser("8080", 10);
	if(server->success != 0){
		CON_ERROR_LOG("SERVER WAS NOT INITIALIZED!");
		return -1;
	}
	
	CON_LOG("SERVER WAS INITIALIZED");

	//main listening loop
	while(!should_close){
		conn = server->Accept();
		if(conn.fd == -1){
			CON_ERROR_LOG("SERVER->ACCEPT() FAILED");
		}
		
		child_pid = fork();
		
		if(child_pid == 0){
			CON_LOG("CHILD PROCESS WAS FORKED");
			child(server, conn);
		}

	}

	delete server;
	return 0;
}

void handle_signals(int signum){
	if(signum == SIGCHLD){
		pid_t pid;
		int status;
	
		while((pid = waitpid(-1, &status, WNOHANG)) > 0){
			if(WIFEXITED(status)){
				CON_LOG("CHILD PROCESS, EXITED");
			}
		}
	}

	if(signum == SIGINT){
		CON_LOG("\nGood bye! :)");
		exit(0);
	}
}


