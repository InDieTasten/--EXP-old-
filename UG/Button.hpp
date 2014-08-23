#ifndef _Button_hpp_
#define _Button_hpp_

#include <string.h>
#include <math.h>
#include "DataBank.hpp"

class Button
{
    //MEMBERS
private:
    sf::RectangleShape rect;
    sf::Text displayText;
    bool mouseHover;
public:
    int X;
    int Y;
    int Height;
    int Width;

    std::string Text;
    bool isActive;

    //CONSTRUCTORS

    //DESTRUCTORS

    //METHODS
    void Setup();
    void Update(DataBank* _dataLink, int _x, int _y, std::string _id);
    void Render(DataBank* _dataLink, int _x, int _y, std::string _id);
    void handleEvent(DataBank* datalink, sf::Event* _event, int _x, int _y, std::string _id);
};

#endif
