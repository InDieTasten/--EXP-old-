#include <Core\Databank.hpp>

Databank::Databank(sf::RenderWindow* _window)
{
	//pointer
	renderWindow = _window;

	//WORK set parents of level and guiManager
}
Databank::~Databank()
{
	//pointer
	renderWindow = nullptr;

	//WORK unset parents of level and guiManager
}
void Databank::addTexture(string _id, string _path)
{
	//WORK check for id already existing
	//WORK check for valid path
	textures.insert(pair<string, Texture*>(_id, new Texture(_path)));
}
void Databank::removeTexture(string* _id)
{
	//WORK check for valid id
	//WORK unload Texture beforehand
	textures.erase(textures.find(*_id));
}
sf::Texture* Databank::getTexture(string* _id)
{
	//WORK check for valid id
	return textures.find(*_id)->second->getTexture();
}
void Databank::addFont(string _id, string _path)
{
	//WORK check for id already existing
	//WORK check for valid path
	fonts.insert(pair<string, Font*>(_id, new Font(_path)));
}
void Databank::removeFont(string* _id)
{
	//WORK check for valid id
	//WORK unload Texture beforehand
	fonts.erase(fonts.find(*_id));
}
sf::Font* Databank::getFont(string* _id)
{
	//WORK check for valid id
	return fonts.find(*_id)->second->getFont();
}
void Databank::addSound(string _id, string _path)
{
	//WORK check for id already existing
	//WORK check for valid path
	sounds.insert(pair<string, Sound*>(_id, new Sound(_path)));
}
void Databank::removeSound(string* _id)
{
	//WORK check for valid id
	//WORK unload Texture beforehand
	sounds.erase(sounds.find(*_id));
}
sf::SoundBuffer* Databank::getSound(string* _id)
{
	//WORK check for valid id
	return sounds.find(*_id)->second->getSound();
}

void Databank::addMusic(string _id, string _path)
{
	//WORK check for id already existing
	//WORK check for valid path
	tracks.insert(pair<string, Music*>(_id, new Music(_path)));
}
void Databank::removeMusic(string* _id)
{
	//WORK check for valid id
	//WORK unload Texture beforehand
	tracks.erase(tracks.find(*_id));
}
sf::Music* Databank::getMusic(string* _id)
{
	//WORK check for valid id
	return tracks.find(*_id)->second->getMusic();
}