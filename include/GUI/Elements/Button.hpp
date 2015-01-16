#ifndef _Button_hpp_
#define _Button_hpp_

#include <string.h>
#include <math.h>
#include "MemoryBank/DataBank.hpp"
#include <SFML\Graphics.hpp>

extern DataBank* dLink;

class Button
{
    //MEMBERS
private:
    sf::RectangleShape rect;
    sf::Text displayText;
    bool mouseHover;
    bool clicked;
public:
    int X;
    int Y;
    int Height;
    int Width;

    sf::Color BackgroundColorInactive; //
    sf::Color BackgroundColorActive; //
    sf::Color BackgroundColorHover; //
    sf::Color BackgroundColorClicked;

    sf::Color BorderColorInactive; //
    sf::Color BorderColorActive; //
    sf::Color BorderColorHover; //
    sf::Color BorderColorClicked;

    sf::Color TextColorInactive; //
    sf::Color TextColorActive; //
    sf::Color TextColorHover; //
    sf::Color TextColorClicked;
    int TextScale;
    std::string FontID;

    std::string Text;
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

#endif
