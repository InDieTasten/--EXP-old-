#include "TextBox.hpp"

//CONSTRUCTORS

//DESTRUCTORS

//METHODS
void TextBox::Setup()
{
    cursorX = 1;
    cursorY = 1;
    content = "";
    multiline = false;
    isActive = true;
}
void TextBox::Update(int _x, int _y,std::string _id)
{
    rect.setPosition((float)_x,(float)_y);
    rect.setSize(sf::Vector2f((float)Width,(float)Height));
    rect.setFillColor(sf::Color(20,20,20,150));
    rect.setOutlineThickness(1.0f);
    rect.setOutlineColor(sf::Color(255,255,255,50));
    if(multiline)
    {

    }
    else
    {

    }
    text.setColor(sf::Color::White);
    text.setPosition(_x+1, _y+1);
    text.setFont(*dLink->FontGet("$_menuTitle"));
    text.setCharacterSize(12);
    text.setString(content);
}
void TextBox::Render(int _x, int _y, std::string _id)
{
    dLink->renderWindow->draw(rect);
    dLink->renderWindow->draw(text);
}
void TextBox::handleEvent(sf::Event* _event, int _x, int _y,std::string _id)
{
    if(isActive)
    {
        if(multiline)
        {
            if(_event->type == sf::Event::KeyPressed)
            {
                if(_event->key.code == sf::Keyboard::Left)
                {
                    cursorX--;
                    if(cursorX < 1)
                        cursorX = 1;
                }
                if(_event->key.code == sf::Keyboard::Right)
                {
                    cursorX++;
                    if(cursorX > content.size()+1)
                        cursorX = content.size()+1;
                }
                if(_event->key.code == sf::Keyboard::Up)
                {
                    cursorY--;
                    if(cursorX < 1)
                        cursorX = 1;
                }
                if(_event->key.code == sf::Keyboard::Down)
                {
                    cursorY--;
                    if(cursorX < 1)
                        cursorX = 1;
                }
            }
            else if(_event->type == sf::Event::TextEntered)
            {
                std::cout << _event->text.unicode << std::endl;
                if (static_cast<char>(_event->text.unicode) == sf::Uint32(13)) {
                    content += "\n";

                    return;
                }
                if (static_cast<char>(_event->text.unicode) == '\b') {
                    if(content.size() == 0) { return; }
                    std::string::iterator it = content.begin();
                    for(int i = 1; i < cursorX-1; i++)
                    {
                        it++;
                    }
                    content.erase(it);
                    cursorX--;
                    return;
                }
                if (_event->text.unicode < 128)
                {
                    std::string::iterator it = content.begin();
                    for(int i = 1; i < cursorX; i++)
                    {
                        it++;
                    }
                    content.insert(it,static_cast<char>(_event->text.unicode));
                    std::list<std::string> x;
                    x.push_back("textbox_insert");
                    x.push_back(_id);
                    x.push_back(content);
                    dLink->pushEvent(x);
                    cursorX++;
                }
            }
        }
        else
        {
            if(_event->type == sf::Event::KeyPressed)
            {
                if(_event->key.code == sf::Keyboard::Return)
                {

                }
                if(_event->key.code == sf::Keyboard::Left)
                {
                    cursorX--;
                    if(cursorX < 1)
                        cursorX = 1;
                }
                if(_event->key.code == sf::Keyboard::Right)
                {
                    cursorX++;
                    if(cursorX > content.size()+1)
                        cursorX = content.size()+1;
                }
            }
            else if(_event->type == sf::Event::TextEntered)
            {
                std::cout << _event->text.unicode << std::endl;
                if (static_cast<char>(_event->text.unicode) == sf::Uint32(13)) {
                    std::list<std::string> x;
                    x.push_back("textbox_submit");
                    x.push_back(_id);
                    x.push_back(content);
                    dLink->pushEvent(x);
                    return;
                }
                if (static_cast<char>(_event->text.unicode) == '\b') {
                    if(content.size() == 0) { return; }
                    std::string::iterator it = content.begin();
                    for(int i = 1; i < cursorX-1; i++)
                    {
                        it++;
                    }
                    content.erase(it);
                    cursorX--;
                    return;
                }
                if (_event->text.unicode < 128)
                {
                    std::string::iterator it = content.begin();
                    for(int i = 1; i < cursorX; i++)
                    {
                        it++;
                    }
                    content.insert(it,static_cast<char>(_event->text.unicode));
                    std::list<std::string> x;
                    x.push_back("textbox_insert");
                    x.push_back(_id);
                    x.push_back(content);
                    dLink->pushEvent(x);
                    cursorX++;
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
    if(*_args.begin() == "textbox_clear")
    {
        _args.pop_front();
        if(*_args.begin() == _id)
        {
            content = "";
            cursorX = 1;
            cursorY = 1;
        }
    }
}
