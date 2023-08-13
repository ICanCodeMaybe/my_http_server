SOURCE='main.cpp child.cpp include/stream_server.cpp'
gcc -std=c++11 -Wall -Wextra -lstdc++ -I include/ -o out/server $SOURCE
