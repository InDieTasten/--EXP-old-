#ifndef _HorSlider_hpp_
#define _HorSlider_hpp_

#include <string.h>
#include <math.h>
#include "DataBank.hpp"

extern DataBank* dLink;

class HorSlider
{
    //MEMBERS
private:
    bool mouseHover;
    sf::RectangleShape bar;
    sf::RectangleShape decBox;
    sf::RectangleShape incBox;
    sf::RectangleShape slider;
    bool hoverSlide;
    bool moveSlide;
    int oldMouseX;
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
    sf::Color SliderBackgroundInactive;
    sf::Color SliderBackgroundActive;
    sf::color SliderBackgroundHover;
    sf::Color SliderBackgroundMoving;
    int TextScale;
    std::string FontID


    //CONSTRUCTORS

    //DESTRUCTORS

    //METHODS
    void Setup();
    void Update(int _x, int _y, std::string _id);
    void Render(int _x, int _y, std::string _id);
    void handleEvent(sf::Event* _event, int _x, int _y, std::string _id);
    void handleSoftEvent(std::list<std::string> _args, int _x, int _y, std::string _id);
    void handleTask(std::list<std::string> _args, int _x, int _y, std::string _id);
};

#endif
