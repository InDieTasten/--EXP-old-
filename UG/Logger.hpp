#ifndef _Logger_hpp_
#define _Logger_hpp_

#include <iostream>
#include <time.h>
#include <string>
#include <fstream>
#include <stdio.h>
#include <sstream>

class Logger
{
private:
    time_t rawtime;
    struct tm * timeinfo;

public:
    std::string T; //Stunden
    std::string D; //Tag


    void log(std::string name,std::string msg);
};
#endif
