#include "GUI/Elements/VertSlider.hpp"

//CONSTRUCTORS

//DESTRUCTORS

//METHODS
void VertSlider::Setup()
{
    isActive = false;
    moveSlide = false;
    hoverInc = false;
    hoverDec = false;

    ButtonBackgroundInactive = dLink->settings.guiVertsliderButtonBackgroundInactive;
    ButtonBackgroundActive   = dLink->settings.guiVertsliderButtonBackgroundActive;
    ButtonBackgroundHover    = dLink->settings.guiVertsliderButtonBackgroundHover;
    ButtonBorderInactive     = dLink->settings.guiVertsliderButtonBorderInactive;
    ButtonBorderActive       = dLink->settings.guiVertsliderButtonBorderActive;
    ButtonBorderHover        = dLink->settings.guiVertsliderButtonBorderHover;
    BarBackgroundInactive    = dLink->settings.guiVertsliderBarBackgroundInactive;
    BarBackgroundActive      = dLink->settings.guiVertsliderBarBackgroundActive;
    BarBorderInactive        = dLink->settings.guiVertsliderBarBorderInactive;
    BarBorderActive          = dLink->settings.guiVertsliderBarBorderActive;
    SliderBackgroundInactive = dLink->settings.guiVertsliderSliderBackgroundInactive;
    SliderBackgroundActive   = dLink->settings.guiVertsliderSliderBackgroundActive;
    SliderBackgroundHover    = dLink->settings.guiVertsliderSliderBackgroundHover;
    SliderBackgroundMoving   = dLink->settings.guiVertsliderSliderBackgroundMoving;
    SliderBorderInactive     = dLink->settings.guiVertsliderSliderBorderInactive;
    SliderBorderActive       = dLink->settings.guiVertsliderSliderBorderActive;
    SliderBorderHover        = dLink->settings.guiVertsliderSliderBorderHover;
    SliderBorderMoving       = dLink->settings.guiVertsliderSliderBorderMoving;
    TextScale                = dLink->settings.guiVertsliderTextScale;
    FontID                   = dLink->settings.guiVertsliderFontID;
}
void VertSlider::Update(int _x, int _y, std::string _id, std::string _mID)
{
    if(isActive)
    {
        if(hoverDec)
        {
            decBox.setPosition((float)_x, (float)_y);
            decBox.setSize(sf::Vector2f((float)Width, (float)Width));
            decBox.setFillColor(ButtonBackgroundHover);
            decBox.setOutlineThickness(1.0f);
            decBox.setOutlineColor(ButtonBorderHover);
        }
        else
        {
            decBox.setPosition((float)_x, (float)_y);
            decBox.setSize(sf::Vector2f((float)Width, (float)Width));
            decBox.setFillColor(ButtonBackgroundActive);
            decBox.setOutlineThickness(1.0f);
            decBox.setOutlineColor(ButtonBorderActive);
        }
        if(hoverInc)
        {
            incBox.setPosition((float)_x, (float)_y + Height-Width);
            incBox.setSize(sf::Vector2f((float)Width, (float)_y + Height - (_y + Height-Width)));
            incBox.setFillColor(ButtonBackgroundHover);
            incBox.setOutlineThickness(1.0f);
            incBox.setOutlineColor(ButtonBorderHover);
        }
        else
        {

            incBox.setPosition((float)_x, (float)_y + Height-Width);
            incBox.setSize(sf::Vector2f((float)Width, (float)_y + Height - (_y + Height-Width)));
            incBox.setFillColor(ButtonBackgroundActive);
            incBox.setOutlineThickness(1.0f);
            incBox.setOutlineColor(ButtonBorderActive);
        }
        if(moveSlide)
        {
            slider.setPosition((float)_x, (float) 2 + _y + Width+((ratio*(Height-2*Width))/2) + ((value-min)/(max-min))*(Height-2*Width-(ratio*(Height-2*Width))) - (ratio*(Height-2*Width))/2);
            slider.setSize(sf::Vector2f((float)_x+Width - (_x), (float) (-2) + _y + Width+((ratio*(Height-2*Width))/2) + ((value-min)/(max-min))*(Height-2*Width-(ratio*(Height-2*Width))) + (ratio*(Height-2*Width))/2 - (2 + _y + Width+((ratio*(Height-2*Width))/2) + ((value-min)/(max-min))*(Height-2*Width-(ratio*(Height-2*Width))) - (ratio*(Height-2*Width))/2)));
            slider.setFillColor(SliderBackgroundMoving);
            slider.setOutlineThickness(1.0f);
            slider.setOutlineColor(SliderBorderMoving);
        }
        else
        {
            if(hoverSlide)
            {
                slider.setPosition((float)_x, (float) 2 + _y + Width+((ratio*(Height-2*Width))/2) + ((value-min)/(max-min))*(Height-2*Width-(ratio*(Height-2*Width))) - (ratio*(Height-2*Width))/2);
                slider.setSize(sf::Vector2f((float)_x+Width - (_x), (float) (-2) + _y + Width+((ratio*(Height-2*Width))/2) + ((value-min)/(max-min))*(Height-2*Width-(ratio*(Height-2*Width))) + (ratio*(Height-2*Width))/2 - (2 + _y + Width+((ratio*(Height-2*Width))/2) + ((value-min)/(max-min))*(Height-2*Width-(ratio*(Height-2*Width))) - (ratio*(Height-2*Width))/2)));
                slider.setFillColor(SliderBackgroundHover);
                slider.setOutlineThickness(1.0f);
                slider.setOutlineColor(SliderBorderHover);
            }
            else
            {
                slider.setPosition((float)_x, (float) 2 + _y + Width+((ratio*(Height-2*Width))/2) + ((value-min)/(max-min))*(Height-2*Width-(ratio*(Height-2*Width))) - (ratio*(Height-2*Width))/2);
                slider.setSize(sf::Vector2f((float)_x+Width - (_x), (float) (-2) + _y + Width+((ratio*(Height-2*Width))/2) + ((value-min)/(max-min))*(Height-2*Width-(ratio*(Height-2*Width))) + (ratio*(Height-2*Width))/2 - (2 + _y + Width+((ratio*(Height-2*Width))/2) + ((value-min)/(max-min))*(Height-2*Width-(ratio*(Height-2*Width))) - (ratio*(Height-2*Width))/2)));
                slider.setFillColor(SliderBackgroundActive);
                slider.setOutlineThickness(1.0f);
                slider.setOutlineColor(SliderBorderActive);
            }

        }
        bar.setPosition((float)_x+Width/2-2, (float)_y+7);
        bar.setSize(sf::Vector2f((float)_x+Width/2+2-(_x+Width/2-2), (float)_y + Height-7-(_y+7)));
        bar.setFillColor(BarBackgroundActive);
        bar.setOutlineThickness(1.0f);
        bar.setOutlineColor(BarBorderActive);
    }
    else
    {
        decBox.setPosition((float)_x, (float)_y);
        decBox.setSize(sf::Vector2f((float)Width, (float)Width));
        decBox.setFillColor(ButtonBackgroundInactive);
        decBox.setOutlineThickness(1.0f);
        decBox.setOutlineColor(ButtonBorderInactive);

        incBox.setPosition((float)_x, (float)_y + Height-Width);
        incBox.setSize(sf::Vector2f((float)Width, (float)_y + Height - (_y + Height-Width)));
        incBox.setFillColor(ButtonBackgroundInactive);
        incBox.setOutlineThickness(1.0f);
        incBox.setOutlineColor(ButtonBorderInactive);

        bar.setPosition((float)_x+Width/2-2, (float)_y+7);
        bar.setSize(sf::Vector2f((float)_x+Width/2+2-(_x+Width/2-2), (float)_y + Height-7-(_y+7)));
        bar.setFillColor(BarBackgroundInactive);
        bar.setOutlineThickness(1.0f);
        bar.setOutlineColor(BarBorderInactive);

        slider.setPosition((float)_x, (float) 2 + _y + Width+((ratio*(Height-2*Width))/2) + ((value-min)/(max-min))*(Height-2*Width-(ratio*(Height-2*Width))) - (ratio*(Height-2*Width))/2);
        slider.setSize(sf::Vector2f((float)_x+Width - (_x), (float) (-2) + _y + Width+((ratio*(Height-2*Width))/2) + ((value-min)/(max-min))*(Height-2*Width-(ratio*(Height-2*Width))) + (ratio*(Height-2*Width))/2 - (2 + _y + Width+((ratio*(Height-2*Width))/2) + ((value-min)/(max-min))*(Height-2*Width-(ratio*(Height-2*Width))) - (ratio*(Height-2*Width))/2)));
        slider.setFillColor(SliderBackgroundInactive);
        slider.setOutlineThickness(1.0f);
        slider.setOutlineColor(SliderBorderInactive);
    }
    displayText.setString(util::toString(value));
    displayText.setFont(*dLink->FontGet(FontID));
    displayText.setOrigin(floorf(displayText.getLocalBounds().width/2), floorf(displayText.getLocalBounds().height/2));
    displayText.setPosition(floorf(_x+(Width/2.0)),floorf(_y+(Height/2.0)));
    displayText.setRotation(90.0);
    displayText.setCharacterSize(TextScale);
}
void VertSlider::Render(int _x, int _y, std::string _id, std::string _mID)
{
    dLink->renderWindow->draw(bar);
    dLink->renderWindow->draw(decBox);
    dLink->renderWindow->draw(incBox);
    dLink->renderWindow->draw(slider);
    dLink->renderWindow->draw(displayText);
}
void VertSlider::handleEvent(sf::Event* _event, int _x, int _y, std::string _id, std::string _mID)
{
    int mousey;
    if(_event->type == sf::Event::MouseMoved && isActive)
    {
        mousey = _event->mouseMove.y;
        int mousex = _event->mouseMove.x;
        hoverSlide = false;
        if(mousex >= _x && mousex <= _x+Width)
        {
            if(mousey >= _y + Width+((ratio*(Height-2*Width))/2) + ((value-min)/(max-min))*(Height-2*Width-(ratio*(Height-2*Width))) - (ratio*(Height-2*Width))/2 && mousey <= _y + Width+((ratio*(Height-2*Width))/2) + ((value-min)/(max-min))*(Height-2*Width-(ratio*(Height-2*Width))) + (ratio*(Height-2*Width))/2 - 2)
            {
                hoverSlide = true;
            }
        }
        if(moveSlide)
        {
            int delta = mousey-oldMouseY;
            //translate
            value += (max-min) / ((ratio*(Height-2*Width))/2)*ratio * delta;
            if (value>max)
            {
                value = max;
            }
            if (value<min)
            {
                value = min;
            }
            std::list<std::string> x;
            x.push_back("vertslider_move");
            x.push_back(_mID);
            x.push_back(_id);
            x.push_back(util::toString(value));
            dLink->pushEvent(x);
        }
    }
    if(_event->type == sf::Event::MouseButtonReleased && isActive)
    {
        mousey = _event->mouseButton.y;
        if(moveSlide)
        {
            moveSlide = false;
        }
    }
    if(_event->type == sf::Event::MouseButtonPressed && isActive)
    {
        mousey = _event->mouseButton.y;
        if(hoverSlide)
        {
            moveSlide = true;
        }
    }
    oldMouseY = mousey;
}
void VertSlider::handleSoftEvent(std::list<std::string> _args, int _x, int _y, std::string _id, std::string _mID)
{

}
void VertSlider::handleTask(std::list<std::string> _args, int _x, int _y, std::string _id, std::string _mID)
{

}
