#ifndef _Databank_hpp_
#define _Databank_hpp_

#include <Utilities/Logger.hpp>
#include <map>
#include <string>
#include <Assets\Texture.hpp>
#include <Assets\Font.hpp>
#include <Assets\Sound.hpp>
#include <Assets\Music.hpp>
#include <Assets\Video.hpp>
#include <Level\Level.hpp>
#include <SFML\Audio.hpp>
#include <Core\GUIManager.hpp>

using namespace std;
extern void ug::log(std::string);

/// <summary>
/// Class holding pretty much the entire game state.
/// Also handles resource management and memory usage
/// </summary>
class Databank
{
private:
	map<string, Texture*> textures;
	map<string, Font*> fonts;
	map<string, Sound*> sounds;
	map<string, Music*> tracks;
	map<string, Video*> videos;

	sf::RenderWindow* renderWindow;
	Level level;
	GUIManager guiManager;
	
public:
	Databank(sf::RenderWindow* _window);
	~Databank();

	void addTexture(string _id, string _path);
	void removeTexture(string* _id);
	sf::Texture* getTexture(string* _id);

	void addFont(string _id, string _path);
	void removeFont(string* _id);
	sf::Font* getFont(string* _id);

	void addSound(string _id, string _path);
	void removeSound(string* _id);
	sf::SoundBuffer* getSound(string* _id);

	void addMusic(string _id, string _path);
	void removeMusic(string* _id);
	sf::Music* getMusic(string* _id);

	void addVideo(string _id, string _path);
	void removeVideo(string* _id);
	Video* getVideo(string* _id);

	/// <summary>
	/// Forces the databank to unload all resources that haven't been used in a specified time
	/// </summary>
	/// <param name="_access">Specifies the time, at which a resource gets unloaded</param>
	void shrink(sf::Time _access);

	/// <summary>
	/// Will inject the thread pointer to the level
	/// </summary>
	void injectEventThread(EventThread* _thread);

};

#endif // !_Databank_hpp_
