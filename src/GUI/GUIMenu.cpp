#include "GUIMenu.hpp"
//CONSTRUCTORS
GUIMenu::GUIMenu()
{
    BorderInactive = dLink->settings.guiMenuBorderInactive;
    BorderActive = dLink->settings.guiMenuBorderActive;
    BackgroundInactive = dLink->settings.guiMenuBackgroundInactive;
    BackgroundActive = dLink->settings.guiMenuBackgroundActive;
    TitleBackgroundInactive = dLink->settings.guiMenuTitleBackgroundInactive;
    TitleBackgroundActive = dLink->settings.guiMenuTitleBackgroundActive;
    TitleTextInactive = dLink->settings.guiMenuTitleTextInactive;
    TitleTextActive = dLink->settings.guiMenuTitleTextActive;

    moving = false;
    closeButtonHover = false;
    closeButtonPushed = false;
    isActive = false;
    isHidden = false;

    scrollX = 0;
    scrollY = 0;
    scrollable = false;

    bottomSlider.Setup();
    rightSlider.Setup();

    bottomSlider.value = 0;
    rightSlider.value = 0;
}
//DESTRUCTORS

//METHODS
void GUIMenu::update()
{
    if(isHidden == false)
    {
        view = dLink->guiView;
        view.reset(sf::FloatRect(X+scrollable*bottomSlider.value, Y+scrollable*(rightSlider.value+16+1), Width, Height+16));
        float posx = (X)/(float)dLink->renderWindow->getSize().x;
        float posy = (Y+scrollable*(16+1))/(float)dLink->renderWindow->getSize().y;
        float sizex = Width/(float)dLink->renderWindow->getSize().x;
        float sizey = (Height+ !scrollable*16)/(float)dLink->renderWindow->getSize().y;
        view.setViewport(sf::FloatRect(posx, posy, sizex, sizey));

        int opacity = 190;
        for(std::list<GUIElement>::iterator it = GuiElements.begin(); it != GuiElements.end(); it++)
        {
            it->isActive = isActive;

            dLink->renderWindow->setView(view);

            it->update(X, Y+16, ID);
        }
        //recalcualte the renderShapes
        if(isActive)
        {
            mainBackground.setPosition((float)X,(float)Y);
            mainBackground.setSize(sf::Vector2f((float)Width+scrollable*16,(float)Height+16+scrollable*16));
            mainBackground.setFillColor(BackgroundActive);
            mainBackground.setOutlineThickness(1.0f);
            mainBackground.setOutlineColor(BorderActive);

            titleBar.setPosition((float)X,(float)Y);
            titleBar.setSize(sf::Vector2f((float)Width+scrollable*16,(float)16));
            titleBar.setFillColor(TitleBackgroundActive);
            titleBar.setOutlineThickness(1.0f);
            titleBar.setOutlineColor(BorderActive);

            menuTitle.setFont(*dLink->FontGet("$_menuTitle"));
            menuTitle.setCharacterSize(12.0f);
            menuTitle.setPosition((float)(X+4),(float)(Y));
            menuTitle.setColor(TitleTextActive);
        }
        else
        {
            mainBackground.setPosition((float)X,(float)Y);
            mainBackground.setSize(sf::Vector2f((float)Width+scrollable*16,(float)Height+16+scrollable*16));
            mainBackground.setFillColor(BackgroundInactive);
            mainBackground.setOutlineThickness(1.0f);
            mainBackground.setOutlineColor(BorderInactive);

            titleBar.setPosition((float)X,(float)Y);
            titleBar.setSize(sf::Vector2f((float)Width+scrollable*16,(float)16));
            titleBar.setFillColor(TitleBackgroundInactive);
            titleBar.setOutlineThickness(1.0f);
            titleBar.setOutlineColor(BorderInactive);

            menuTitle.setFont(*dLink->FontGet("$_menuTitle"));
            menuTitle.setCharacterSize(12.0f);
            menuTitle.setPosition((float)(X+4),(float)(Y));
            menuTitle.setColor(TitleTextInactive);
        }

        if (closeButtonHover)
            closeButton.setTexture(*dLink->TextureGet("$_closeButtonHover"));
        else
            closeButton.setTexture(*dLink->TextureGet("$_closeButtonNormal"));
        closeButton.setPosition((float)(X+Width-15+scrollable*16),(float)(Y+1));

        if(scrollable)
        {
            bottomSlider.min = 0;
            bottomSlider.max = totalWidth-Width;
            bottomSlider.Height = 16;
            bottomSlider.Width = Width-1;
            bottomSlider.isActive = isActive;
            bottomSlider.ratio = (float)Width/(float)totalWidth;
            bottomSlider.Update(X, Y+Height+16,"horMenuSlider", ID);

            rightSlider.min = 0;
            rightSlider.max = totalHeight-Height;
            rightSlider.Height = Height-2;
            rightSlider.Width = 16;
            rightSlider.isActive = isActive;
            rightSlider.ratio = (float)Height/(float)totalHeight;
            rightSlider.Update(X+Width, Y+16+1,"vertMenuSlider", ID);
        }

    }
}
void GUIMenu::SetHeight(int _height)
{
    Height = _height;
}
void GUIMenu::SetWidth(int _width)
{
    Width = _width;
}
void GUIMenu::SetX(int _x)
{
    X = _x;
}
void GUIMenu::SetY(int _y)
{
    Y = _y;
}
void GUIMenu::SetMenuTitle(std::string _title)
{
    menuTitle.setString(_title);
}
void GUIMenu::render()
{
    if(isHidden == false)
    {
        //Rendermyself
        dLink->renderWindow->setView(dLink->guiView);
        dLink->renderWindow->draw(mainBackground);
        dLink->renderWindow->draw(titleBar);
        dLink->renderWindow->draw(menuTitle);
        dLink->renderWindow->draw(closeButton);
        bottomSlider.Render(X, Y+Height+16-10,"horMenuSlider", ID);
        rightSlider.Render(X+Width, Y+16+1,"vertMenuSlider", ID);
        //RenderElements:
        for (std::list<GUIElement>::iterator it = GuiElements.begin(); it != GuiElements.end(); it++)
        {
            dLink->renderWindow->setView(view);
            it->render(X, Y+16, ID);
        }
    }
}
void GUIMenu::handleEvent(sf::Event* _event)
{
    bottomSlider.handleEvent(_event, X, Y+Height+16-10,"horMenuSlider", ID);
    rightSlider.handleEvent(_event, X+Width, Y+16+1,"vertMenuSlider", ID);

    //moving menu
    int x,y;
    //start?
    if(_event->type == sf::Event::MouseButtonPressed)
    {
        x = _event->mouseButton.x;
        y = _event->mouseButton.y;
        if(x >= X && x <= X+Width && y >= Y && y <= Y+16)
        {
            moving = true;
            movingD.x = x;
            movingD.y = y;
        }
    }
    //end?
    if(_event->type == sf::Event::MouseButtonReleased)
    {
        moving = false;
    }
    if(_event->type == sf::Event::MouseMoved)
    {
        x = _event->mouseMove.x;
        y = _event->mouseMove.y;
        if(moving)
        {
            X += x-movingD.x;
            Y += y-movingD.y;
            /*for(std::list<GUIElement>::iterator it = GuiElements.begin(); it != GuiElements.end(); it++)
            {
            	it->X += x-movingD.x;
            	it->Y += y-movingD.y;
            }*/
            movingD.x = x;
            movingD.y = y;
        }
        closeButtonHover = (x >= (X+Width+scrollable*16-15) && y >= (Y+1) && x <= (X+Width+scrollable*16-1) && y <= (Y+15));
    }
    if(_event->type == sf::Event::MouseButtonReleased)
    {
        if(_event->mouseButton.button == sf::Mouse::Left)
        {
            if(closeButtonHover)
            {
                std::list<std::string> x;
                x.push_back("menu_close");
                x.push_back(ID);
                dLink->pushEvent(x);
                Hide();
            }
        }
    }
    for(std::list<GUIElement>::iterator it = GuiElements.begin(); it != GuiElements.end(); it++)
    {
        it->handleEvent(_event, X-scrollable*bottomSlider.value, Y+16-scrollable*rightSlider.value, ID);
    }
}
void GUIMenu::handleSoftEvent(std::list<std::string> _args)
{
    for(std::list<GUIElement>::iterator it = GuiElements.begin(); it != GuiElements.end(); it++)
    {
        it->handleSoftEvent(_args, X, Y+16, ID);
    }
}
void GUIMenu::handleTask(std::list<std::string> _args)
{
    for(std::list<GUIElement>::iterator it = GuiElements.begin(); it != GuiElements.end(); it++)
    {
        it->handleTask(_args, X, Y+16, ID);
    }
}
void GUIMenu::Enable()
{
    isActive = true;
}
void GUIMenu::Disable()
{
    isActive = false;
}
void GUIMenu::Show()
{
    isHidden = false;
    for(std::list<GUIElement>::iterator it = GuiElements.begin(); it != GuiElements.end(); it++)
    {
        it->Show();
    }
}
void GUIMenu::Hide()
{
    isHidden = true;
    for(std::list<GUIElement>::iterator it = GuiElements.begin(); it != GuiElements.end(); it++)
    {
        it->Hide();
    }
}
bool GUIMenu::isHit(int mouseX, int mouseY)
{
    if(mouseX >= X && mouseX <= X+Width)
    {
        if(mouseY >= Y && mouseY <= Y+Height+16)
        {
            return true;
        }
    }
    return false;
}
