#include <Assets\Texture.hpp>

Texture::Texture(string* _id, string _path)
{
	id = _id;
	path = _path;
	ug::log("A Texture has been constructed: " + *id);
}
Texture::~Texture()
{
	if (data)
		unload();
	ug::log("A Texture has been destructed: " + *id);
}