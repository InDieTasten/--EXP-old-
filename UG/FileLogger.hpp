#ifndef _FileLogger_hpp_
#define _FileLogger_hpp_
#include <SFML\Graphics.hpp>

#include <iostream>
#include <fstream>
#include <time.h>
#include <stdio.h>
#include <direct.h>
#include <stdlib.h>

extern sf::Mutex GMutex;
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

