#include "GUIElement.hpp"
//CONSTRUCTORS
GUIElement::GUIElement()
{
	CodeBox.Setup();
	Button.Setup();
	Label.Setup();
	HorSlider.Setup();
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
	if(Type == "codebox") {
		CodeBox.isActive = isActive;
		CodeBox.Update(dataLink, _x+X, _y+Y);
	} else if (Type == "button") {
		Button.isActive = isActive;
		Button.Update(dataLink, _x+X, _y+Y);
	} else if (Type == "label") {
		Label.Update(dataLink, _x+X, _y+Y);
	} else if (Type == "horslider") {
		HorSlider.isActive = isActive;
		HorSlider.Update(dataLink, _x+X, _y+Y);
	}
}
void GUIElement::render(DataBank *dataLink)
{
	if(Type == "codebox"){
		CodeBox.Render(dataLink);
	} else if (Type == "button") {
		Button.Render(dataLink);
	} else if (Type == "label") {
		Label.Render(dataLink);
	} else if (Type == "horslider") {
		HorSlider.Render(dataLink);
	}
}
void GUIElement::handleEvent(DataBank* datalink, sf::Event* _event, const sf::Input* _input, int _x, int _y)
{
	if(Type == "codebox"){
		CodeBox.handleEvent(_event, _input, _x+X, _y+Y);
	} else if (Type == "button") {
		Button.handleEvent(datalink, _event, _input, _x+X, _y+Y, ID);
	} else if (Type == "horslider") {
		HorSlider.handleEvent(datalink, _event, _input, _x+X, _y+Y, ID);
	} else if (Type == "label") {
		Label.handleEvent(_event, _input);
	}
}