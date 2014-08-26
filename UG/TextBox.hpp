#ifndef _TextBox_hpp_
#define _TextBox_hpp_

#include <string.h>
#include "DataBank.hpp"

extern DataBank* dLink;

class TextBox
{
    //MEMBERS
private:
    sf::RectangleShape rect;
public:
    int X;
    int Y;
    int Height;
    int Width;
    std::string ID;
    bool isActive;

    std::string content;
    sf::Text text;
    int cursorX;
    int cursorY;
    bool multiline;

    //CONSTRUCTORS

    //DESTRUCTORS

    //METHODS
    void Show();
    void Hide();

    void Setup();
    void Update(int _x, int _y,std::string _id);
    void Render(int _x, int _y, std::string _id);
    void handleEvent(sf::Event* _event, int _x, int _y,std::string _id);
    void handleSoftEvent(std::list<std::string> _args, int _x, int _y, std::string _id);
    void handleTask(std::list<std::string> _args, int _x, int _y, std::string _id);
};

#endif
