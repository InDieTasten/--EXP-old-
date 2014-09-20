
#include "FileLogger.hpp"
/* FileLogger:
    Logs everything to the Filesystem*/

FileLogger::FileLogger()
{

    logfile.open("untiteld.ulog", std::ios::out | std::ios::trunc );



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
