#include <Assets\Font.hpp>

Font::Font(string* _id, string _path)
{
	id = _id;
	path = _path;
	ug::log("A Font has been constructed");
}