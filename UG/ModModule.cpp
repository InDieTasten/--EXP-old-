#include "ModModule.hpp"
//CONSTRUCTORS

//DESTRUCTORS

//METHODS
void ModModule::Run()
{
    std::list<Script> *scripts;
    scripts = datalink->GetScripts();

    for(std::list<Script>::iterator it = scripts->begin(); it != scripts->end(); it++)
    {
        luaL_openlibs(it->state);

        lua_pushstring(it->state, it->path.c_str());
        lua_setglobal(it->state, "_SCRIPT");

        lua_register(it->state, "print", ModModule::lPrint);
        lua_register(it->state, "pushEvent", ModModule::lPushTask);
        lua_register(it->state, "pushTask", ModModule::lPushTask);

        luaL_dofile(it->state, it->path.c_str());

        lua_getglobal(it->state, "onLoad");

        lua_call(it->state, 0, 0);
    }

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
        for(std::list< std::list<std::string> >::iterator event = eventBuffer.begin(); event != eventBuffer.end(); event++)
        {
            for(std::list<Script>::iterator script = scripts->begin(); script != scripts->end(); script++)
            {
                lua_getglobal(script->state, "onSoftEvent");
                for(std::list<std::string>::iterator parameter = event->begin(); parameter != event->end(); parameter++)
                {
                    lua_pushstring(script->state, parameter->c_str());
                }
                lua_call(script->state, event->size(), 0);
            }
        }
        eventBuffer.clear();

        GMutex.unlock();
    }
    for(std::list<Script>::iterator it = scripts->begin(); it != scripts->end(); it++)
    {
        lua_getglobal(it->state, "onUnload");
        lua_call(it->state, 0, 0);
        lua_close(it->state);
    }
    logger.log(4, "Thread stopped");
}
void ModModule::SetDataLink(DataBank* _datalink, GUIManager* _gmanager, int *_level)
{
    logger.init(_level, "PluginEngine");
    logger.log(4, "Logger initialized");
    datalink = _datalink;
    logger.log(8, "Databank connected via datalink");
    ModModule::gManager = _gmanager;
}
int ModModule::lPrint(lua_State *L)
{
    //number of arguments
    int n = lua_gettop(L);

    std::string message = "";

    for(int i = 1; i <= n; i++)
    {
        message.append(lua_tostring(L,i));
    }
    Logger lo;
    int x = 999;
    lo.init(&x,"Plugin");
    lo.log(0,message);
    return 0;
}
int ModModule::lPushEvent(lua_State *L) // api.print("mein text hat ", 5, "W�rter")
{
    //number of arguments
    int n = lua_gettop(L);

    std::list<std::string> event;

    for(int i = 1; i <= n; i++)
    {
        event.push_back(lua_tostring(L,i));
    }
    eventBuffer.push_back(event);
    return 0;
}
int ModModule::lPushTask(lua_State *L) // api.print("mein text hat ", 5, "W�rter")
{
    //number of arguments
    int n = lua_gettop(L);

    std::list<std::string> task;

    for(int i = 1; i <= n; i++)
    {
        task.push_back(lua_tostring(L,i));
    }
    taskBuffer.push_back(task);
    return 0;
}

int ModModule::lAddMenu(lua_State *L) // api.addMenu(_id)
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
