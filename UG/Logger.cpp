#include "Logger.hpp"
#include "FileLogger.hpp"
#include <sstream>
//CONSTRUCTORS
//DESTRUCTORS
//METHODS
FileLogger logger;

void log(std::string name, std::string msg)
{
    time_t rawtime;
    struct tm * timeinfo;

    char T[14];

    time (&rawtime);
    timeinfo = localtime (&rawtime);

    strftime (T,14,"%j|%H:%M:%S",timeinfo);


    std::cout <<  T << "[" << name << "]" << msg << std::endl;
    std::stringstream ss;
    ss << T << "[" << name << "]" << msg;
    logger.log(ss.str());
}
