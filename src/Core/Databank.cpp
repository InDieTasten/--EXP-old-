#include <Core\Databank.hpp>

Databank::Databank(EventThread* _eventThread, GraphicsThread* _graphThread)
{
	level = new Level(this, _eventThread, _graphThread);
	guiManager = new GUIManager(this);

	ug::log("[Info]Databank has been constructed");
}
Databank::~Databank()
{
	delete level;
	level = nullptr;
	delete guiManager;
	guiManager = nullptr;

	for (auto it : textures)
	{
		delete it.second;
		delete it.first;
		it.second = nullptr;
	}
	for (auto it : fonts)
	{
		delete it.second;
		delete it.first;
		it.second = nullptr;
	}
	for (auto it : sounds)
	{
		delete it.second;
		delete it.first;
		it.second = nullptr;
	}
	for (auto it : tracks)
	{
		delete it.second;
		delete it.first;
		it.second = nullptr;
	}
	for (auto it : videos)
	{
		delete it.second;
		delete it.first;
		it.second = nullptr;
	}
	ug::log("[Info]Databank has been destructed");
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
			delete i.second;
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
			delete i.second;
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
	//WORK
}
void Databank::addMusic(string _id, string _path)
{
	//WORK
}
void Databank::removeMusic(string* _id)
{
	//WORK
}
Music* Databank::getMusic(string* _id)
{
	//WORK
}
void Databank::addVideo(string _id, string _path)
{
	//WORK
}
void Databank::removeVideo(string* _id)
{
	//WORK
}
Video* Databank::getVideo(string* _id)
{
	//WORK
}
Level* Databank::getLevel()
{
	if (level)
		return level;
	else
		ug::log("[Error]Tried getting non-existant Level");
}