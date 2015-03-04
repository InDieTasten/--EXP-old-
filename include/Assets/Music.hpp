#ifndef _Music_hpp_
#define _Music_hpp_

#include <Assets\Asset.hpp>
#include <SFML\Audio.hpp>

using namespace std;

class Music : public Asset
{
private:
	sf::Music* data;

public:

	sf::Music* getMusic();
	void load();
	void unload();
};

#endif // !_Music_hpp_