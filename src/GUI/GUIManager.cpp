#include "GUI/GUIManager.hpp"
//CONSTRUCTORS
GUIManager::GUIManager()
{
    add_StockButton();
    add_MainMenu();
    add_ConsoleMenu();
    add_CodeIDE();

    std::list<std::string> x;
    x.push_back("plugin");
    x.push_back("load");
    x.push_back("mSettings");
    dLink->pushTask(x);
    x.clear();
    x.push_back("plugin");
    x.push_back("load");
    x.push_back("mDebug");
    dLink->pushTask(x);
    x.clear();
    x.push_back("plugin");
    x.push_back("load");
    x.push_back("mMenu");
    dLink->pushTask(x);
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
    if(!dLink->guiMode)
    {
        for(std::list<GUIMenu>::iterator it = guiMenus.begin(); it != guiMenus.end(); it++)
        {
            it->isActive = false;
            it->update();
        }
        return;
    }

    if(_event->type == sf::Event::MouseMoved)
    {
        int x,y;
        x = _event->mouseMove.x;
        y = _event->mouseMove.y;

        dockHover = (x <= dLink->settings.dockWidth +2);

        int i = 0;
        for(std::list<GUIDockItem>::iterator it = dockButtons.begin(); it != dockButtons.end(); it++)
        {
            if (x >= 1 && x <= dLink->settings.dockWidth && y >= (i*(dLink->settings.dockWidth+1)+2) && y <= ((i+1)*dLink->settings.dockWidth+i))
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
                if(it->isHidden)
                    continue;
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
}

void GUIManager::update()
{
    if(dockHover)
    {
        dock.setPosition((float)-1,(float)-1);
        dock.setSize(sf::Vector2f((float)dLink->settings.dockWidth+3,(float)dLink->renderWindow->getSize().y+3.0f));
        dock.setFillColor(dLink->settings.guiDockBackgroundHover);
        dock.setOutlineThickness(1.0f);
        dock.setOutlineColor(dLink->settings.guiDockBorderHover);
    }
    else
    {
        dock.setPosition((float)-1,(float)-1);
        dock.setSize(sf::Vector2f((float)dLink->settings.dockWidth+3,(float)dLink->renderWindow->getSize().y+3.0f));
        dock.setFillColor(dLink->settings.guiDockBackground);
        dock.setOutlineThickness(1.0f);
        dock.setOutlineColor(dLink->settings.guiDockBorder);
    }
}
void GUIManager::render()
{
    //render the dock
    if(dLink->guiMode)
    {
        dLink->renderWindow->draw(dock);
        int i = 0;
        for (std::list<GUIDockItem>::iterator it = dockButtons.begin(); it != dockButtons.end(); it++)
        {
            sf::RectangleShape temp;
            if(it->mouseHover)
            {
                temp.setPosition(2.0f,(float)(i*(dLink->settings.dockWidth+1)+2));
                temp.setSize(sf::Vector2f((float)dLink->settings.dockWidth-2.0,(float)(i+1)*dLink->settings.dockWidth+i-(i*(dLink->settings.dockWidth+1)+2)));
                temp.setFillColor(dLink->settings.guiDockItemBackgroundHover);
                temp.setOutlineThickness(1.0f);
                temp.setOutlineColor(dLink->settings.guiDockItemBorderHover);
            }
            else
            {
                temp.setPosition(2.0f,(float)(i*(dLink->settings.dockWidth+1)+2));
                temp.setSize(sf::Vector2f((float)dLink->settings.dockWidth-2.0,(float)(i+1)*dLink->settings.dockWidth+i-(i*(dLink->settings.dockWidth+1)+2)));
                temp.setFillColor(dLink->settings.guiDockItemBackground);
                temp.setOutlineThickness(1.0f);
                temp.setOutlineColor(dLink->settings.guiDockItemBorder);
            }
            dLink->renderWindow->draw(temp);
            sf::Sprite temp2;
            temp2.setTexture(*(dLink->TextureGet(it->ImageID)));
            temp2.setPosition(3.0f, (float)(i*(dLink->settings.dockWidth+1)+3));

            temp2.setScale(((float)dLink->settings.dockWidth)/((float)dLink->TextureGet(it->ImageID)->getSize().x+4.0f),
                           (((float)dLink->settings.dockWidth)/((float)dLink->TextureGet(it->ImageID)->getSize().y+4.0f)));

            dLink->renderWindow->draw(temp2);
            i++;
        }
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
    main.SetX(dLink->settings.dockWidth+10);
    main.SetY(10);
    main.SetWidth(200);
    main.SetHeight(116);
    main.SetMenuTitle("--[[ MAIN ]]--");

    GUIElement elem1;
    elem1.ID = "new";
    elem1.Type = "button";
    elem1.X = 10;
    elem1.Y = 10;
    elem1.button.Width = 180;
    elem1.button.Height = 16;
    elem1.button.Text = "Start new...";

    GUIElement elem2;
    elem2.ID = "save";
    elem2.Type = "button";
    elem2.X = 10;
    elem2.Y = 36;
    elem2.button.Width = 180;
    elem2.button.Height = 16;
    elem2.button.Text = "Save current...";

    GUIElement elem3;
    elem3.ID = "load";
    elem3.Type = "button";
    elem3.X = 10;
    elem3.Y = 62;
    elem3.button.Width = 180;
    elem3.button.Height = 16;
    elem3.button.Text = "Load other...";

    GUIElement elem4;
    elem4.ID = "close";
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
    console.isHidden = true;
    console.ID = "$_consoleMenu";
    console.SetX(dLink->settings.dockWidth+10);
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

void GUIManager::add_CodeIDE()
{
    GUIMenu menu;
    menu.ID = "$_codeIDE";
    menu.SetX(dLink->settings.dockWidth+500);
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
