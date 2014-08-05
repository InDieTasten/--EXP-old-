
#ifndef _Loader_cpp_
#define _Loader_cpp_

#include <list>
#include <iostream>
#include <conio.h>
#include "dirent.h"
#include <string>
#include <vector>

class dir
{
	//MEMBER
protected:
	struct dirent* curDirEntry;
	DIR *directory;
public:
	//CONSTRUCTOR
	dir(const char *dir);

	//DESTRUCTOR
	~dir();

	//METHODS
	std::vector<std::string> getEntries();
	virtual bool selectDirEntry();
};

class Loader
{
	//MEMBER
private:
public:
	//CONTRUCTOR

	//DESTRUCTOR

	//METHODS
	std::list<std::string> getFolderContent(std::string _path);
};

#endif
