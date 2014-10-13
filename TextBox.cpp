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
void TextBox::moveview(int _x, int _y)
{
    while((float)_x + (float)Width + (float)sliderX < text.findCharacterPos(position).x)
    {
        sliderX =  sliderX + 16;
    }
    while((float)_x + (float)sliderX > text.findCharacterPos(position).x)
    {
        sliderX =  sliderX - 16;
    }

    while((float)_y + (float)Height + (float)sliderY < text.findCharacterPos(position).y + 14.0f)
    {
        sliderY =  sliderY + 16;
    }
    while((float)_y + (float)sliderY > text.findCharacterPos(position).y)
    {
        sliderY =  sliderY - 16;
    }
}
void TextBox::Setup()
{
    position = 0;
    content = "";
    isActive = true;
    multiline = true;
    clicked = true;
    sliderX = 0;
    sliderY = 0;
}
void TextBox::Update(int _x, int _y,std::string _id, std::string _mID)
{
    rect.setPosition((float)_x,(float)_y);
    rect.setSize(sf::Vector2f((float)Width,(float)Height));
    rect.setFillColor(sf::Color(20,20,20,150));
    rect.setOutlineThickness(1.0f);
    rect.setOutlineColor(sf::Color(255,255,255,50));

    curs.setPosition(text.findCharacterPos(position));
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

    view.setViewport(sf::FloatRect(posx, posy, sizex, sizey));
    view.move(sliderX,sliderY);
}
void TextBox::Render(int _x, int _y, std::string _id, std::string _mID)
{
    dLink->renderWindow->draw(rect);
    dLink->renderWindow->setView(view);
    dLink->renderWindow->draw(text);
    if(clicked)
        dLink->renderWindow->draw(curs);
    dLink->renderWindow->setView(dLink->guiView);
}
void TextBox::handleEvent(sf::Event* _event, int _x, int _y,std::string _id, std::string _mID)
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
                if(sf::Event::MouseLeft)
                {
                    if(content.size() >= 1)
                    {
                        tmp = 0;
                        do
                        {
                            tmpY = text.findCharacterPos(tmp).y;
                            tmp++;
                        }
                        while(tmp < content.size()+1 && tmpY < (float)y + sliderY);
                        tmp-=2;
                        if(!((float)x + sliderX > text.findCharacterPos(tmp).x && text.findCharacterPos(tmp++).y == text.findCharacterPos(tmp).y))
                        {
                            do
                            {
                                tmpX = text.findCharacterPos(tmp).x;
                                tmp--;
                            }
                            while(tmpX > ((float)x+2.0f) + sliderX && tmp < content.size()+1);
                        }

                        tmp++;
                        position = tmp;
                    }
                }
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

                if(_event->key.code == sf::Keyboard::Up)
                {
                    if(text.findCharacterPos(position).y > 8.0f + _y)
                    {


                        for(tmp = 0;text.findCharacterPos(tmp) == sf::Vector2f(text.findCharacterPos(position).y - 8.0f,text.findCharacterPos(position).x);tmp++){}
                        position = tmp;
                    }
                }
                if(_event->key.code == sf::Keyboard::Down)
                {
                    if(text.findCharacterPos(position).y > 8.0f + _y)
                    {
                        for(tmp = 0;text.findCharacterPos(tmp) == sf::Vector2f(text.findCharacterPos(position).y + 8.0f,text.findCharacterPos(position).x);tmp++){}
                        position = tmp;
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
                    text.findCharacterPos(position);
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
        moveview(_x,_y);
    }
}
void TextBox::handleSoftEvent(std::list<std::string> _args, int _x, int _y, std::string _id, std::string _mID)
{

}
void TextBox::handleTask(std::list<std::string> _args, int _x, int _y, std::string _id, std::string _mID)
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
