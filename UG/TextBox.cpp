#include "TextBox.hpp"

//CONSTRUCTORS

//DESTRUCTORS

//METHODS
void TextBox::Setup()
{
    multiline = true;
    cursor = 0;
    line = 0;
    std::list<std::string>::iterator it=text.begin();
    text.push_back("");

}
void TextBox::Update(DataBank* _dataLink, int _x, int _y,std::string _id)
{
    for(std::list<std::string>::iterator it = text.begin(); it != text.end(); ++it)
    {
        std::list<sf::Text>::iterator it1 = text1.begin();
        it1->setString(*it);

        it1->setPosition((float)_x, (float)_y+(12*line));
        it1->setFont(*_dataLink->FontGet("$_menuTitle"));
        it1->setCharacterSize(12.0);
        it1->setScale(1.0,1.0);
        ++it1;
    }

    rect.setPosition((float)_x,(float)_y);
    rect.setSize(sf::Vector2f((float)Width,(float)Height));
    rect.setFillColor(sf::Color(20,20,20,150));
    rect.setOutlineThickness(1.0f);
    rect.setOutlineColor(sf::Color(255,255,255,50));

    c.setPosition((float)_x+(cursor*7),(float)_y+(line*12));
    c.setSize(sf::Vector2f(7,12));
    c.setFillColor(sf::Color(20,150,20,150));
    c.setOutlineThickness(1.0f);
    c.setOutlineColor(sf::Color(255,255,255,50));
}
void TextBox::Render(DataBank* _dataLink, int _x, int _y, std::string _id)
{
    _dataLink->renderWindow->draw(rect);
    _dataLink->renderWindow->draw(c);
    //_dataLink->renderWindow->draw(*it1); //IDT: it1 ist hier nicht deklariert. Immer noch ;)
}
void TextBox::handleEvent(DataBank* datalink,sf::Event* _event, int _x, int _y,std::string _id)
{
    if(isActive)
    {
        if(_event->type == sf::Event::KeyPressed)
        {
            if(_event->key.code == 58)
            {
                clear = 1;
                if(multiline == false)
                {
                    std::list<std::string> x;
                    x.push_back("textbox_submit");
                    x.push_back(_id);
                    //x.push_back(text); // IDT: Listentyp ist std::string, keine Liste von std::string
                    datalink->pushEvent(x);
                    //text=""; // IDT: Du kannst eine std::list<std::string> nicht auf einen leeren string setzen
                    cursor = 0;
                }
                else if(multiline == true)
                {
                    line++;
                    //for(;*it != line;*it++){} // IDT: "it" ist nirgendwo deklariert
                    cursor = 0;
                }
            }
            else if(_event->key.code == 59)
            {
                clear = 1;
                if(cursor>=1)
                {
                    //tmp = *it.substr (0,(cursor-1));// IDT: "it" ist nirgendwo deklariert
                    //tmp2 = *it.substr (cursor,*it.size());// IDT: "it" ist nirgendwo deklariert
                    cursor--;
                    //*it = tmp + tmp2;//????????????? // IDT: "it" ist nirgendwo deklariert
                }
            }
            else if(_event->key.code == 72)
            {
                /*if(cursor < *it.size()) // IDT: "it" ist nirgendwo deklariert
                {
                    cursor++;
                }*/
            }
            else if(_event->key.code == 71)
            {
                if(cursor >= 1)
                {
                    cursor--;
                }
            }
            else if(_event->key.code == 73)
            {
                if(line >= 1)
                {
                    line--;
                }
            }
            else if(_event->key.code == 74)
            {
                if(line >= 1)
                {
                    line++;
                }
            }
            else if(_event->key.code == sf::Keyboard::Delete)
            {
                /*if(cursor < *it.size()) // IDT: "it" ist nirgendwo deklariert
                {
                    tmp = *it.substr (0,(cursor));
                    tmp2 = *it.substr (cursor+1,*it.size());
                    *it = tmp + tmp2;
                }*/
            }
            else if(_event->key.code == sf::Keyboard::End)
            {
                //cursor = *it.size();// IDT: "it" ist nirgendwo deklariert
            }
            else if(_event->key.code == sf::Keyboard::Home)
            {
                cursor = 0;
            }
        }
        else if(_event->type == sf::Event::TextEntered && clear == 0)
        {
            /*if (_event->*it.unicode < 128 && _event->*it.unicode > 31) // IDT: "it" ist nirgendwo deklariert
            {
                tmp = *it.substr (0,(cursor));
                tmp2 = _event->*it.unicode;
                tmp3 = *it.substr (cursor,*it.size());
                *it = tmp +tmp2 + tmp3;
                cursor++;
            }*/
        }
        clear = 0;
    }
}
