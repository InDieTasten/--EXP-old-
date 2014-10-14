#ifndef _Logger_hpp_
#define _Logger_hpp_

#include "MemoryBank/DataBank.hpp"
#include <iostream>
#include <time.h>
#include <string>
#include <fstream>
#include <stdio.h>
#include <sstream>

extern DataBank* dLink;

namespace LOG
{
void console(std::string msg);
void file(std::string msg);
void safe(std::string msg);
}

#endif
