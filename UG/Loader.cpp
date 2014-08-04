#include "Loader.hpp"

//CONSTRUCTOR
dir::dir(const char *dir)
{
    directory = opendir(dir);
}
//DESTRUCTOR
dir::~dir()
{
    closedir(directory);
}
//METHODS
std::vector<std::string> dir::getEntries()
{
    struct dirent *dirEntry;
    std::vector<std::string> retVal;
    if(directory == 0)
    {
        return retVal;
    }
    while((dirEntry=readdir(directory)))
    {
        curDirEntry = dirEntry;
        if(selectDirEntry())
        {
            std::string str(dirEntry->d_name);
            retVal.push_back(str);
        }
    }
    return retVal;
}
bool dir::selectDirEntry()
{
    return true;
}
//CONSTRUCTOR
//DESTRUCTOR
//METHODS
std::list<std::string> Loader::getFolderContent(std::string _path)
{
    std::list<std::string> content;
    dir folder(_path.c_str());

    std::vector<std::string> ret = folder.getEntries();
    for(unsigned int i=0; i < ret.size(); i++)
    {
        std::string temp = ret[i];
        if (temp.find(".")) // warning!!! not tested
        {
            content.push_back(ret[i]);
        }
    }
    return content;
}
