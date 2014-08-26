#include "Button.hpp"

//CONSTRUCTORS

//DESTRUCTORS

//METHODS
void Button::Setup()
{
    mouseHover = false;
}
void Button::Update(int _x, int _y, std::string _id)
{
    if(!mouseHover)
    {
        rect.setPosition((float)_x,(float)_y);
        rect.setSize(sf::Vector2f((float)Width,(float)Height));
        rect.setFillColor(sf::Color(10,80,10,140));
        rect.setOutlineThickness(1.0f);
        rect.setOutlineColor(sf::Color(160,160,160,200));

        displayText.setColor(sf::Color(120,120,120,200));
    }
    else
    {
        if(isActive)
        {
            rect.setPosition((float)_x,(float)_y);
            rect.setSize(sf::Vector2f((float)Width,(float)Height));
            rect.setFillColor(sf::Color(50,50,50,200));
            rect.setOutlineThickness(1.0f);
            rect.setOutlineColor(sf::Color(0,255,0,255));
        }
        else
        {
            rect.setPosition((float)_x,(float)_y);
            rect.setSize(sf::Vector2f((float)Width,(float)Height));
            rect.setFillColor(sf::Color(50,50,50,200));
            rect.setOutlineThickness(1.0f);
            rect.setOutlineColor(sf::Color(200,200,200,255));
        }
        displayText.setColor(sf::Color(200,200,200,200));
    }
    displayText.setString(Text);
    displayText.setFont(*dLink->FontGet("$_menuTitle"));
    displayText.setScale(1.0,1.0);
    displayText.setOrigin(floorf(displayText.getLocalBounds().width/2), floorf(displayText.getLocalBounds().height/2));
    displayText.setPosition(floorf(_x+(Width/2.0)),floorf(_y+(Height/2.0)));
    displayText.setCharacterSize(12);
}
void Button::Render(int _x, int _y, std::string _id)
{
    dLink->renderWindow->draw(rect);
    dLink->renderWindow->draw(displayText);
}
void Button::handleEvent(sf::Event* _event, int _x, int _y, std::string _id)
{
    if(isActive)
    {
        if(_event->type == sf::Event::MouseMoved)
        {
            int mouseX = _event->mouseMove.x;
            int mouseY = _event->mouseMove.y;
            if(mouseX >= _x && mouseX <= _x+Width)
            {
                if(mouseY >= _y && mouseY <= _y+Height)
                {
                    if(!mouseHover)
                    {
                        std::list<std::string> x;
                        x.push_back("button_entered");
                        x.push_back(_id);
                        dLink->pushEvent(x);
                        mouseHover = true;
                    }
                }
                else
                {
                    if(mouseHover)
                    {
                        std::list<std::string> x;
                        x.push_back("button_leave");
                        x.push_back(_id);
                        dLink->pushEvent(x);
                        mouseHover = false;
                    }
                }
            }
            else
            {
                if(mouseHover)
                {
                    std::list<std::string> x;
                    x.push_back("button_leave");
                    x.push_back(_id);
                    dLink->pushEvent(x);
                    mouseHover = false;
                }
            }
        }
        if(_event->type == sf::Event::MouseButtonReleased && isActive)
        {
            if(mouseHover)
            {
                std::list<std::string> x;
                x.push_back("button_released");
                x.push_back(_id);
                dLink->pushEvent(x);
            }
        }
        if(_event->type == sf::Event::MouseButtonPressed && isActive)
        {
            if(mouseHover)
            {
                std::list<std::string> x;
                x.push_back("button_pressed");
                x.push_back(_id);
                dLink->pushEvent(x);
            }
        }
    }
}
void Button::handleSoftEvent(std::list<std::string> _args, int _x, int _y, std::string _id)
{

}
void Button::handleTask(std::list<std::string> _args, int _x, int _y, std::string _id)
{

}
