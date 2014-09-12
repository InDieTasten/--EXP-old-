#include "VertSlider.hpp"

//CONSTRUCTORS

//DESTRUCTORS

//METHODS
void VertSlider::Setup()
{
    isActive = false;
    moveSlide = false;
    hoverInc = false;
    hoverDec = false;

    ButtonBackgroundInactive = dLink->settings.guiVertSliderButtonBackgroundInactive;
    ButtonBackgroundActive   = dLink->settings.guiVertSliderButtonBackgroundActive;
    ButtonBackgroundHover    = dLink->settings.guiVertSliderButtonBackgroundHover;
    ButtonBorderInactive     = dLink->settings.guiVertSliderButtonBorderInactive;
    ButtonBorderActive       = dLink->settings.guiVertSliderButtonBorderActive;
    ButtonBorderHover        = dLink->settings.guiVertSliderButtonBorderHover;
    BarBackgroundInactive    = dLink->settings.guiVertSliderBarBackgroundInactive;
    BarBackgroundActive      = dLink->settings.guiVertSliderBarBackgroundActive;
    BarBorderInactive        = dLink->settings.guiVertSliderBarBorderInactive;
    BarBorderActive          = dLink->settings.guiVertSliderBarBorderActive;
    SliderBackgroundInactive = dLink->settings.guiVertSliderSliderBackgroundInactive;
    SliderBackgroundActive   = dLink->settings.guiVertSliderSliderBackgroundActive;
    SliderBackgroundHover    = dLink->settings.guiVertSliderSliderBackgroundHover;
    SliderBackgroundMoving   = dLink->settings.guiVertSliderSliderBackgroundMoving;
    SliderBorderInactive     = dLink->settings.guiVertSliderSliderBorderInactive;
    SliderBorderActive       = dLink->settings.guiVertSliderSliderBorderActive;
    SliderBorderHover        = dLink->settings.guiVertSliderSliderBorderHover;
    SliderBorderMoving       = dLink->settings.guiVertSliderSliderBorderMoving;
    TextScale                = dLink->settings.guiVertSliderTextScale;
    FontID                   = dLink->settings.guiVertSliderFontID;
}
void VertSlider::Update(int _x, int _y, std::string _id)
{
    if(isActive)
    {
        if(hoverDec)
        {
            decBox.setPosition((float)_y, (float)_x);
            decBox.setSize(sf::Vector2f((float)Height, (float)Height));
            decBox.setFillColor(ButtonBackgroundHover);
            decBox.setOutlineThickness(1.0f);
            decBox.setOutlineColor(ButtonBorderHover);
        }
        else
        {
            decBox.setPosition((float)_y, (float)_x);
            decBox.setSize(sf::Vector2f((float)Height, (float)Height));
            decBox.setFillColor(ButtonBackgroundActive);
            decBox.setOutlineThickness(1.0f);
            decBox.setOutlineColor(ButtonBorderActive);
        }
        if(hoverInc)
        {
            incBox.setPosition((float)_y + Width-Height, (float)_x);
            incBox.setSize(sf::Vector2f((float)_y + Width - (_y + Width-Height), (float)Height));
            incBox.setFillColor(ButtonBackgroundHover);
            incBox.setOutlineThickness(1.0f);
            incBox.setOutlineColor(ButtonBorderHover);
        }
        else
        {
            incBox.setPosition((float)_y + Width-Height, (float)_x);
            incBox.setSize(sf::Vector2f((float)_y + Width - (_y + Width-Height), (float)Height));
            incBox.setFillColor(ButtonBackgroundActive);
            incBox.setOutlineThickness(1.0f);
            incBox.setOutlineColor(ButtonBorderActive);
        }
        if(hoverSlide)
        {
            if(moveSlide)
            {
                slider.setPosition((float) 2 + _y + Height+((ratio*(Width-2*Height))/2) + ((value-min)/(max-min))*(Width-2*Height-(ratio*(Width-2*Height))) - (ratio*(Width-2*Height))/2, (float)_x);
                slider.setSize(sf::Vector2f((float) (-2) + _y + Height+((ratio*(Width-2*Height))/2) + ((value-min)/(max-min))*(Width-2*Height-(ratio*(Width-2*Height))) + (ratio*(Width-2*Height))/2 - (2 + _y + Height+((ratio*(Width-2*Height))/2) + ((value-min)/(max-min))*(Width-2*Height-(ratio*(Width-2*Height))) - (ratio*(Width-2*Height))/2), (float)_x+Height - (_x)));
                slider.setFillColor(SliderBackgroundMoving);
                slider.setOutlineThickness(1.0f);
                slider.setOutlineColor(SliderBorderMoving);
            }
            else
            {
                slider.setPosition((float) 2 + _y + Height+((ratio*(Width-2*Height))/2) + ((value-min)/(max-min))*(Width-2*Height-(ratio*(Width-2*Height))) - (ratio*(Width-2*Height))/2, (float)_x);
                slider.setSize(sf::Vector2f((float) (-2) + _y + Height+((ratio*(Width-2*Height))/2) + ((value-min)/(max-min))*(Width-2*Height-(ratio*(Width-2*Height))) + (ratio*(Width-2*Height))/2 - (2 + _y + Height+((ratio*(Width-2*Height))/2) + ((value-min)/(max-min))*(Width-2*Height-(ratio*(Width-2*Height))) - (ratio*(Width-2*Height))/2), (float)_x+Height - (_x)));
                slider.setFillColor(SliderBackgroundHover);
                slider.setOutlineThickness(1.0f);
                slider.setOutlineColor(SliderBorderHover);
            }
        }
        else
        {
            slider.setPosition((float) 2 + _y + Height+((ratio*(Width-2*Height))/2) + ((value-min)/(max-min))*(Width-2*Height-(ratio*(Width-2*Height))) - (ratio*(Width-2*Height))/2, (float)_x);
            slider.setSize(sf::Vector2f((float) (-2) + _y + Height+((ratio*(Width-2*Height))/2) + ((value-min)/(max-min))*(Width-2*Height-(ratio*(Width-2*Height))) + (ratio*(Width-2*Height))/2 - (2 + _y + Height+((ratio*(Width-2*Height))/2) + ((value-min)/(max-min))*(Width-2*Height-(ratio*(Width-2*Height))) - (ratio*(Width-2*Height))/2), (float)_x+Height - (_x)));
            slider.setFillColor(SliderBackgroundActive);
            slider.setOutlineThickness(1.0f);
            slider.setOutlineColor(SliderBorderActive);
        }
        bar.setPosition((float)_y+7, (float)_x+Height/2-2);
        bar.setSize(sf::Vector2f((float)_y + Width-7-(_y+7), (float)_x+Height/2+2-(_x+Height/2-2)));
        bar.setFillColor(BarBackgroundActive);
        bar.setOutlineThickness(1.0f);
        bar.setOutlineColor(BarBorderActive);
    }
    else
    {
        decBox.setPosition((float)_y, (float)_x);
        decBox.setSize(sf::Vector2f((float)Height, (float)Height));
        decBox.setFillColor(ButtonBackgroundInactive);
        decBox.setOutlineThickness(1.0f);
        decBox.setOutlineColor(ButtonBorderInactive);

        incBox.setPosition((float)_y + Width-Height, (float)_x);
        incBox.setSize(sf::Vector2f((float)_y + Width - (_y + Width-Height), (float)Height));
        incBox.setFillColor(ButtonBackgroundInactive);
        incBox.setOutlineThickness(1.0f);
        incBox.setOutlineColor(ButtonBorderInactive);

        bar.setPosition((float)_y+7, (float)_x+Height/2-2);
        bar.setSize(sf::Vector2f((float)_y + Width-7-(_y+7), (float)_x+Height/2+2-(_x+Height/2-2)));
        bar.setFillColor(BarBackgroundInactive);
        bar.setOutlineThickness(1.0f);
        bar.setOutlineColor(BarBorderInactive);

        slider.setPosition((float) 2 + _y + Height+((ratio*(Width-2*Height))/2) + ((value-min)/(max-min))*(Width-2*Height-(ratio*(Width-2*Height))) - (ratio*(Width-2*Height))/2, (float)_x);
        slider.setSize(sf::Vector2f((float) (-2) + _y + Height+((ratio*(Width-2*Height))/2) + ((value-min)/(max-min))*(Width-2*Height-(ratio*(Width-2*Height))) + (ratio*(Width-2*Height))/2 - (2 + _y + Height+((ratio*(Width-2*Height))/2) + ((value-min)/(max-min))*(Width-2*Height-(ratio*(Width-2*Height))) - (ratio*(Width-2*Height))/2), (float)_x+Height - (_x)));
        slider.setFillColor(SliderBackgroundInactive);
        slider.setOutlineThickness(1.0f);
        slider.setOutlineColor(SliderBorderInactive);
    }
    displayText.setString(util::toString(value));
    displayText.setFont(*dLink->FontGet(FontID));
    displayText.setOrigin(floorf(displayText.getLocalBounds().width/2), floorf(displayText.getLocalBounds().height/2));
    displayText.setPosition(floorf(_y+(Width/2.0)),floorf(_x+(Height/2.0)));
    displayText.setCharacterSize(TextScale);
}
void VertSlider::Render(int _x, int _y, std::string _id)
{
    dLink->renderWindow->draw(bar);
    dLink->renderWindow->draw(decBox);
    dLink->renderWindow->draw(incBox);
    dLink->renderWindow->draw(slider);
    dLink->renderWindow->draw(displayText);
}
void VertSlider::handleEvent(sf::Event* _event, int _x, int _y, std::string _id)
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
void VertSlider::handleSoftEvent(std::list<std::string> _args, int _x, int _y, std::string _id)
{

}
void VertSlider::handleTask(std::list<std::string> _args, int _x, int _y, std::string _id)
{

}
