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
    sf::RectangleShape curs;
    int tmp;
    float tmpX;
    float tmpY;

public:
    int X;
    int Y;
    int Height;
    int Width;
    std::string ID;
    bool isActive;
    std::string content;
    sf::Text text;
    std::string::iterator cursor;
    int position;
    bool multiline;
    bool clicked;
    int sliderX;
    int sliderY;

    sf::View view;

    sf::Color BackgroundInactive;
    sf::Color BackgroundActive;
    sf::Color BackgroundHover;
    sf::Color BorderInactive;
    sf::Color BorderActive;
    sf::Color BorderHover;
    int TextScale;
    std::string FontID;

    //CONSTRUCTORS

    //DESTRUCTORS

    //METHODS
private:
    void calibrateCursor();
    void moveview(int _x, int _y);
public:
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
