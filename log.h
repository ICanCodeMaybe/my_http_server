#ifndef LOG_H
#define LOG_H

#define CON_LOG(msg) std::cout << "\x1b[1m"<< msg << "\x1b[0m\n";
#define CON_WARN_LOG(msg) std::cout << "\x1b[1;33m" << msg << "\x1b[0m\n";
#define CON_ERROR_LOG(msg) std::cout << "\x1b[1;31m" << msg << "\x1b[0m\n";


#endif

