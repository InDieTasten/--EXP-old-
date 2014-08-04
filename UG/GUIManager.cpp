#include "GUIManager.hpp"
//CONSTRUCTORS
GUIManager::GUIManager()
{

}
//DESTRUCTORS

//METHODS
void GUIManager::AddMenu(std::string _id)
{
    for(std::list<GUIMenu>::iterator it = guiMenus.begin(); it != guiMenus.end(); it++)
    {
        if(it->ID == _id)
        {
            //Fehler: Menu ID bereits vorhanden
            return;
        }
        GUIMenu tmp;
        tmp.ID = _id;
        guiMenus.push_back(tmp);
    }
}
void GUIManager::EditMenuPosition(std::string _id, int _x, int _y)
{
    for(std::list<GUIMenu>::iterator it = guiMenus.begin(); it != guiMenus.end(); it++)
    {
        if(it->ID == _id)
        {
            it->SetX(_x);
            it->SetY(_y);
            return;
        }
    }
}
void GUIManager::EditMenuSize(std::string _id, int _width, int _height)
{
    for(std::list<GUIMenu>::iterator it = guiMenus.begin(); it != guiMenus.end(); it++)
    {
        if(it->ID == _id)
        {
            it->SetWidth(_width);
            it->SetHeight(_height);
            return;
        }
    }
}
void GUIManager::EnableMenu(std::string _id)
{
    for(std::list<GUIMenu>::iterator it = guiMenus.begin(); it != guiMenus.end(); it++)
    {
        if(it->ID == _id)
        {
            it->Enable();
            return;
        }
    }
}
void GUIManager::DisableMenu(std::string _id)
{
    for(std::list<GUIMenu>::iterator it = guiMenus.begin(); it != guiMenus.end(); it++)
    {
        if(it->ID == _id)
        {
            it->Disable();
            return;
        }
    }
}
void GUIManager::ShowMenu(std::string _id)
{
    for(std::list<GUIMenu>::iterator it = guiMenus.begin(); it != guiMenus.end(); it++)
    {
        if(it->ID == _id)
        {
            it->Show();
            return;
        }
    }
}
void GUIManager::HideMenu(std::string _id)
{
    for(std::list<GUIMenu>::iterator it = guiMenus.begin(); it != guiMenus.end(); it++)
    {
        if(it->ID == _id)
        {
            it->Hide();
            return;
        }
    }
}

void GUIManager::AddGuiElement(std::string _menuid, std::string _elemid)
{
    for(std::list<GUIMenu>::iterator it = guiMenus.begin(); it != guiMenus.end(); it++)
    {
        if(it->ID == _menuid)
        {
            for(std::list<GUIElement>::iterator it2 = it->GuiElements.begin(); it2 != it->GuiElements.end(); it2++)
            {
                if (it2->ID == _elemid)
                {
                    //error
                    return;
                }
            }
            GUIElement tmp;
            tmp.ID = _elemid;
            it->GuiElements.push_back(tmp);
        }
    }
}
void GUIManager::EditElemPosition(std::string _menuid, std::string _elemid, int _x, int _y)
{
    for(std::list<GUIMenu>::iterator it = guiMenus.begin(); it != guiMenus.end(); it++)
    {
        if(it->ID == _menuid)
        {
            for(std::list<GUIElement>::iterator it2 = it->GuiElements.begin(); it2 != it->GuiElements.end(); it2++)
            {
                if (it2->ID == _elemid)
                {
                    it2->X = _x;
                    it2->Y = _y;
                    return;
                }
            }
        }
    }
}
void GUIManager::EditElemSize(std::string _menuid, std::string _elemid, int _width, int _height)
{
    for(std::list<GUIMenu>::iterator it = guiMenus.begin(); it != guiMenus.end(); it++)
    {
        if(it->ID == _menuid)
        {
            for(std::list<GUIElement>::iterator it2 = it->GuiElements.begin(); it2 != it->GuiElements.end(); it2++)
            {
                if (it2->ID == _elemid)
                {
                    it2->Width = _width;
                    it2->Height = _height;
                    return;
                }
            }
        }
    }
}
void GUIManager::EditElemType(std::string _menuid, std::string _elemid, std::string _type)
{
    for(std::list<GUIMenu>::iterator it = guiMenus.begin(); it != guiMenus.end(); it++)
    {
        if(it->ID == _menuid)
        {
            for(std::list<GUIElement>::iterator it2 = it->GuiElements.begin(); it2 != it->GuiElements.end(); it2++)
            {
                if (it2->ID == _elemid)
                {
                    //*(it2->Properties.begin()) = _type;
                    return;
                }
            }
        }
    }
}

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

void GUIManager::SetDataLink(DataBank * _dataLink)
{
    dockWidth = 68;
    dataLink = _dataLink;
    add_StockButton();
    add_MainMenu();
    add_OptionMenu();
    add_CodeIDE();
}
void GUIManager::handleEvent(sf::Event *_event, const sf::Input* _input)
{
    if(_event->Type == sf::Event::MouseMoved)
    {
        int x,y;
        x = _input->GetMouseX();
        y = _input->GetMouseY();
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
                    dataLink->pushEvent(e);
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
                    dataLink->pushEvent(e);
                }
                it->mouseHover = false;
            }
            i++;
        }
    }
    if(_event->Type == sf::Event::MouseButtonPressed)
    {
        for(std::list<GUIDockItem>::iterator it = dockButtons.begin(); it != dockButtons.end(); it++)
        {
            if(it->mouseHover)
            {
                std::list<std::string> e;
                e.push_back("dock_pressed");
                e.push_back(it->ID);
                dataLink->pushEvent(e);
            }
        }
        for(std::list<GUIMenu>::iterator it = guiMenus.begin(); it != guiMenus.end(); it++)
        {
            if(it->isHit(_input->GetMouseX(), _input->GetMouseY()))
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
    if(_event->Type == sf::Event::MouseButtonReleased)
    {
        for(std::list<GUIDockItem>::iterator it = dockButtons.begin(); it != dockButtons.end(); it++)
        {
            if(it->mouseHover)
            {
                std::list<std::string> e;
                e.push_back("dock_released");
                e.push_back(it->ID);
                dataLink->pushEvent(e);
            }
        }
    }
    for(std::list<GUIMenu>::iterator it = guiMenus.begin(); it != guiMenus.end(); it++)
    {
        it->handleEvent(dataLink, _event, _input);
    }
}
void GUIManager::handleSoftEvent(std::list<std::string> _args)
{
    handle_StockButton(_args);
}

void GUIManager::update()
{
    dock = sf::RectangleShape::Rectangle((float)-1,(float)-1,(float)dockWidth+3,(float)dataLink->renderWindow->GetHeight()+2.0f,sf::Color::Black,1.0f,sf::Color::Green);
    dock.EnableFill(true);
    dock.EnableOutline(true);
    dock.SetPosition((float)-1,(float)-1);
}
void GUIManager::render()
{
    //render the dock
    dataLink->renderWindow->Draw(dock);
    int i = 0;
    for (std::list<GUIDockItem>::iterator it = dockButtons.begin(); it != dockButtons.end(); it++)
    {
        sf::RectangleShape temp;
        if(it->mouseHover)
            temp = sf::RectangleShape::Rectangle(2.0f, (float)(i*(dockWidth+1)+2), (float)dockWidth, (float)((i+1)*dockWidth+i), sf::Color::Black,1.0f,sf::Color::White);
        else
            temp = sf::RectangleShape::Rectangle(2.0f, (float)(i*(dockWidth+1)+2), (float)dockWidth, (float)((i+1)*dockWidth+i), sf::Color::Black,1.0f,sf::Color::Green);
        dataLink->renderWindow->Draw(temp);
        sf::Sprite temp2;
        temp2.SetImage(*(dataLink->TextureGet(it->ImageID)));
        temp2.SetPosition(3.0f, (float)(i*(dockWidth+1)+3));

        temp2.SetScaleX(((float)dockWidth)/((float)dataLink->TextureGet(it->ImageID)->GetWidth()+4.0f));
        temp2.SetScaleY(((float)dockWidth)/((float)dataLink->TextureGet(it->ImageID)->GetHeight()+4.0f));

        dataLink->renderWindow->Draw(temp2);
        i++;
    }
    //render the menus
    for (std::list<GUIMenu>::iterator it = guiMenus.begin(); it != guiMenus.end(); it++)
    {
        it->update(dataLink);
        it->render(dataLink);
    }
}

void GUIManager::addMenu(GUIMenu _menu)
{
    for(std::list<GUIMenu>::iterator it = guiMenus.begin(); it != guiMenus.end(); it++)
    {
        if (it->ID == _menu.ID)
        {
            return; //FEHLER
        }
    }
    guiMenus.push_back(_menu);
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

    main.update(dataLink);
    guiMenus.push_back(main);
}
void GUIManager::add_OptionMenu()
{
    GUIMenu main;
    main.ID = "$_optionMenu";
    main.Enable();
    main.SetX(dockWidth+20);
    main.SetY(60);
    main.SetWidth(220);
    main.SetHeight(116);
    main.SetMenuTitle("--[[ OPTIONS ]]--");

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

    main.GuiElements.push_back(elem1);

    main.update(dataLink);
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
    elem1.ID = "codebox";
    elem1.Type = "codebox";
    elem1.X = 10;
    elem1.Y = 10;
    elem1.codeBox.Width = 280;
    elem1.codeBox.Height = 260;

    menu.GuiElements.push_back(elem1);
    menu.update(dataLink);
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
