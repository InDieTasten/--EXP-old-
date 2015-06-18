#include <GUI\Label.hpp>

Label::Label(AssetManager* _assets) : GUIElement(_assets)
{
	type = ElementType::Label;
	EXP::log("[Info]Label has been constructed: " + utils::tostring(this));
}
Label::~Label()
{
	EXP::log("[Info]Destructing Label... " + utils::tostring(this));
	EXP::log("[Info]Label has been destructed: " + utils::tostring(this));
}

void Label::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	//WORK
}
void Label::handleEvent(sf::Event* _event)
{
	//WORK
}

void Label::setText(std::string _text)
{
	text = _text;
}
std::string Label::getText()
{
	return text;
}
