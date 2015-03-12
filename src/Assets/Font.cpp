#include <Assets\Font.hpp>

Font::Font(string* _id, string _path)
{
	id = _id;
	path = _path;
	ug::log("[Info]A Font has been constructed: " + *id);
}
Font::~Font()
{
	if (data)
		unload();
	ug::log("[Info]A Font has been destructed: " + *id);
}
sf::Font* Font::getFont()
{
	if (data)
	{
		lastget = chrono::steady_clock::now();
		ug::log("[Info]The Font '" + *id + "' has been gotton");
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
		ug::log("[Warning]Tried to load already loaded Font: " + *id);
	}
	else {
		ug::log("[Info]Loading Font: " + *id);
		data = new sf::Font();
		data->loadFromFile(path);
	}
}
void Font::unload()
{
	if (!data)
	{
		ug::log("[Warning]Tried to unload already unloaded Font: " + *id);
	}
	else {
		ug::log("[Info]Unloading Font: " + *id);
		delete data;
		data = nullptr;
	}
}