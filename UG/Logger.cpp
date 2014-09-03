#include "Logger.hpp"
//CONSTRUCTORS
//DESTRUCTORS
//METHODS
void log(std::string name, std::string msg)
{
    time (&rawtime);
    timeinfo = localtime (&rawtime);

    strftime (T,20,"%T",timeinfo);
    strftime (D,20,"%j",timeinfo);


    std::cout << T << "|" << D << "[" << name << "] " << msg << std::endl;
}
