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

class ModModule
{
    //MEMBERS
private:
    Logger logger;
    Loader loader;
    DataBank* datalink;
    GUIManager* gManager;
public:
    std::list< std::list<std::string> > eventBuffer;

    //CONSTRUCTORS

    //DESTRUCTORS

    //METHODS
private:
    void log(std::string);
    static int lPrint(lua_State *L); //message


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
