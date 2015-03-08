#include <Assets\Music.hpp>

Music::Music(string* _id, string _path)
{
	id = _id;
	path = _path;
	ug::log("A Track has been constructed: " + *id);
}
Music::~Music()
{
	if (data)
		unload();
	ug::log("A Track has been destructed: " + *id);
}
sf::Music* Music::getMusic()
{
	if (data)
	{
		lastget.restart();
		ug::log("The Track '" + *id + "' has been gotton");
		return data;
	}
	else {
		load();
		getMusic();
	}
}