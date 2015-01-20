#ifndef _CodeBox_hpp_
#define _CodeBox_hpp_

#include <string.h>
#include <MemoryBank/DataBank.hpp>
#include <iostream>
#include <list>

extern DataBank* dLink;

class CodeBox
{
    //MEMBERS
private:
    sf::Text text1;
    char tmp;
    sf::RectangleShape rect;
    sf::RectangleShape c;
    int ViewY;
    int ViewX;
    int cursor_line;
    int cursor_char;
public:
    //std::string text;
    std::list<std::string> text;
    int X;
    int Y;
    int Height;
    int Width;
    float Textsize;
    bool isActive;
    int enter;

    //CONSTRUCTORS

    //DESTRUCTORS

    //METHODS
    void Setup();

    void Update(int _x, int _y, std::string _id, std::string _mID);

    void Render(int _x, int _y, std::string _id, std::string _mID);
    void handleEvent(sf::Event* _event, int _x, int _y, std::string _id, std::string _mID);
    void handleSoftEvent(std::list<std::string> _args, int _x, int _y, std::string _id, std::string _mID);
    void handleTask(std::list<std::string> _args, int _x, int _y, std::string _id, std::string _mID);

    char getInput(int Type,sf::Event* _event);

};

#endif
