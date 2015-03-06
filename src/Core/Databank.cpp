#include <Core\Databank.hpp>

Databank::Databank(sf::RenderWindow* _window)
{
	//pointer
	renderWindow = _window;

	//construct real data
	textures = new map<string*, Texture*>();
	fonts = new map<string*, Font*>();
	sounds = new map<string*, Sound*>();
	tracks = new map<string*, Music*>();
	videos = new map<string*, Video*>();
	level = new Level();
	guiManager = new GUIManager();
}