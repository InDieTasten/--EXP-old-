#include "GUI/Elements/Button.hpp"

//CONSTRUCTORS

//DESTRUCTORS

//METHODS
void Button::Setup()
{
    mouseHover = false;

    BackgroundColorInactive = dLink->settings.guiButtonBackgroundInactive;
    BackgroundColorActive   = dLink->settings.guiButtonBackgroundActive;
    BackgroundColorHover    = dLink->settings.guiButtonBackgroundHover;
    BorderColorInactive = dLink->settings.guiButtonBorderInactive;
    BorderColorActive   = dLink->settings.guiButtonBorderActive;
    BorderColorHover    = dLink->settings.guiButtonBorderHover;
    TextColorInactive = dLink->settings.guiButtonTextInactive;
    TextColorActive   = dLink->settings.guiButtonTextActive;
    TextColorHover    = dLink->settings.guiButtonTextHover;
    TextScale = dLink->settings.guiButtonTextScale;
    FontID = dLink->settings.guiButtonFontID;
}
void Button::Update(int _x, int _y, std::string _id, std::string _mID)
{
    if(isActive)
    {
        if(mouseHover)
        {
            rect.setPosition((float)_x,(float)_y);
            rect.setSize(sf::Vector2f((float)Width,(float)Height));
            rect.setFillColor(BackgroundColorHover);
            rect.setOutlineThickness(1.0f);
            rect.setOutlineColor(BorderColorHover);

            displayText.setColor(TextColorHover);
        }
        else
        {
            rect.setPosition((float)_x,(float)_y);
            rect.setSize(sf::Vector2f((float)Width,(float)Height));
            rect.setFillColor(BackgroundColorActive);
            rect.setOutlineThickness(1.0f);
            rect.setOutlineColor(BorderColorActive);

            displayText.setColor(TextColorActive);
        }
    }
    else
    {
        rect.setPosition((float)_x,(float)_y);
        rect.setSize(sf::Vector2f((float)Width,(float)Height));
        rect.setFillColor(BackgroundColorInactive);
        rect.setOutlineThickness(1.0f);
        rect.setOutlineColor(BorderColorInactive);

        displayText.setColor(TextColorInactive);
    }
    displayText.setString(Text);
    displayText.setFont(*dLink->FontGet(FontID));
    displayText.setOrigin(floorf(displayText.getLocalBounds().width/2), floorf(displayText.getLocalBounds().height/2));
    displayText.setPosition(floorf(_x+(Width/2.0)),floorf(_y+(Height/2.0)));
    displayText.setCharacterSize(TextScale);
}
void Button::Render(int _x, int _y, std::string _id, std::string _mID)
{
    dLink->renderWindow->draw(rect);
    dLink->renderWindow->draw(displayText);
}
void Button::handleEvent(sf::Event* _event, int _x, int _y, std::string _id, std::string _mID)
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
                        x.push_back(_mID);
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
                    x.push_back(_mID);
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
                x.push_back(_mID);
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
                x.push_back(_mID);
                x.push_back(_id);
                dLink->pushEvent(x);
            }
        }
    }
}
void Button::handleSoftEvent(std::list<std::string> _args, int _x, int _y, std::string _id, std::string _mID)
{

}
void Button::handleTask(std::list<std::string> _args, int _x, int _y, std::string _id, std::string _mID)
{

}
