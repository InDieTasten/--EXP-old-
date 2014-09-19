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
                                                x.push_back(util::toString(counter)); counter++;
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
                                                x.push_back(util::toString(counter)); counter++;
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
                                                x.push_back(util::toString(counter)); counter++;
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
                                                x.push_back(util::toString(counter)); counter++;
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
                                                    x.push_back(util::toString(counter)); counter++;
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
                                                    x.push_back(util::toString(counter)); counter++;
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
                                                    x.push_back(util::toString(counter)); counter++;
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
                                                    x.push_back(util::toString(counter)); counter++;
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
                                                    x.push_back(util::toString(counter)); counter++;
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
                                                    x.push_back(util::toString(counter)); counter++;
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
                                                    x.push_back(util::toString(counter)); counter++;
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
                                                    x.push_back(util::toString(counter)); counter++;
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
                                                    x.push_back(util::toString(counter)); counter++;
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
                                                    x.push_back(util::toString(counter)); counter++;
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
                                                    x.push_back(util::toString(counter)); counter++;
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
                                                    x.push_back(util::toString(counter)); counter++;
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
                                                    x.push_back(util::toString(counter)); counter++;
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
                                                    x.push_back(util::toString(counter)); counter++;
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
                                                    x.push_back(util::toString(counter)); counter++;
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
                                                    x.push_back(util::toString(counter)); counter++;
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
                                                    x.push_back(util::toString(counter)); counter++;
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
                                                    x.push_back(util::toString(counter)); counter++;
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
                                                    x.push_back(util::toString(counter)); counter++;
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
                                                    x.push_back(util::toString(counter)); counter++;
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
                                                    x.push_back(util::toString(counter)); counter++;
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
                                                    x.push_back(util::toString(counter)); counter++;
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
                                                    x.push_back(util::toString(counter)); counter++;
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
                                                    x.push_back(util::toString(counter)); counter++;
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
                                                    x.push_back(util::toString(counter)); counter++;
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
                                                    x.push_back(util::toString(counter)); counter++;
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
                                                    x.push_back(util::toString(counter)); counter++;
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
                                                    x.push_back(util::toString(counter)); counter++;
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
                                                    x.push_back(util::toString(counter)); counter++;
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
                                                    x.push_back(util::toString(counter)); counter++;
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
                                                    x.push_back(util::toString(counter)); counter++;
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
                                                    x.push_back(util::toString(counter)); counter++;
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
                                                    x.push_back(util::toString(counter)); counter++;
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
                                                    x.push_back(util::toString(counter)); counter++;
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
                                                    x.push_back(util::toString(counter)); counter++;
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
                                                    x.push_back(util::toString(counter)); counter++;
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
                                                    x.push_back(util::toString(counter)); counter++;
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
                                                    x.push_back(util::toString(counter)); counter++;
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
                                                    x.push_back(util::toString(counter)); counter++;
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
                                                    x.push_back(util::toString(counter)); counter++;
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
                                                    x.push_back(util::toString(counter)); counter++;
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
                                                    x.push_back(util::toString(counter)); counter++;
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
                                                    x.push_back(util::toString(counter)); counter++;
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
                                                    x.push_back(util::toString(counter)); counter++;
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
                                            else if(elem->Type == "horSlider")
                                            {

                                            }
                                        }
                                        else if(*_args.begin() == "action") // gui menu access {ID} element access {ID} action
                                        {

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
    else if(*_args.begin() == "resource") //resource
    {
        _args.pop_front();
    }
}
