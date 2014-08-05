#include "GUIElement.hpp"
//CONSTRUCTORS
GUIElement::GUIElement()
{
    codeBox.Setup();
    button.Setup();
    label.Setup();
    horSlider.Setup();
    textBox.Setup();
}
//DESTRUCTORS

//METHODS
void GUIElement::Show()
{
    isHidden = false;
}
void GUIElement::Hide()
{
    isHidden = true;
}

void GUIElement::update(DataBank *dataLink, int _x, int _y)
{
    if(Type == "codebox")
    {
        codeBox.isActive = isActive;
        codeBox.Update(dataLink, _x+X, _y+Y);
    }
    else if (Type == "button")
    {
        button.isActive = isActive;
        button.Update(dataLink, _x+X, _y+Y);
    }
    else if (Type == "label")
    {
        label.Update(dataLink, _x+X, _y+Y);
    }
    else if (Type == "horslider")
    {
        horSlider.isActive = isActive;
        horSlider.Update(dataLink, _x+X, _y+Y);
    }
    else if (Type == "textbox")
    {
        textBox.isActive = isActive;
        textBox.Update(dataLink, _x+X, _y+Y);
    }
}
void GUIElement::render(DataBank *dataLink)
{
    if(Type == "codebox")
    {
        codeBox.Render(dataLink);
    }
    else if (Type == "button")
    {
        button.Render(dataLink);
    }
    else if (Type == "label")
    {
        label.Render(dataLink);
    }
    else if (Type == "horslider")
    {
        horSlider.Render(dataLink);
    }
    else if (Type == "textbox")
    {
        textBox.Render(dataLink);
    }
}
void GUIElement::handleEvent(DataBank* datalink, sf::Event* _event, int _x, int _y)
{
    if(Type == "codebox")
    {
        codeBox.handleEvent(_event, _x+X, _y+Y);
    }
    else if (Type == "button")
    {
        button.handleEvent(datalink, _event, _x+X, _y+Y, ID);
    }
    else if (Type == "horslider")
    {
        horSlider.handleEvent(datalink, _event, _x+X, _y+Y, ID);
    }
    else if (Type == "label")
    {
        label.handleEvent(_event);
    }
    else if (Type == "textBox")
    {
        textBox.handleEvent(_event, _x+X, _y+Y);
    }
}
