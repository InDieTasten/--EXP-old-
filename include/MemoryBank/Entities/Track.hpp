#ifndef _Track_hpp_
#define _Track_hpp_

#include <SFML\Audio.hpp>
#include <string>
#include <list>

class Track
{
	//MEMBERS
private:
	std::list<sf::SoundBuffer> buffer;
public:
	std::string id;
	std::string path;

	//CONSTRUCTORS
	Track(std::string _id, std::string _path);

	//DESTRUCTORS

	//METHODS
	void load();
	void unload();
	sf::SoundBuffer* getTrack();
};

#endif
