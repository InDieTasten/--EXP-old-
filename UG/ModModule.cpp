#include "ModModule.hpp"
//CONSTRUCTORS

//DESTRUCTORS

//METHODS
void ModModule::Run()
{
    log(std::string("Mod-Module"), std::string("Thread started"));
    std::list<Script> *scripts;
    scripts = dLink->GetScripts();

    for(std::list<Script>::iterator it = scripts->begin(); it != scripts->end(); it++)
    {
        luaL_openlibs(it->state);

        lua_pushstring(it->state, it->path.c_str());
        lua_setglobal(it->state, "_SCRIPT");

        lua_register(it->state, "print", ModModule::lPrint);
        lua_register(it->state, "pushEvent", ModModule::lPushEvent);
        lua_register(it->state, "pushTask", ModModule::lPushTask);

        luaL_dofile(it->state, it->path.c_str());

        lua_getglobal(it->state, "onLoad");

        lua_call(it->state, 0, 0);
    }

    sf::Clock limiter;
    limiter.restart();

    std::list< std::list<std::string> > events;
    while(dLink->runModules)
    {
        if(limiter.getElapsedTime().asSeconds() < 1.0/mLimit)
        {
            sf::sleep(sf::seconds(1.0/mLimit - limiter.getElapsedTime().asSeconds()));
        }
        limiter.restart();
        GMutex.lock();
        events = eventBuffer;
        eventBuffer.clear();
        for(std::list< std::list<std::string> >::iterator event = events.begin(); event != events.end(); event++)
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
        for(std::list< std::list<std::string> >::iterator task = taskBuffer.begin(); task != taskBuffer.end(); task++)
        {
            for(std::list<Script>::iterator script = scripts->begin(); script != scripts->end(); script++)
            {
                lua_getglobal(script->state, "onTask");
                for(std::list<std::string>::iterator parameter = task->begin(); parameter != task->end(); parameter++)
                {
                    lua_pushstring(script->state, parameter->c_str());
                }
                lua_call(script->state, task->size(), 0);
            }
        }
        taskBuffer.clear();

        GMutex.unlock();
    }
    for(std::list<Script>::iterator it = scripts->begin(); it != scripts->end(); it++)
    {
        lua_getglobal(it->state, "onUnload");
        lua_call(it->state, 0, 0);
        lua_close(it->state);
    }
    log(std::string("Mod-Module"), std::string("Thread stopped"));
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
    int x = 999;
    log("Plugin    ",message);
    return 0;
}
int ModModule::lPushEvent(lua_State *L) // api.print("mein text hat ", 5, "Wörter")
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
int ModModule::lPushTask(lua_State *L) // api.print("mein text hat ", 5, "Wörter")
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

    guiLink->AddMenu(id);
    lua_pushboolean(L,0);
    return 1;
}
