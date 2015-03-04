#ifndef _Texture_hpp_
#define _Texture_hpp_

#include <Assets\Asset.hpp>
#include <string>
#include <SFML\Graphics.hpp>

using namespace std;

class Texture : public Asset
{
private:
	sf::Texture* data;

public:
	sf::Texture* getTexture();
	void load();
	void unload();
};

#endif // !_Texture_hpp_