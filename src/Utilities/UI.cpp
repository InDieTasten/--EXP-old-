#include <Utilities\UI.hpp>

bool utils::hovering(sf::FloatRect object, sf::Vector2i mouse)
{
	if (mouse.x < object.left)
		return false;
	if (mouse.y < object.top)
		return false;
	if (mouse.x > object.left + object.width)
		return false;
	if (mouse.y > object.top + object.height)
		return false;

	return true;
}
