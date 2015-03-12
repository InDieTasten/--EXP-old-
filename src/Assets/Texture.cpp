#include <Assets\Texture.hpp>

Texture::Texture(string* _id, string _path)
{
	id = _id;
	path = _path;
	ug::log("[Info]A Texture has been constructed: " + *id);
}
Texture::~Texture()
{
	if (data)
		unload();
	ug::log("[Info]A Texture has been destructed: " + *id);
}
sf::Texture* Texture::getTexture()
{
	if (data)
	{
		lastget = chrono::steady_clock::now();
		ug::log("[Info]The Texture '" + *id + "' has been gotton");
		return data;
	}
	else {
		load();
		getTexture();
	}
}
void Texture::load()
{
	if (data)
	{
		ug::log("[Warning]Tried to load already loaded Texture: " + *id);
	}
	else {
		ug::log("[Info]Loading Texture: " + *id);
		data = new sf::Texture();
		data->loadFromFile(path);
	}
}
void Texture::unload()
{
	if (!data)
	{
		ug::log("[Warning]Tried to unload already unloaded Texture: " + *id);
	}
	else {
		ug::log("[Info]Unloading Texture: " + *id);
		delete data;
		data = nullptr;
	}
}