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

void GraphicalInfo::setTexture(sf::Texture* _texture)
{
	texture = _texture;
}
sf::Texture* GraphicalInfo::getTexture()
{
	return texture;
}