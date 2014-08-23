#ifndef _Logger_cpp_
#define _Logger_cpp_

#include <iostream>
#include <time.h>
#include <string>
#include <fstream>
#include <stdio.h>
#include <sstream>

class Logger
{
    //MEMBERS
private:
public:
    int* Level;
    std::string Source;

    //CONSTRUCTORS

    //DESTRUCTORS

    //METHODS
    void init(int* _level, std::string _source);
    void log(int detail,std::string msg);
};

#endif
