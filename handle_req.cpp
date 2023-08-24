#include "handle_req.h"

#include "log.h"

#include <algorithm>
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

std::string req_f_cont;
std::string req_finnal;

void load_file(std::string path_to_file, struct response &resp);



void meth_get(struct response& resp);
void meth_post(struct response& resp);
void meth_not_impl(struct response& resp);

void parase(std::string& request, struct response& resp){

	req_f_cont.clear();
	
	req_finnal.clear();
		
	lines.clear();
	
	request_vec.clear();

	//spliting into lines
	std::istringstream line_stream(request);
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

	//depends on the method
	if(method == "GET"){
		meth_get(resp);
	}
	else if(method == "POST"){
		meth_post(resp);
	}
	else{
		meth_not_impl(resp);
	}

}

void get_response(std::vector<char>& response, struct response& resp){
	std::stringstream ss;

	//status line
	ss << resp.http_ver << " " << resp.status << " " << resp.phrase << "\r\n";

	//headers
	ss << "Content-Type:" << resp.content_type << "\r\n";
	ss << "Content-Length: " << resp.content_lenght << "\r\n\r\n";

	
	std::string resp_head = ss.str();

	response.clear();
	response.resize(resp_head.size(), 0); // head size + body size
	std::copy(resp_head.begin(), resp_head.end(), response.begin());
	
	//body	
	response.insert(response.end(), resp.data.begin(), resp.data.end());
	response.push_back('\r');
	response.push_back('\n');

}

void meth_get(struct response& mine_resp){
	load_file(path, mine_resp);
}

void meth_post(struct response& mine_resp){
	//TODO
	mine_resp.status = "404";
}

void meth_not_impl(struct response& mine_resp){
	//TODO
	mine_resp.status = "404";
}

void load_file(std::string path, struct response &resp){
//this is probably super unnecesary, will finish it when it is needed
	std::string extension;
	int i = 0;
	int helper = 0;
	while(path[i]!='\0'){
		if(path[i] == '.'){
			helper = i;
		}

		if(helper != 0)
		{
			extension += path[i];	
		}	
		i++;
	}

	if(extension ==".html"){
		resp.content_type = " text/html; charset=UTF-8";
	}
	else if(extension == ".css"){
		resp.content_type = " text/css";
	}
	else if(extension == ".jpg" || extension == ".jpeg"){
		resp.content_type = " image/jpeg";
	}

	//this is just test, will make it more general
	if(path == "/")
		path = "source/test.html";
	else
		path = "source" + path;
	
	std::ifstream ifs(path, std::ios::binary);
	
	if(!ifs.is_open()){
		CON_ERROR_LOG("ERROR: OPENING OF FILE");
	}

	char byte;
	resp.data.clear();
	while(ifs.read(reinterpret_cast<char*>(&byte), sizeof(byte))){
		resp.data.push_back(byte);
	}
	ifs.close();

	resp.content_lenght = resp.data.size();
}
