#ifndef _FileLogger_hpp_
#define _FileLogger_hpp_


#include <iostream>
#include <fstream>

class FileLogger
{
private:
    std::ofstream logfile;
public:
	FileLogger();
	~FileLogger();

	std::string breakline();
	void log(std::string);
	void log(std::string, std::string);
	void clean();

};

#endif

