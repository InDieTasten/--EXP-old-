#ifndef _Logger_hpp_
#define _Logger_hpp_

#include <iostream>
#include <time.h>
#include <string>
#include <fstream>
#include <stdio.h>
#include <sstream>


namespace LOG
{
	void console(std::string msg);
	void file(std::string msg);
	void safe(std::string msg);
}

#endif
