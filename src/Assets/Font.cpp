#include <Assets\Font.hpp>

Font::Font(string* _id, string _path)
{
	id = _id;
	path = _path;
	ug::log("A Font has been constructed: " + *id);
}
Font::~Font()
{
	ug::log("A Font has been deconstructed: " + *id);
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
void Font::load()
{
	if (data)
	{
		ug::log("Tried to load already loaded Font: " + *id);
	}
	else {
		ug::log("Loading Font: " + *id);
		data = new sf::Font();
		data->loadFromFile(path);
	}
}