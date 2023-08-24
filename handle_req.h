#ifndef PARASE_H
#define PARASE_H

#include <string>
#include <vector>

struct response{
	//status line
	std::string http_ver = "HTTP/1.1";
	std::string status = "200";
	std::string phrase = "OK";

	//HTTP headers
	std::string content_type = "text/html; charset=UTF-8";
	int content_lenght = 0;
	
	//Body
	std::vector<char> data;
};


void parase(std::string& request, struct response& resp);
void get_response(std::vector<char>& response, struct response& resp);

#endif

