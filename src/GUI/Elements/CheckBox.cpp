#include <GUI/Elements/CheckBox.hpp>
//CONSTRUCTORS

//DESTRUCTORS

//METHODS
void CheckBox::Setup()
{
    mouseHover = false;
    checked = false;

    BackgroundColorInactive = dLink->settings.guiCheckboxBackgroundInactive;
    BackgroundColorActive   = dLink->settings.guiCheckboxBackgroundActive;
    BackgroundColorHover    = dLink->settings.guiCheckboxBackgroundHover;
    BackgroundColorChecked  = dLink->settings.guiCheckboxBackgroundChecked;
    BorderColorInactive = dLink->settings.guiCheckboxBorderInactive;
    BorderColorActive   = dLink->settings.guiCheckboxBorderActive;
    BorderColorHover    = dLink->settings.guiCheckboxBorderHover;
    BorderColorChecked  = dLink->settings.guiCheckboxBorderChecked;

}
void CheckBox::Update(int _x, int _y, std::string _id, std::string _mID)
{
    if(isActive)
    {
        if(checked)
        {
            rect.setPosition((float)_x,(float)_y);
            rect.setSize(sf::Vector2f((float)Width,(float)Height));
            rect.setFillColor(BackgroundColorChecked);
            rect.setOutlineThickness(1.0f);
            rect.setOutlineColor(BorderColorChecked);
        }
        else if(mouseHover)
        {
            rect.setPosition((float)_x,(float)_y);
            rect.setSize(sf::Vector2f((float)Width,(float)Height));
            rect.setFillColor(BackgroundColorHover);
            rect.setOutlineThickness(1.0f);
            rect.setOutlineColor(BorderColorHover);
        }
        else
        {
            rect.setPosition((float)_x,(float)_y);
            rect.setSize(sf::Vector2f((float)Width,(float)Height));
            rect.setFillColor(BackgroundColorActive);
            rect.setOutlineThickness(1.0f);
            rect.setOutlineColor(BorderColorActive);
        }
    }
    else
    {
        rect.setPosition((float)_x,(float)_y);
        rect.setSize(sf::Vector2f((float)Width,(float)Height));
        rect.setFillColor(BackgroundColorInactive);
        rect.setOutlineThickness(1.0f);
        rect.setOutlineColor(BorderColorInactive);
    }
}
void CheckBox::Render(int _x, int _y, std::string _id, std::string _mID)
{
    dLink->renderWindow->draw(rect);
}
void CheckBox::handleEvent(sf::Event* _event, int _x, int _y, std::string _id, std::string _mID)
{
    if(isActive)
    {
        if(_event->type == sf::Event::MouseMoved)
        {
            int mouseX = _event->mouseMove.x;
            int mouseY = _event->mouseMove.y;

            mouseHover = (mouseX >= _x && mouseX <= _x+Width)&&(mouseY >= _y && mouseY <= _y+Height);
        }
        else if(_event->type == sf::Event::MouseButtonReleased)
        {
            if(mouseHover)
            {
                checked = !checked;
            }
        }
    }
}
void CheckBox::handleSoftEvent(std::list<std::string> _args, int _x, int _y, std::string _id, std::string _mID)
{

}
void CheckBox::handleTask(std::list<std::string> _args, int _x, int _y, std::string _id, std::string _mID)
{

}
