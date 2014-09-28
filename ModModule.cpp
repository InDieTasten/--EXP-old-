#include "ModModule.hpp"
//CONSTRUCTORS

//DESTRUCTORS

//METHODS
void ModModule::Run()
{
    GMutex.lock();
    log("&f[ModModule][Info] Thread started");
    std::list<Script> scripts;
    Script pluginLoader("./content/stock/scripts/plugin_loader.lua");
    scripts.push_back(pluginLoader);

    for(std::list<Script>::iterator it = scripts.begin(); it != scripts.end(); it++)
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

    GMutex.unlock();

    while(dLink->runModules)
    {
        while(dLink->debug.tModSleep.size() > dLink->settings.threadMeanAmount)
        {
            dLink->debug.tModSleep.pop_front();
        }
        if(limiter.getElapsedTime().asSeconds() < 1.0/mLimit)
        {
            dLink->debug.tModSleep.push_back((1.0/mLimit - limiter.getElapsedTime().asSeconds())*1000);
            sf::sleep(sf::seconds(1.0/mLimit - limiter.getElapsedTime().asSeconds()));
        }
        else
        {
            dLink->debug.tModSleep.push_back(0.0);
        }
        limiter.restart();
        GMutex.lock();

        //async tasks
        for(std::list<ASync>::iterator aTask = waitingTasks.begin(); aTask != waitingTasks.end(); aTask++)
        {
            if(aTask->time.getElapsedTime().asMilliseconds() >= aTask->target)
            {
                dLink->pushTask(aTask->task);
                waitingTasks.erase(aTask);
                break;
            }
        }

        events = eventBuffer;
        eventBuffer.clear();
        for(std::list< std::list<std::string> >::iterator event = events.begin(); event != events.end(); event++)
        {
            for(std::list<Script>::iterator script = scripts.begin(); script != scripts.end(); script++)
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
            for(std::list<Script>::iterator script = scripts.begin(); script != scripts.end(); script++)
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
    for(std::list<Script>::iterator it = scripts.begin(); it != scripts.end(); it++)
    {
        lua_getglobal(it->state, "onHardUnload");
        lua_call(it->state, 0, 0);
        lua_close(it->state);
    }
    log("&f[ModModule][Info] Thread stopped");
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
    log("&f[ModModule]"+message);
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
    if(*_args.begin() == "gui") // gui
    {
        _args.pop_front();
        if(*_args.begin() == "list") // gui list
        {

        }
        else if(*_args.begin() == "menu") // gui menu
        {
            _args.pop_front();
            if(*_args.begin() == "list") // gui menu list
            {
                int counter = 1;
                for(std::list<GUIMenu>::iterator it = guiLink->guiMenus.begin(); it != guiLink->guiMenus.end(); it++)
                {
                    std::list<std::string> x;
                    x.push_back("gui");
                    x.push_back("menu");
                    x.push_back("list");
                    x.push_back(util::toString(counter));
                    x.push_back(it->ID);
                    dLink->pushEvent(x);
                    counter++;
                }
            }
            else if(*_args.begin() == "add") // gui menu add
            {
                _args.pop_front();
                GUIMenu x;
                x.ID = *_args.begin();
                guiLink->guiMenus.push_back(x);
            }
            else if(*_args.begin() == "remove") //gui menu remove
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
            else if(*_args.begin() == "access") //gui menu access
            {
                _args.pop_front();
                for(std::list<GUIMenu>::iterator it = guiLink->guiMenus.begin(); it != guiLink->guiMenus.end(); it++)
                {
                    if(it->ID == *_args.begin())
                    {
                        _args.pop_front();
                        if(*_args.begin() == "property") // gui menu access {ID} property
                        {
                            _args.pop_front();
                            if(*_args.begin() == "list") // gui menu access {ID} property list
                            {
                                std::list<std::string> x;
                                x.push_back("gui");
                                x.push_back("menu");
                                x.push_back("access");
                                x.push_back(it->ID);
                                x.push_back("property");
                                x.push_back("list");
                                x.push_back("1");
                                x.push_back("id");
                                dLink->pushEvent(x);
                                x.clear();
                                x.push_back("gui");
                                x.push_back("menu");
                                x.push_back("access");
                                x.push_back(it->ID);
                                x.push_back("property");
                                x.push_back("list");
                                x.push_back("2");
                                x.push_back("title");
                                dLink->pushEvent(x);
                                x.clear();
                                x.push_back("gui");
                                x.push_back("menu");
                                x.push_back("access");
                                x.push_back(it->ID);
                                x.push_back("property");
                                x.push_back("list");
                                x.push_back("3");
                                x.push_back("x");
                                dLink->pushEvent(x);
                                x.clear();
                                x.push_back("gui");
                                x.push_back("menu");
                                x.push_back("access");
                                x.push_back(it->ID);
                                x.push_back("property");
                                x.push_back("list");
                                x.push_back("4");
                                x.push_back("y");
                                dLink->pushEvent(x);
                                x.clear();
                                x.push_back("gui");
                                x.push_back("menu");
                                x.push_back("access");
                                x.push_back(it->ID);
                                x.push_back("property");
                                x.push_back("list");
                                x.push_back("5");
                                x.push_back("width");
                                dLink->pushEvent(x);
                                x.clear();
                                x.push_back("gui");
                                x.push_back("menu");
                                x.push_back("access");
                                x.push_back(it->ID);
                                x.push_back("property");
                                x.push_back("list");
                                x.push_back("6");
                                x.push_back("height");
                                dLink->pushEvent(x);
                                x.clear();
                                x.push_back("gui");
                                x.push_back("menu");
                                x.push_back("access");
                                x.push_back(it->ID);
                                x.push_back("property");
                                x.push_back("list");
                                x.push_back("7");
                                x.push_back("widthT");
                                dLink->pushEvent(x);
                                x.clear();
                                x.push_back("gui");
                                x.push_back("menu");
                                x.push_back("access");
                                x.push_back(it->ID);
                                x.push_back("property");
                                x.push_back("list");
                                x.push_back("8");
                                x.push_back("heightT");
                                dLink->pushEvent(x);
                                x.clear();
                                x.push_back("gui");
                                x.push_back("menu");
                                x.push_back("access");
                                x.push_back(it->ID);
                                x.push_back("property");
                                x.push_back("list");
                                x.push_back("9");
                                x.push_back("scollX");
                                dLink->pushEvent(x);
                                x.clear();
                                x.push_back("gui");
                                x.push_back("menu");
                                x.push_back("access");
                                x.push_back(it->ID);
                                x.push_back("property");
                                x.push_back("list");
                                x.push_back("10");
                                x.push_back("scrollY");
                                dLink->pushEvent(x);
                                x.clear();
                                x.push_back("gui");
                                x.push_back("menu");
                                x.push_back("access");
                                x.push_back(it->ID);
                                x.push_back("property");
                                x.push_back("list");
                                x.push_back("11");
                                x.push_back("scrollable");
                                dLink->pushEvent(x);
                                x.clear();
                                x.push_back("gui");
                                x.push_back("menu");
                                x.push_back("access");
                                x.push_back(it->ID);
                                x.push_back("property");
                                x.push_back("list");
                                x.push_back("12");
                                x.push_back("active");
                                dLink->pushEvent(x);
                                x.clear();
                                x.push_back("gui");
                                x.push_back("menu");
                                x.push_back("access");
                                x.push_back(it->ID);
                                x.push_back("property");
                                x.push_back("list");
                                x.push_back("13");
                                x.push_back("visible");
                                dLink->pushEvent(x);
                                x.clear();
                                x.push_back("gui");
                                x.push_back("menu");
                                x.push_back("access");
                                x.push_back(it->ID);
                                x.push_back("property");
                                x.push_back("list");
                                x.push_back("14");
                                x.push_back("borderColorA");
                                dLink->pushEvent(x);
                                x.clear();
                                x.push_back("gui");
                                x.push_back("menu");
                                x.push_back("access");
                                x.push_back(it->ID);
                                x.push_back("property");
                                x.push_back("list");
                                x.push_back("15");
                                x.push_back("backgroundColorA");
                                dLink->pushEvent(x);
                                x.clear();
                                x.push_back("gui");
                                x.push_back("menu");
                                x.push_back("access");
                                x.push_back(it->ID);
                                x.push_back("property");
                                x.push_back("list");
                                x.push_back("16");
                                x.push_back("titleBackgroundColorA");
                                dLink->pushEvent(x);
                                x.clear();
                                x.push_back("gui");
                                x.push_back("menu");
                                x.push_back("access");
                                x.push_back(it->ID);
                                x.push_back("property");
                                x.push_back("list");
                                x.push_back("17");
                                x.push_back("titleTextColorA");
                                dLink->pushEvent(x);
                                x.clear();
                                x.push_back("gui");
                                x.push_back("menu");
                                x.push_back("access");
                                x.push_back(it->ID);
                                x.push_back("property");
                                x.push_back("list");
                                x.push_back("18");
                                x.push_back("borderColorB");
                                dLink->pushEvent(x);
                                x.clear();
                                x.push_back("gui");
                                x.push_back("menu");
                                x.push_back("access");
                                x.push_back(it->ID);
                                x.push_back("property");
                                x.push_back("list");
                                x.push_back("19");
                                x.push_back("backgroundColorB");
                                dLink->pushEvent(x);
                                x.clear();
                                x.push_back("gui");
                                x.push_back("menu");
                                x.push_back("access");
                                x.push_back(it->ID);
                                x.push_back("property");
                                x.push_back("list");
                                x.push_back("20");
                                x.push_back("titleBackgroundColorB");
                                dLink->pushEvent(x);
                                x.clear();
                                x.push_back("gui");
                                x.push_back("menu");
                                x.push_back("access");
                                x.push_back(it->ID);
                                x.push_back("property");
                                x.push_back("list");
                                x.push_back("21");
                                x.push_back("titleTextColorB");
                                dLink->pushEvent(x);
                            }
                            else if(*_args.begin() == "id") // gui menu access {ID} property id
                            {
                                _args.pop_front();
                                if(*_args.begin() == "set") // gui menu access {ID} property id set
                                {
                                    _args.pop_front();
                                    it->ID = *_args.begin();
                                }
                                else if(*_args.begin() == "get") // gui menu access {ID} property id get
                                {
                                    std::list<std::string> x;
                                    x.push_back("gui");
                                    x.push_back("menu");
                                    x.push_back("access");
                                    x.push_back(it->ID);
                                    x.push_back("property");
                                    x.push_back("id");
                                    x.push_back(it->ID);
                                    dLink->pushEvent(x);
                                }
                            }
                            else if(*_args.begin() == "title") // gui menu access {ID} property title
                            {
                                _args.pop_front();
                                if(*_args.begin() == "set") // gui menu access {ID} property title set
                                {
                                    _args.pop_front();
                                    it->menuTitle.setString(*_args.begin());
                                }
                                else if(*_args.begin() == "get") // gui menu access {ID} property title get
                                {
                                    std::list<std::string> x;
                                    x.push_back("gui");
                                    x.push_back("menu");
                                    x.push_back("access");
                                    x.push_back(it->ID);
                                    x.push_back("property");
                                    x.push_back("title");
                                    x.push_back(it->menuTitle.getString());
                                    dLink->pushEvent(x);
                                }
                            }
                            else if(*_args.begin() == "x") // gui menu access {ID} property x
                            {
                                _args.pop_front();
                                if(*_args.begin() == "set") // gui menu access {ID} property x set
                                {
                                    _args.pop_front();
                                    it->X = util::toInt(*_args.begin());
                                }
                                else if(*_args.begin() == "get") // gui menu access {ID} property x get
                                {
                                    std::list<std::string> x;
                                    x.push_back("gui");
                                    x.push_back("menu");
                                    x.push_back("access");
                                    x.push_back(it->ID);
                                    x.push_back("property");
                                    x.push_back("x");
                                    x.push_back(util::toString(it->X));
                                    dLink->pushEvent(x);
                                }
                            }
                            else if(*_args.begin() == "y") // gui menu access {ID} property y
                            {
                                _args.pop_front();
                                if(*_args.begin() == "set") // gui menu access {ID} property y set
                                {
                                    _args.pop_front();
                                    it->Y = util::toInt(*_args.begin());
                                }
                                else if(*_args.begin() == "get") // gui menu access {ID} property y get
                                {
                                    std::list<std::string> x;
                                    x.push_back("gui");
                                    x.push_back("menu");
                                    x.push_back("access");
                                    x.push_back(it->ID);
                                    x.push_back("property");
                                    x.push_back("y");
                                    x.push_back(util::toString(it->Y));
                                    dLink->pushEvent(x);
                                }
                            }
                            else if(*_args.begin() == "width") // gui menu access {ID} property width
                            {
                                _args.pop_front();
                                if(*_args.begin() == "set") // gui menu access {ID} property width set
                                {
                                    _args.pop_front();
                                    it->Width = util::toInt(*_args.begin());
                                }
                                else if(*_args.begin() == "get") // gui menu access {ID} property width get
                                {
                                    std::list<std::string> x;
                                    x.push_back("gui");
                                    x.push_back("menu");
                                    x.push_back("access");
                                    x.push_back(it->ID);
                                    x.push_back("property");
                                    x.push_back("width");
                                    x.push_back(util::toString(it->Width));
                                    dLink->pushEvent(x);
                                }
                            }
                            else if(*_args.begin() == "height") // gui menu access {ID} property height
                            {
                                _args.pop_front();
                                if(*_args.begin() == "set") // gui menu access {ID} property height set
                                {
                                    _args.pop_front();
                                    it->Height = util::toInt(*_args.begin());
                                }
                                else if(*_args.begin() == "get") // gui menu access {ID} property height get
                                {
                                    std::list<std::string> x;
                                    x.push_back("gui");
                                    x.push_back("menu");
                                    x.push_back("access");
                                    x.push_back(it->ID);
                                    x.push_back("property");
                                    x.push_back("height");
                                    x.push_back(util::toString(it->Height));
                                    dLink->pushEvent(x);
                                }
                            }
                            else if(*_args.begin() == "widthT") // gui menu access {ID} property widthT
                            {
                                _args.pop_front();
                                if(*_args.begin() == "set") // gui menu access {ID} property widthT set
                                {
                                    _args.pop_front();
                                    it->totalWidth = util::toInt(*_args.begin());
                                }
                                else if(*_args.begin() == "get") // gui menu access {ID} property widthT get
                                {
                                    std::list<std::string> x;
                                    x.push_back("gui");
                                    x.push_back("menu");
                                    x.push_back("access");
                                    x.push_back(it->ID);
                                    x.push_back("property");
                                    x.push_back("widthT");
                                    x.push_back(util::toString(it->totalWidth));
                                    dLink->pushEvent(x);
                                }
                            }
                            else if(*_args.begin() == "heightT") // gui menu access {ID} property heightT
                            {
                                _args.pop_front();
                                if(*_args.begin() == "set") // gui menu access {ID} property heightT set
                                {
                                    _args.pop_front();
                                    it->totalHeight = util::toInt(*_args.begin());
                                }
                                else if(*_args.begin() == "get") // gui menu access {ID} property heightT get
                                {
                                    std::list<std::string> x;
                                    x.push_back("gui");
                                    x.push_back("menu");
                                    x.push_back("access");
                                    x.push_back(it->ID);
                                    x.push_back("property");
                                    x.push_back("heightT");
                                    x.push_back(util::toString(it->totalHeight));
                                    dLink->pushEvent(x);
                                }
                            }
                            else if(*_args.begin() == "scrollX") // gui menu access {ID} property scrollX
                            {
                                _args.pop_front();
                                if(*_args.begin() == "set") // gui menu access {ID} property scrollX set
                                {
                                    _args.pop_front();
                                    it->scrollX = util::toInt(*_args.begin());
                                }
                                else if(*_args.begin() == "get") // gui menu access {ID} property scrollX get
                                {
                                    std::list<std::string> x;
                                    x.push_back("gui");
                                    x.push_back("menu");
                                    x.push_back("access");
                                    x.push_back(it->ID);
                                    x.push_back("property");
                                    x.push_back("scrollX");
                                    x.push_back(util::toString(it->scrollX));
                                    dLink->pushEvent(x);
                                }
                            }
                            else if(*_args.begin() == "scrollY") // gui menu access {ID} property scrollY
                            {
                                _args.pop_front();
                                if(*_args.begin() == "set") // gui menu access {ID} property scrollY set
                                {
                                    _args.pop_front();
                                    it->scrollY = util::toInt(*_args.begin());
                                }
                                else if(*_args.begin() == "get") // gui menu access {ID} property scrollY get
                                {
                                    std::list<std::string> x;
                                    x.push_back("gui");
                                    x.push_back("menu");
                                    x.push_back("access");
                                    x.push_back(it->ID);
                                    x.push_back("property");
                                    x.push_back("scrollY");
                                    x.push_back(util::toString(it->scrollY));
                                    dLink->pushEvent(x);
                                }
                            }
                            else if(*_args.begin() == "scrollable") // gui menu access {ID} property scrollable
                            {
                                _args.pop_front();
                                if(*_args.begin() == "set") // gui menu access {ID} property scrollable set
                                {
                                    _args.pop_front();
                                    it->scrollable = util::toBool(*_args.begin());
                                }
                                else if(*_args.begin() == "get") // gui menu access {ID} property scrollable get
                                {
                                    std::list<std::string> x;
                                    x.push_back("gui");
                                    x.push_back("menu");
                                    x.push_back("access");
                                    x.push_back(it->ID);
                                    x.push_back("property");
                                    x.push_back("scrollable");
                                    x.push_back(util::toString(it->scrollable));
                                    dLink->pushEvent(x);
                                }
                            }
                            else if(*_args.begin() == "active") // gui menu access {ID} property active
                            {
                                _args.pop_front();
                                if(*_args.begin() == "set") // gui menu access {ID} property active set
                                {
                                    _args.pop_front();
                                    it->isActive = util::toBool(*_args.begin());
                                }
                                else if(*_args.begin() == "get") // gui menu access {ID} property active get
                                {
                                    std::list<std::string> x;
                                    x.push_back("gui");
                                    x.push_back("menu");
                                    x.push_back("access");
                                    x.push_back(it->ID);
                                    x.push_back("property");
                                    x.push_back("active");
                                    x.push_back(util::toString(it->isActive));
                                    dLink->pushEvent(x);
                                }
                            }
                            else if(*_args.begin() == "visible") // gui menu access {ID} property visible
                            {
                                _args.pop_front();
                                if(*_args.begin() == "set") // gui menu access {ID} property visible set
                                {
                                    _args.pop_front();
                                    it->isHidden = !util::toBool(*_args.begin());
                                }
                                else if(*_args.begin() == "get") // gui menu access {ID} property visible get
                                {
                                    std::list<std::string> x;
                                    x.push_back("gui");
                                    x.push_back("menu");
                                    x.push_back("access");
                                    x.push_back(it->ID);
                                    x.push_back("property");
                                    x.push_back("visible");
                                    x.push_back(util::toString(!it->isHidden));
                                    dLink->pushEvent(x);
                                }
                            }
                            else if(*_args.begin() == "borderColorA") // gui menu access {ID} property borderColorA
                            {
                                _args.pop_front();
                                if(*_args.begin() == "set") // gui menu access {ID} property borderColorA set
                                {
                                    _args.pop_front();
                                    it->BorderActive = util::toColor(*_args.begin());
                                }
                                else if(*_args.begin() == "get") // gui menu access {ID} property borderColorA get
                                {
                                    std::list<std::string> x;
                                    x.push_back("gui");
                                    x.push_back("menu");
                                    x.push_back("access");
                                    x.push_back(it->ID);
                                    x.push_back("property");
                                    x.push_back("borderColorA");
                                    x.push_back(util::toString(it->BorderActive));
                                    dLink->pushEvent(x);
                                }
                            }
                            else if(*_args.begin() == "backgroundColorA") // gui menu access {ID} property backgroundColorA
                            {
                                _args.pop_front();
                                if(*_args.begin() == "set") // gui menu access {ID} property backgroundColorA set
                                {
                                    _args.pop_front();
                                    it->BackgroundActive = util::toColor(*_args.begin());
                                }
                                else if(*_args.begin() == "get") // gui menu access {ID} property backgroundColorA get
                                {
                                    std::list<std::string> x;
                                    x.push_back("gui");
                                    x.push_back("menu");
                                    x.push_back("access");
                                    x.push_back(it->ID);
                                    x.push_back("property");
                                    x.push_back("backgroundColorA");
                                    x.push_back(util::toString(it->BackgroundActive));
                                    dLink->pushEvent(x);
                                }
                            }
                            else if(*_args.begin() == "titleBackgroundColorA") // gui menu access {ID} property titleBackgroundColorA
                            {
                                _args.pop_front();
                                if(*_args.begin() == "set") // gui menu access {ID} property titleBackgroundColorA set
                                {
                                    _args.pop_front();
                                    it->TitleBackgroundActive = util::toColor(*_args.begin());
                                }
                                else if(*_args.begin() == "get") // gui menu access {ID} propertyt titleBackgroundColorA get
                                {
                                    std::list<std::string> x;
                                    x.push_back("gui");
                                    x.push_back("menu");
                                    x.push_back("access");
                                    x.push_back(it->ID);
                                    x.push_back("property");
                                    x.push_back("titleBackgroundColorA");
                                    x.push_back(util::toString(it->TitleBackgroundActive));
                                    dLink->pushEvent(x);
                                }
                            }
                            else if(*_args.begin() == "titleTextColorA") // gui menu access {ID} property titleTextColorA
                            {
                                _args.pop_front();
                                if(*_args.begin() == "set") // gui menu access {ID} property titleTextColorA set
                                {
                                    _args.pop_front();
                                    it->TitleTextActive = util::toColor(*_args.begin());
                                }
                                else if(*_args.begin() == "get") // gui menu access {ID} property titleTextColorA get
                                {
                                    std::list<std::string> x;
                                    x.push_back("gui");
                                    x.push_back("menu");
                                    x.push_back("access");
                                    x.push_back(it->ID);
                                    x.push_back("property");
                                    x.push_back("titleTextColorA");
                                    x.push_back(util::toString(it->TitleTextActive));
                                    dLink->pushEvent(x);
                                }
                            }
                            else if(*_args.begin() == "borderColorB") // gui menu access {ID} property borderColorB
                            {
                                _args.pop_front();
                                if(*_args.begin() == "set") // gui menu access {ID} property borderColorB set
                                {
                                    _args.pop_front();
                                    it->BorderInactive = util::toColor(*_args.begin());
                                }
                                else if(*_args.begin() == "get") // gui menu access {ID} property borderColorB get
                                {
                                    std::list<std::string> x;
                                    x.push_back("gui");
                                    x.push_back("menu");
                                    x.push_back("access");
                                    x.push_back(it->ID);
                                    x.push_back("property");
                                    x.push_back("borderColorB");
                                    x.push_back(util::toString(it->BorderInactive));
                                    dLink->pushEvent(x);
                                }
                            }
                            else if(*_args.begin() == "backgroundColorB") // gui menu access {ID} property backgroundColorB
                            {
                                _args.pop_front();
                                if(*_args.begin() == "set") // gui menu access {ID} property backgroundColorB set
                                {
                                    _args.pop_front();
                                    it->BackgroundInactive = util::toColor(*_args.begin());
                                }
                                else if(*_args.begin() == "get") // gui menu access {ID} property backgroundColorB get
                                {
                                    std::list<std::string> x;
                                    x.push_back("gui");
                                    x.push_back("menu");
                                    x.push_back("access");
                                    x.push_back(it->ID);
                                    x.push_back("property");
                                    x.push_back("backgroundColorB");
                                    x.push_back(util::toString(it->BackgroundInactive));
                                    dLink->pushEvent(x);
                                }
                            }
                            else if(*_args.begin() == "titleBackgroundColorB") // gui menu access {ID} property titleBackgroundColorB
                            {
                                _args.pop_front();
                                if(*_args.begin() == "set") // gui menu access {ID} property titleBackgroundColorB set
                                {
                                    _args.pop_front();
                                    it->TitleBackgroundInactive = util::toColor(*_args.begin());
                                }
                                else if(*_args.begin() == "get") // gui menu access {ID} property titleBackgroundColorB get
                                {
                                    std::list<std::string> x;
                                    x.push_back("gui");
                                    x.push_back("menu");
                                    x.push_back("access");
                                    x.push_back(it->ID);
                                    x.push_back("property");
                                    x.push_back("titleBackgroundColorB");
                                    x.push_back(util::toString(it->TitleBackgroundInactive));
                                    dLink->pushEvent(x);
                                }
                            }
                            else if(*_args.begin() == "titleTextColorB") // gui menu access {ID} property titleTextColorB
                            {
                                _args.pop_front();
                                if(*_args.begin() == "set") // gui menu access {ID} property titleTextColorB set
                                {
                                    _args.pop_front();
                                    it->TitleTextInactive = util::toColor(*_args.begin());
                                }
                                else if(*_args.begin() == "get") // gui menu access {ID} property titleTextColorB get
                                {
                                    std::list<std::string> x;
                                    x.push_back("gui");
                                    x.push_back("menu");
                                    x.push_back("access");
                                    x.push_back(it->ID);
                                    x.push_back("property");
                                    x.push_back("titleTextColorB");
                                    x.push_back(util::toString(it->TitleTextInactive));
                                    dLink->pushEvent(x);
                                }
                            }
                        }
                        else if(*_args.begin() == "action") // gui menu access {ID} action
                        {

                        }
                        else if(*_args.begin() == "element") // gui menu access {ID} element
                        {
                            _args.pop_front();
                            if(*_args.begin() == "list") // gui menu access {ID} element list
                            {
                                int counter = 1;
                                for(std::list<GUIElement>::iterator elem = it->GuiElements.begin(); elem != it->GuiElements.end(); elem++)
                                {
                                    std::list<std::string> x;
                                    x.push_back("gui");
                                    x.push_back("access");
                                    x.push_back(it->ID);
                                    x.push_back("element");
                                    x.push_back("list");
                                    x.push_back(util::toString(counter));
                                    x.push_back(elem->ID);
                                    dLink->pushEvent(x);

                                    counter++;
                                }
                            }
                            else if(*_args.begin() == "add") // gui menu access {ID} element add
                            {
                                GUIElement e;
                                _args.pop_front();
                                e.ID = *_args.begin();
                                it->GuiElements.push_back(e);
                            }
                            else if(*_args.begin() == "remove") // gui menu access {ID} element remove
                            {
                                _args.pop_front();
                                for(std::list<GUIElement>::iterator elem = it->GuiElements.begin(); elem != it->GuiElements.end(); elem++)
                                {
                                    if(elem->ID == *_args.begin())
                                    {
                                        it->GuiElements.erase(elem);
                                        return;
                                    }
                                }
                            }
                            else if(*_args.begin() == "access") // gui menu access {ID} element access
                            {
                                _args.pop_front();
                                for(std::list<GUIElement>::iterator elem = it->GuiElements.begin(); elem != it->GuiElements.end(); elem++)
                                {
                                    if(elem->ID == *_args.begin())
                                    {
                                        _args.pop_front();
                                        if(*_args.begin() == "list") // gui menu access {ID} element access {ID} list
                                        {
                                            std::list<std::string> x;
                                            x.push_back("gui");
                                            x.push_back("menu");
                                            x.push_back("access");
                                            x.push_back(it->ID);
                                            x.push_back("element");
                                            x.push_back("access");
                                            x.push_back(elem->ID);
                                            x.push_back("list");
                                            x.push_back("1");
                                            x.push_back("property");
                                            dLink->pushEvent(x);
                                            x.clear();
                                            x.push_back("gui");
                                            x.push_back("menu");
                                            x.push_back("access");
                                            x.push_back(it->ID);
                                            x.push_back("element");
                                            x.push_back("access");
                                            x.push_back(elem->ID);
                                            x.push_back("list");
                                            x.push_back("2");
                                            x.push_back("action");
                                            dLink->pushEvent(x);
                                        }
                                        else if(*_args.begin() == "property") // gui menu access {ID} element access {ID} property
                                        {
                                            _args.pop_front();
                                            if(*_args.begin() == "list") // gui menu access {ID} element access {ID} property list
                                            {
                                                int counter = 1;
                                                std::list<std::string> x;
                                                x.push_back("gui");
                                                x.push_back("menu");
                                                x.push_back("access");
                                                x.push_back(it->ID);
                                                x.push_back("element");
                                                x.push_back("access");
                                                x.push_back(elem->ID);
                                                x.push_back("property");
                                                x.push_back("list");
                                                x.push_back(util::toString(counter));
                                                counter++;
                                                x.push_back("id");
                                                dLink->pushEvent(x);
                                                x.clear();
                                                x.push_back("gui");
                                                x.push_back("menu");
                                                x.push_back("access");
                                                x.push_back(it->ID);
                                                x.push_back("element");
                                                x.push_back("access");
                                                x.push_back(elem->ID);
                                                x.push_back("property");
                                                x.push_back("list");
                                                x.push_back(util::toString(counter));
                                                counter++;
                                                x.push_back("type");
                                                dLink->pushEvent(x);
                                                x.clear();
                                                x.push_back("gui");
                                                x.push_back("menu");
                                                x.push_back("access");
                                                x.push_back(it->ID);
                                                x.push_back("element");
                                                x.push_back("access");
                                                x.push_back(elem->ID);
                                                x.push_back("property");
                                                x.push_back("list");
                                                x.push_back(util::toString(counter));
                                                counter++;
                                                x.push_back("x");
                                                dLink->pushEvent(x);
                                                x.clear();
                                                x.push_back("gui");
                                                x.push_back("menu");
                                                x.push_back("access");
                                                x.push_back(it->ID);
                                                x.push_back("element");
                                                x.push_back("access");
                                                x.push_back(elem->ID);
                                                x.push_back("property");
                                                x.push_back("list");
                                                x.push_back(util::toString(counter));
                                                counter++;
                                                x.push_back("y");
                                                dLink->pushEvent(x);
                                                x.clear();
                                                if(elem->Type == "button")
                                                {
                                                    x.push_back("gui");
                                                    x.push_back("menu");
                                                    x.push_back("access");
                                                    x.push_back(it->ID);
                                                    x.push_back("element");
                                                    x.push_back("access");
                                                    x.push_back(elem->ID);
                                                    x.push_back("property");
                                                    x.push_back("list");
                                                    x.push_back(util::toString(counter));
                                                    counter++;
                                                    x.push_back("width");
                                                    dLink->pushEvent(x);
                                                    x.clear();
                                                    x.push_back("gui");
                                                    x.push_back("menu");
                                                    x.push_back("access");
                                                    x.push_back(it->ID);
                                                    x.push_back("element");
                                                    x.push_back("access");
                                                    x.push_back(elem->ID);
                                                    x.push_back("property");
                                                    x.push_back("list");
                                                    x.push_back(util::toString(counter));
                                                    counter++;
                                                    x.push_back("height");
                                                    dLink->pushEvent(x);
                                                    x.clear();
                                                    x.push_back("gui");
                                                    x.push_back("menu");
                                                    x.push_back("access");
                                                    x.push_back(it->ID);
                                                    x.push_back("element");
                                                    x.push_back("access");
                                                    x.push_back(elem->ID);
                                                    x.push_back("property");
                                                    x.push_back("list");
                                                    x.push_back(util::toString(counter));
                                                    counter++;
                                                    x.push_back("displayText");
                                                    dLink->pushEvent(x);
                                                    x.clear();
                                                    x.push_back("gui");
                                                    x.push_back("menu");
                                                    x.push_back("access");
                                                    x.push_back(it->ID);
                                                    x.push_back("element");
                                                    x.push_back("access");
                                                    x.push_back(elem->ID);
                                                    x.push_back("property");
                                                    x.push_back("list");
                                                    x.push_back(util::toString(counter));
                                                    counter++;
                                                    x.push_back("backgroundColorA");
                                                    dLink->pushEvent(x);
                                                    x.clear();
                                                    x.push_back("gui");
                                                    x.push_back("menu");
                                                    x.push_back("access");
                                                    x.push_back(it->ID);
                                                    x.push_back("element");
                                                    x.push_back("access");
                                                    x.push_back(elem->ID);
                                                    x.push_back("property");
                                                    x.push_back("list");
                                                    x.push_back(util::toString(counter));
                                                    counter++;
                                                    x.push_back("borderColorA");
                                                    dLink->pushEvent(x);
                                                    x.clear();
                                                    x.push_back("gui");
                                                    x.push_back("menu");
                                                    x.push_back("access");
                                                    x.push_back(it->ID);
                                                    x.push_back("element");
                                                    x.push_back("access");
                                                    x.push_back(elem->ID);
                                                    x.push_back("property");
                                                    x.push_back("list");
                                                    x.push_back(util::toString(counter));
                                                    counter++;
                                                    x.push_back("textColorA");
                                                    dLink->pushEvent(x);
                                                    x.clear();
                                                    x.push_back("gui");
                                                    x.push_back("menu");
                                                    x.push_back("access");
                                                    x.push_back(it->ID);
                                                    x.push_back("element");
                                                    x.push_back("access");
                                                    x.push_back(elem->ID);
                                                    x.push_back("property");
                                                    x.push_back("list");
                                                    x.push_back(util::toString(counter));
                                                    counter++;
                                                    x.push_back("backgroundColorB");
                                                    dLink->pushEvent(x);
                                                    x.clear();
                                                    x.push_back("gui");
                                                    x.push_back("menu");
                                                    x.push_back("access");
                                                    x.push_back(it->ID);
                                                    x.push_back("element");
                                                    x.push_back("access");
                                                    x.push_back(elem->ID);
                                                    x.push_back("property");
                                                    x.push_back("list");
                                                    x.push_back(util::toString(counter));
                                                    counter++;
                                                    x.push_back("borderColorB");
                                                    dLink->pushEvent(x);
                                                    x.clear();
                                                    x.push_back("gui");
                                                    x.push_back("menu");
                                                    x.push_back("access");
                                                    x.push_back(it->ID);
                                                    x.push_back("element");
                                                    x.push_back("access");
                                                    x.push_back(elem->ID);
                                                    x.push_back("property");
                                                    x.push_back("list");
                                                    x.push_back(util::toString(counter));
                                                    counter++;
                                                    x.push_back("textColorB");
                                                    dLink->pushEvent(x);
                                                    x.clear();
                                                    x.push_back("gui");
                                                    x.push_back("menu");
                                                    x.push_back("access");
                                                    x.push_back(it->ID);
                                                    x.push_back("element");
                                                    x.push_back("access");
                                                    x.push_back(elem->ID);
                                                    x.push_back("property");
                                                    x.push_back("list");
                                                    x.push_back(util::toString(counter));
                                                    counter++;
                                                    x.push_back("backgroundColorC");
                                                    dLink->pushEvent(x);
                                                    x.clear();
                                                    x.push_back("gui");
                                                    x.push_back("menu");
                                                    x.push_back("access");
                                                    x.push_back(it->ID);
                                                    x.push_back("element");
                                                    x.push_back("access");
                                                    x.push_back(elem->ID);
                                                    x.push_back("property");
                                                    x.push_back("list");
                                                    x.push_back(util::toString(counter));
                                                    counter++;
                                                    x.push_back("borderColorC");
                                                    dLink->pushEvent(x);
                                                    x.clear();
                                                    x.push_back("gui");
                                                    x.push_back("menu");
                                                    x.push_back("access");
                                                    x.push_back(it->ID);
                                                    x.push_back("element");
                                                    x.push_back("access");
                                                    x.push_back(elem->ID);
                                                    x.push_back("property");
                                                    x.push_back("list");
                                                    x.push_back(util::toString(counter));
                                                    counter++;
                                                    x.push_back("textColorC");
                                                    dLink->pushEvent(x);
                                                    x.clear();
                                                    x.push_back("gui");
                                                    x.push_back("menu");
                                                    x.push_back("access");
                                                    x.push_back(it->ID);
                                                    x.push_back("element");
                                                    x.push_back("access");
                                                    x.push_back(elem->ID);
                                                    x.push_back("property");
                                                    x.push_back("list");
                                                    x.push_back(util::toString(counter));
                                                    counter++;
                                                    x.push_back("fontID");
                                                    dLink->pushEvent(x);
                                                    x.clear();
                                                    x.push_back("gui");
                                                    x.push_back("menu");
                                                    x.push_back("access");
                                                    x.push_back(it->ID);
                                                    x.push_back("element");
                                                    x.push_back("access");
                                                    x.push_back(elem->ID);
                                                    x.push_back("property");
                                                    x.push_back("list");
                                                    x.push_back(util::toString(counter));
                                                    counter++;
                                                    x.push_back("textScale");
                                                    dLink->pushEvent(x);
                                                    x.clear();
                                                }
                                                else if(elem->Type == "horSlider" || elem->Type == "vertSlider")
                                                {
                                                    x.push_back("gui");
                                                    x.push_back("menu");
                                                    x.push_back("access");
                                                    x.push_back(it->ID);
                                                    x.push_back("element");
                                                    x.push_back("access");
                                                    x.push_back(elem->ID);
                                                    x.push_back("property");
                                                    x.push_back("list");
                                                    x.push_back(util::toString(counter));
                                                    counter++;
                                                    x.push_back("width");
                                                    dLink->pushEvent(x);
                                                    x.clear();
                                                    x.push_back("gui");
                                                    x.push_back("menu");
                                                    x.push_back("access");
                                                    x.push_back(it->ID);
                                                    x.push_back("element");
                                                    x.push_back("access");
                                                    x.push_back(elem->ID);
                                                    x.push_back("property");
                                                    x.push_back("list");
                                                    x.push_back(util::toString(counter));
                                                    counter++;
                                                    x.push_back("height");
                                                    dLink->pushEvent(x);
                                                    x.clear();
                                                    x.push_back("gui");
                                                    x.push_back("menu");
                                                    x.push_back("access");
                                                    x.push_back(it->ID);
                                                    x.push_back("element");
                                                    x.push_back("access");
                                                    x.push_back(elem->ID);
                                                    x.push_back("property");
                                                    x.push_back("list");
                                                    x.push_back(util::toString(counter));
                                                    counter++;
                                                    x.push_back("max");
                                                    dLink->pushEvent(x);
                                                    x.clear();
                                                    x.push_back("gui");
                                                    x.push_back("menu");
                                                    x.push_back("access");
                                                    x.push_back(it->ID);
                                                    x.push_back("element");
                                                    x.push_back("access");
                                                    x.push_back(elem->ID);
                                                    x.push_back("property");
                                                    x.push_back("list");
                                                    x.push_back(util::toString(counter));
                                                    counter++;
                                                    x.push_back("min");
                                                    dLink->pushEvent(x);
                                                    x.clear();
                                                    x.push_back("gui");
                                                    x.push_back("menu");
                                                    x.push_back("access");
                                                    x.push_back(it->ID);
                                                    x.push_back("element");
                                                    x.push_back("access");
                                                    x.push_back(elem->ID);
                                                    x.push_back("property");
                                                    x.push_back("list");
                                                    x.push_back(util::toString(counter));
                                                    counter++;
                                                    x.push_back("ratio");
                                                    dLink->pushEvent(x);
                                                    x.clear();
                                                    x.push_back("gui");
                                                    x.push_back("menu");
                                                    x.push_back("access");
                                                    x.push_back(it->ID);
                                                    x.push_back("element");
                                                    x.push_back("access");
                                                    x.push_back(elem->ID);
                                                    x.push_back("property");
                                                    x.push_back("list");
                                                    x.push_back(util::toString(counter));
                                                    counter++;
                                                    x.push_back("value");
                                                    dLink->pushEvent(x);
                                                    x.clear();
                                                    x.push_back("gui");
                                                    x.push_back("menu");
                                                    x.push_back("access");
                                                    x.push_back(it->ID);
                                                    x.push_back("element");
                                                    x.push_back("access");
                                                    x.push_back(elem->ID);
                                                    x.push_back("property");
                                                    x.push_back("list");
                                                    x.push_back(util::toString(counter));
                                                    counter++;
                                                    x.push_back("barBackgroundA");
                                                    dLink->pushEvent(x);
                                                    x.clear();
                                                    x.push_back("gui");
                                                    x.push_back("menu");
                                                    x.push_back("access");
                                                    x.push_back(it->ID);
                                                    x.push_back("element");
                                                    x.push_back("access");
                                                    x.push_back(elem->ID);
                                                    x.push_back("property");
                                                    x.push_back("list");
                                                    x.push_back(util::toString(counter));
                                                    counter++;
                                                    x.push_back("barBorderA");
                                                    dLink->pushEvent(x);
                                                    x.clear();
                                                    x.push_back("gui");
                                                    x.push_back("menu");
                                                    x.push_back("access");
                                                    x.push_back(it->ID);
                                                    x.push_back("element");
                                                    x.push_back("access");
                                                    x.push_back(elem->ID);
                                                    x.push_back("property");
                                                    x.push_back("list");
                                                    x.push_back(util::toString(counter));
                                                    counter++;
                                                    x.push_back("barBackgroundB");
                                                    dLink->pushEvent(x);
                                                    x.clear();
                                                    x.push_back("gui");
                                                    x.push_back("menu");
                                                    x.push_back("access");
                                                    x.push_back(it->ID);
                                                    x.push_back("element");
                                                    x.push_back("access");
                                                    x.push_back(elem->ID);
                                                    x.push_back("property");
                                                    x.push_back("list");
                                                    x.push_back(util::toString(counter));
                                                    counter++;
                                                    x.push_back("barBorderB");
                                                    dLink->pushEvent(x);
                                                    x.clear();
                                                    x.push_back("gui");
                                                    x.push_back("menu");
                                                    x.push_back("access");
                                                    x.push_back(it->ID);
                                                    x.push_back("element");
                                                    x.push_back("access");
                                                    x.push_back(elem->ID);
                                                    x.push_back("property");
                                                    x.push_back("list");
                                                    x.push_back(util::toString(counter));
                                                    counter++;
                                                    x.push_back("buttonBackgroundA");
                                                    dLink->pushEvent(x);
                                                    x.clear();
                                                    x.push_back("gui");
                                                    x.push_back("menu");
                                                    x.push_back("access");
                                                    x.push_back(it->ID);
                                                    x.push_back("element");
                                                    x.push_back("access");
                                                    x.push_back(elem->ID);
                                                    x.push_back("property");
                                                    x.push_back("list");
                                                    x.push_back(util::toString(counter));
                                                    counter++;
                                                    x.push_back("buttonBorderA");
                                                    dLink->pushEvent(x);
                                                    x.clear();
                                                    x.push_back("gui");
                                                    x.push_back("menu");
                                                    x.push_back("access");
                                                    x.push_back(it->ID);
                                                    x.push_back("element");
                                                    x.push_back("access");
                                                    x.push_back(elem->ID);
                                                    x.push_back("property");
                                                    x.push_back("list");
                                                    x.push_back(util::toString(counter));
                                                    counter++;
                                                    x.push_back("buttonBackgroundB");
                                                    dLink->pushEvent(x);
                                                    x.clear();
                                                    x.push_back("gui");
                                                    x.push_back("menu");
                                                    x.push_back("access");
                                                    x.push_back(it->ID);
                                                    x.push_back("element");
                                                    x.push_back("access");
                                                    x.push_back(elem->ID);
                                                    x.push_back("property");
                                                    x.push_back("list");
                                                    x.push_back(util::toString(counter));
                                                    counter++;
                                                    x.push_back("buttonBorderB");
                                                    dLink->pushEvent(x);
                                                    x.clear();
                                                    x.push_back("gui");
                                                    x.push_back("menu");
                                                    x.push_back("access");
                                                    x.push_back(it->ID);
                                                    x.push_back("element");
                                                    x.push_back("access");
                                                    x.push_back(elem->ID);
                                                    x.push_back("property");
                                                    x.push_back("list");
                                                    x.push_back(util::toString(counter));
                                                    counter++;
                                                    x.push_back("buttonBackgroundC");
                                                    dLink->pushEvent(x);
                                                    x.clear();
                                                    x.push_back("gui");
                                                    x.push_back("menu");
                                                    x.push_back("access");
                                                    x.push_back(it->ID);
                                                    x.push_back("element");
                                                    x.push_back("access");
                                                    x.push_back(elem->ID);
                                                    x.push_back("property");
                                                    x.push_back("list");
                                                    x.push_back(util::toString(counter));
                                                    counter++;
                                                    x.push_back("buttonBorderC");
                                                    dLink->pushEvent(x);
                                                    x.clear();
                                                    x.push_back("gui");
                                                    x.push_back("menu");
                                                    x.push_back("access");
                                                    x.push_back(it->ID);
                                                    x.push_back("element");
                                                    x.push_back("access");
                                                    x.push_back(elem->ID);
                                                    x.push_back("property");
                                                    x.push_back("list");
                                                    x.push_back(util::toString(counter));
                                                    counter++;
                                                    x.push_back("sliderBackgroundA");
                                                    dLink->pushEvent(x);
                                                    x.clear();
                                                    x.push_back("gui");
                                                    x.push_back("menu");
                                                    x.push_back("access");
                                                    x.push_back(it->ID);
                                                    x.push_back("element");
                                                    x.push_back("access");
                                                    x.push_back(elem->ID);
                                                    x.push_back("property");
                                                    x.push_back("list");
                                                    x.push_back(util::toString(counter));
                                                    counter++;
                                                    x.push_back("sliderBorderA");
                                                    dLink->pushEvent(x);
                                                    x.clear();
                                                    x.push_back("gui");
                                                    x.push_back("menu");
                                                    x.push_back("access");
                                                    x.push_back(it->ID);
                                                    x.push_back("element");
                                                    x.push_back("access");
                                                    x.push_back(elem->ID);
                                                    x.push_back("property");
                                                    x.push_back("list");
                                                    x.push_back(util::toString(counter));
                                                    counter++;
                                                    x.push_back("sliderBackgroundB");
                                                    dLink->pushEvent(x);
                                                    x.clear();
                                                    x.push_back("gui");
                                                    x.push_back("menu");
                                                    x.push_back("access");
                                                    x.push_back(it->ID);
                                                    x.push_back("element");
                                                    x.push_back("access");
                                                    x.push_back(elem->ID);
                                                    x.push_back("property");
                                                    x.push_back("list");
                                                    x.push_back(util::toString(counter));
                                                    counter++;
                                                    x.push_back("sliderBorderB");
                                                    dLink->pushEvent(x);
                                                    x.clear();
                                                    x.push_back("gui");
                                                    x.push_back("menu");
                                                    x.push_back("access");
                                                    x.push_back(it->ID);
                                                    x.push_back("element");
                                                    x.push_back("access");
                                                    x.push_back(elem->ID);
                                                    x.push_back("property");
                                                    x.push_back("list");
                                                    x.push_back(util::toString(counter));
                                                    counter++;
                                                    x.push_back("sliderBackgroundC");
                                                    dLink->pushEvent(x);
                                                    x.clear();
                                                    x.push_back("gui");
                                                    x.push_back("menu");
                                                    x.push_back("access");
                                                    x.push_back(it->ID);
                                                    x.push_back("element");
                                                    x.push_back("access");
                                                    x.push_back(elem->ID);
                                                    x.push_back("property");
                                                    x.push_back("list");
                                                    x.push_back(util::toString(counter));
                                                    counter++;
                                                    x.push_back("sliderBorderC");
                                                    dLink->pushEvent(x);
                                                    x.clear();
                                                    x.push_back("gui");
                                                    x.push_back("menu");
                                                    x.push_back("access");
                                                    x.push_back(it->ID);
                                                    x.push_back("element");
                                                    x.push_back("access");
                                                    x.push_back(elem->ID);
                                                    x.push_back("property");
                                                    x.push_back("list");
                                                    x.push_back(util::toString(counter));
                                                    counter++;
                                                    x.push_back("sliderBackgroundD");
                                                    dLink->pushEvent(x);
                                                    x.clear();
                                                    x.push_back("gui");
                                                    x.push_back("menu");
                                                    x.push_back("access");
                                                    x.push_back(it->ID);
                                                    x.push_back("element");
                                                    x.push_back("access");
                                                    x.push_back(elem->ID);
                                                    x.push_back("property");
                                                    x.push_back("list");
                                                    x.push_back(util::toString(counter));
                                                    counter++;
                                                    x.push_back("sliderBorderD");
                                                    dLink->pushEvent(x);
                                                    x.clear();
                                                }
                                                else if(elem->Type == "label")
                                                {
                                                    x.push_back("gui");
                                                    x.push_back("menu");
                                                    x.push_back("access");
                                                    x.push_back(it->ID);
                                                    x.push_back("element");
                                                    x.push_back("access");
                                                    x.push_back(elem->ID);
                                                    x.push_back("property");
                                                    x.push_back("list");
                                                    x.push_back(util::toString(counter));
                                                    counter++;
                                                    x.push_back("displayText");
                                                    dLink->pushEvent(x);
                                                    x.clear();
                                                    x.push_back("gui");
                                                    x.push_back("menu");
                                                    x.push_back("access");
                                                    x.push_back(it->ID);
                                                    x.push_back("element");
                                                    x.push_back("access");
                                                    x.push_back(elem->ID);
                                                    x.push_back("property");
                                                    x.push_back("list");
                                                    x.push_back(util::toString(counter));
                                                    counter++;
                                                    x.push_back("textColorA");
                                                    dLink->pushEvent(x);
                                                    x.clear();
                                                    x.push_back("gui");
                                                    x.push_back("menu");
                                                    x.push_back("access");
                                                    x.push_back(it->ID);
                                                    x.push_back("element");
                                                    x.push_back("access");
                                                    x.push_back(elem->ID);
                                                    x.push_back("property");
                                                    x.push_back("list");
                                                    x.push_back(util::toString(counter));
                                                    counter++;
                                                    x.push_back("textColorB");
                                                    dLink->pushEvent(x);
                                                    x.clear();
                                                    x.push_back("gui");
                                                    x.push_back("menu");
                                                    x.push_back("access");
                                                    x.push_back(it->ID);
                                                    x.push_back("element");
                                                    x.push_back("access");
                                                    x.push_back(elem->ID);
                                                    x.push_back("property");
                                                    x.push_back("list");
                                                    x.push_back(util::toString(counter));
                                                    counter++;
                                                    x.push_back("textColorC");
                                                    dLink->pushEvent(x);
                                                    x.clear();
                                                    x.push_back("gui");
                                                    x.push_back("menu");
                                                    x.push_back("access");
                                                    x.push_back(it->ID);
                                                    x.push_back("element");
                                                    x.push_back("access");
                                                    x.push_back(elem->ID);
                                                    x.push_back("property");
                                                    x.push_back("list");
                                                    x.push_back(util::toString(counter));
                                                    counter++;
                                                    x.push_back("fontID");
                                                    dLink->pushEvent(x);
                                                    x.clear();
                                                    x.push_back("gui");
                                                    x.push_back("menu");
                                                    x.push_back("access");
                                                    x.push_back(it->ID);
                                                    x.push_back("element");
                                                    x.push_back("access");
                                                    x.push_back(elem->ID);
                                                    x.push_back("property");
                                                    x.push_back("list");
                                                    x.push_back(util::toString(counter));
                                                    counter++;
                                                    x.push_back("textScale");
                                                    dLink->pushEvent(x);
                                                    x.clear();
                                                }
                                            }
                                            else if(*_args.begin() == "id")
                                            {
                                                _args.pop_front();
                                                if(*_args.begin() == "set")
                                                {
                                                    _args.pop_front();
                                                    elem->ID = *_args.begin();
                                                }
                                                else if(*_args.begin() == "get")
                                                {
                                                    std::list<std::string> x;
                                                    x.push_back("gui");
                                                    x.push_back("menu");
                                                    x.push_back("access");
                                                    x.push_back(it->ID);
                                                    x.push_back("element");
                                                    x.push_back("access");
                                                    x.push_back(elem->ID);
                                                    x.push_back("property");
                                                    x.push_back("id");
                                                    x.push_back(elem->ID);
                                                    dLink->pushEvent(x);
                                                }
                                            }
                                            else if(*_args.begin() == "type")
                                            {
                                                _args.pop_front();
                                                if(*_args.begin() == "set")
                                                {
                                                    _args.pop_front();
                                                    elem->Type = *_args.begin();
                                                }
                                                else if(*_args.begin() == "get")
                                                {
                                                    std::list<std::string> x;
                                                    x.push_back("gui");
                                                    x.push_back("menu");
                                                    x.push_back("access");
                                                    x.push_back(it->ID);
                                                    x.push_back("element");
                                                    x.push_back("access");
                                                    x.push_back(elem->ID);
                                                    x.push_back("property");
                                                    x.push_back("type");
                                                    x.push_back(elem->Type);
                                                    dLink->pushEvent(x);
                                                }
                                            }
                                            else if(*_args.begin() == "x")
                                            {
                                                _args.pop_front();
                                                if(*_args.begin() == "set")
                                                {
                                                    _args.pop_front();
                                                    elem->X = util::toInt(*_args.begin());
                                                }
                                                else if(*_args.begin() == "get")
                                                {
                                                    std::list<std::string> x;
                                                    x.push_back("gui");
                                                    x.push_back("menu");
                                                    x.push_back("access");
                                                    x.push_back(it->ID);
                                                    x.push_back("element");
                                                    x.push_back("access");
                                                    x.push_back(elem->ID);
                                                    x.push_back("property");
                                                    x.push_back("x");
                                                    x.push_back(util::toString(elem->X));
                                                    dLink->pushEvent(x);
                                                }
                                            }
                                            else if(*_args.begin() == "y")
                                            {
                                                _args.pop_front();
                                                if(*_args.begin() == "set")
                                                {
                                                    _args.pop_front();
                                                    elem->Y = util::toInt(*_args.begin());
                                                }
                                                else if(*_args.begin() == "get")
                                                {
                                                    std::list<std::string> x;
                                                    x.push_back("gui");
                                                    x.push_back("menu");
                                                    x.push_back("access");
                                                    x.push_back(it->ID);
                                                    x.push_back("element");
                                                    x.push_back("access");
                                                    x.push_back(elem->ID);
                                                    x.push_back("property");
                                                    x.push_back("y");
                                                    x.push_back(util::toString(elem->Y));
                                                    dLink->pushEvent(x);
                                                }
                                            }
                                            if(elem->Type == "button")
                                            {
                                                if(*_args.begin() == "width")
                                                {
                                                    _args.pop_front();
                                                    if(*_args.begin() == "set")
                                                    {
                                                        _args.pop_front();
                                                        elem->button.Width = util::toInt(*_args.begin());
                                                    }
                                                    else if(*_args.begin() == "get")
                                                    {
                                                        std::list<std::string> x;
                                                        x.push_back("gui");
                                                        x.push_back("menu");
                                                        x.push_back("access");
                                                        x.push_back(it->ID);
                                                        x.push_back("element");
                                                        x.push_back("access");
                                                        x.push_back(elem->ID);
                                                        x.push_back("property");
                                                        x.push_back("width");
                                                        x.push_back(util::toString(elem->button.Width));
                                                        dLink->pushEvent(x);
                                                    }
                                                }
                                                else if(*_args.begin() == "height")
                                                {
                                                    _args.pop_front();
                                                    if(*_args.begin() == "set")
                                                    {
                                                        _args.pop_front();
                                                        elem->button.Height = util::toInt(*_args.begin());
                                                    }
                                                    else if(*_args.begin() == "get")
                                                    {
                                                        std::list<std::string> x;
                                                        x.push_back("gui");
                                                        x.push_back("menu");
                                                        x.push_back("access");
                                                        x.push_back(it->ID);
                                                        x.push_back("element");
                                                        x.push_back("access");
                                                        x.push_back(elem->ID);
                                                        x.push_back("property");
                                                        x.push_back("height");
                                                        x.push_back(util::toString(elem->button.Height));
                                                        dLink->pushEvent(x);
                                                    }
                                                }
                                                else if(*_args.begin() == "displayText")
                                                {
                                                    _args.pop_front();
                                                    if(*_args.begin() == "set")
                                                    {
                                                        _args.pop_front();
                                                        elem->button.Text = *_args.begin();
                                                    }
                                                    else if(*_args.begin() == "get")
                                                    {
                                                        std::list<std::string> x;
                                                        x.push_back("gui");
                                                        x.push_back("menu");
                                                        x.push_back("access");
                                                        x.push_back(it->ID);
                                                        x.push_back("element");
                                                        x.push_back("access");
                                                        x.push_back(elem->ID);
                                                        x.push_back("property");
                                                        x.push_back("displayText");
                                                        x.push_back(elem->button.Text);
                                                        dLink->pushEvent(x);
                                                    }
                                                }
                                            }
                                            else if(elem->Type == "label")
                                            {
                                                if(*_args.begin() == "displayText")
                                                {
                                                    _args.pop_front();
                                                    if(*_args.begin() == "set")
                                                    {
                                                        _args.pop_front();
                                                        elem->label.DisplayText = *_args.begin();
                                                    }
                                                    else if(*_args.begin() == "get")
                                                    {
                                                        std::list<std::string> x;
                                                        x.push_back("gui");
                                                        x.push_back("menu");
                                                        x.push_back("access");
                                                        x.push_back(it->ID);
                                                        x.push_back("element");
                                                        x.push_back("access");
                                                        x.push_back(elem->ID);
                                                        x.push_back("property");
                                                        x.push_back("displayText");
                                                        x.push_back(elem->label.DisplayText);
                                                        dLink->pushEvent(x);
                                                    }
                                                }
                                                else if(*_args.begin() == "textColorA")
                                                {
                                                    _args.pop_front();
                                                    if(*_args.begin() == "set")
                                                    {
                                                        _args.pop_front();
                                                        elem->label.TextColorActive = util::toColor(*_args.begin());
                                                    }
                                                    else if(*_args.begin() == "get")
                                                    {
                                                        std::list<std::string> x;
                                                        x.push_back("gui");
                                                        x.push_back("menu");
                                                        x.push_back("access");
                                                        x.push_back(it->ID);
                                                        x.push_back("property");
                                                        x.push_back("backgroundColorA");
                                                        x.push_back(util::toString(elem->label.TextColorActive));
                                                        dLink->pushEvent(x);
                                                    }
                                                }
                                                else if(*_args.begin() == "textColorB")
                                                {
                                                    _args.pop_front();
                                                    if(*_args.begin() == "set")
                                                    {
                                                        _args.pop_front();
                                                        elem->label.TextColorInactive = util::toColor(*_args.begin());
                                                    }
                                                    else if(*_args.begin() == "get")
                                                    {
                                                        std::list<std::string> x;
                                                        x.push_back("gui");
                                                        x.push_back("menu");
                                                        x.push_back("access");
                                                        x.push_back(it->ID);
                                                        x.push_back("property");
                                                        x.push_back("backgroundColorA");
                                                        x.push_back(util::toString(elem->label.TextColorInactive));
                                                        dLink->pushEvent(x);
                                                    }
                                                }
                                            }
                                            else if(elem->Type == "horslider")
                                            {
                                                if(*_args.begin() == "width")
                                                {
                                                    _args.pop_front();
                                                    if(*_args.begin() == "set")
                                                    {
                                                        _args.pop_front();
                                                        elem->horSlider.Width = util::toInt(*_args.begin());
                                                    }
                                                    else if(*_args.begin() == "get")
                                                    {
                                                        std::list<std::string> x;
                                                        x.push_back("gui");
                                                        x.push_back("menu");
                                                        x.push_back("access");
                                                        x.push_back(it->ID);
                                                        x.push_back("element");
                                                        x.push_back("access");
                                                        x.push_back(elem->ID);
                                                        x.push_back("property");
                                                        x.push_back("width");
                                                        x.push_back(util::toString(elem->horSlider.Width));
                                                        dLink->pushEvent(x);
                                                    }
                                                }
                                                else if(*_args.begin() == "height")
                                                {
                                                    _args.pop_front();
                                                    if(*_args.begin() == "set")
                                                    {
                                                        _args.pop_front();
                                                        elem->horSlider.Height = util::toInt(*_args.begin());
                                                    }
                                                    else if(*_args.begin() == "get")
                                                    {
                                                        std::list<std::string> x;
                                                        x.push_back("gui");
                                                        x.push_back("menu");
                                                        x.push_back("access");
                                                        x.push_back(it->ID);
                                                        x.push_back("element");
                                                        x.push_back("access");
                                                        x.push_back(elem->ID);
                                                        x.push_back("property");
                                                        x.push_back("height");
                                                        x.push_back(util::toString(elem->horSlider.Height));
                                                        dLink->pushEvent(x);
                                                    }
                                                }
                                                else if(*_args.begin() == "min")
                                                {
                                                    _args.pop_front();
                                                    if(*_args.begin() == "set")
                                                    {
                                                        _args.pop_front();
                                                        elem->horSlider.min = util::toFloat(*_args.begin());
                                                    }
                                                    else if(*_args.begin() == "get")
                                                    {
                                                        std::list<std::string> x;
                                                        x.push_back("gui");
                                                        x.push_back("menu");
                                                        x.push_back("access");
                                                        x.push_back(it->ID);
                                                        x.push_back("element");
                                                        x.push_back("access");
                                                        x.push_back(elem->ID);
                                                        x.push_back("property");
                                                        x.push_back("min");
                                                        x.push_back(util::toString(elem->horSlider.min));
                                                        dLink->pushEvent(x);
                                                    }
                                                }
                                                else if(*_args.begin() == "max")
                                                {
                                                    _args.pop_front();
                                                    if(*_args.begin() == "set")
                                                    {
                                                        _args.pop_front();
                                                        elem->horSlider.max = util::toFloat(*_args.begin());
                                                    }
                                                    else if(*_args.begin() == "get")
                                                    {
                                                        std::list<std::string> x;
                                                        x.push_back("gui");
                                                        x.push_back("menu");
                                                        x.push_back("access");
                                                        x.push_back(it->ID);
                                                        x.push_back("element");
                                                        x.push_back("access");
                                                        x.push_back(elem->ID);
                                                        x.push_back("property");
                                                        x.push_back("max");
                                                        x.push_back(util::toString(elem->horSlider.max));
                                                        dLink->pushEvent(x);
                                                    }
                                                }
                                                else if(*_args.begin() == "val")
                                                {
                                                    _args.pop_front();
                                                    if(*_args.begin() == "set")
                                                    {
                                                        _args.pop_front();
                                                        elem->horSlider.value = util::toFloat(*_args.begin());
                                                    }
                                                    else if(*_args.begin() == "get")
                                                    {
                                                        std::list<std::string> x;
                                                        x.push_back("gui");
                                                        x.push_back("menu");
                                                        x.push_back("access");
                                                        x.push_back(it->ID);
                                                        x.push_back("element");
                                                        x.push_back("access");
                                                        x.push_back(elem->ID);
                                                        x.push_back("property");
                                                        x.push_back("val");
                                                        x.push_back(util::toString(elem->horSlider.value));
                                                        dLink->pushEvent(x);
                                                    }
                                                }
                                                else if(*_args.begin() == "ratio")
                                                {
                                                    _args.pop_front();
                                                    if(*_args.begin() == "set")
                                                    {
                                                        _args.pop_front();
                                                        elem->horSlider.ratio = util::toFloat(*_args.begin());
                                                    }
                                                    else if(*_args.begin() == "get")
                                                    {
                                                        std::list<std::string> x;
                                                        x.push_back("gui");
                                                        x.push_back("menu");
                                                        x.push_back("access");
                                                        x.push_back(it->ID);
                                                        x.push_back("element");
                                                        x.push_back("access");
                                                        x.push_back(elem->ID);
                                                        x.push_back("property");
                                                        x.push_back("ratio");
                                                        x.push_back(util::toString(elem->horSlider.ratio));
                                                        dLink->pushEvent(x);
                                                    }
                                                }
                                            }
                                            else if(elem->Type == "canvas")
                                            {
                                                if(*_args.begin() == "width")
                                                {
                                                    _args.pop_front();
                                                    if(*_args.begin() == "set")
                                                    {
                                                        _args.pop_front();
                                                        elem->canvas.Width = util::toInt(*_args.begin());
                                                        log("&c[API][Info] Set complete");
                                                    }
                                                    else if(*_args.begin() == "get")
                                                    {
                                                        std::list<std::string> x;
                                                        x.push_back("gui");
                                                        x.push_back("menu");
                                                        x.push_back("access");
                                                        x.push_back(it->ID);
                                                        x.push_back("element");
                                                        x.push_back("access");
                                                        x.push_back(elem->ID);
                                                        x.push_back("property");
                                                        x.push_back("width");
                                                        x.push_back(util::toString(elem->canvas.Width));
                                                        dLink->pushEvent(x);
                                                    }
                                                }
                                                else if(*_args.begin() == "height")
                                                {
                                                    _args.pop_front();
                                                    if(*_args.begin() == "set")
                                                    {
                                                        _args.pop_front();
                                                        elem->canvas.Height = util::toInt(*_args.begin());
                                                    }
                                                    else if(*_args.begin() == "get")
                                                    {
                                                        std::list<std::string> x;
                                                        x.push_back("gui");
                                                        x.push_back("menu");
                                                        x.push_back("access");
                                                        x.push_back(it->ID);
                                                        x.push_back("element");
                                                        x.push_back("access");
                                                        x.push_back(elem->ID);
                                                        x.push_back("property");
                                                        x.push_back("height");
                                                        x.push_back(util::toString(elem->canvas.Height));
                                                        dLink->pushEvent(x);
                                                    }
                                                }
                                            }
                                        }
                                        else if(*_args.begin() == "action") // gui menu access {ID} element access {ID} action
                                        {
                                            _args.pop_front();
                                            if(*_args.begin() == "list")
                                            {
                                                int counter = 1;
                                                std::list<std::string> x;

                                                if(elem->Type == "canvas")
                                                {
                                                    x.clear();
                                                    x.push_back("gui");
                                                    x.push_back("menu");
                                                    x.push_back("access");
                                                    x.push_back(it->ID);
                                                    x.push_back("element");
                                                    x.push_back("access");
                                                    x.push_back(elem->ID);
                                                    x.push_back("action");
                                                    x.push_back(util::toString(counter));
                                                    counter++;
                                                    x.push_back("clear");
                                                    dLink->pushEvent(x);
                                                    x.clear();
                                                    x.push_back("gui");
                                                    x.push_back("menu");
                                                    x.push_back("access");
                                                    x.push_back(it->ID);
                                                    x.push_back("element");
                                                    x.push_back("access");
                                                    x.push_back(elem->ID);
                                                    x.push_back("action");
                                                    x.push_back(util::toString(counter));
                                                    counter++;
                                                    x.push_back("setFillColor");
                                                    dLink->pushEvent(x);
                                                    x.clear();
                                                    x.push_back("gui");
                                                    x.push_back("menu");
                                                    x.push_back("access");
                                                    x.push_back(it->ID);
                                                    x.push_back("element");
                                                    x.push_back("access");
                                                    x.push_back(elem->ID);
                                                    x.push_back("action");
                                                    x.push_back(util::toString(counter));
                                                    counter++;
                                                    x.push_back("setOutlineColor");
                                                    dLink->pushEvent(x);
                                                    x.clear();
                                                    x.push_back("gui");
                                                    x.push_back("menu");
                                                    x.push_back("access");
                                                    x.push_back(it->ID);
                                                    x.push_back("element");
                                                    x.push_back("access");
                                                    x.push_back(elem->ID);
                                                    x.push_back("action");
                                                    x.push_back(util::toString(counter));
                                                    counter++;
                                                    x.push_back("draw");
                                                    dLink->pushEvent(x);
                                                }
                                            }
                                            if(elem->Type == "canvas")
                                            {
                                                if(*_args.begin() == "clear")
                                                {
                                                    elem->canvas.vertexbuffer.clear();
                                                    elem->canvas.shapebuffer.clear();
                                                }
                                                else if(*_args.begin() == "display")
                                                {
                                                    elem->canvas.vertex = elem->canvas.vertexbuffer;
                                                    elem->canvas.shapes  = elem->canvas.shapebuffer;
                                                }
                                                else if(*_args.begin() == "setFillColor")
                                                {
                                                    _args.pop_front();
                                                    elem->canvas.fillColor = util::toColor(*_args.begin());
                                                }
                                                else if(*_args.begin() == "setOutlineColor")
                                                {
                                                    _args.pop_front();
                                                    elem->canvas.outlineColor = util::toColor(*_args.begin());
                                                }
                                                else if(*_args.begin() == "draw")
                                                {
                                                    _args.pop_front();
                                                    if(*_args.begin() == "line")
                                                    {
                                                        _args.pop_front();
                                                        line x;
                                                        x.line[0].position.x = util::toFloat(*_args.begin());
                                                        _args.pop_front();
                                                        x.line[0].position.y = util::toFloat(*_args.begin());
                                                        _args.pop_front();
                                                        x.line[1].position.x = util::toFloat(*_args.begin());
                                                        _args.pop_front();
                                                        x.line[1].position.y = util::toFloat(*_args.begin());

                                                        x.line[0].color = elem->canvas.fillColor;
                                                        x.line[1].color = elem->canvas.fillColor;

                                                        elem->canvas.vertexbuffer.push_back(x);
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        return;
                    }
                }
            }
        }
        else if(*_args.begin() == "dock") // gui dock
        {

        }
    }
    else if (*_args.begin() == "level") //level
    {
        _args.pop_front();
    }
    else if(*_args.begin() == "settings") //settings
    {
        _args.pop_front();
        if(*_args.begin() == "threadMeanAmount")
        {
            _args.pop_front();
            if(*_args.begin() == "set")
            {
                _args.pop_front();
                dLink->settings.threadMeanAmount = util::toInt(*_args.begin());
            }
            else if (*_args.begin() == "get")
            {
                std::list<std::string> x;
                x.push_back("settings");
                x.push_back("threadMeanAmount");
                x.push_back("get");
                x.push_back(util::toString(dLink->settings.threadMeanAmount));
                dLink->pushEvent(x);
            }
        }
        else if(*_args.begin() == "eventtaskMeanAmount")
        {
            _args.pop_front();
            if(*_args.begin() == "set")
            {
                _args.pop_front();
                dLink->settings.eventtaskMeanAmount = util::toInt(*_args.begin());
            }
            else if (*_args.begin() == "get")
            {
                std::list<std::string> x;
                x.push_back("settings");
                x.push_back("eventtaskMeanAmount");
                x.push_back("get");
                x.push_back(util::toString(dLink->settings.eventtaskMeanAmount));
                dLink->pushEvent(x);
            }
        }
        else if(*_args.begin() == "countResetInterval")
        {
            _args.pop_front();
            if(*_args.begin() == "set")
            {
                _args.pop_front();
                dLink->settings.countResetInterval = util::toFloat(*_args.begin());
            }
            else if (*_args.begin() == "get")
            {
                std::list<std::string> x;
                x.push_back("settings");
                x.push_back("countResetInterval");
                x.push_back("get");
                x.push_back(util::toString(dLink->settings.countResetInterval));
                dLink->pushEvent(x);
            }
        }
        else if(*_args.begin() == "dockWidth")
        {
            _args.pop_front();
            if(*_args.begin() == "set")
            {
                _args.pop_front();
                dLink->settings.dockWidth = util::toInt(*_args.begin());
            }
            else if (*_args.begin() == "get")
            {
                std::list<std::string> x;
                x.push_back("settings");
                x.push_back("dockWidth");
                x.push_back("get");
                x.push_back(util::toString(dLink->settings.dockWidth));
                dLink->pushEvent(x);
            }
        }
        else if(*_args.begin() == "guiDockBackgroundColorB")
        {
            _args.pop_front();
            if(*_args.begin() == "set")
            {
                _args.pop_front();
                dLink->settings.guiDockBackground = util::toColor(*_args.begin());
            }
            else if (*_args.begin() == "get")
            {
                std::list<std::string> x;
                x.push_back("settings");
                x.push_back("guiDockBackgroundColorB");
                x.push_back("get");
                x.push_back(util::toString(dLink->settings.guiDockBackground));
                dLink->pushEvent(x);
            }
        }
        else if(*_args.begin() == "guiDockBackgroundColorA")
        {
            _args.pop_front();
            if(*_args.begin() == "set")
            {
                _args.pop_front();
                dLink->settings.guiDockBackgroundHover = util::toColor(*_args.begin());
            }
            else if (*_args.begin() == "get")
            {
                std::list<std::string> x;
                x.push_back("settings");
                x.push_back("guiDockBackgroundColorA");
                x.push_back("get");
                x.push_back(util::toString(dLink->settings.guiDockBackgroundHover));
                dLink->pushEvent(x);
            }
        }
        else if(*_args.begin() == "guiDockBorderColorB")
        {
            _args.pop_front();
            if(*_args.begin() == "set")
            {
                _args.pop_front();
                dLink->settings.guiDockBorder = util::toColor(*_args.begin());
            }
            else if (*_args.begin() == "get")
            {
                std::list<std::string> x;
                x.push_back("settings");
                x.push_back("guiDockBorderColorB");
                x.push_back("get");
                x.push_back(util::toString(dLink->settings.guiDockBorder));
                dLink->pushEvent(x);
            }
        }
        else if(*_args.begin() == "guiDockBorderColorA")
        {
            _args.pop_front();
            if(*_args.begin() == "set")
            {
                _args.pop_front();
                dLink->settings.guiDockBorderHover = util::toColor(*_args.begin());
            }
            else if (*_args.begin() == "get")
            {
                std::list<std::string> x;
                x.push_back("settings");
                x.push_back("guiDockBorderColorA");
                x.push_back("get");
                x.push_back(util::toString(dLink->settings.guiDockBorderHover));
                dLink->pushEvent(x);
            }
        }
        else if(*_args.begin() == "guiDockItemBackgroundColorB")
        {
            _args.pop_front();
            if(*_args.begin() == "set")
            {
                _args.pop_front();
                dLink->settings.guiDockItemBackground = util::toColor(*_args.begin());
            }
            else if (*_args.begin() == "get")
            {
                std::list<std::string> x;
                x.push_back("settings");
                x.push_back("guiDockItemBackgroundColorB");
                x.push_back("get");
                x.push_back(util::toString(dLink->settings.guiDockItemBackground));
                dLink->pushEvent(x);
            }
        }
        else if(*_args.begin() == "guiDockItemBackgroundColorA")
        {
            _args.pop_front();
            if(*_args.begin() == "set")
            {
                _args.pop_front();
                dLink->settings.guiDockItemBackgroundHover = util::toColor(*_args.begin());
            }
            else if (*_args.begin() == "get")
            {
                std::list<std::string> x;
                x.push_back("settings");
                x.push_back("guiDockItemBackgroundColorA");
                x.push_back("get");
                x.push_back(util::toString(dLink->settings.guiDockItemBackgroundHover));
                dLink->pushEvent(x);
            }
        }
        else if(*_args.begin() == "guiDockItemBorderColorB")
        {
            _args.pop_front();
            if(*_args.begin() == "set")
            {
                _args.pop_front();
                dLink->settings.guiDockItemBorder = util::toColor(*_args.begin());
            }
            else if (*_args.begin() == "get")
            {
                std::list<std::string> x;
                x.push_back("settings");
                x.push_back("guiDockItemBorderColorB");
                x.push_back("get");
                x.push_back(util::toString(dLink->settings.guiDockItemBorder));
                dLink->pushEvent(x);
            }
        }
        else if(*_args.begin() == "guiDockItemBorderColorA")
        {
            _args.pop_front();
            if(*_args.begin() == "set")
            {
                _args.pop_front();
                dLink->settings.guiDockItemBorderHover = util::toColor(*_args.begin());
            }
            else if (*_args.begin() == "get")
            {
                std::list<std::string> x;
                x.push_back("settings");
                x.push_back("guiDockItemBorderColorA");
                x.push_back("get");
                x.push_back(util::toString(dLink->settings.guiDockItemBorderHover));
                dLink->pushEvent(x);
            }
        }
        else if(*_args.begin() == "guiMenuBorderColorB")
        {
            _args.pop_front();
            if(*_args.begin() == "set")
            {
                _args.pop_front();
                dLink->settings.guiMenuBorderInactive = util::toColor(*_args.begin());
            }
            else if (*_args.begin() == "get")
            {
                std::list<std::string> x;
                x.push_back("settings");
                x.push_back("guiMenuBorderColorB");
                x.push_back("get");
                x.push_back(util::toString(dLink->settings.guiMenuBorderInactive));
                dLink->pushEvent(x);
            }
        }
        else if(*_args.begin() == "guiMenuBorderColorA")
        {
            _args.pop_front();
            if(*_args.begin() == "set")
            {
                _args.pop_front();
                dLink->settings.guiMenuBorderActive = util::toColor(*_args.begin());
            }
            else if (*_args.begin() == "get")
            {
                std::list<std::string> x;
                x.push_back("settings");
                x.push_back("guiMenuBorderColorA");
                x.push_back("get");
                x.push_back(util::toString(dLink->settings.guiMenuBorderActive));
                dLink->pushEvent(x);
            }
        }
        else if(*_args.begin() == "guiMenuBackgroundColorB")
        {
            _args.pop_front();
            if(*_args.begin() == "set")
            {
                _args.pop_front();
                dLink->settings.guiMenuBackgroundInactive = util::toColor(*_args.begin());
            }
            else if (*_args.begin() == "get")
            {
                std::list<std::string> x;
                x.push_back("settings");
                x.push_back("guiMenuBackgroundColorB");
                x.push_back("get");
                x.push_back(util::toString(dLink->settings.guiMenuBackgroundInactive));
                dLink->pushEvent(x);
            }
        }
        else if(*_args.begin() == "guiMenuBackgroundColorA")
        {
            _args.pop_front();
            if(*_args.begin() == "set")
            {
                _args.pop_front();
                dLink->settings.guiMenuBackgroundActive = util::toColor(*_args.begin());
            }
            else if (*_args.begin() == "get")
            {
                std::list<std::string> x;
                x.push_back("settings");
                x.push_back("guiMenuBackgroundColorA");
                x.push_back("get");
                x.push_back(util::toString(dLink->settings.guiMenuBackgroundActive));
                dLink->pushEvent(x);
            }
        }
        else if(*_args.begin() == "guiMenuTitleBackgroundColorB")
        {
            _args.pop_front();
            if(*_args.begin() == "set")
            {
                _args.pop_front();
                dLink->settings.guiMenuTitleBackgroundInactive = util::toColor(*_args.begin());
            }
            else if (*_args.begin() == "get")
            {
                std::list<std::string> x;
                x.push_back("settings");
                x.push_back("guiMenuTitleBackgroundColorB");
                x.push_back("get");
                x.push_back(util::toString(dLink->settings.guiMenuTitleBackgroundInactive));
                dLink->pushEvent(x);
            }
        }
        else if(*_args.begin() == "guiMenuTitleBackgroundColorA")
        {
            _args.pop_front();
            if(*_args.begin() == "set")
            {
                _args.pop_front();
                dLink->settings.guiMenuTitleBackgroundActive = util::toColor(*_args.begin());
            }
            else if (*_args.begin() == "get")
            {
                std::list<std::string> x;
                x.push_back("settings");
                x.push_back("guiMenuTitleBackgroundColorA");
                x.push_back("get");
                x.push_back(util::toString(dLink->settings.guiMenuTitleBackgroundActive));
                dLink->pushEvent(x);
            }
        }
        else if(*_args.begin() == "guiMenuTitleTextColorB")
        {
            _args.pop_front();
            if(*_args.begin() == "set")
            {
                _args.pop_front();
                dLink->settings.guiMenuTitleTextInactive = util::toColor(*_args.begin());
            }
            else if (*_args.begin() == "get")
            {
                std::list<std::string> x;
                x.push_back("settings");
                x.push_back("guiMenuTitleTextColorB");
                x.push_back("get");
                x.push_back(util::toString(dLink->settings.guiMenuTitleTextInactive));
                dLink->pushEvent(x);
            }
        }
        else if(*_args.begin() == "guiMenuTitleTextColorA")
        {
            _args.pop_front();
            if(*_args.begin() == "set")
            {
                _args.pop_front();
                dLink->settings.guiMenuTitleTextActive = util::toColor(*_args.begin());
            }
            else if (*_args.begin() == "get")
            {
                std::list<std::string> x;
                x.push_back("settings");
                x.push_back("guiMenuTitleTextColorA");
                x.push_back("get");
                x.push_back(util::toString(dLink->settings.guiMenuTitleTextActive));
                dLink->pushEvent(x);
            }
        }
        else if(*_args.begin() == "guiButtonBackgroundColorC")
        {
            _args.pop_front();
            if(*_args.begin() == "set")
            {
                _args.pop_front();
                dLink->settings.guiButtonBackgroundHover = util::toColor(*_args.begin());
            }
            else if (*_args.begin() == "get")
            {
                std::list<std::string> x;
                x.push_back("settings");
                x.push_back("guiButtonBackgroundColorC");
                x.push_back("get");
                x.push_back(util::toString(dLink->settings.guiButtonBackgroundHover));
                dLink->pushEvent(x);
            }
        }
        else if(*_args.begin() == "guiButtonBackgroundColorB")
        {
            _args.pop_front();
            if(*_args.begin() == "set")
            {
                _args.pop_front();
                dLink->settings.guiButtonBackgroundInactive = util::toColor(*_args.begin());
            }
            else if (*_args.begin() == "get")
            {
                std::list<std::string> x;
                x.push_back("settings");
                x.push_back("guiButtonBackgroundColorB");
                x.push_back("get");
                x.push_back(util::toString(dLink->settings.guiButtonBackgroundInactive));
                dLink->pushEvent(x);
            }
        }
        else if(*_args.begin() == "guiButtonBackgroundColorA")
        {
            _args.pop_front();
            if(*_args.begin() == "set")
            {
                _args.pop_front();
                dLink->settings.guiButtonBackgroundActive = util::toColor(*_args.begin());
            }
            else if (*_args.begin() == "get")
            {
                std::list<std::string> x;
                x.push_back("settings");
                x.push_back("guiButtonBackgroundColorA");
                x.push_back("get");
                x.push_back(util::toString(dLink->settings.guiButtonBackgroundActive));
                dLink->pushEvent(x);
            }
        }
        else if(*_args.begin() == "guiButtonBorderColorC")
        {
            _args.pop_front();
            if(*_args.begin() == "set")
            {
                _args.pop_front();
                dLink->settings.guiButtonBorderHover = util::toColor(*_args.begin());
            }
            else if (*_args.begin() == "get")
            {
                std::list<std::string> x;
                x.push_back("settings");
                x.push_back("guiButtonBorderColorC");
                x.push_back("get");
                x.push_back(util::toString(dLink->settings.guiButtonBorderHover));
                dLink->pushEvent(x);
            }
        }
        else if(*_args.begin() == "guiButtonBorderColorB")
        {
            _args.pop_front();
            if(*_args.begin() == "set")
            {
                _args.pop_front();
                dLink->settings.guiButtonBorderInactive = util::toColor(*_args.begin());
            }
            else if (*_args.begin() == "get")
            {
                std::list<std::string> x;
                x.push_back("settings");
                x.push_back("guiButtonBorderColorB");
                x.push_back("get");
                x.push_back(util::toString(dLink->settings.guiButtonBorderInactive));
                dLink->pushEvent(x);
            }
        }
        else if(*_args.begin() == "guiButtonBorderColorA")
        {
            _args.pop_front();
            if(*_args.begin() == "set")
            {
                _args.pop_front();
                dLink->settings.guiButtonBorderActive = util::toColor(*_args.begin());
            }
            else if (*_args.begin() == "get")
            {
                std::list<std::string> x;
                x.push_back("settings");
                x.push_back("guiButtonBorderColorA");
                x.push_back("get");
                x.push_back(util::toString(dLink->settings.guiButtonBorderActive));
                dLink->pushEvent(x);
            }
        }
        else if(*_args.begin() == "guiButtonTextColorC")
        {
            _args.pop_front();
            if(*_args.begin() == "set")
            {
                _args.pop_front();
                dLink->settings.guiButtonTextHover = util::toColor(*_args.begin());
            }
            else if (*_args.begin() == "get")
            {
                std::list<std::string> x;
                x.push_back("settings");
                x.push_back("guiButtonTextColorC");
                x.push_back("get");
                x.push_back(util::toString(dLink->settings.guiButtonTextHover));
                dLink->pushEvent(x);
            }
        }
        else if(*_args.begin() == "guiButtonTextColorB")
        {
            _args.pop_front();
            if(*_args.begin() == "set")
            {
                _args.pop_front();
                dLink->settings.guiButtonTextInactive = util::toColor(*_args.begin());
            }
            else if (*_args.begin() == "get")
            {
                std::list<std::string> x;
                x.push_back("settings");
                x.push_back("guiButtonTextColorB");
                x.push_back("get");
                x.push_back(util::toString(dLink->settings.guiButtonTextInactive));
                dLink->pushEvent(x);
            }
        }
        else if(*_args.begin() == "guiButtonTextColorA")
        {
            _args.pop_front();
            if(*_args.begin() == "set")
            {
                _args.pop_front();
                dLink->settings.guiButtonTextActive = util::toColor(*_args.begin());
            }
            else if (*_args.begin() == "get")
            {
                std::list<std::string> x;
                x.push_back("settings");
                x.push_back("guiButtonTextColorA");
                x.push_back("get");
                x.push_back(util::toString(dLink->settings.guiButtonTextActive));
                dLink->pushEvent(x);
            }
        }
        else if(*_args.begin() == "guiHorsliderButtonBackgroundColorC")
        {
            _args.pop_front();
            if(*_args.begin() == "set")
            {
                _args.pop_front();
                dLink->settings.guiHorsliderButtonBackgroundHover = util::toColor(*_args.begin());
            }
            else if (*_args.begin() == "get")
            {
                std::list<std::string> x;
                x.push_back("settings");
                x.push_back("guiHorsliderButtonBackgroundColorC");
                x.push_back("get");
                x.push_back(util::toString(dLink->settings.guiHorsliderButtonBackgroundHover));
                dLink->pushEvent(x);
            }
        }
        else if(*_args.begin() == "guiHorsliderButtonBackgroundColorB")
        {
            _args.pop_front();
            if(*_args.begin() == "set")
            {
                _args.pop_front();
                dLink->settings.guiHorsliderButtonBackgroundInactive = util::toColor(*_args.begin());
            }
            else if (*_args.begin() == "get")
            {
                std::list<std::string> x;
                x.push_back("settings");
                x.push_back("guiHorsliderButtonBackgroundColorB");
                x.push_back("get");
                x.push_back(util::toString(dLink->settings.guiHorsliderButtonBackgroundInactive));
                dLink->pushEvent(x);
            }
        }
        else if(*_args.begin() == "guiHorsliderButtonBackgroundColorA")
        {
            _args.pop_front();
            if(*_args.begin() == "set")
            {
                _args.pop_front();
                dLink->settings.guiHorsliderButtonBackgroundActive = util::toColor(*_args.begin());
            }
            else if (*_args.begin() == "get")
            {
                std::list<std::string> x;
                x.push_back("settings");
                x.push_back("guiHorsliderButtonBackgroundColorA");
                x.push_back("get");
                x.push_back(util::toString(dLink->settings.guiHorsliderButtonBackgroundActive));
                dLink->pushEvent(x);
            }
        }
        else if(*_args.begin() == "guiHorsliderButtonBorderColorC")
        {
            _args.pop_front();
            if(*_args.begin() == "set")
            {
                _args.pop_front();
                dLink->settings.guiHorsliderButtonBorderHover = util::toColor(*_args.begin());
            }
            else if (*_args.begin() == "get")
            {
                std::list<std::string> x;
                x.push_back("settings");
                x.push_back("guiHorsliderButtonBorderColorC");
                x.push_back("get");
                x.push_back(util::toString(dLink->settings.guiHorsliderButtonBorderHover));
                dLink->pushEvent(x);
            }
        }
        else if(*_args.begin() == "guiHorsliderButtonBorderColorB")
        {
            _args.pop_front();
            if(*_args.begin() == "set")
            {
                _args.pop_front();
                dLink->settings.guiHorsliderButtonBorderInactive = util::toColor(*_args.begin());
            }
            else if (*_args.begin() == "get")
            {
                std::list<std::string> x;
                x.push_back("settings");
                x.push_back("guiHorsliderButtonBorderColorB");
                x.push_back("get");
                x.push_back(util::toString(dLink->settings.guiHorsliderButtonBorderInactive));
                dLink->pushEvent(x);
            }
        }
        else if(*_args.begin() == "guiHorsliderButtonBorderColorA")
        {
            _args.pop_front();
            if(*_args.begin() == "set")
            {
                _args.pop_front();
                dLink->settings.guiHorsliderButtonBorderActive = util::toColor(*_args.begin());
            }
            else if (*_args.begin() == "get")
            {
                std::list<std::string> x;
                x.push_back("settings");
                x.push_back("guiHorsliderButtonBorderColorA");
                x.push_back("get");
                x.push_back(util::toString(dLink->settings.guiHorsliderButtonBorderActive));
                dLink->pushEvent(x);
            }
        }
        else if(*_args.begin() == "guiHorsliderBarBackgroundColorB")
        {
            _args.pop_front();
            if(*_args.begin() == "set")
            {
                _args.pop_front();
                dLink->settings.guiHorsliderBarBackgroundInactive = util::toColor(*_args.begin());
            }
            else if (*_args.begin() == "get")
            {
                std::list<std::string> x;
                x.push_back("settings");
                x.push_back("guiHorsliderBarBackgroundColorB");
                x.push_back("get");
                x.push_back(util::toString(dLink->settings.guiHorsliderBarBackgroundInactive));
                dLink->pushEvent(x);
            }
        }
        else if(*_args.begin() == "guiHorsliderBarBackgroundColorA")
        {
            _args.pop_front();
            if(*_args.begin() == "set")
            {
                _args.pop_front();
                dLink->settings.guiHorsliderBarBackgroundActive = util::toColor(*_args.begin());
            }
            else if (*_args.begin() == "get")
            {
                std::list<std::string> x;
                x.push_back("settings");
                x.push_back("guiHorsliderBarBackgroundColorA");
                x.push_back("get");
                x.push_back(util::toString(dLink->settings.guiHorsliderBarBackgroundActive));
                dLink->pushEvent(x);
            }
        }
        else if(*_args.begin() == "guiHorsliderBarBorderColorB")
        {
            _args.pop_front();
            if(*_args.begin() == "set")
            {
                _args.pop_front();
                dLink->settings.guiHorsliderBarBorderInactive = util::toColor(*_args.begin());
            }
            else if (*_args.begin() == "get")
            {
                std::list<std::string> x;
                x.push_back("settings");
                x.push_back("guiHorsliderBarBorderColorB");
                x.push_back("get");
                x.push_back(util::toString(dLink->settings.guiHorsliderBarBorderInactive));
                dLink->pushEvent(x);
            }
        }
        else if(*_args.begin() == "guiHorsliderBarBorderColorA")
        {
            _args.pop_front();
            if(*_args.begin() == "set")
            {
                _args.pop_front();
                dLink->settings.guiHorsliderBarBorderActive = util::toColor(*_args.begin());
            }
            else if (*_args.begin() == "get")
            {
                std::list<std::string> x;
                x.push_back("settings");
                x.push_back("guiHorsliderBarBorderColorA");
                x.push_back("get");
                x.push_back(util::toString(dLink->settings.guiHorsliderBarBorderActive));
                dLink->pushEvent(x);
            }
        }
        else if(*_args.begin() == "guiHorsliderSliderBackgroundColorD")
        {
            _args.pop_front();
            if(*_args.begin() == "set")
            {
                _args.pop_front();
                dLink->settings.guiHorsliderSliderBackgroundMoving = util::toColor(*_args.begin());
            }
            else if (*_args.begin() == "get")
            {
                std::list<std::string> x;
                x.push_back("settings");
                x.push_back("guiHorsliderSliderBackgroundColorD");
                x.push_back("get");
                x.push_back(util::toString(dLink->settings.guiHorsliderSliderBackgroundMoving));
                dLink->pushEvent(x);
            }
        }
        else if(*_args.begin() == "guiHorsliderSliderBackgroundColorC")
        {
            _args.pop_front();
            if(*_args.begin() == "set")
            {
                _args.pop_front();
                dLink->settings.guiHorsliderSliderBackgroundHover = util::toColor(*_args.begin());
            }
            else if (*_args.begin() == "get")
            {
                std::list<std::string> x;
                x.push_back("settings");
                x.push_back("guiHorsliderSliderBackgroundColorC");
                x.push_back("get");
                x.push_back(util::toString(dLink->settings.guiHorsliderSliderBackgroundHover));
                dLink->pushEvent(x);
            }
        }
        else if(*_args.begin() == "guiHorsliderSliderBackgroundColorB")
        {
            _args.pop_front();
            if(*_args.begin() == "set")
            {
                _args.pop_front();
                dLink->settings.guiHorsliderSliderBackgroundInactive = util::toColor(*_args.begin());
            }
            else if (*_args.begin() == "get")
            {
                std::list<std::string> x;
                x.push_back("settings");
                x.push_back("guiHorsliderSliderBackgroundColorB");
                x.push_back("get");
                x.push_back(util::toString(dLink->settings.guiHorsliderSliderBackgroundInactive));
                dLink->pushEvent(x);
            }
        }
        else if(*_args.begin() == "guiHorsliderSliderBackgroundColorA")
        {
            _args.pop_front();
            if(*_args.begin() == "set")
            {
                _args.pop_front();
                dLink->settings.guiHorsliderSliderBackgroundActive = util::toColor(*_args.begin());
            }
            else if (*_args.begin() == "get")
            {
                std::list<std::string> x;
                x.push_back("settings");
                x.push_back("guiHorsliderSliderBackgroundColorA");
                x.push_back("get");
                x.push_back(util::toString(dLink->settings.guiHorsliderSliderBackgroundActive));
                dLink->pushEvent(x);
            }
        }
        else if(*_args.begin() == "guiHorsliderSliderBorderColorD")
        {
            _args.pop_front();
            if(*_args.begin() == "set")
            {
                _args.pop_front();
                dLink->settings.guiHorsliderSliderBorderMoving = util::toColor(*_args.begin());
            }
            else if (*_args.begin() == "get")
            {
                std::list<std::string> x;
                x.push_back("settings");
                x.push_back("guiHorsliderSliderBorderColorD");
                x.push_back("get");
                x.push_back(util::toString(dLink->settings.guiHorsliderSliderBorderMoving));
                dLink->pushEvent(x);
            }
        }
        else if(*_args.begin() == "guiHorsliderSliderBorderColorC")
        {
            _args.pop_front();
            if(*_args.begin() == "set")
            {
                _args.pop_front();
                dLink->settings.guiHorsliderSliderBorderHover = util::toColor(*_args.begin());
            }
            else if (*_args.begin() == "get")
            {
                std::list<std::string> x;
                x.push_back("settings");
                x.push_back("guiHorsliderSliderBorderColorC");
                x.push_back("get");
                x.push_back(util::toString(dLink->settings.guiHorsliderSliderBorderHover));
                dLink->pushEvent(x);
            }
        }
        else if(*_args.begin() == "guiHorsliderSliderBorderColorB")
        {
            _args.pop_front();
            if(*_args.begin() == "set")
            {
                _args.pop_front();
                dLink->settings.guiHorsliderSliderBorderInactive = util::toColor(*_args.begin());
            }
            else if (*_args.begin() == "get")
            {
                std::list<std::string> x;
                x.push_back("settings");
                x.push_back("guiHorsliderSliderBorderColorB");
                x.push_back("get");
                x.push_back(util::toString(dLink->settings.guiHorsliderSliderBorderInactive));
                dLink->pushEvent(x);
            }
        }
        else if(*_args.begin() == "guiHorsliderSliderBorderColorA")
        {
            _args.pop_front();
            if(*_args.begin() == "set")
            {
                _args.pop_front();
                dLink->settings.guiHorsliderSliderBorderActive = util::toColor(*_args.begin());
            }
            else if (*_args.begin() == "get")
            {
                std::list<std::string> x;
                x.push_back("settings");
                x.push_back("guiHorsliderSliderBorderColorA");
                x.push_back("get");
                x.push_back(util::toString(dLink->settings.guiHorsliderSliderBorderActive));
                dLink->pushEvent(x);
            }
        }
        else if(*_args.begin() == "guiVertsliderButtonBackgroundColorC")
        {
            _args.pop_front();
            if(*_args.begin() == "set")
            {
                _args.pop_front();
                dLink->settings.guiVertsliderButtonBackgroundHover = util::toColor(*_args.begin());
            }
            else if (*_args.begin() == "get")
            {
                std::list<std::string> x;
                x.push_back("settings");
                x.push_back("guiVertsliderButtonBackgroundColorC");
                x.push_back("get");
                x.push_back(util::toString(dLink->settings.guiVertsliderButtonBackgroundHover));
                dLink->pushEvent(x);
            }
        }
        else if(*_args.begin() == "guiVertsliderButtonBackgroundColorB")
        {
            _args.pop_front();
            if(*_args.begin() == "set")
            {
                _args.pop_front();
                dLink->settings.guiVertsliderButtonBackgroundInactive = util::toColor(*_args.begin());
            }
            else if (*_args.begin() == "get")
            {
                std::list<std::string> x;
                x.push_back("settings");
                x.push_back("guiVertsliderButtonBackgroundColorB");
                x.push_back("get");
                x.push_back(util::toString(dLink->settings.guiVertsliderButtonBackgroundInactive));
                dLink->pushEvent(x);
            }
        }
        else if(*_args.begin() == "guiVertsliderButtonBackgroundColorA")
        {
            _args.pop_front();
            if(*_args.begin() == "set")
            {
                _args.pop_front();
                dLink->settings.guiVertsliderButtonBackgroundActive = util::toColor(*_args.begin());
            }
            else if (*_args.begin() == "get")
            {
                std::list<std::string> x;
                x.push_back("settings");
                x.push_back("guiVertsliderButtonBackgroundColorA");
                x.push_back("get");
                x.push_back(util::toString(dLink->settings.guiVertsliderButtonBackgroundActive));
                dLink->pushEvent(x);
            }
        }
        else if(*_args.begin() == "guiVertsliderButtonBorderColorC")
        {
            _args.pop_front();
            if(*_args.begin() == "set")
            {
                _args.pop_front();
                dLink->settings.guiVertsliderButtonBorderHover = util::toColor(*_args.begin());
            }
            else if (*_args.begin() == "get")
            {
                std::list<std::string> x;
                x.push_back("settings");
                x.push_back("guiVertsliderButtonBorderColorC");
                x.push_back("get");
                x.push_back(util::toString(dLink->settings.guiVertsliderButtonBorderHover));
                dLink->pushEvent(x);
            }
        }
        else if(*_args.begin() == "guiVertsliderButtonBorderColorB")
        {
            _args.pop_front();
            if(*_args.begin() == "set")
            {
                _args.pop_front();
                dLink->settings.guiVertsliderButtonBorderInactive = util::toColor(*_args.begin());
            }
            else if (*_args.begin() == "get")
            {
                std::list<std::string> x;
                x.push_back("settings");
                x.push_back("guiVertsliderButtonBorderColorB");
                x.push_back("get");
                x.push_back(util::toString(dLink->settings.guiVertsliderButtonBorderInactive));
                dLink->pushEvent(x);
            }
        }
        else if(*_args.begin() == "guiVertsliderButtonBorderColorA")
        {
            _args.pop_front();
            if(*_args.begin() == "set")
            {
                _args.pop_front();
                dLink->settings.guiVertsliderButtonBorderActive = util::toColor(*_args.begin());
            }
            else if (*_args.begin() == "get")
            {
                std::list<std::string> x;
                x.push_back("settings");
                x.push_back("guiVertsliderButtonBorderColorA");
                x.push_back("get");
                x.push_back(util::toString(dLink->settings.guiVertsliderButtonBorderActive));
                dLink->pushEvent(x);
            }
        }
        else if(*_args.begin() == "guiVertsliderBarBackgroundColorB")
        {
            _args.pop_front();
            if(*_args.begin() == "set")
            {
                _args.pop_front();
                dLink->settings.guiVertsliderBarBackgroundInactive = util::toColor(*_args.begin());
            }
            else if (*_args.begin() == "get")
            {
                std::list<std::string> x;
                x.push_back("settings");
                x.push_back("guiVertsliderBarBackgroundColorB");
                x.push_back("get");
                x.push_back(util::toString(dLink->settings.guiVertsliderBarBackgroundInactive));
                dLink->pushEvent(x);
            }
        }
        else if(*_args.begin() == "guiVertsliderBarBackgroundColorA")
        {
            _args.pop_front();
            if(*_args.begin() == "set")
            {
                _args.pop_front();
                dLink->settings.guiVertsliderBarBackgroundActive = util::toColor(*_args.begin());
            }
            else if (*_args.begin() == "get")
            {
                std::list<std::string> x;
                x.push_back("settings");
                x.push_back("guiVertsliderBarBackgroundColorA");
                x.push_back("get");
                x.push_back(util::toString(dLink->settings.guiVertsliderBarBackgroundActive));
                dLink->pushEvent(x);
            }
        }
        else if(*_args.begin() == "guiVertsliderBarBorderColorB")
        {
            _args.pop_front();
            if(*_args.begin() == "set")
            {
                _args.pop_front();
                dLink->settings.guiVertsliderBarBorderInactive = util::toColor(*_args.begin());
            }
            else if (*_args.begin() == "get")
            {
                std::list<std::string> x;
                x.push_back("settings");
                x.push_back("guiVertsliderBarBorderColorB");
                x.push_back("get");
                x.push_back(util::toString(dLink->settings.guiVertsliderBarBorderInactive));
                dLink->pushEvent(x);
            }
        }
        else if(*_args.begin() == "guiVertsliderBarBorderColorA")
        {
            _args.pop_front();
            if(*_args.begin() == "set")
            {
                _args.pop_front();
                dLink->settings.guiVertsliderBarBorderActive = util::toColor(*_args.begin());
            }
            else if (*_args.begin() == "get")
            {
                std::list<std::string> x;
                x.push_back("settings");
                x.push_back("guiVertsliderBarBorderColorA");
                x.push_back("get");
                x.push_back(util::toString(dLink->settings.guiVertsliderBarBorderActive));
                dLink->pushEvent(x);
            }
        }
        else if(*_args.begin() == "guiVertsliderSliderBackgroundColorD")
        {
            _args.pop_front();
            if(*_args.begin() == "set")
            {
                _args.pop_front();
                dLink->settings.guiVertsliderSliderBackgroundMoving = util::toColor(*_args.begin());
            }
            else if (*_args.begin() == "get")
            {
                std::list<std::string> x;
                x.push_back("settings");
                x.push_back("guiVertsliderSliderBackgroundColorD");
                x.push_back("get");
                x.push_back(util::toString(dLink->settings.guiVertsliderSliderBackgroundMoving));
                dLink->pushEvent(x);
            }
        }
        else if(*_args.begin() == "guiVertsliderSliderBackgroundColorC")
        {
            _args.pop_front();
            if(*_args.begin() == "set")
            {
                _args.pop_front();
                dLink->settings.guiVertsliderSliderBackgroundHover = util::toColor(*_args.begin());
            }
            else if (*_args.begin() == "get")
            {
                std::list<std::string> x;
                x.push_back("settings");
                x.push_back("guiVertsliderSliderBackgroundColorC");
                x.push_back("get");
                x.push_back(util::toString(dLink->settings.guiVertsliderSliderBackgroundHover));
                dLink->pushEvent(x);
            }
        }
        else if(*_args.begin() == "guiVertsliderSliderBackgroundColorB")
        {
            _args.pop_front();
            if(*_args.begin() == "set")
            {
                _args.pop_front();
                dLink->settings.guiVertsliderSliderBackgroundInactive = util::toColor(*_args.begin());
            }
            else if (*_args.begin() == "get")
            {
                std::list<std::string> x;
                x.push_back("settings");
                x.push_back("guiVertsliderSliderBackgroundColorB");
                x.push_back("get");
                x.push_back(util::toString(dLink->settings.guiVertsliderSliderBackgroundInactive));
                dLink->pushEvent(x);
            }
        }
        else if(*_args.begin() == "guiVertsliderSliderBackgroundColorA")
        {
            _args.pop_front();
            if(*_args.begin() == "set")
            {
                _args.pop_front();
                dLink->settings.guiVertsliderSliderBackgroundActive = util::toColor(*_args.begin());
            }
            else if (*_args.begin() == "get")
            {
                std::list<std::string> x;
                x.push_back("settings");
                x.push_back("guiVertsliderSliderBackgroundColorA");
                x.push_back("get");
                x.push_back(util::toString(dLink->settings.guiVertsliderSliderBackgroundActive));
                dLink->pushEvent(x);
            }
        }
        else if(*_args.begin() == "guiVertsliderSliderBorderColorD")
        {
            _args.pop_front();
            if(*_args.begin() == "set")
            {
                _args.pop_front();
                dLink->settings.guiVertsliderSliderBorderMoving = util::toColor(*_args.begin());
            }
            else if (*_args.begin() == "get")
            {
                std::list<std::string> x;
                x.push_back("settings");
                x.push_back("guiVertsliderSliderBorderColorD");
                x.push_back("get");
                x.push_back(util::toString(dLink->settings.guiVertsliderSliderBorderMoving));
                dLink->pushEvent(x);
            }
        }
        else if(*_args.begin() == "guiVertsliderSliderBorderColorC")
        {
            _args.pop_front();
            if(*_args.begin() == "set")
            {
                _args.pop_front();
                dLink->settings.guiVertsliderSliderBorderHover = util::toColor(*_args.begin());
            }
            else if (*_args.begin() == "get")
            {
                std::list<std::string> x;
                x.push_back("settings");
                x.push_back("guiVertsliderSliderBorderColorC");
                x.push_back("get");
                x.push_back(util::toString(dLink->settings.guiVertsliderSliderBorderHover));
                dLink->pushEvent(x);
            }
        }
        else if(*_args.begin() == "guiVertsliderSliderBorderColorB")
        {
            _args.pop_front();
            if(*_args.begin() == "set")
            {
                _args.pop_front();
                dLink->settings.guiVertsliderSliderBorderInactive = util::toColor(*_args.begin());
            }
            else if (*_args.begin() == "get")
            {
                std::list<std::string> x;
                x.push_back("settings");
                x.push_back("guiVertsliderSliderBorderColorB");
                x.push_back("get");
                x.push_back(util::toString(dLink->settings.guiVertsliderSliderBorderInactive));
                dLink->pushEvent(x);
            }
        }
        else if(*_args.begin() == "guiVertsliderSliderBorderColorA")
        {
            _args.pop_front();
            if(*_args.begin() == "set")
            {
                _args.pop_front();
                dLink->settings.guiVertsliderSliderBorderActive = util::toColor(*_args.begin());
            }
            else if (*_args.begin() == "get")
            {
                std::list<std::string> x;
                x.push_back("settings");
                x.push_back("guiVertsliderSliderBorderColorA");
                x.push_back("get");
                x.push_back(util::toString(dLink->settings.guiVertsliderSliderBorderActive));
                dLink->pushEvent(x);
            }
        }
        else if(*_args.begin() == "guiLabelTextColorC")
        {
            _args.pop_front();
            if(*_args.begin() == "set")
            {
                _args.pop_front();
                dLink->settings.guiLabelTextHover = util::toColor(*_args.begin());
            }
            else if (*_args.begin() == "get")
            {
                std::list<std::string> x;
                x.push_back("settings");
                x.push_back("guiLabelTextColorC");
                x.push_back("get");
                x.push_back(util::toString(dLink->settings.guiLabelTextHover));
                dLink->pushEvent(x);
            }
        }
        else if(*_args.begin() == "guiLabelTextColorB")
        {
            _args.pop_front();
            if(*_args.begin() == "set")
            {
                _args.pop_front();
                dLink->settings.guiLabelTextInactive = util::toColor(*_args.begin());
            }
            else if (*_args.begin() == "get")
            {
                std::list<std::string> x;
                x.push_back("settings");
                x.push_back("guiLabelTextColorB");
                x.push_back("get");
                x.push_back(util::toString(dLink->settings.guiLabelTextInactive));
                dLink->pushEvent(x);
            }
        }
        else if(*_args.begin() == "guiLabelTextColorA")
        {
            _args.pop_front();
            if(*_args.begin() == "set")
            {
                _args.pop_front();
                dLink->settings.guiLabelTextActive = util::toColor(*_args.begin());
            }
            else if (*_args.begin() == "get")
            {
                std::list<std::string> x;
                x.push_back("settings");
                x.push_back("guiLabelTextColorA");
                x.push_back("get");
                x.push_back(util::toString(dLink->settings.guiLabelTextActive));
                dLink->pushEvent(x);
            }
        }
        else if(*_args.begin() == "guiTextboxBackgroundColorC")
        {
            _args.pop_front();
            if(*_args.begin() == "set")
            {
                _args.pop_front();
                dLink->settings.guiTextboxBackgroundHover = util::toColor(*_args.begin());
            }
            else if (*_args.begin() == "get")
            {
                std::list<std::string> x;
                x.push_back("settings");
                x.push_back("guiTextboxBackgroundColorC");
                x.push_back("get");
                x.push_back(util::toString(dLink->settings.guiTextboxBackgroundHover));
                dLink->pushEvent(x);
            }
        }
        else if(*_args.begin() == "guiTextboxBackgroundColorB")
        {
            _args.pop_front();
            if(*_args.begin() == "set")
            {
                _args.pop_front();
                dLink->settings.guiTextboxBackgroundInactive = util::toColor(*_args.begin());
            }
            else if (*_args.begin() == "get")
            {
                std::list<std::string> x;
                x.push_back("settings");
                x.push_back("guiTextboxBackgroundColorB");
                x.push_back("get");
                x.push_back(util::toString(dLink->settings.guiTextboxBackgroundInactive));
                dLink->pushEvent(x);
            }
        }
        else if(*_args.begin() == "guiTextboxBackgroundColorA")
        {
            _args.pop_front();
            if(*_args.begin() == "set")
            {
                _args.pop_front();
                dLink->settings.guiTextboxBackgroundActive = util::toColor(*_args.begin());
            }
            else if (*_args.begin() == "get")
            {
                std::list<std::string> x;
                x.push_back("settings");
                x.push_back("guiTextboxBackgroundColorA");
                x.push_back("get");
                x.push_back(util::toString(dLink->settings.guiTextboxBackgroundActive));
                dLink->pushEvent(x);
            }
        }
        else if(*_args.begin() == "guiTextboxBorderColorC")
        {
            _args.pop_front();
            if(*_args.begin() == "set")
            {
                _args.pop_front();
                dLink->settings.guiTextboxBorderHover = util::toColor(*_args.begin());
            }
            else if (*_args.begin() == "get")
            {
                std::list<std::string> x;
                x.push_back("settings");
                x.push_back("guiTextboxBorderColorC");
                x.push_back("get");
                x.push_back(util::toString(dLink->settings.guiTextboxBorderHover));
                dLink->pushEvent(x);
            }
        }
        else if(*_args.begin() == "guiTextboxBorderColorB")
        {
            _args.pop_front();
            if(*_args.begin() == "set")
            {
                _args.pop_front();
                dLink->settings.guiTextboxBorderInactive = util::toColor(*_args.begin());
            }
            else if (*_args.begin() == "get")
            {
                std::list<std::string> x;
                x.push_back("settings");
                x.push_back("guiTextboxBorderColorB");
                x.push_back("get");
                x.push_back(util::toString(dLink->settings.guiTextboxBorderInactive));
                dLink->pushEvent(x);
            }
        }
        else if(*_args.begin() == "guiTextboxBorderColorA")
        {
            _args.pop_front();
            if(*_args.begin() == "set")
            {
                _args.pop_front();
                dLink->settings.guiTextboxBorderActive = util::toColor(*_args.begin());
            }
            else if (*_args.begin() == "get")
            {
                std::list<std::string> x;
                x.push_back("settings");
                x.push_back("guiTextboxBorderColorA");
                x.push_back("get");
                x.push_back(util::toString(dLink->settings.guiTextboxBorderActive));
                dLink->pushEvent(x);
            }
        }
        else if(*_args.begin() == "guiMenuTitleTextScale")
        {
            _args.pop_front();
            if(*_args.begin() == "set")
            {
                _args.pop_front();
                dLink->settings.guiMenuTitleTextScale = util::toInt(*_args.begin());
            }
            else if (*_args.begin() == "get")
            {
                std::list<std::string> x;
                x.push_back("settings");
                x.push_back("guiMenuTitleTextScale");
                x.push_back("get");
                x.push_back(util::toString(dLink->settings.guiMenuTitleTextScale));
                dLink->pushEvent(x);
            }
        }
        else if(*_args.begin() == "guiButtonTextScale")
        {
            _args.pop_front();
            if(*_args.begin() == "set")
            {
                _args.pop_front();
                dLink->settings.guiButtonTextScale = util::toInt(*_args.begin());
            }
            else if (*_args.begin() == "get")
            {
                std::list<std::string> x;
                x.push_back("settings");
                x.push_back("guiButtonTextScale");
                x.push_back("get");
                x.push_back(util::toString(dLink->settings.guiButtonTextScale));
                dLink->pushEvent(x);
            }
        }
        else if(*_args.begin() == "guiHorsliderTextScale")
        {
            _args.pop_front();
            if(*_args.begin() == "set")
            {
                _args.pop_front();
                dLink->settings.guiHorsliderTextScale = util::toInt(*_args.begin());
            }
            else if (*_args.begin() == "get")
            {
                std::list<std::string> x;
                x.push_back("settings");
                x.push_back("guiHorsliderTextScale");
                x.push_back("get");
                x.push_back(util::toString(dLink->settings.guiHorsliderTextScale));
                dLink->pushEvent(x);
            }
        }
        else if(*_args.begin() == "guiVertsliderTextScale")
        {
            _args.pop_front();
            if(*_args.begin() == "set")
            {
                _args.pop_front();
                dLink->settings.guiVertsliderTextScale = util::toInt(*_args.begin());
            }
            else if (*_args.begin() == "get")
            {
                std::list<std::string> x;
                x.push_back("settings");
                x.push_back("guiVertsliderTextScale");
                x.push_back("get");
                x.push_back(util::toString(dLink->settings.guiVertsliderTextScale));
                dLink->pushEvent(x);
            }
        }
        else if(*_args.begin() == "guiLabelTextScale")
        {
            _args.pop_front();
            if(*_args.begin() == "set")
            {
                _args.pop_front();
                dLink->settings.guiLabelTextScale = util::toInt(*_args.begin());
            }
            else if (*_args.begin() == "get")
            {
                std::list<std::string> x;
                x.push_back("settings");
                x.push_back("guiLabelTextScale");
                x.push_back("get");
                x.push_back(util::toString(dLink->settings.guiLabelTextScale));
                dLink->pushEvent(x);
            }
        }
        else if(*_args.begin() == "guiTextboxTextScale")
        {
            _args.pop_front();
            if(*_args.begin() == "set")
            {
                _args.pop_front();
                dLink->settings.guiTextboxTextScale = util::toInt(*_args.begin());
            }
            else if (*_args.begin() == "get")
            {
                std::list<std::string> x;
                x.push_back("settings");
                x.push_back("guiTextboxTextScale");
                x.push_back("get");
                x.push_back(util::toString(dLink->settings.guiTextboxTextScale));
                dLink->pushEvent(x);
            }
        }
        else if(*_args.begin() == "guiMenuTitleFontID")
        {
            _args.pop_front();
            if(*_args.begin() == "set")
            {
                _args.pop_front();
                dLink->settings.guiMenuTitleFontID = *_args.begin();
            }
            else if (*_args.begin() == "get")
            {
                std::list<std::string> x;
                x.push_back("settings");
                x.push_back("guiMenuTitleFontID");
                x.push_back("get");
                x.push_back(dLink->settings.guiMenuTitleFontID);
                dLink->pushEvent(x);
            }
        }
        else if(*_args.begin() == "guiButtonFontID")
        {
            _args.pop_front();
            if(*_args.begin() == "set")
            {
                _args.pop_front();
                dLink->settings.guiButtonFontID = *_args.begin();
            }
            else if (*_args.begin() == "get")
            {
                std::list<std::string> x;
                x.push_back("settings");
                x.push_back("guiButtonFontID");
                x.push_back("get");
                x.push_back(dLink->settings.guiButtonFontID);
                dLink->pushEvent(x);
            }
        }
        else if(*_args.begin() == "guiHorsliderFontID")
        {
            _args.pop_front();
            if(*_args.begin() == "set")
            {
                _args.pop_front();
                dLink->settings.guiHorsliderFontID = *_args.begin();
            }
            else if (*_args.begin() == "get")
            {
                std::list<std::string> x;
                x.push_back("settings");
                x.push_back("guiHorsliderFontID");
                x.push_back("get");
                x.push_back(dLink->settings.guiHorsliderFontID);
                dLink->pushEvent(x);
            }
        }
        else if(*_args.begin() == "guiVertsliderFontID")
        {
            _args.pop_front();
            if(*_args.begin() == "set")
            {
                _args.pop_front();
                dLink->settings.guiVertsliderFontID = *_args.begin();
            }
            else if (*_args.begin() == "get")
            {
                std::list<std::string> x;
                x.push_back("settings");
                x.push_back("guiVertsliderFontID");
                x.push_back("get");
                x.push_back(dLink->settings.guiVertsliderFontID);
                dLink->pushEvent(x);
            }
        }
        else if(*_args.begin() == "guiLabelFontID")
        {
            _args.pop_front();
            if(*_args.begin() == "set")
            {
                _args.pop_front();
                dLink->settings.guiLabelFontID = *_args.begin();
            }
            else if (*_args.begin() == "get")
            {
                std::list<std::string> x;
                x.push_back("settings");
                x.push_back("guiLabelFontID");
                x.push_back("get");
                x.push_back(dLink->settings.guiLabelFontID);
                dLink->pushEvent(x);
            }
        }
        else if(*_args.begin() == "guiTextboxFontID")
        {
            _args.pop_front();
            if(*_args.begin() == "set")
            {
                _args.pop_front();
                dLink->settings.guiTextboxFontID = *_args.begin();
            }
            else if (*_args.begin() == "get")
            {
                std::list<std::string> x;
                x.push_back("settings");
                x.push_back("guiTextboxFontID");
                x.push_back("get");
                x.push_back(dLink->settings.guiTextboxFontID);
                dLink->pushEvent(x);
            }
        }
    }
    else if(*_args.begin() == "resource") //resource
    {
        _args.pop_front();
        if(*_args.begin() == "texture")
        {
            _args.pop_front();
            if(*_args.begin() == "register")
            {
                _args.pop_front();
                std::string id = *_args.begin();
                _args.pop_front();
                dLink->TextureRegister(id, *_args.begin());
            }
            else if(*_args.begin() == "erase")
            {
                _args.pop_front();
                dLink->TextureErase(*_args.begin());
            }
            else if(*_args.begin() == "load")
            {
                _args.pop_front();
                dLink->TextureLoad(*_args.begin());
            }
            else if(*_args.begin() == "unload")
            {
                _args.pop_front();
                dLink->TextureUnload(*_args.begin());
            }
        }
        else if(*_args.begin() == "sound")
        {
            _args.pop_front();
            if(*_args.begin() == "register")
            {
                _args.pop_front();
                std::string id = *_args.begin();
                _args.pop_front();
                dLink->SoundRegister(id, *_args.begin());
            }
            else if(*_args.begin() == "erase")
            {
                _args.pop_front();
                dLink->SoundErase(*_args.begin());
            }
            else if(*_args.begin() == "load")
            {
                _args.pop_front();
                dLink->SoundLoad(*_args.begin());
            }
            else if(*_args.begin() == "unload")
            {
                _args.pop_front();
                dLink->SoundUnload(*_args.begin());
            }
        }
        else if(*_args.begin() == "font")
        {
            _args.pop_front();
            if(*_args.begin() == "register")
            {
                _args.pop_front();
                std::string id = *_args.begin();
                _args.pop_front();
                dLink->FontRegister(id, *_args.begin());
            }
            else if(*_args.begin() == "erase")
            {
                _args.pop_front();
                dLink->FontErase(*_args.begin());
            }
            else if(*_args.begin() == "load")
            {
                _args.pop_front();
                dLink->FontLoad(*_args.begin());
            }
            else if(*_args.begin() == "unload")
            {
                _args.pop_front();
                dLink->FontUnload(*_args.begin());
            }
        }
        else if(*_args.begin() == "track")
        {
            _args.pop_front();
            if(*_args.begin() == "register")
            {
                _args.pop_front();
                std::string id = *_args.begin();
                _args.pop_front();
                dLink->TrackRegister(id, *_args.begin());
            }
            else if(*_args.begin() == "erase")
            {
                _args.pop_front();
                dLink->TrackErase(*_args.begin());
            }
            else if(*_args.begin() == "load")
            {
                _args.pop_front();
                dLink->TrackLoad(*_args.begin());
            }
            else if(*_args.begin() == "unload")
            {
                _args.pop_front();
                dLink->TrackUnload(*_args.begin());
            }
        }
    }
    else if(*_args.begin() == "delay")
    {
        _args.pop_front();
        ASync x;
        x.target = util::toInt(*_args.begin());
        _args.pop_front();
        x.time.restart();
        x.task = _args;
        waitingTasks.push_back(x);
    }
}
