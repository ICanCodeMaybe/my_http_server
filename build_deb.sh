SOURCE='main.cpp child.cpp handle_req.cpp include/stream_server.cpp'
gcc -g -std=c++11 -Wall -Wextra -lstdc++ -I include/ -o out/server_debug $SOURCE
