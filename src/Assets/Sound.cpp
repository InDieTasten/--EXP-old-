#include <Assets\Sound.hpp>

Sound::Sound(string* _id, string _path)
{
	id = _id;
	path = _path;
	ug::log("A Sound has been constructed: " + *id);
}
Sound::~Sound()
{
	if (data)
		unload();
	ug::log("A Sound has been destructed: " + *id);
}
