#include <Assets\Video.hpp>

Video::Video(string* _id, string _path)
{
	id = _id;
	path = _path;
	ug::log("[Info]A Video has been constructed: " + *id);
}
Video::~Video()
{
	ug::log("[Info]A Video has been destructed: " + *id);
}
//WORK rest of video management