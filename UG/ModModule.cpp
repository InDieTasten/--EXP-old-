#include "ModModule.hpp"
//CONSTRUCTORS

//DESTRUCTORS

//METHODS
void ModModule::Run()
{
    sf::Clock limiter;
    limiter.restart();
    while(datalink->runModules)
    {
        if(limiter.getElapsedTime().asSeconds() < 1.0/ModThread)
        {
            sf::sleep(sf::seconds(1.0/ModThread - limiter.getElapsedTime().asSeconds()));
        }
        limiter.restart();
        GMutex.lock();
        GMutex.unlock();
    }
}
void ModModule::SetDataLink(DataBank* _datalink, GUIManager* _gmanager, int *_level)
{
    logger.init(_level, "PluginEngine");
    logger.log(4, "Logger initialized");
    datalink = _datalink;
    logger.log(8, "Databank connected via datalink");
    gManager = _gmanager;
}

int ModModule::lPrint(lua_State *L)
{
    //number of arguments
    int n = lua_gettop(L);

    std::string message = "";

    for(int i = 1; i <= n; i++)
    {
        message.append(lua_tostring(L,n));
    }
    std::cout << message << std::endl;
    return 0;
}

int ModModule::lAddMenu(lua_State *L)
{
    //number of arguments
    int n = lua_gettop(L);
    if(n != 1)
    {
        lua_pushboolean(L,1);
        return 1;
    }

    //get id as string
    std::string id = lua_tostring(L,1);

    gManager->AddMenu(id);
    lua_pushboolean(L,0);
    return 1;
}
