#ifndef _Texture_hpp_
#define _Texture_hpp_

#include <SFML\Graphics.hpp>
#include <string>
#include <list>

class Texture
{
	//MEMBERS
private:
	std::list<sf::Texture> image;
public:
	std::string id;
	std::string path;
	bool isLoaded;

	//CONSTRUCTORS
	Texture(std::string _id, std::string _path);

	//DESTRUCTORS

	//METHODS
	void load();
	void unload();
	sf::Texture* getImage();
};

#endif
