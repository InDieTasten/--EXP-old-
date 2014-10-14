#include "GUI/Elements/Label.hpp"

//CONSTRUCTORS

//DESTRUCTORS

//METHODS

void Label::Setup()
{
    TextColorInactive = dLink->settings.guiLabelTextInactive;
    TextColorActive   = dLink->settings.guiLabelTextActive;
    TextColorHover    = dLink->settings.guiLabelTextHover;
    TextScale = dLink->settings.guiLabelTextScale;
    FontID = dLink->settings.guiLabelFontID;
}
void Label::Update(int _x, int _y, std::string _id, std::string _mID)
{
    if(isActive)
    {
        if(isHover)
        {
            displayText.setColor(TextColorHover);
        }
        else
        {
            displayText.setColor(TextColorActive);
        }
    }
    else
    {
        displayText.setColor(TextColorInactive);
    }

    displayText.setString(DisplayText);
    displayText.setPosition((float)_x,(float)_y);
    displayText.setFont(*dLink->FontGet(FontID));
    displayText.setCharacterSize(TextScale);
}
void Label::Render(int _x, int _y, std::string _id, std::string _mID)
{
    dLink->renderWindow->draw(displayText);
}
void Label::handleEvent(sf::Event* _event, int _x, int _y, std::string _id, std::string _mID)
{
    if(isActive)
    {
        if(_event->type == sf::Event::MouseMoved)
        {
            int mouseX = _event->mouseMove.x;
            int mouseY = _event->mouseMove.y;
            isHover = false;//(mouseX >= _x && mouseX <= _x+Width);
            isHover = false;//isHover && (mouseY >= _y && mouseY <= _y+Height);
        }
    }
}
void Label::handleSoftEvent(std::list<std::string> _args, int _x, int _y, std::string _id, std::string _mID)
{

}
void Label::handleTask(std::list<std::string> _args, int _x, int _y, std::string _id, std::string _mID)
{

}
