#ifndef _ModModule_hpp_
#define _ModModule_hpp_

#include <list>
#include "DataBank.hpp"
#include "GUIManager.hpp"
#include "Logger.hpp"
#include "Script.hpp"
#include <sstream>
extern float mLimit;
extern DataBank* dLink;
extern GUIManager* guiLink;
extern sf::Mutex GMutex;


extern std::list< std::list<std::string> > eventBuffer;
extern std::list< std::list<std::string> > taskBuffer;


class ModModule
{
    //MEMBERS
private:
    Loader loader;
public:
    //CONSTRUCTORS

    //DESTRUCTORS

    //METHODS
private:
    //void log(std::string);
    static int lPrint(lua_State *L); //message
    static int lPushEvent(lua_State *L);
    static int lPushTask(lua_State *L);

    void processTask(std::list<std::string> _args);

public:
    void Run();
    void Stop();
    void SetDataLink(DataBank* _datalink, GUIManager* _gmanager, int *_level);
};

#endif
