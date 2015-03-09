#ifndef _Sound_hpp_
#define _Sound_hpp_

#include <Utilities\Logger.hpp>
#include <Assets/Asset.hpp>
#include <SFML\Audio.hpp>

using namespace std;
extern void ug::log(std::string);

class Sound : public Asset
{
private:
	sf::SoundBuffer* data;

public:
	Sound(string* _id, string _path);
	~Sound();

	sf::SoundBuffer* getSound();
	void load();
	void unload();
};

#endif // !_Sound_hpp_