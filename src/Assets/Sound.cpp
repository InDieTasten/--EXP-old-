#include <Assets\Sound.hpp>

Sound::Sound(string* _id, string _path)
{
	id = _id;
	path = _path;
	ug::log("A Sound has been constructed: " + *id);
}
Sound::~Sound()
{
	if (data)
		unload();
	ug::log("A Sound has been destructed: " + *id);
}
sf::SoundBuffer* Sound::getSound()
{
	if (data)
	{
		lastget.restart();
		ug::log("The Sound '" + *id + "' has been gotton");
		return data;
	}
	else {
		load();
		getSound();
	}
}
void Sound::load()
{
	if (data)
	{
		ug::log("Tried to load already loaded Sound: " + *id);
	}
	else {
		ug::log("Loading Sound: " + *id);
		data = new sf::SoundBuffer();
		data->loadFromFile(path);
	}
}
void Sound::unload()
{
	if (!data)
	{
		ug::log("Tried to unload already unloaded Sound: " + *id);
	}
	else {
		ug::log("Unloading Sound: " + *id);
		delete data;
		data = nullptr;
	}
}