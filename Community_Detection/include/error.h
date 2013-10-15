#ifndef ERROR_H_INCLUDED
#define ERROR_H_INCLUDED

#define ERR_SUCCESS 0
#define ERR_OPENING_FILE 1
#define ERR_READING_FILE 2
#define ERR_WRITING_FILE 3
#define ERR_CLOSING_FILE 4
#define ERR_MEMORY_ALLOC 5
#define ERR_GENERIC_ERROR 10

#include<iostream>
#include<cstdio>

inline void handle_error(const char* msg, int code = ERR_GENERIC_ERROR) 
{ 
    perror(msg); 
    std::cerr<<"error status code: "<<code<<std::endl;
    exit(code); 
}

#endif // ERROR_H_INCLUDED
