#ifndef _VertSlider_hpp_
#define _VertSlider_hpp_

#include <Utilities/util.hpp>
#include <string.h>
#include <math.h>
#include <MemoryBank/DataBank.hpp>

extern DataBank* dLink;

class VertSlider
{
    //MEMBERS
private:
    bool mouseHover;
    sf::RectangleShape bar;
    sf::RectangleShape decBox;
    sf::RectangleShape incBox;
    sf::RectangleShape slider;
    bool hoverSlide;
    bool hoverDec;
    bool hoverInc;
    bool moveSlide;
    int oldMouseY;
    sf::Text displayText;
public:
    int X;
    int Y;
    int Height;
    int Width;

    float ratio;
    float min;
    float max;
    float value;

    std::string Text;
    bool isActive;


    sf::Color ButtonBackgroundInactive;
    sf::Color ButtonBackgroundActive;
    sf::Color ButtonBackgroundHover;
    sf::Color ButtonBorderInactive;
    sf::Color ButtonBorderActive;
    sf::Color ButtonBorderHover;
    sf::Color BarBackgroundInactive;
    sf::Color BarBackgroundActive;
    sf::Color BarBorderInactive;
    sf::Color BarBorderActive;
    sf::Color SliderBackgroundInactive;
    sf::Color SliderBackgroundActive;
    sf::Color SliderBackgroundHover;
    sf::Color SliderBackgroundMoving;
    sf::Color SliderBorderInactive;
    sf::Color SliderBorderActive;
    sf::Color SliderBorderHover;
    sf::Color SliderBorderMoving;
    int TextScale;
    std::string FontID;


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
