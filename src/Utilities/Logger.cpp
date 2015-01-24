#include <Utilities/Logger.hpp>
#include <Utilities/FileLogger.hpp>
#include <sstream>
//CONSTRUCTORS
//DESTRUCTORS
//METHODS
FileLogger logger;


void LOG::console(std::string msg)
{
    time_t rawtime;
    struct tm * timeinfo;

    char T[14];

    time (&rawtime);
    timeinfo = localtime (&rawtime);

    strftime (T,14,"%j|%H:%M:%S",timeinfo);


    std::cout << "&f" <<  T << msg << std::endl;
    std::stringstream ss;
    ss << "&f" << T << msg;
    logger.log(ss.str());
}
void LOG::file(std::string msg)
{
    time_t rawtime;
    struct tm * timeinfo;

    char T[14];

    time (&rawtime);
    timeinfo = localtime (&rawtime);

    strftime (T,14,"%j|%H:%M:%S",timeinfo);

    std::stringstream ss;
    ss << "&f" << T << msg;
    logger.log(ss.str());
    if(true) // SAFEMODE
        std::cout << "&f" <<  T << msg << std::endl;
}
void LOG::safe(std::string msg)
{
    if(!true) //SAFEMODE
        return;
    time_t rawtime;
    struct tm * timeinfo;

    char T[14];

    time (&rawtime);
    timeinfo = localtime (&rawtime);

    strftime (T,14,"%j|%H:%M:%S",timeinfo);

    std::stringstream ss;
    ss << "&f" << T << msg;
    logger.log(ss.str());
}
