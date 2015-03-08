#ifndef _Music_hpp_
#define _Music_hpp_

#include <Assets\Asset.hpp>
#include <SFML\Audio.hpp>

using namespace std;
extern void ug::log(std::string);

class Music : public Asset
{
private:
	sf::Music* data;

public:
	Music(string* _id, string _path);
	~Music();

	sf::Music* getMusic();
	void load();
	void unload();
};

#endif // !_Music_hpp_