#ifndef _CheckBox_hpp_
#define _CheckBox_hpp_

#include <SFML/Graphics.hpp>
#include <list>
#include <string>
#include "MemoryBank/DataBank.hpp"

extern DataBank* dLink;

class CheckBox
{
    //MEMBERS
private:
    sf::RectangleShape rect;
    bool mouseHover;
    bool checked;
public:
    int X;
    int Y;
    int Height;
    int Width;

    sf::Color BackgroundColorInactive;
    sf::Color BackgroundColorActive;
    sf::Color BackgroundColorHover;
    sf::Color BackgroundColorChecked;

    sf::Color BorderColorInactive;
    sf::Color BorderColorActive;
    sf::Color BorderColorHover;
    sf::Color BorderColorChecked;


    bool isActive;

    //CONSTRUCTORS

    //DESTRUCTORS

    //METHODS
    void Setup();
    void Update(int _x, int _y, std::string _id, std::string _mID);
    void Render(int _x, int _y, std::string _id, std::string _mID);
    void handleEvent(sf::Event* _event, int _x, int _y, std::string _id, std::string _mID);
    void handleSoftEvent(std::list<std::string> _args, int _x, int _y, std::string _id, std::string _mID);
    void handleTask(std::list<std::string> _args, int _x, int _y, std::string _id, std::string _mID);
};

#endif // _Checkbox_hpp_
