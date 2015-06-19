#ifndef _AssetManager_hpp_
#define _AssetManager_hpp_

#include <Assets\FontManager.hpp>
#include <Assets\TextureManager.hpp>

class AssetManager : public FontManager, public TextureManager
{
private:
public:
	AssetManager();
	~AssetManager();
};

#endif // !_AssetManager_hpp_
