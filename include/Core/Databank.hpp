#ifndef _Databank_hpp_
#define _Databank_hpp_

#include <map>
#include <string>
#include <Assets\Texture.hpp>
#include <Assets\Font.hpp>
#include <Assets\Sound.hpp>
#include <Assets\Music.hpp>
#include <Assets\Video.hpp>
#include <Level\Level.hpp>
#include <Core\ThreadManager.hpp>
#include <SFML\Audio.hpp>

using namespace std;

class Databank
{
private:
	std::map<string, Texture>* textures;
	std::map<string, Font>* fonts;
	std::map<string, Sound>* sounds;
	std::map<string, Music>* tracks;
	std::map<string, Video>* videos;

	sf::RenderWindow* renderWindow;
	Level* level;
	ThreadManager* threadManager;
	GUIManager* guiManager;
	
public:
	Databank(sf::RenderWindow* _window);
	~Databank();

	void addTexture(string* _id, string* _path);
	void removeTexture(string* _id);
	sf::Texture* getTexture(string* _id);

	void addFont(string* _id, string* _path);
	void removeFont(string* _id);
	sf::Font* getFont(string* _id);

	void addSound(string* _id, string* _path);
	void removeSound(string* _id);
	sf::Sound* getSound(string* _id);

	void addMusic(string* _id, string* _path);
	void removeMusic(string* _id);
	sf::Music* getMusic(string* _id);

	void addVideo(string* _id, string* _path);
	void removeVideo(string* _id);
	Video* getVideo(string* _id);

};

#endif // !_Databank_hpp_
