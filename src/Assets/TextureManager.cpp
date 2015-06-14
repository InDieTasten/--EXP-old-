#include <Assets\TextureManager.hpp>

TextureManager::TextureManager()
{
	EXP::log("[Info]TextureManager has been constructed: " + utils::tostring(this));
}
TextureManager::~TextureManager()
{
	if (textures.size() != 0)
	{
		EXP::log("[Warning]Forcefully destructing textures");
		for (auto it : textures)
		{
			delete it.second;
			it.second = nullptr;
		}
	}
	EXP::log("[Info]TextureManager has been destructed: " + utils::tostring(this));
}
void TextureManager::addTexture(std::string _id, std::string _path)
{
	if (textures.count(_id))
	{
		EXP::log("[Error]Tried registrating already registered Texture: " + _id);
		return;
	}
	textures[_id] = nullptr;
	const std::string* ptr = &textures.find(_id)->first;
	textures[*ptr] = new Texture(ptr, _path);
	EXP::log("[Info]Texture has been added to Manager: " + _id);
}
void TextureManager::removeTexture(std::string _id)
{
	textures.erase(textures.find(_id));
	EXP::log("[Info]Texture has been removed from Manager: " + _id);
}
Texture* TextureManager::getTexture(std::string _id)
{
	Texture* tmp = textures[_id];
	if (tmp)
	{
		return tmp;
	}
	else {
		EXP::log("[Warning]Trtied to get unknown Texture: " + _id);
	}
}
