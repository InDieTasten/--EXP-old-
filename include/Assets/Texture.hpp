#ifndef _Texture_hpp_
#define _Texture_hpp_


#include <SFML\Graphics.hpp>
#include <string>
#include <Utilities\Logger.hpp>

extern void EXP::log(std::string);

class Texture
{
private:
	sf::Texture* data;
	std::string* id;
	std::string path;
public:
	Texture(std::string* _id, std::string _path);
	~Texture();

	void load();
	void unload();
	sf::Texture* get();
};

#endif // !_Texture_hpp_