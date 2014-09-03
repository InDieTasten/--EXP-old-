#include "Logger.hpp"
//CONSTRUCTORS
//DESTRUCTORS
//METHODS
void log(std::string name, std::string msg)
{
    time_t rawtime;
    struct tm * timeinfo;

    char T[10]; //HH,mm,ss
    char D[10]; //Tag

    time (&rawtime);
    timeinfo = localtime (&rawtime);

    strftime (T,20,"%H:%M:%S",timeinfo);
    strftime (D,20,"%j",timeinfo);


    std::cout << D << "|" << T << "[" << name << "] " << msg << std::endl;
}
