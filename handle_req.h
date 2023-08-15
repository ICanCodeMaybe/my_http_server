#ifndef PARASE_H
#define PARASE_H

struct response{
	//status line
	const char* http_ver = "HTTP/1.1";
	const char* status = "200";
	const char* phrase = "OK";

	//HTTP headers
	const char* content_type = "text/html; charset=UTF-8";
	int content_lenght = 0;
	
	//Body
	char* data = nullptr;
};

struct response parase(char* request);
char* get_response(struct response resp, int* size);

#endif

