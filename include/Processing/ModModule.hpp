#ifndef _ModModule_hpp_
#define _ModModule_hpp_

#include <list>
#include "MemoryBank/DataBank.hpp"
#include "GUI/GUIManager.hpp"
#include "Utilities/Logger.hpp"
#include "MemoryBank/Entities/Script.hpp"
#include <sstream>
extern float mLimit;
extern DataBank* dLink;
extern GUIManager* guiLink;
extern sf::Mutex GMutex;


extern std::list< std::list<std::string> > eventBuffer;
extern std::list< std::list<std::string> > taskBuffer;

struct ASync
{
    sf::Clock time;
    int target;
    std::list<std::string> task;
};

class ModModule
{
    //MEMBERS
private:
    std::list<ASync> waitingTasks;
public:
    //CONSTRUCTORS

    //DESTRUCTORS

    //METHODS
private:
    static int lGetLevel(lua_State *L);
    static int lGetSystems(lua_State *L);
    static int lPrint(lua_State *L); //message
    static int lPushEvent(lua_State *L);
    static int lPushTask(lua_State *L);

    void processTask(std::list<std::string> _args);

public:
    void Run();
    void Stop();
    void SetDataLink(DataBank* _datalink, GUIManager* _gmanager, int *_level);
    void handleEvent(sf::Event* _event);
};

#endif
