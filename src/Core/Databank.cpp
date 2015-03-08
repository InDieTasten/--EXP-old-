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
	string* index = new string(_id);
	textures.insert(pair<string*, Texture*>(index, new Texture(index, _path)));
	//WORK debug output
}
void Databank::removeTexture(string* _id)
{
	//WORK check for valid id
	for (auto i : textures)
	{
		if (*(i.first) == *_id)
		{
			i.second->unload();
			//WORK make sure all pointers to it are removed
			textures.erase(i.first);
			break;
		}
	}
	//WORK debug output
}
Texture* Databank::getTexture(string *_id)
{
	//WORK check for valid id
	for (auto i : textures)
	{
		if (*(i.first) == *_id)
		{
			return i.second;
		}
	}
	return getTexture(new string("missing"));
	//WORK debug output
}
void Databank::addFont(string _id, string _path)
{
	//WORK check for id already existing
	//WORK check for valid path
	string* index = new string(_id);
	fonts.insert(pair<string*, Font*>(index, new Font(index, _path)));
	//WORK debug output
}
void Databank::removeFont(string* _id)
{
	//WORK check for valid id
	for (auto i : fonts)
	{
		if (*(i.first) == *_id)
		{
			i.second->unload();
			//WORK make sure all pointers to it are removed
			fonts.erase(i.first);
			break;
		}
	}
	//WORK debug output
}
Font* Databank::getFont(string* _id)
{
	//WORK check for valid id
	for (auto i : fonts)
	{
		if (*(i.first) == *_id)
		{
			return i.second;
		}
	}
	return getFont(new string("missing"));
	//WORK debug output
}
void Databank::addSound(string _id, string _path)
{
	//WORK
}
void Databank::removeSound(string* _id)
{
	//WORK
}
Sound* Databank::getSound(string* _id)
{
	//WORK check for valid id
	return sounds.find(*_id)->second;
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
Music* Databank::getMusic(string* _id)
{
	//WORK check for valid id
	return tracks.find(*_id)->second;
}
void Databank::addVideo(string _id, string _path)
{
	//WORK check for id already existing
	//WORK check for valid path
	sounds.insert(pair<string, Sound*>(_id, new Sound(_path)));
}
void Databank::removeVideo(string* _id)
{
	//WORK check for valid id
	//WORK unload Texture beforehand
	videos.erase(videos.find(*_id));
}
Video* Databank::getVideo(string* _id)
{
	//WORK check for valid id
	return videos.find(*_id)->second;
}