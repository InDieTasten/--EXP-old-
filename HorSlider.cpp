#include "HorSlider.hpp"

//CONSTRUCTORS

//DESTRUCTORS

//METHODS
void HorSlider::Setup()
{
    isActive = false;
    moveSlide = false;
    hoverInc = false;
    hoverDec = false;

    mouseHover = false;
    Width = 100;
    Height = 16;

    ratio = 0.5;
    min = 1;
    max = 10;
    value = 5;

    ButtonBackgroundInactive = dLink->settings.guiHorsliderButtonBackgroundInactive;
    ButtonBackgroundActive   = dLink->settings.guiHorsliderButtonBackgroundActive;
    ButtonBackgroundHover    = dLink->settings.guiHorsliderButtonBackgroundHover;
    ButtonBorderInactive     = dLink->settings.guiHorsliderButtonBorderInactive;
    ButtonBorderActive       = dLink->settings.guiHorsliderButtonBorderActive;
    ButtonBorderHover        = dLink->settings.guiHorsliderButtonBorderHover;
    BarBackgroundInactive    = dLink->settings.guiHorsliderBarBackgroundInactive;
    BarBackgroundActive      = dLink->settings.guiHorsliderBarBackgroundActive;
    BarBorderInactive        = dLink->settings.guiHorsliderBarBorderInactive;
    BarBorderActive          = dLink->settings.guiHorsliderBarBorderActive;
    SliderBackgroundInactive = dLink->settings.guiHorsliderSliderBackgroundInactive;
    SliderBackgroundActive   = dLink->settings.guiHorsliderSliderBackgroundActive;
    SliderBackgroundHover    = dLink->settings.guiHorsliderSliderBackgroundHover;
    SliderBackgroundMoving   = dLink->settings.guiHorsliderSliderBackgroundMoving;
    SliderBorderInactive     = dLink->settings.guiHorsliderSliderBorderInactive;
    SliderBorderActive       = dLink->settings.guiHorsliderSliderBorderActive;
    SliderBorderHover        = dLink->settings.guiHorsliderSliderBorderHover;
    SliderBorderMoving       = dLink->settings.guiHorsliderSliderBorderMoving;
    TextScale                = dLink->settings.guiHorsliderTextScale;
    FontID                   = dLink->settings.guiHorsliderFontID;
}
void HorSlider::Update(int _x, int _y, std::string _id, std::string _mID)
{
    if(isActive)
    {
        if(hoverDec)
        {
            decBox.setPosition((float)_x, (float)_y);
            decBox.setSize(sf::Vector2f((float)Height, (float)Height));
            decBox.setFillColor(ButtonBackgroundHover);
            decBox.setOutlineThickness(1.0f);
            decBox.setOutlineColor(ButtonBorderHover);
        }
        else
        {
            decBox.setPosition((float)_x, (float)_y);
            decBox.setSize(sf::Vector2f((float)Height, (float)Height));
            decBox.setFillColor(ButtonBackgroundActive);
            decBox.setOutlineThickness(1.0f);
            decBox.setOutlineColor(ButtonBorderActive);
        }
        if(hoverInc)
        {
            incBox.setPosition((float)_x + Width-Height, (float)_y);
            incBox.setSize(sf::Vector2f((float)_x + Width - (_x + Width-Height), (float)Height));
            incBox.setFillColor(ButtonBackgroundHover);
            incBox.setOutlineThickness(1.0f);
            incBox.setOutlineColor(ButtonBorderHover);
        }
        else
        {
            incBox.setPosition((float)_x + Width-Height, (float)_y);
            incBox.setSize(sf::Vector2f((float)_x + Width - (_x + Width-Height), (float)Height));
            incBox.setFillColor(ButtonBackgroundActive);
            incBox.setOutlineThickness(1.0f);
            incBox.setOutlineColor(ButtonBorderActive);
        }
        if(moveSlide)
        {
            slider.setPosition((float) 2 + _x + Height+((ratio*(Width-2*Height))/2) + ((value-min)/(max-min))*(Width-2*Height-(ratio*(Width-2*Height))) - (ratio*(Width-2*Height))/2, (float)_y);
            slider.setSize(sf::Vector2f((float) (-2) + _x + Height+((ratio*(Width-2*Height))/2) + ((value-min)/(max-min))*(Width-2*Height-(ratio*(Width-2*Height))) + (ratio*(Width-2*Height))/2 - (2 + _x + Height+((ratio*(Width-2*Height))/2) + ((value-min)/(max-min))*(Width-2*Height-(ratio*(Width-2*Height))) - (ratio*(Width-2*Height))/2), (float)_y+Height - (_y)));
            slider.setFillColor(SliderBackgroundMoving);
            slider.setOutlineThickness(1.0f);
            slider.setOutlineColor(SliderBorderMoving);
        }
        else
        {
            if(hoverSlide)
            {
                slider.setPosition((float) 2 + _x + Height+((ratio*(Width-2*Height))/2) + ((value-min)/(max-min))*(Width-2*Height-(ratio*(Width-2*Height))) - (ratio*(Width-2*Height))/2, (float)_y);
                slider.setSize(sf::Vector2f((float) (-2) + _x + Height+((ratio*(Width-2*Height))/2) + ((value-min)/(max-min))*(Width-2*Height-(ratio*(Width-2*Height))) + (ratio*(Width-2*Height))/2 - (2 + _x + Height+((ratio*(Width-2*Height))/2) + ((value-min)/(max-min))*(Width-2*Height-(ratio*(Width-2*Height))) - (ratio*(Width-2*Height))/2), (float)_y+Height - (_y)));
                slider.setFillColor(SliderBackgroundHover);
                slider.setOutlineThickness(1.0f);
                slider.setOutlineColor(SliderBorderHover);
            }
            else
            {
                slider.setPosition((float) 2 + _x + Height+((ratio*(Width-2*Height))/2) + ((value-min)/(max-min))*(Width-2*Height-(ratio*(Width-2*Height))) - (ratio*(Width-2*Height))/2, (float)_y);
                slider.setSize(sf::Vector2f((float) (-2) + _x + Height+((ratio*(Width-2*Height))/2) + ((value-min)/(max-min))*(Width-2*Height-(ratio*(Width-2*Height))) + (ratio*(Width-2*Height))/2 - (2 + _x + Height+((ratio*(Width-2*Height))/2) + ((value-min)/(max-min))*(Width-2*Height-(ratio*(Width-2*Height))) - (ratio*(Width-2*Height))/2), (float)_y+Height - (_y)));
                slider.setFillColor(SliderBackgroundActive);
                slider.setOutlineThickness(1.0f);
                slider.setOutlineColor(SliderBorderActive);
            }

        }
        bar.setPosition((float)_x+7, (float)_y+Height/2-2);
        bar.setSize(sf::Vector2f((float)_x + Width-7-(_x+7), (float)_y+Height/2+2-(_y+Height/2-2)));
        bar.setFillColor(BarBackgroundActive);
        bar.setOutlineThickness(1.0f);
        bar.setOutlineColor(BarBorderActive);
    }
    else
    {
        decBox.setPosition((float)_x, (float)_y);
        decBox.setSize(sf::Vector2f((float)Height, (float)Height));
        decBox.setFillColor(ButtonBackgroundInactive);
        decBox.setOutlineThickness(1.0f);
        decBox.setOutlineColor(ButtonBorderInactive);

        incBox.setPosition((float)_x + Width-Height, (float)_y);
        incBox.setSize(sf::Vector2f((float)_x + Width - (_x + Width-Height), (float)Height));
        incBox.setFillColor(ButtonBackgroundInactive);
        incBox.setOutlineThickness(1.0f);
        incBox.setOutlineColor(ButtonBorderInactive);

        bar.setPosition((float)_x+7, (float)_y+Height/2-2);
        bar.setSize(sf::Vector2f((float)_x + Width-7-(_x+7), (float)_y+Height/2+2-(_y+Height/2-2)));
        bar.setFillColor(BarBackgroundInactive);
        bar.setOutlineThickness(1.0f);
        bar.setOutlineColor(BarBorderInactive);

        slider.setPosition((float) 2 + _x + Height+((ratio*(Width-2*Height))/2) + ((value-min)/(max-min))*(Width-2*Height-(ratio*(Width-2*Height))) - (ratio*(Width-2*Height))/2, (float)_y);
        slider.setSize(sf::Vector2f((float) (-2) + _x + Height+((ratio*(Width-2*Height))/2) + ((value-min)/(max-min))*(Width-2*Height-(ratio*(Width-2*Height))) + (ratio*(Width-2*Height))/2 - (2 + _x + Height+((ratio*(Width-2*Height))/2) + ((value-min)/(max-min))*(Width-2*Height-(ratio*(Width-2*Height))) - (ratio*(Width-2*Height))/2), (float)_y+Height - (_y)));
        slider.setFillColor(SliderBackgroundInactive);
        slider.setOutlineThickness(1.0f);
        slider.setOutlineColor(SliderBorderInactive);
    }
    displayText.setString(util::toString(value));
    displayText.setFont(*dLink->FontGet(FontID));
    displayText.setOrigin(floorf(displayText.getLocalBounds().width/2), floorf(displayText.getLocalBounds().height/2));
    displayText.setPosition(floorf(_x+(Width/2.0)),floorf(_y+(Height/2.0)));
    displayText.setCharacterSize(TextScale);
}
void HorSlider::Render(int _x, int _y, std::string _id, std::string _mID)
{
    dLink->renderWindow->draw(bar);
    dLink->renderWindow->draw(decBox);
    dLink->renderWindow->draw(incBox);
    dLink->renderWindow->draw(slider);
    dLink->renderWindow->draw(displayText);
}
void HorSlider::handleEvent(sf::Event* _event, int _x, int _y, std::string _id, std::string _mID)
{
    int mousex;
    if(_event->type == sf::Event::MouseMoved && isActive)
    {
        mousex = _event->mouseMove.x;
        int mousey = _event->mouseMove.y;
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
            int depr = value;
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

            if(value != depr)
            {
                std::list<std::string> x;
                x.push_back("horslider_move");
                x.push_back(_mID);
                x.push_back(_id);
                x.push_back(util::toString(value));
                dLink->pushEvent(x);
            }
        }
    }
    if(_event->type == sf::Event::MouseButtonReleased && isActive)
    {
        mousex = _event->mouseButton.x;
        if(moveSlide)
        {
            moveSlide = false;
        }
    }
    if(_event->type == sf::Event::MouseButtonPressed && isActive)
    {
        mousex = _event->mouseButton.x;
        if(hoverSlide)
        {
            moveSlide = true;
        }
    }
    oldMouseX = mousex;
}
void HorSlider::handleSoftEvent(std::list<std::string> _args, int _x, int _y, std::string _id, std::string _mID)
{

}
void HorSlider::handleTask(std::list<std::string> _args, int _x, int _y, std::string _id, std::string _mID)
{

}
