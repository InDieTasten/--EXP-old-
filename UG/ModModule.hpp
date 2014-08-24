#ifndef _ModModule_hpp_
#define _ModModule_hpp_

#include <list>
#include "DataBank.hpp"
#include "GUIManager.hpp"
#include "Logger.hpp"
#include "Script.hpp"
#include <sstream>
extern float ModThread;
extern sf::Mutex GMutex;


extern std::list< std::list<std::string> > eventBuffer;
extern std::list< std::list<std::string> > taskBuffer;


class ModModule
{
    //MEMBERS
private:
    Loader loader;
    DataBank* datalink;
    GUIManager* gManager;
public:
    //static std::list< std::list<std::string> > eventBuffer;
    //static std::list< std::list<std::string> > taskBuffer;

    //CONSTRUCTORS

    //DESTRUCTORS

    //METHODS
private:
    //void log(std::string);
    static int lPrint(lua_State *L); //message
    static int lPushEvent(lua_State *L);
    static int lPushTask(lua_State *L);

    int lAddMenu(lua_State *L); //menu_id
    int lEditMenuPosition(lua_State *L); //menu_id
    int lEditMenuSize(lua_State *L); //menu_id
    int lEnableMenu(lua_State *L); //menu_id
    int lDisableMenu(lua_State *L); //menu_id
    int lShowMenu(lua_State *L); //menu_id
    int lHideMenu(lua_State *L); //menu_id

    int lAddGuiElement(lua_State *L); //menu_id, elem_id
public:
    void Run();
    void Stop();
    void SetDataLink(DataBank* _datalink, GUIManager* _gmanager, int *_level);
};

#endif
