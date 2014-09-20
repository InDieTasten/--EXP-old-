
#include "FileLogger.hpp"
/* FileLogger:
    Logs everything to the Filesystem*/

FileLogger::FileLogger()
{
    /*
    time_t rawtime;
    struct tm * timeinfo;

    char T[14];

    time (&rawtime);
    timeinfo = localtime (&rawtime);

    strftime (T,14,"%j|%H:%M:%S",timeinfo); */

    //std::string t = "logs/";
       // t += T;
    //t += "untiteld.ulog";

    logfile.open("logs/untiteld.ulog", std::ios::out | std::ios::trunc );



}


FileLogger::~FileLogger()
{

    logfile.close();
}
std::string FileLogger::breakline(){
    return "<br>";
}

void FileLogger::log(std::string temp){
    GMutex.lock();

    logfile << temp << "\n";
    GMutex.unlock();
}

void FileLogger::log(std::string temp, std::string color){
    logfile << "<span color=\"" + color + "\">" << temp << "</span>" << breakline();
}

void FileLogger::clean(){

}
