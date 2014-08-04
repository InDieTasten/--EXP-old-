#include "HorSlider.hpp"

//CONSTRUCTORS

//DESTRUCTORS

//METHODS
void HorSlider::Setup()
{
    isActive = false;
    moveSlide = false;
}
void HorSlider::Update(DataBank* _dataLink, int _x, int _y)
{
    decBox = sf::RectangleShape::Rectangle((float)_x, (float)_y, (float)_x+Height, (float)_y+16, sf::Color(0,0,0,128), 1.0, sf::Color(255,0,0,200));
    incBox = sf::RectangleShape::Rectangle((float)_x + Width-Height, (float)_y, (float)_x + Width, (float)_y+16, sf::Color(0,0,0,128), 1.0, sf::Color(0,0,255,200));
    bar    = sf::RectangleShape::Rectangle((float)_x+7, (float)_y+Height/2-2, (float)_x + Width-7, (float)_y+Height/2+2, sf::Color(0,0,0,128), 1.0, sf::Color(120,120,120,200));
    slider = sf::RectangleShape::Rectangle((float) 2 + _x + Height+((ratio*(Width-2*Height))/2) + ((value-min)/(max-min))*(Width-2*Height-(ratio*(Width-2*Height))) - (ratio*(Width-2*Height))/2, (float)_y, (float) (-2) + _x + Height+((ratio*(Width-2*Height))/2) + ((value-min)/(max-min))*(Width-2*Height-(ratio*(Width-2*Height))) + (ratio*(Width-2*Height))/2, (float)_y+Height, sf::Color(0,0,0,128), 1.0, sf::Color(0,255,0,200));
}
void HorSlider::Render(DataBank* _dataLink)
{
    _dataLink->renderWindow->Draw(bar);
    _dataLink->renderWindow->Draw(decBox);
    _dataLink->renderWindow->Draw(incBox);
    _dataLink->renderWindow->Draw(slider);
}
void HorSlider::handleEvent(DataBank* datalink, sf::Event* _event, const sf::Input* _input, int _x, int _y, std::string _id)
{
    int mousex = _input->GetMouseX();
    if(_event->Type == sf::Event::MouseMoved && isActive)
    {
        int mousey = _input->GetMouseY();
        hoverSlide = false;
        if(mousey >= _y && mousey <= _y+Height)
        {
            if(mousex >= _x + Height+((ratio*(Width-2*Height))/2) + ((value-min)/(max-min))*(Width-2*Height-(ratio*(Width-2*Height))) - (ratio*(Width-2*Height))/2 && mousex <= _x + Height+((ratio*(Width-2*Height))/2) + ((value-min)/(max-min))*(Width-2*Height-(ratio*(Width-2*Height))) + (ratio*(Width-2*Height))/2 - 2)
            {
                hoverSlide = true;
            }
        }
        if(moveSlide)
        {
            int delta = mousex-oldMouseX;
            //translate
            value += (max-min) / ((ratio*(Width-2*Height))/2)*ratio * delta;
            if (value>max)
            {
                value = max;
            }
            if (value<min)
            {
                value = min;
            }
        }
    }
    if(_event->Type == sf::Event::MouseButtonReleased && isActive)
    {
        if(moveSlide)
        {
            moveSlide = false;
        }
    }
    if(_event->Type == sf::Event::MouseButtonPressed && isActive)
    {
        if(hoverSlide)
        {
            moveSlide = true;
        }
    }
    oldMouseX = mousex;
}
