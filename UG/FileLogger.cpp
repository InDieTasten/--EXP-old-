
#include "FileLogger.hpp"
/* FileLogger:
    Logs everything to the Filesystem*/

FileLogger::FileLogger()
{

    logfile.open("untiteld.ulog", std::ios::out | std::ios::trunc );
    logfile << "<!DOCTYPE html><head><meta charset=\"UTF-8\"><title>Document</title></head><body>";


}


FileLogger::~FileLogger()
{
    logfile << "</body></html>";
    logfile.close();
}
std::string FileLogger::breakline(){
    return "<br>";
}

void FileLogger::log(std::string temp){
    logfile << temp << breakline();
}

void FileLogger::log(std::string temp, std::string color){
    logfile << "<span color=\"" + color + "\">" << temp << "</span>" << breakline();
}

void FileLogger::clean(){

}
