#include <Assets\AssetManager.hpp>

AssetManager::AssetManager() : FontManager(), TextureManager()
{
	EXP::log("[Info]Constructing AssetManager... " + utils::tostring(this));
	EXP::log("[Info]AssetManager has been constructed: " + utils::tostring(this));
}
AssetManager::~AssetManager()
{
	EXP::log("[Info]Destructing AssetManager... " + utils::tostring(this));
	EXP::log("[Info]AssetManager has been destructed: " + utils::tostring(this));
}
