#ifndef _util_hpp_
#define _util_hpp_

#include <iostream>
#include <sstream>
#include <list>
#include <Windows.h>

namespace util
{
std::string toString(int);
std::string toString(bool);
std::string toString(float);
std::string toString(double);
std::string toString(char*);
std::string toString(std::list<std::string>);
char getCharAt(std::string, int);

int toInt(std::string);
bool toBool(std::string);
float toFloat(std::string);
double toDouble(std::string);

std::list<std::string> getFolderContent(std::string);
}

#endif
