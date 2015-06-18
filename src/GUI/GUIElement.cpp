#include <GUI\GUIElement.hpp>

GUIElement::GUIElement(AssetManager* _assets) : Responsive(_assets)
{

	EXP::log("[Info]GUIElement has been constructed: " + utils::tostring(this));
}
GUIElement::~GUIElement()
{

	EXP::log("[Info]GUIElement has been destructed: " + utils::tostring(this));
}

void GUIElement::setX(int _x)
{
	x = _x;
}
void GUIElement::setY(int _y)
{
	y = _y;
}
int GUIElement::getX()
{
	return x;
}
int GUIElement::getY()
{
	return y;
}
