#include "GUIMenu.hpp"
//CONSTRUCTORS
GUIMenu::GUIMenu()
{
    moving = false;
    closeButtonHover = false;
    closeButtonPushed = false;
    isActive = false;
    isHidden = false;
}
//DESTRUCTORS

//METHODS
void GUIMenu::update(DataBank *datalink)
{
    if(isHidden == false)
    {
        int opacity = 190;
        for(std::list<GUIElement>::iterator it = GuiElements.begin(); it != GuiElements.end(); it++)
        {
            it->isActive = isActive;
            it->update(datalink, X, Y+16);
        }
        //recalcualte the renderShapes
        if(isActive)
        {
            mainBackground = sf::RectangleShape::Rectangle((float)X,(float)Y,(float)X+Width,(float)Y+Height+16,sf::Color(0,0,0,opacity),1.0f,sf::Color::Green);
        }
        else
        {
            mainBackground = sf::RectangleShape::Rectangle((float)X,(float)Y,(float)X+Width,(float)Y+Height+16,sf::Color(0,0,0,opacity),1.0f,sf::Color::White);
        }
        mainBackground.EnableFill(true);
        mainBackground.EnableOutline(true);

        if(isActive)
        {
            titleBar = sf::RectangleShape::Rectangle((float)X,(float)Y,(float)X+Width,(float)Y+16,sf::Color(10,10,10,opacity),1.0f,sf::Color::Green);
        }
        else
        {
            titleBar = sf::RectangleShape::Rectangle((float)X,(float)Y,(float)X+Width,(float)Y+16,sf::Color(10,10,10,opacity),1.0f,sf::Color::White);
        }
        titleBar.EnableFill(true);
        titleBar.EnableOutline(true);

        menuTitle.SetFont(*datalink->FontGet("$_menuTitle"));
        menuTitle.SetSize(12.0f);
        menuTitle.SetPosition((float)(X+4),(float)(Y));
        menuTitle.SetColor(sf::Color(200,200,200,255));

        if (closeButtonHover)
            closeButton.SetImage(*datalink->TextureGet("$_closeButtonHover"));
        else
            closeButton.SetImage(*datalink->TextureGet("$_closeButtonNormal"));
        closeButton.SetPosition((float)(X+Width-15),(float)(Y+1));
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
    menuTitle.SetText(_title);
}
void GUIMenu::render(DataBank *dataLink)
{
    if(isHidden == false)
    {
        //Rendermyself
        dataLink->renderWindow->Draw(mainBackground);
        dataLink->renderWindow->Draw(titleBar);
        dataLink->renderWindow->Draw(menuTitle);
        dataLink->renderWindow->Draw(closeButton);
        //RenderElements:
        for (std::list<GUIElement>::iterator it = GuiElements.begin(); it != GuiElements.end(); it++)
        {
            it->render(dataLink);
        }
    }
}
void GUIMenu::handleEvent(DataBank* _datalink, sf::Event* _event, const sf::Input* _input)
{
    //moving menu
    int x,y;
    //start?
    if(_event->Type == sf::Event::MouseButtonPressed)
    {
        x = _input->GetMouseX();
        y = _input->GetMouseY();
        if(x >= X && x <= X+Width && y >= Y && y <= Y+16)
        {
            moving = true;
            movingD.x = x;
            movingD.y = y;
        }
    }
    //end?
    if(_event->Type == sf::Event::MouseButtonReleased)
    {
        moving = false;
    }
    if(_event->Type == sf::Event::MouseMoved)
    {
        x = _input->GetMouseX();
        y = _input->GetMouseY();
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
        closeButtonHover = (x >= (X+Width-15) && y >= (Y+1) && x <= (X+Width-1) && y <= (Y+15));
    }
    if(_event->Type == sf::Event::MouseButtonReleased)
    {
        if(_event->MouseButton.Button == sf::Mouse::Left)
        {
            if(closeButtonHover)
            {
                std::list<std::string> x;
                x.push_back("menu_close");
                x.push_back(ID);
                _datalink->pushEvent(x);
                Hide();
            }
        }
    }
    for(std::list<GUIElement>::iterator it = GuiElements.begin(); it != GuiElements.end(); it++)
    {
        it->handleEvent(_datalink, _event, _input, X, Y+16);
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
