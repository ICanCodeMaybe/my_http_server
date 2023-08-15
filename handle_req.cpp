#include "handle_req.h"

#include "log.h"

#include <cstdio>
#include <cstring>
#include <iostream>
#include <istream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

std::vector<std::string> lines;
std::vector<std::vector<std::string>> request_vec;

std::string method;
std::string path;
std::string version;

char* req_f_cont;
char* req_finnal;

char* load_file(std::string path_to_file, int* size);



struct response meth_get();
struct response meth_post();
struct response meth_not_impl();

struct response parase(char* request){
	if(req_f_cont != nullptr){
		delete req_f_cont;
	}
	if(req_finnal != nullptr){
		delete req_finnal;
	}
	if(!lines.empty()){
		lines.clear();
	}
	if(!request_vec.empty()){
		request_vec.clear();
	}

	std::string text = request;
	delete request;
	//spliting into lines
	std::istringstream line_stream(text);
	std::string line;

	while(std::getline(line_stream, line)){
		lines.push_back(line);
	}

	//getting seperate words
	for(const std::string& line : lines){
		std::string word;
		std::istringstream word_stream(line);
		std::vector<std::string> words;

		while(word_stream >> word){
			words.push_back(word);
		}

		request_vec.push_back(words);
	}

	//getting method, path, version
	method = request_vec[0][0];
	path = request_vec[0][1];
	version = request_vec[0][2];

	CON_LOG(method << ", " << path << ", " << version);

	struct response resp;
	//depends on the method
	if(method == "GET"){
		resp = meth_get();
	}
	else if(method == "POST"){
		resp = meth_post();
	}
	else{
		resp = meth_not_impl();
	}

	return resp;
}

char* get_response(struct response resp, int* size){
	std::stringstream ss;

	//status line
	ss << resp.http_ver << " " << resp.status << " " << resp.phrase << "\r\n";

	//headers
	ss << "Content-Type:" << resp.content_type << "\r\n";
	ss << "Content-Length: " << resp.content_lenght << "\r\n";

	//body
	ss << "\r\n" << resp.data << "\r\n";
	std::string finnal = ss.str();
	req_finnal = new char[finnal.size() + 1];
	strcpy(req_finnal, finnal.c_str());

	*size = finnal.size() + 1;

	return req_finnal;
}

struct response meth_get(){
	int data_size;
	struct response mine_resp;
	char* data = load_file(path, &data_size);
	mine_resp.content_lenght = data_size;
	mine_resp.data = data;

	return mine_resp;
}

struct response meth_post(){
//TODO
}

struct response meth_not_impl(){
//TODO
}

char* load_file(std::string path, int* size){
//this is probably super unnecesary, will finish it when it is needed
/*	char extension[8];
	int i = 0;
	bool helper = false;
	while(path[i]){
		if(path[i] == '.'){
			helper = i;
		}

		if(helper != 0)
			
		i++;
	}
*/
	//this is just test, will make it more general
	if(path == "/")
		path = "source/test.html";
	else
		path = "source" + path;
	
	std::ifstream ifs(path);
	std::stringstream ss;
	std::string line;
	
	if(!ifs.is_open()){
		CON_ERROR_LOG("ERROR: OPENING OF FILE");
	}

	while(getline(ifs, line)){
		ss << line << "\r\n";
	}
	ifs.close();

	std::string content = ss.str();	
	*size = content.length() + 1;
	req_f_cont = new char[*size];
	strcpy(req_f_cont, content.c_str());

	return req_f_cont;
}
