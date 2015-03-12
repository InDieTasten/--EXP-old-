#include <Assets\Music.hpp>

Music::Music(string* _id, string _path)
{
	id = _id;
	path = _path;
	ug::log("[Info]A Track has been constructed: " + *id);
}
Music::~Music()
{
	if (data)
		unload();
	ug::log("[Info]A Track has been destructed: " + *id);
}
sf::Music* Music::getMusic()
{
	if (data)
	{
		lastget = chrono::steady_clock::now();
		ug::log("[Info]The Track '" + *id + "' has been gotton");
		return data;
	}
	else {
		load();
		getMusic();
	}
}
void Music::load()
{
	if (data)
	{
		ug::log("[Warning]Tried to load already loaded Track: " + *id);
	}
	else {
		ug::log("[Info]Loading Track: " + *id);
		data = new sf::Music();
		data->openFromFile(path);
	}
}
void Music::unload()
{
	if (!data)
	{
		ug::log("[Warning]Tried to unload already unloaded Track: " + *id);
	}
	else {
		ug::log("[Info]Unloading Track: " + *id);
		delete data;
		data = nullptr;
	}
}