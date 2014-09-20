#include "TextBox.hpp"

//CONSTRUCTORS

//DESTRUCTORS

//METHODS
void TextBox::calibrateCursor()
{
    cursor = content.begin();
    for(int i = 0; i < position; i++)
    {
        cursor++;
    }
}
void TextBox::Setup()
{
    position = 0;
    content = "";
    isActive = true;
    multiline = true;
    clicked = false;
    sliderX = 0;
    sliderY = 0;
}
void TextBox::Update(int _x, int _y,std::string _id)
{
    rect.setPosition((float)_x,(float)_y);
    rect.setSize(sf::Vector2f((float)Width,(float)Height));
    rect.setFillColor(sf::Color(20,20,20,150));
    rect.setOutlineThickness(1.0f);
    rect.setOutlineColor(sf::Color(255,255,255,50));

    sf::Vector2f temp = text.findCharacterPos(position);
    curs.setPosition(temp);
    curs.setSize(sf::Vector2f((float)0,(float)12));
    curs.setFillColor(sf::Color(0,0,0,128));
    curs.setOutlineThickness(1.0f);
    curs.setOutlineColor(sf::Color(0,255,0,255));

    text.setColor(sf::Color::White);
    text.setPosition(_x+1, _y+1);
    text.setFont(*dLink->FontGet("$_menuTitle"));
    text.setCharacterSize(12);
    text.setString(content);
    view = dLink->guiView;
    view.reset(sf::FloatRect(_x, _y, Width, Height));

    float posx = _x/(float)dLink->renderWindow->getSize().x;
    float posy = _y/(float)dLink->renderWindow->getSize().y;

    float sizex = Width/(float)dLink->renderWindow->getSize().x;
    float sizey = Height/(float)dLink->renderWindow->getSize().y;
    view.move(sliderX,sliderY);
    view.setViewport(sf::FloatRect(posx, posy, sizex, sizey));
}
void TextBox::Render(int _x, int _y, std::string _id)
{
    dLink->renderWindow->draw(rect);
    dLink->renderWindow->setView(view);
    dLink->renderWindow->draw(text);
    if(clicked)
        dLink->renderWindow->draw(curs);
    dLink->renderWindow->setView(dLink->guiView);
}
void TextBox::handleEvent(sf::Event* _event, int _x, int _y,std::string _id)
{
    if(isActive && _event->type == sf::Event::MouseButtonPressed)
    {
        int x = _event->mouseButton.x;
        int y = _event->mouseButton.y;
        if(x >= _x && x <= _x+Width)
        {
            if(y >= _y && y <= _y+Height)
            {
                clicked = true;
            }
            else
            {
                clicked = false;
            }
        }
        else
        {
            clicked = false;
        }
    }
    else if(isActive && clicked)
    {
        if(multiline)
        {
            if(_event->type == sf::Event::KeyPressed)
            {
                if(_event->key.code == sf::Keyboard::Left)
                {
                    if(position > 0)
                    {
                        position--;
                    }
                }
                if(_event->key.code == sf::Keyboard::Right)
                {
                    if(position < content.size())
                    {
                        position++;
                    }
                }
                if(_event->key.code == sf::Keyboard::Delete)
                {
                    if(position < content.size())
                    {
                        position++;
                        if(position > 0)
                        {
                            position--;
                            calibrateCursor();
                            content.erase(cursor);
                            std::list<std::string> x;
                            x.push_back("textbox_update");
                            x.push_back(_id);
                            x.push_back(content);
                            dLink->pushEvent(x);
                        }
                    }
                }
            }
            else if(_event->type == sf::Event::TextEntered)
            {
                if (static_cast<char>(_event->text.unicode) == sf::Uint32(13))
                {
                    calibrateCursor();
                    content.insert(cursor,'\n');
                    position++;
                    return;
                }
                if (static_cast<char>(_event->text.unicode) == '\b')
                {
                    if(position > 0)
                    {
                        position--;
                        calibrateCursor();
                        content.erase(cursor);
                        std::list<std::string> x;
                        x.push_back("textbox_update");
                        x.push_back(_id);
                        x.push_back(content);
                        dLink->pushEvent(x);
                    }
                    return;
                }
                if (_event->text.unicode < 128)
                {
                    calibrateCursor();
                    if(content.size() == 0)
                    {
                        content.push_back(static_cast<char>(_event->text.unicode));
                        cursor = content.begin();
                    }
                    else
                    {
                        content.insert(cursor,static_cast<char>(_event->text.unicode));
                    }
                    std::list<std::string> x;
                    x.push_back("textbox_update");
                    x.push_back(_id);
                    x.push_back(content);
                    dLink->pushEvent(x);
                    position++;
                }
            }
        }
        else
        {
            if(_event->type == sf::Event::KeyPressed)
            {
                if(_event->key.code == sf::Keyboard::Left)
                {
                    if(position > 0)
                    {
                        position--;
                    }
                }
                if(_event->key.code == sf::Keyboard::Right)
                {
                    if(position < content.size())
                    {
                        position++;
                    }
                }
                if(_event->key.code == sf::Keyboard::Delete)
                {
                    if(position < content.size())
                    {
                        position++;
                        if(position > 0)
                        {
                            position--;
                            calibrateCursor();
                            content.erase(cursor);
                            std::list<std::string> x;
                            x.push_back("textbox_update");
                            x.push_back(_id);
                            x.push_back(content);
                            dLink->pushEvent(x);
                        }
                    }
                }
            }
            else if(_event->type == sf::Event::TextEntered)
            {
                if (static_cast<char>(_event->text.unicode) == sf::Uint32(13))
                {
                    std::list<std::string> x;
                    x.push_back("textbox_submit");
                    x.push_back(_id);
                    x.push_back(content);
                    dLink->pushEvent(x);
                    content = "";
                    position = 0;
                    calibrateCursor();
                    return;
                }
                if (static_cast<char>(_event->text.unicode) == '\b')
                {
                    if(position > 0)
                    {
                        position--;
                        calibrateCursor();
                        content.erase(cursor);
                        std::list<std::string> x;
                        x.push_back("textbox_update");
                        x.push_back(_id);
                        x.push_back(content);
                        dLink->pushEvent(x);
                    }
                    return;
                }
                if (_event->text.unicode < 128)
                {
                    calibrateCursor();
                    if(content.size() == 0)
                    {
                        content.push_back(static_cast<char>(_event->text.unicode));
                        cursor = content.begin();
                    }
                    else
                    {
                        content.insert(cursor,static_cast<char>(_event->text.unicode));
                    }
                    std::list<std::string> x;
                    x.push_back("textbox_update");
                    x.push_back(_id);
                    x.push_back(content);
                    dLink->pushEvent(x);
                    position++;
                }
            }
        }
    }
}
void TextBox::handleSoftEvent(std::list<std::string> _args, int _x, int _y, std::string _id)
{

}
void TextBox::handleTask(std::list<std::string> _args, int _x, int _y, std::string _id)
{
    if(!multiline)
    {
        if(*_args.begin() == "textbox_clear")
        {
            _args.pop_front();
            if(*_args.begin() == _id)
            {
                content = "";
                position = 0;
                calibrateCursor();
            }
        }
    }
}
