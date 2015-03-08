#include <Assets\Font.hpp>

Font::Font(string* _id, string _path)
{
	id = _id;
	path = _path;
	ug::log("A Font has been constructed");
}
Font::~Font()
{
	ug::log("A Font has been deconstructed");
}
sf::Font* Font::getFont()
{
	if (data)
	{
		lastget.restart();
		ug::log("The Font '" + *id + "' has been gotton");
		return data;
	}
	else {
		load();
		getFont();
	}
}