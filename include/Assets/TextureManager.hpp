#ifndef _TextureManager_hpp_
#define _TextureManager_hpp_

#include <map>
#include <Assets\Texture.hpp>
#include <Utilities\Logger.hpp>
#include <Utilities\Conversion.hpp>

extern void EXP::log(std::string);

class TextureManager
{
private:
	std::map<std::string, Texture*> textures;

public:
	TextureManager();
	~TextureManager();

	void addTexture(std::string _id, std::string _path);
	void removeTexture(std::string _id);
	Texture* getTexture(std::string _id);
};

#endif // !_TextureManager_hpp_
