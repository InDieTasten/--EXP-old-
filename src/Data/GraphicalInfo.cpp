#include <Data\GraphicalInfo.hpp>

GraphicalInfo::GraphicalInfo()
{
	texture = nullptr;
	EXP::log("[Info]GraphicalInfo has been constructed: " + utils::tostring(this));
}
GraphicalInfo::~GraphicalInfo()
{
	texture = nullptr;
	EXP::log("[Info]GraphicalInfo has been destructed: " + utils::tostring(this));
}

void GraphicalInfo::draw(sf::RenderTarget& _target, sf::RenderStates _states)
{
	sf::Sprite sprite;
	sprite.setTexture(*texture);
	_target.draw(sprite, _states);
}

void GraphicalInfo::setTexture(sf::Texture* _texture)
{
	texture = _texture;
}
sf::Texture* GraphicalInfo::getTexture()
{
	return texture;
}
