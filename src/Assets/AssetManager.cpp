#include <Assets\AssetManager.hpp>

AssetManager::AssetManager() : FontManager(), TextureManager()
{
	EXP::log("[Info]AssetManager has been constructed: " + utils::tostring(this));
}
AssetManager::~AssetManager()
{
	EXP::log("[Info]AssetManager has been constructed: " + utils::tostring(this));
}
