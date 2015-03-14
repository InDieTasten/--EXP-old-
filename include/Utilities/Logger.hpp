#ifndef _Logger_hpp_
#define _Logger_hpp_

#include <iostream>
#include <time.h>
#include <string>
#include <fstream>
#include <stdio.h>
#include <sstream>
#include <thread>
#include <mutex>

namespace ug
{
	std::mutex loggermtx;
	void log(std::string msg);
}

#endif
