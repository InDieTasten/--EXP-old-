#include "Logger.hpp"
//CONSTRUCTORS
//DESTRUCTORS
//METHODS
void Logger::init(int* _level, std::string _source)
{
    Level = _level;
    while(_source.length() < 12)
    {
        _source = _source+" ";
    }
    Source = _source;
}
void Logger::log(int detail,std::string msg)
{
    if(detail <= *Level)
    {
        std::ostringstream sstream;
        if(detail < 10)
            sstream <<" [0"<<detail<<" "<<Source<<"] "<< msg <<std::endl;
        else
            sstream <<" ["<<detail<<" "<<Source<<"] "<< msg <<std::endl;
        std::string result= sstream.str();

        //writing to console
        std::cout << result;
        //writing to file
        //missing
    }
}
