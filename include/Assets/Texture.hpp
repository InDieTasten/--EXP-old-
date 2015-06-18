#ifndef _Texture_hpp_
#define _Texture_hpp_


#include <SFML\Graphics.hpp>
#include <string>
#include <Utilities\Logger.hpp>
#include <Utilities\Conversion.hpp>

extern void EXP::log(std::string);

class Texture
{
private:
	sf::Texture* data;
	const std::string* id;
	std::string path;
public:
	Texture(const std::string* _id, std::string _path);
	~Texture();

	void load();
	void unload();
	sf::Texture* get();
	std::string getID();
	std::string getPath();
};

#endif // !_Texture_hpp_
