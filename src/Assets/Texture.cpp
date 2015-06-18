#include <Assets\Texture.hpp>

Texture::Texture(const std::string* _id, std::string _path)
{
	EXP::log("[Info]Constructing Texture... " + utils::tostring(this));

	if (!_id)
	{
		EXP::log("[Error]Trying to construct Texture with null-pointer ID");
		return;
	}
	id = _id;
	path = _path;
	data = nullptr;

	//check
	load();
	unload();

	EXP::log("[Info]Texture has been constructed: " + *id);
}
Texture::~Texture()
{
	EXP::log("[Info]Destructing Texture... " + utils::tostring(this));
	std::string tmp = *id;
	if (data)
	{
		EXP::log("[Info]Forcefully unloading Texture: " + tmp);
		unload();
	}
	id = nullptr;
	EXP::log("[Info]Texture has been destructed: " + tmp);
}
void Texture::load()
{
	if (data)
	{
		EXP::log("[Warning]Tried to load already loaded Texture: " + *id);
		return;
	}
	data = new sf::Texture();
	if (!data->loadFromFile(path))
	{
		EXP::log("[Error]Cannot find Texture: " + *id);
		return;
	}
	EXP::log("[Info]Texture has been loaded: " + *id);
}
void Texture::unload()
{
	if (!data)
	{
		EXP::log("[Warning]Tried to unload already unloaded Texture: " + *id);
		return;
	}
	delete data;
	data = nullptr;
	EXP::log("[Info]Texture has been unloaded: " + *id);
}
sf::Texture* Texture::get()
{
	if (!data)
	{
		EXP::log("[Warning]Tried retrieving unloaded Texture: " + *id);
		load();
		if (!data)
		{
			EXP::log("[Error]Could not load Texture!!: " + *id);
			return nullptr;
		}
	}
	return data;
}
std::string Texture::getID()
{
	return *id;
}
std::string Texture::getPath()
{
	return path;
}
