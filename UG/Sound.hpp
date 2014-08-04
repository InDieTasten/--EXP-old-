#ifndef _Sound_hpp_
#define _Sound_hpp_

#include <SFML\Audio.hpp>
#include <string>
#include <list>

class Sound
{
	//MEMBERS
private:
	std::list<sf::SoundBuffer> sound;
public:
	std::string id;
	std::string path;

	//CONSTRUCTORS
	Sound(std::string _id, std::string _path);

	//DESTRUCTORS

	//METHODS
	void load();
	void unload();
	sf::SoundBuffer* getSound();
};

#endif