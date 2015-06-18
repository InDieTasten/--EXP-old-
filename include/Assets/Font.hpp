#ifndef _Font_hpp_
#define _Font_hpp_


#include <SFML\Graphics.hpp>
#include <string>
#include <Utilities\Logger.hpp>
#include <Utilities\Conversion.hpp>

extern void EXP::log(std::string);

class Font
{
private:
	sf::Font* data;
	const std::string* id;
	std::string path;
public:
	Font(const std::string* _id, std::string _path);
	~Font();

	void load();
	void unload();
	sf::Font* get();
	std::string getID();
	std::string getPath();
};

#endif // !_Font_hpp_
