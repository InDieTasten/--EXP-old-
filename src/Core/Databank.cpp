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