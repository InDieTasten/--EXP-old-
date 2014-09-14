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

        lua_getglobal(it->state, "onHardLoad");

        lua_call(it->state, 0, 0);
    }

    sf::Clock limiter;
    limiter.restart();

    std::list< std::list<std::string> > events;
    std::list< std::list<std::string> > tasks;
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
                lua_getglobal(script->state, "onHardEvent");
                for(std::list<std::string>::iterator parameter = event->begin(); parameter != event->end(); parameter++)
                {
                    lua_pushstring(script->state, parameter->c_str());
                }
                lua_call(script->state, event->size(), 0);
            }
        }
        tasks = taskBuffer;
        taskBuffer.clear();
        for(std::list< std::list<std::string> >::iterator task = tasks.begin(); task != tasks.end(); task++)
        {
            processTask(*task);
            for(std::list<Script>::iterator script = scripts->begin(); script != scripts->end(); script++)
            {
                lua_getglobal(script->state, "onHardTask");
                for(std::list<std::string>::iterator parameter = task->begin(); parameter != task->end(); parameter++)
                {
                    lua_pushstring(script->state, parameter->c_str());
                }
                lua_call(script->state, task->size(), 0);
            }
        }

        GMutex.unlock();
    }
    for(std::list<Script>::iterator it = scripts->begin(); it != scripts->end(); it++)
    {
        lua_getglobal(it->state, "onHardUnload");
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
    //eventBuffer.push_back(event);
    dLink->pushEvent(event);
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
    //taskBuffer.push_back(task);
    dLink->pushTask(task);
    return 0;
}
void ModModule::processTask(std::list<std::string> _args)
{
    if(*_args.begin() == "gui")
    {
        _args.pop_front();
        if(*_args.begin() == "list")
        {
            int counter = 1;
            for(std::list<GUIMenu>::iterator it = guiLink->guiMenus.begin(); it != guiLink->guiMenus.end(); it++)
            {
                std::list<std::string> x;
                x.push_back("gui");
                x.push_back("list");
                x.push_back(util::toString(counter));
                x.push_back(it->ID);
                dLink->pushEvent(x);
                counter++;
            }
        }
        else if(*_args.begin() == "add")
        {
            _args.pop_front();
            GUIMenu x;
            x.ID = *_args.begin();
            guiLink->guiMenus.push_back(x);
        }
        else if(*_args.begin() == "remove")
        {
            _args.pop_front();
            for(std::list<GUIMenu>::iterator it = guiLink->guiMenus.begin(); it != guiLink->guiMenus.end(); it++)
            {
                if(it->ID == *_args.begin())
                {
                    guiLink->guiMenus.erase(it);
                    return;
                }
            }
        }
        else if(*_args.begin() == "access")
        {
            _args.pop_front()
            for(std::list<GUIMenu>::iterator it = guiLink->guiMenus.begin(); it != guiLink->guiMenus.end(); it++)
            {
                if(it->ID == *_args.begin())
                {
                    _args.pop_front();
                    if(*_args.begin() == "property")
                    {
                        _args.pop_front();
                        if(*_args.begin() == "list")
                        {
                            std::list<std::string> x;
                            x.push_back("gui");
                            x.push_back("access");
                            x.push_back(it->ID);
                            x.push_back("property");
                            x.push_back("list")
                            x.push_back("1"));
                            x.push_back("x");
                            dLink->pushEvent(x);
                            x.clear();
                            x.push_back("gui");
                            x.push_back("access");
                            x.push_back(it->ID);
                            x.push_back("property");
                            x.push_back("list")
                            x.push_back("2"));
                            x.push_back("y");
                            dLink->pushEvent(x);
                            x.clear();
                            x.push_back("gui");
                            x.push_back("access");
                            x.push_back(it->ID);
                            x.push_back("property");
                            x.push_back("list")
                            x.push_back("3"));
                            x.push_back("width");
                            dLink->pushEvent(x);
                            x.clear();
                            x.push_back("gui");
                            x.push_back("access");
                            x.push_back(it->ID);
                            x.push_back("property");
                            x.push_back("list")
                            x.push_back("4"));
                            x.push_back("height");
                            dLink->pushEvent(x);
                            x.clear();
                            x.push_back("gui");
                            x.push_back("access");
                            x.push_back(it->ID);
                            x.push_back("property");
                            x.push_back("list")
                            x.push_back("5"));
                            x.push_back("title");
                            dLink->pushEvent(x);
                            x.clear();
                            x.push_back("gui");
                            x.push_back("access");
                            x.push_back(it->ID);
                            x.push_back("property");
                            x.push_back("list")
                            x.push_back("6"));
                            x.push_back("visible");
                            dLink->pushEvent(x);
                            x.clear();
                            x.push_back("gui");
                            x.push_back("access");
                            x.push_back(it->ID);
                            x.push_back("property");
                            x.push_back("list")
                            x.push_back("7"));
                            x.push_back("scrollable");
                            dLink->pushEvent(x);
                            x.clear();
                            x.push_back("gui");
                            x.push_back("access");
                            x.push_back(it->ID);
                            x.push_back("property");
                            x.push_back("list")
                            x.push_back("8"));
                            x.push_back("widthT");
                            dLink->pushEvent(x);
                            x.clear();
                            x.push_back("gui");
                            x.push_back("access");
                            x.push_back(it->ID);
                            x.push_back("property");
                            x.push_back("list")
                            x.push_back("9"));
                            x.push_back("heightT");
                            dLink->pushEvent(x);
                            x.clear();
                            x.push_back("gui");
                            x.push_back("access");
                            x.push_back(it->ID);
                            x.push_back("property");
                            x.push_back("list")
                            x.push_back("10"));
                            x.push_back("scrollX");
                            dLink->pushEvent(x);
                            x.clear();
                            x.push_back("gui");
                            x.push_back("access");
                            x.push_back(it->ID);
                            x.push_back("property");
                            x.push_back("list")
                            x.push_back("11"));
                            x.push_back("scrollY");
                            dLink->pushEvent(x);
                            x.clear();
                            x.push_back("gui");
                            x.push_back("access");
                            x.push_back(it->ID);
                            x.push_back("property");
                            x.push_back("list")
                            x.push_back("12"));
                            x.push_back("active");
                            dLink->pushEvent(x);
                            x.clear();
                        }
                        else if(*_args.begin() == "x")
                        {

                        }
                        else if(*_args.begin() == "y")
                        {

                        }
                        else if(*_args.begin() == "width")
                        {

                        }
                        else if(*_args.begin() == "height")
                        {

                        }
                        else if(*_args.begin() == "widthT")
                        {

                        }
                        else if(*_args.begin() == "heightT")
                        {

                        }
                        else if(*_args.begin() == "scrollX")
                        {

                        }
                        else if(*_args.begin() == "scrollY")
                        {

                        }
                        else if(*_args.begin() == "visible")
                        {

                        }
                        else if(*_args.begin() == "active")
                        {

                        }
                        else if(*_args.begin() == "scrollable")
                        {

                        }
                        else if(*_args.begin() == "title")
                        {

                        }
                    }
                    else if(*_args.begin() == "action")
                    {

                    }
                    else if(*_args.begin() == "element")
                    {

                    }
                    return;
                }
            }
        }
    }
    else if (*_args.begin() == "level")
    {
        _args.pop_front();
    }
    else if(*_args.begin() == "resource")
    {
        _args.pop_front();
    }
}
