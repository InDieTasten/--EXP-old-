#include <Assets\Video.hpp>

Video::Video(string* _id, string _path)
{
	id = _id;
	path = _path;
	ug::log("A Video has been constructed: " + *id);
}
Video::~Video()
{
	if (data)
		unload();
	ug::log("A Video has been destructed: " + *id);
}