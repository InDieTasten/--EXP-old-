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
	if (textures.find(_id) == textures.end())
	{

	}
	else
	{
		
	}
}