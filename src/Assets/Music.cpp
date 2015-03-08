#include <Assets\Music.hpp>

Music::Music(string* _id, string _path)
{
	id = _id;
	path = _path;
}
Music::~Music()
{
	if (data)
		unload();
	ug::log("A Track has been destructed")
}