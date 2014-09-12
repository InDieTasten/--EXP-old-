#include "GUIManager.hpp"
//CONSTRUCTORS
GUIManager::GUIManager()
{
    dockWidth = 68;
    add_StockButton();
    add_MainMenu();
    add_OptionMenu();
    add_ConsoleMenu();
    add_CodeIDE();
}
//DESTRUCTORS

//METHODS

void GUIManager::AddDockItem(std::string _itemid)
{
    for(std::list<GUIDockItem>::iterator it = dockButtons.begin(); it != dockButtons.end(); it++)
    {
        if(it->ID == _itemid)
        {
            //Fehler
            return;
        }
    }
    dockButtons.push_back(GUIDockItem(_itemid,"$_missing"));
}
void GUIManager::EditDockItemImage(std::string _itemid, std::string _imageid)
{
    for(std::list<GUIDockItem>::iterator it = dockButtons.begin(); it != dockButtons.end(); it++)
    {
        if(it->ID == _itemid)
        {
            it->ImageID = _imageid;
            return;
        }
    }
}

void GUIManager::handleEvent(sf::Event *_event)
{
    if(_event->type == sf::Event::MouseMoved)
    {
        int x,y;
        x = _event->mouseMove.x;
        y = _event->mouseMove.y;
        int i = 0;
        for(std::list<GUIDockItem>::iterator it = dockButtons.begin(); it != dockButtons.end(); it++)
        {
            if (x >= 1 && x <= dockWidth && y >= (i*(dockWidth+1)+2) && y <= ((i+1)*dockWidth+i))
            {
                if(!it->mouseHover)
                {
                    std::list<std::string> e;
                    e.push_back("dock_enter");
                    e.push_back(it->ID);
                    dLink->pushEvent(e);
                }
                it->mouseHover = true;
            }
            else
            {
                if(it->mouseHover)
                {
                    std::list<std::string> e;
                    e.push_back("dock_leave");
                    e.push_back(it->ID);
                    dLink->pushEvent(e);
                }
                it->mouseHover = false;
            }
            i++;
        }
    }
    if(_event->type == sf::Event::MouseButtonPressed)
    {
        for(std::list<GUIDockItem>::iterator it = dockButtons.begin(); it != dockButtons.end(); it++)
        {
            if(it->mouseHover)
            {
                std::list<std::string> e;
                e.push_back("dock_pressed");
                e.push_back(it->ID);
                dLink->pushEvent(e);
            }
        }
        for(std::list<GUIMenu>::iterator it = guiMenus.begin(); it != guiMenus.end(); it++)
        {
            if(it->isHit(_event->mouseButton.x, _event->mouseButton.y))
            {
                if(!it->isActive)
                {
                    for(std::list<GUIMenu>::iterator it2 = guiMenus.begin(); it2 != guiMenus.end(); it2++)
                    {
                        it2->isActive = false;
                    }
                    it->isActive = true;
                }
            }
        }
        for(std::list<GUIMenu>::iterator it = guiMenus.begin(); it != guiMenus.end(); it++)
        {
            if(it->isActive)
            {
                guiMenus.splice(guiMenus.end(), guiMenus, it);
            }
        }
    }
    if(_event->type == sf::Event::MouseButtonReleased)
    {
        for(std::list<GUIDockItem>::iterator it = dockButtons.begin(); it != dockButtons.end(); it++)
        {
            if(it->mouseHover)
            {
                std::list<std::string> e;
                e.push_back("dock_released");
                e.push_back(it->ID);
                dLink->pushEvent(e);
            }
        }
    }
    for(std::list<GUIMenu>::iterator it = guiMenus.begin(); it != guiMenus.end(); it++)
    {
        it->handleEvent(_event);
    }
}
void GUIManager::handleSoftEvent(std::list<std::string> _args)
{
    handle_StockButton(_args);

    for(std::list<GUIMenu>::iterator it = guiMenus.begin(); it != guiMenus.end(); it++)
    {
        it->handleSoftEvent(_args);
    }
}
void GUIManager::handleTask(std::list<std::string> _args)
{
    for(std::list<GUIMenu>::iterator it = guiMenus.begin(); it != guiMenus.end(); it++)
    {
        it->handleTask(_args);
    }
    if(*_args.begin() == "addMenu")
    {
        _args.pop_front();
        GUIMenu newMenu;
        newMenu.ID = *_args.begin();
        guiMenus.push_back(newMenu);
    }
    else if (*_args.begin() == "removeMenu")
    {
        _args.pop_front();
        for(std::list<GUIMenu>::iterator it = guiMenus.begin(); it != guiMenus.end(); it++)
        {
            if(it->ID == *_args.begin())
            {
                guiMenus.erase(it);
                break;
            }
        }
    }
    else if (*_args.begin() == "modifyMenu")
    {
        _args.pop_front();
        for(std::list<GUIMenu>::iterator it = guiMenus.begin(); it != guiMenus.end(); it++)
        {
            if(it->ID == *_args.begin())
            {
                _args.pop_front();
                if(*_args.begin() == "x")
                {
                    _args.pop_front();
                    it->X = util::toInt(*_args.begin());
                }
                else if (*_args.begin() == "y")
                {
                    _args.pop_front();
                    it->Y = util::toInt(*_args.begin());
                }
                else if (*_args.begin() == "width")
                {
                    _args.pop_front();
                    it->Width = util::toInt(*_args.begin());
                }
                else if (*_args.begin() == "height")
                {
                    _args.pop_front();
                    it->Height = util::toInt(*_args.begin());
                }
                else if (*_args.begin() == "title")
                {
                    _args.pop_front();
                    it->SetMenuTitle(*_args.begin());
                }
                else if (*_args.begin() == "visible")
                {
                    _args.pop_front();
                    it->isHidden = util::toBool(*_args.begin())==false;
                }
                break;
            }
        }
    }
    else if (*_args.begin() == "addElement")
    {
        _args.pop_front();
        for(std::list<GUIMenu>::iterator it = guiMenus.begin(); it != guiMenus.end(); it++)
        {
            if(it->ID == *_args.begin())
            {
                _args.pop_front();
                GUIElement tmp;
                tmp.ID = *_args.begin();
                it->GuiElements.push_back(tmp);
            }
        }
    }
    else if (*_args.begin() == "removeElement")
    {
        _args.pop_front();
        for(std::list<GUIMenu>::iterator it = guiMenus.begin(); it != guiMenus.end(); it++)
        {
            if(it->ID == *_args.begin())
            {
                _args.pop_front();
                for(std::list<GUIElement>::iterator it2 = it->GuiElements.begin(); it2 != it->GuiElements.end(); it2++)
                {
                    if(it2->ID == *_args.begin())
                    {
                        it->GuiElements.erase(it2);
                        break;
                    }
                }
                break;
            }
        }
    }
    else if (*_args.begin() == "modifyElement")
    {
        _args.pop_front();
        for(std::list<GUIMenu>::iterator it = guiMenus.begin(); it != guiMenus.end(); it++)
        {
            if(it->ID == *_args.begin())
            {
                _args.pop_front();
                for(std::list<GUIElement>::iterator it2 = it->GuiElements.begin(); it2 != it->GuiElements.end(); it2++)
                {
                    if(it2->ID == *_args.begin())
                    {
                        _args.pop_front();
                        if(*_args.begin() == "x")
                        {
                            _args.pop_front();
                            it2->button.X = util::toInt(*_args.begin());
                            it2->horSlider.X = util::toInt(*_args.begin());
                            it2->label.X = util::toInt(*_args.begin());
                        }
                        else if (*_args.begin() == "y")
                        {
                            _args.pop_front();
                            it2->button.Y = util::toInt(*_args.begin());
                            it2->horSlider.Y = util::toInt(*_args.begin());
                            it2->label.Y = util::toInt(*_args.begin());
                        }
                        else if (*_args.begin() == "width")
                        {
                            _args.pop_front();
                            it2->button.Width = util::toInt(*_args.begin());
                            it2->horSlider.Width = util::toInt(*_args.begin());
                        }
                        else if (*_args.begin() == "height")
                        {
                            _args.pop_front();
                            it2->button.Height = util::toInt(*_args.begin());
                            it2->horSlider.Height = util::toInt(*_args.begin());
                        }
                        else if (*_args.begin() == "type")
                        {
                            _args.pop_front();
                            it2->Type = *_args.begin();
                        }
                        else if (*_args.begin() == "id")
                        {
                            _args.pop_front();
                            it2->ID = *_args.begin();
                        }
                        else if (*_args.begin() == "displayText")
                        {
                            _args.pop_front();
                            it2->button.Text = *_args.begin();
                            it2->label.DisplayText = *_args.begin();
                        }
                        else if (*_args.begin() == "ratio")
                        {
                            _args.pop_front();
                            it2->horSlider.ratio = util::toFloat(*_args.begin());
                        }
                        else if (*_args.begin() == "min")
                        {
                            _args.pop_front();
                            it2->horSlider.min = util::toFloat(*_args.begin());
                        }
                        else if (*_args.begin() == "max")
                        {
                            _args.pop_front();
                            it2->horSlider.max = util::toFloat(*_args.begin());
                        }
                        else if (*_args.begin() == "value")
                        {
                            _args.pop_front();
                            it2->horSlider.value = util::toFloat(*_args.begin());
                        }
                        break;
                    }
                }
                break;
            }
        }
    }
    else if (*_args.begin() == "getMenuDef")
    {
        _args.pop_front();
        for(std::list<GUIMenu>::iterator it = guiMenus.begin(); it != guiMenus.end(); it++)
        {
            if(it->ID == *_args.begin())
            {
                _args.pop_front();
                if(*_args.begin() == "x")
                {
                    std::list<std::string> x;
                    x.push_back("guiRequest");
                    x.push_back(it->ID);
                    x.push_back("x");
                    x.push_back(util::toString(it->X));
                    dLink->pushEvent(x);
                }
                else if (*_args.begin() == "y")
                {
                    std::list<std::string> x;
                    x.push_back("guiRequest");
                    x.push_back(it->ID);
                    x.push_back("y");
                    x.push_back(util::toString(it->Y));
                    dLink->pushEvent(x);
                }
                else if (*_args.begin() == "width")
                {
                    std::list<std::string> x;
                    x.push_back("guiRequest");
                    x.push_back(it->ID);
                    x.push_back("width");
                    x.push_back(util::toString(it->Width));
                    dLink->pushEvent(x);
                }
                else if (*_args.begin() == "height")
                {
                    std::list<std::string> x;
                    x.push_back("guiRequest");
                    x.push_back(it->ID);
                    x.push_back("height");
                    x.push_back(util::toString(it->Height));
                    dLink->pushEvent(x);
                }
                else if (*_args.begin() == "title")
                {
                    std::list<std::string> x;
                    x.push_back("guiRequest");
                    x.push_back(it->ID);
                    x.push_back("title");
                    x.push_back(it->menuTitle.getString());
                    dLink->pushEvent(x);
                }
                else if (*_args.begin() == "visible")
                {
                    std::list<std::string> x;
                    x.push_back("guiRequest");
                    x.push_back(it->ID);
                    x.push_back("visible");
                    x.push_back(util::toString(!it->isHidden));
                    dLink->pushEvent(x);
                }
                break;
            }
        }

    }
    else if (*_args.begin() == "getElementDef")
    {
        _args.pop_front();
        for(std::list<GUIMenu>::iterator it = guiMenus.begin(); it != guiMenus.end(); it++)
        {
            if(it->ID == *_args.begin())
            {
                _args.pop_front();
                for(std::list<GUIElement>::iterator it2 = it->GuiElements.begin(); it2 != it->GuiElements.end(); it2++)
                {
                    if(it2->ID == *_args.begin())
                    {
                        _args.pop_front();
                        if(*_args.begin() == "x")
                        {
                            std::list<std::string> x;
                            x.push_back("guiRequest");
                            x.push_back(it->ID);
                            x.push_back(it2->ID);
                            x.push_back("x");
                            x.push_back(util::toString(it2->button.X));
                            dLink->pushEvent(x);
                        }
                        else if (*_args.begin() == "y")
                        {
                            std::list<std::string> x;
                            x.push_back("guiRequest");
                            x.push_back(it->ID);
                            x.push_back(it2->ID);
                            x.push_back("y");
                            x.push_back(util::toString(it2->button.Y));
                            dLink->pushEvent(x);
                        }
                        else if (*_args.begin() == "width")
                        {
                            std::list<std::string> x;
                            x.push_back("guiRequest");
                            x.push_back(it->ID);
                            x.push_back(it2->ID);
                            x.push_back("width");
                            x.push_back(util::toString(it2->button.Width));
                            dLink->pushEvent(x);
                        }
                        else if (*_args.begin() == "height")
                        {
                            std::list<std::string> x;
                            x.push_back("guiRequest");
                            x.push_back(it->ID);
                            x.push_back(it2->ID);
                            x.push_back("height");
                            x.push_back(util::toString(it2->button.Height));
                            dLink->pushEvent(x);
                        }
                        else if (*_args.begin() == "type")
                        {
                            std::list<std::string> x;
                            x.push_back("guiRequest");
                            x.push_back(it->ID);
                            x.push_back(it2->ID);
                            x.push_back("type");
                            x.push_back(it2->Type);
                            dLink->pushEvent(x);
                        }
                        else if (*_args.begin() == "id")
                        {
                            std::list<std::string> x;
                            x.push_back("guiRequest");
                            x.push_back(it->ID);
                            x.push_back(it2->ID);
                            x.push_back("id");
                            x.push_back(it2->ID);
                            dLink->pushEvent(x);
                        }
                        else if (*_args.begin() == "displayText")
                        {
                            std::list<std::string> x;
                            x.push_back("guiRequest");
                            x.push_back(it->ID);
                            x.push_back(it2->ID);
                            x.push_back("displayText");
                            x.push_back(it2->button.Text);
                            dLink->pushEvent(x);
                        }
                        else if (*_args.begin() == "ratio")
                        {
                            std::list<std::string> x;
                            x.push_back("guiRequest");
                            x.push_back(it->ID);
                            x.push_back(it2->ID);
                            x.push_back("ratio");
                            x.push_back(util::toString(it2->horSlider.ratio));
                            dLink->pushEvent(x);
                        }
                        else if (*_args.begin() == "min")
                        {
                            std::list<std::string> x;
                            x.push_back("guiRequest");
                            x.push_back(it->ID);
                            x.push_back(it2->ID);
                            x.push_back("min");
                            x.push_back(util::toString(it2->horSlider.min));
                            dLink->pushEvent(x);
                        }
                        else if (*_args.begin() == "max")
                        {
                            std::list<std::string> x;
                            x.push_back("guiRequest");
                            x.push_back(it->ID);
                            x.push_back(it2->ID);
                            x.push_back("max");
                            x.push_back(util::toString(it2->horSlider.max));
                            dLink->pushEvent(x);
                        }
                        else if (*_args.begin() == "value")
                        {
                            std::list<std::string> x;
                            x.push_back("guiRequest");
                            x.push_back(it->ID);
                            x.push_back(it2->ID);
                            x.push_back("value");
                            x.push_back(util::toString(it2->horSlider.value));
                            dLink->pushEvent(x);
                        }
                        break;
                    }
                }
                break;
            }
        }
    }

}

void GUIManager::update()
{
    dock.setPosition((float)-1,(float)-1);
    dock.setSize(sf::Vector2f((float)dockWidth+4,(float)dLink->renderWindow->getSize().y+3.0f));
    dock.setFillColor(sf::Color::Black);
    dock.setOutlineThickness(1.0f);
    dock.setOutlineColor(sf::Color::Green);
}
void GUIManager::render()
{
    //render the dock
    dLink->renderWindow->draw(dock);
    int i = 0;
    for (std::list<GUIDockItem>::iterator it = dockButtons.begin(); it != dockButtons.end(); it++)
    {
        sf::RectangleShape temp;
        if(it->mouseHover)
        {
            temp.setPosition(2.0f,(float)(i*(dockWidth+1)+2));
            temp.setSize(sf::Vector2f((float)dockWidth-2.0,(float)(i+1)*dockWidth+i-(i*(dockWidth+1)+2)));
            temp.setFillColor(sf::Color::Black);
            temp.setOutlineThickness(1.0f);
            temp.setOutlineColor(sf::Color::White);
        }
        else
        {
            temp.setPosition(2.0f,(float)(i*(dockWidth+1)+2));
            temp.setSize(sf::Vector2f((float)dockWidth-2.0,(float)(i+1)*dockWidth+i-(i*(dockWidth+1)+2)));
            temp.setFillColor(sf::Color::Black);
            temp.setOutlineThickness(1.0f);
            temp.setOutlineColor(sf::Color::Green);
        }
        dLink->renderWindow->draw(temp);
        sf::Sprite temp2;
        temp2.setTexture(*(dLink->TextureGet(it->ImageID)));
        temp2.setPosition(3.0f, (float)(i*(dockWidth+1)+3));

        temp2.setScale(((float)dockWidth)/((float)dLink->TextureGet(it->ImageID)->getSize().x+4.0f),
                       (((float)dockWidth)/((float)dLink->TextureGet(it->ImageID)->getSize().y+4.0f)));

        dLink->renderWindow->draw(temp2);
        i++;
    }
    //render the menus
    for (std::list<GUIMenu>::iterator it = guiMenus.begin(); it != guiMenus.end(); it++)
    {
        it->update();
        it->render();
    }
}

void GUIManager::add_MainMenu()
{
    GUIMenu main;
    main.ID = "$_mainMenu";
    main.SetX(dockWidth+10);
    main.SetY(10);
    main.SetWidth(200);
    main.SetHeight(116);
    main.SetMenuTitle("--[[ MAIN ]]--");

    GUIElement elem1;
    elem1.ID = "$_mainMenu.new";
    elem1.Type = "button";
    elem1.X = 10;
    elem1.Y = 10;
    elem1.button.Width = 180;
    elem1.button.Height = 16;
    elem1.button.Text = "Start new...";

    GUIElement elem2;
    elem2.ID = "$_mainMenu.save";
    elem2.Type = "button";
    elem2.X = 10;
    elem2.Y = 36;
    elem2.button.Width = 180;
    elem2.button.Height = 16;
    elem2.button.Text = "Save current...";

    GUIElement elem3;
    elem3.ID = "$_mainMenu.load";
    elem3.Type = "button";
    elem3.X = 10;
    elem3.Y = 62;
    elem3.button.Width = 180;
    elem3.button.Height = 16;
    elem3.button.Text = "Load other...";

    GUIElement elem4;
    elem4.ID = "$_mainMenu.close";
    elem4.Type = "button";
    elem4.X = 10;
    elem4.Y = 88;
    elem4.button.Width = 180;
    elem4.button.Height = 16;
    elem4.button.Text = "Close without saving!";

    main.GuiElements.push_back(elem1);
    main.GuiElements.push_back(elem2);
    main.GuiElements.push_back(elem3);
    main.GuiElements.push_back(elem4);

    main.update();
    guiMenus.push_back(main);
}
void GUIManager::add_ConsoleMenu()
{
    GUIMenu console;
    console.ID = "$_consoleMenu";
    console.SetX(dockWidth+10);
    console.SetY(100);
    console.SetWidth(300);
    console.SetHeight(200);
    console.SetMenuTitle("--[[ Console ]]--");

    GUIElement elem1;
    elem1.ID = "$_consoleMenu.output";
    elem1.Type = "textbox";
    elem1.X = 10;
    elem1.Y = 10;
    elem1.textBox.Width = 280;
    elem1.textBox.Height = 160;
    elem1.textBox.multiline = true;

    GUIElement elem2;
    elem2.ID = "$_consoleMenu.input";
    elem2.Type = "textbox";
    elem2.X = 10;
    elem2.Y = 170;
    elem2.textBox.Width = 280;
    elem2.textBox.Height = 20;
    elem2.textBox.multiline = false;

    console.GuiElements.push_back(elem1);
    console.GuiElements.push_back(elem2);

    console.update();
    guiMenus.push_back(console);
}
void GUIManager::add_OptionMenu()
{
    GUIMenu main;
    main.ID = "$_optionMenu";
    main.Enable();
    main.SetX(dockWidth+20);
    main.SetY(60);
    main.SetWidth(220);
    main.SetHeight(220);
    main.SetMenuTitle("--[[ SETTINGS ]]--");

    GUIElement elem1;
    elem1.ID = "$_optionMenu.test";
    elem1.Type = "horslider";
    elem1.X = 10;
    elem1.Y = 10;
    elem1.horSlider.max = 200;
    elem1.horSlider.min = 1;
    elem1.horSlider.Width = 200;
    elem1.horSlider.Height = 16;
    elem1.horSlider.ratio = 0.5;
    elem1.horSlider.value = 10;
    GUIElement elem2;
    elem2.ID = "$_optionMenu.test2";
    elem2.Type = "vertslider";
    elem2.X = 10;
    elem2.Y = 10;
    elem2.vertSlider.max = 200;
    elem2.vertSlider.min = 1;
    elem2.vertSlider.Width = 16;
    elem2.vertSlider.Height = 200;
    elem2.vertSlider.ratio = 0.5;
    elem2.vertSlider.value = 10;

    main.GuiElements.push_back(elem1);
    main.GuiElements.push_back(elem2);

    main.update();
    guiMenus.push_back(main);
}
void GUIManager::add_CodeIDE()
{
    GUIMenu menu;
    menu.ID = "$_codeIDE";
    menu.SetX(dockWidth+500);
    menu.SetY(10);
    menu.SetWidth(300);
    menu.SetHeight(280);
    menu.SetMenuTitle("--[[ Lua-IDE ]]--");

    GUIElement elem1;
    elem1.ID = "$_codeIDE.main";
    elem1.Type = "textbox";
    elem1.X = 10;
    elem1.Y = 10;
    elem1.textBox.Width = 280;
    elem1.textBox.Height = 260;

    menu.GuiElements.push_back(elem1);


    menu.update();

    guiMenus.push_back(menu);
}

void GUIManager::add_StockButton()
{
    AddDockItem("$_mainmenu");
    EditDockItemImage("$_mainmenu", "$_dockMain");
    AddDockItem("$_optionsmenu");
    EditDockItemImage("$_optionsmenu", "$_dockOptions");
}
void GUIManager::handle_StockButton(std::list<std::string> _args)
{
    if(*_args.begin() == "dock_released")
    {
        _args.pop_front();
        if(*_args.begin() == "$_mainmenu")
        {
            for(std::list<GUIMenu>::iterator it = guiMenus.begin(); it != guiMenus.end(); it++)
            {
                if(it->ID == "$_mainMenu")
                {
                    it->Show();
                }
            }
        }
    }
}
