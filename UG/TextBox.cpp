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
<<<<<<< HEAD
    multiline = false;
    cursor = 0;
    line = 0;
    std::list<std::string>::iterator it=text.begin();
    text.push_back("");

=======
    position = 0;
    content = "";
    isActive = true;
    multiline = true;
    clicked = false;
>>>>>>> origin/indie-only
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
}
void TextBox::Render(int _x, int _y, std::string _id)
{
<<<<<<< HEAD
    for(std::list<sf::Text>::iterator it1 = text1.begin(); it1 != text1.end(); ++it1)
    {
        dLink->renderWindow->draw(rect);
        dLink->renderWindow->draw(c);
        dLink->renderWindow->draw(*it1);
    }
=======
    dLink->renderWindow->draw(rect);
    dLink->renderWindow->draw(text);
    if(clicked)
        dLink->renderWindow->draw(curs);
>>>>>>> origin/indie-only
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
            }else{
                clicked = false;
            }
        } else {
            clicked = false;
        }
    } else
    if(isActive && clicked)
    {
<<<<<<< HEAD
        //häääääääääässlich
        a = line;
        for(std::list<std::string>::iterator it = text.begin();a != -1; it++){a--;}
        if(_event->type == sf::Event::KeyPressed)
=======
        if(multiline)
>>>>>>> origin/indie-only
        {
            if(_event->type == sf::Event::KeyPressed)
            {
                if(_event->key.code == sf::Keyboard::Left)
                {
<<<<<<< HEAD
                    std::list<std::string>::iterator itt =text.begin();
                    std::list<std::string> x;
                    x.push_back("textbox_submit");
                    x.push_back(_id);
                    x.push_back(*itt);
                    dLink->pushEvent(x);
                    *itt="";
                    cursor = 0;
=======
                    if(position > 0)
                    {
                        position--;
                    }
>>>>>>> origin/indie-only
                }
                if(_event->key.code == sf::Keyboard::Right)
                {
<<<<<<< HEAD
                    line++;
                    cursor = 0;
=======
                    if(position < content.size())
                    {
                        position++;
                    }
>>>>>>> origin/indie-only
                }
                if(_event->key.code == sf::Keyboard::Delete)
                {
<<<<<<< HEAD
                    it->erase(cursor--);//
                }
            }
            else if(_event->key.code == sf::Keyboard::Right)
            {
                if(cursor < it->size())//
                {
                    cursor++;
                }
            }
            else if(_event->key.code == sf::Keyboard::Left)
            {
                if(cursor >= 1)
=======
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
>>>>>>> origin/indie-only
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
<<<<<<< HEAD
            }
            else if(_event->key.code == sf::Keyboard::Down)
            {
                if(line >= 1)
=======
                if (_event->text.unicode < 128)
>>>>>>> origin/indie-only
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
<<<<<<< HEAD
            else if(_event->key.code == sf::Keyboard::Up)
=======
        }
        else
        {
            if(_event->type == sf::Event::KeyPressed)
>>>>>>> origin/indie-only
            {
                if(_event->key.code == sf::Keyboard::Left)
                {
                    if(position > 0)
                    {
                        position--;
                    }
                }
<<<<<<< HEAD
            }
            else if(_event->key.code == sf::Keyboard::Delete)
            {
                if(cursor < it->size())//
                {
                    it->erase(cursor);//
                }
            }
            else if(_event->key.code == sf::Keyboard::End)
            {
                cursor = it->size();//
=======
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
>>>>>>> origin/indie-only
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
<<<<<<< HEAD
        else if(_event->type == sf::Event::TextEntered && clear == 0)
        {
            if (_event->text.unicode < 128)
            {
                it->insert(cursor,_event->it->unicode);//?????????????????
                cursor++;
            }
        }
        clear = 0;
=======
>>>>>>> origin/indie-only
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
