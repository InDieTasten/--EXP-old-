#include <Assets\Video.hpp>

Video::Video(string* _id, string _path)
{
	id = _id;
	path = _path;
	ug::log("A Font has been constructed: " + *id);
}