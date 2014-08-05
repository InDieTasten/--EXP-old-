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

void GUIElement::update(DataBank *datalink, int _x, int _y)
{
    if(Type == "codebox")
    {
        codeBox.isActive = isActive;
        codeBox.Update(datalink, _x+X, _y+Y, ID);
    }
    else if (Type == "button")
    {
        button.isActive = isActive;
        button.Update(datalink, _x+X, _y+Y, ID);
    }
    else if (Type == "label")
    {
        label.isActive = isActive;
        label.Update(datalink, _x+X, _y+Y, ID);
    }
    else if (Type == "horslider")
    {
        horSlider.isActive = isActive;
        horSlider.Update(datalink, _x+X, _y+Y, ID);
    }
    else if (Type == "textbox")
    {
        textBox.isActive = isActive;
        textBox.Update(datalink, _x+X, _y+Y, ID);
    }
}
void GUIElement::render(DataBank *datalink)
{
    if(Type == "codebox")
    {
        codeBox.Render(datalink, _x+X, _y+Y, ID);
    }
    else if (Type == "button")
    {
        button.Render(datalink, _x+X, _y+Y, ID);
    }
    else if (Type == "label")
    {
        label.Render(datalink, _x+X, _y+Y, ID);
    }
    else if (Type == "horslider")
    {
        horSlider.Render(datalink, _x+X, _y+Y, ID);
    }
    else if (Type == "textbox")
    {
        textBox.Render(datalink, _x+X, _y+Y, ID);
    }
}
void GUIElement::handleEvent(DataBank* datalink, sf::Event* _event, int _x, int _y)
{
    if(Type == "codebox")
    {
        codeBox.handleEvent(datalink, _event, _x+X, _y+Y, ID);
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
        label.handleEvent(datalink, _event, _x+X, _y+Y, ID);
    }
    else if (Type == "textbox")
    {
        textBox.handleEvent(datalink, _event, _x+X, _y+Y, ID);
    }
}
