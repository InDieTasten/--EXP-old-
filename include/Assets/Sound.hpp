#ifndef _Sound_hpp_
#define _Sound_hpp_

#include <Assets/Asset.hpp>

using namespace std;

class Sound : public Asset
{
private:
	sf::SoundBuffer* data;

public:
	sf::SoundBuffer* getSound();
	void load();
	void unload();
};

#endif // !_Sound_hpp_