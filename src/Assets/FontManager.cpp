#include <Assets\FontManager.hpp>

FontManager::FontManager()
{
	EXP::log("[Info]FontManager has been constructed: " + utils::tostring(this));
}
FontManager::~FontManager()
{
	if (fonts.size() != 0)
	{
		EXP::log("[Warning]Forcefully destructing fonts");
		for (auto it : fonts)
		{
			delete it.second;
			it.second = nullptr;
		}
	}
	EXP::log("[Info]FontManager has been destructed: " + utils::tostring(this));
}
void FontManager::addFont(std::string _id, std::string _path)
{
	if (fonts.count(_id))
	{
		EXP::log("[Error]Tried registrating already registered Font: " + _id);
		return;
	}
	fonts[_id] = nullptr;
	const std::string* ptr = &fonts.find(_id)->first;
	fonts[*ptr] = new Font(ptr, _path);
	EXP::log("[Info]Font has been added to Manager: " + _id);
}
void FontManager::removeFont(std::string _id)
{
	fonts.erase(fonts.find(_id));
	EXP::log("[Info]Font has been removed from Manager: " + _id);
}
Font* FontManager::getFont(std::string _id)
{
	Font* tmp = fonts[_id];
	if (tmp)
	{
		return tmp;
	}
	else {
		EXP::log("[Warning]Trtied to get unknown Font: " + _id);
	}
}
