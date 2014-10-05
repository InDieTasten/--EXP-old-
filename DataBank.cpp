#include "DataBank.hpp"
//CONSTRUCTORS
DataBank::DataBank()
{
    debug.eventCount = 0;
    debug.taskCount = 0;
    runGraphics = true;
    runPhysics = true;
    runModules = true;
    guiMode = false;
}

//DESTRUCTORS

//METHODS
void DataBank::TextureRegister(std::string _id, std::string _path)
{
    for(std::list<Texture>::iterator it = textures.begin(); it != textures.end(); it++)
    {
        if(it->id == _id)
        {
            LOG::console("[MemBank]&e[Warning] Texture ID conflict. Recovery routine aborts registration");
            return;
        }
    }
    textures.push_back(Texture(_id, _path));
}
void DataBank::TextureErase(std::string _id)
{
    for(std::list<Texture>::iterator it = textures.begin(); it != textures.end(); it++)
    {
        if(it->id == _id)
        {
            it->unload();
            textures.erase(it);
            return;
        }
    }
    LOG::console("[MemBank]&e[Warning] Tried erasing non-registered texture");
}
void DataBank::TextureLoad(std::string _id)
{
    for(std::list<Texture>::iterator it = textures.begin(); it != textures.end(); it++)
    {
        if(it->id == _id)
        {
            it->load();
            return;
        }
    }
    LOG::console("[MemBank]&e[Warning] Tried loading non-registered texture");
}
void DataBank::TextureUnload(std::string _id)
{
    for(std::list<Texture>::iterator it = textures.begin(); it != textures.end(); it++)
    {
        if(it->id == _id)
        {
            it->unload();
            return;
        }
    }
    LOG::console("[MemBank]&e[Warning] Tried unloading non-registered texture");
}
sf::Texture* DataBank::TextureGet(std::string _id)
{
    for(std::list<Texture>::iterator it = textures.begin(); it != textures.end(); it++)
    {
        if(it->id == _id)
        {
            return it->getImage();
        }
    }
    LOG::console("[MemBank]&c[Error] Trying to load non-registered texture. In this case no recovery routine is available and the game might crash right after this message");
}

void DataBank::FontRegister(std::string _id, std::string _path)
{
    for(std::list<Font>::iterator it = fonts.begin(); it != fonts.end(); it++)
    {
        if(it->id == _id)
        {
            LOG::console("[MemBank]&e[Warning] Font ID conflict. Recovery routine aborts registration");
            return;
        }
    }
    fonts.push_back(Font(_id, _path));
}
void DataBank::FontErase(std::string _id)
{
    for(std::list<Font>::iterator it = fonts.begin(); it != fonts.end(); it++)
    {
        if(it->id == _id)
        {
            it->unload();
            fonts.erase(it);
            return;
        }
    }
    LOG::console("[MemBank]&e[Warning] Tried erasing non-registered font");
}
void DataBank::FontLoad(std::string _id)
{
    for(std::list<Font>::iterator it = fonts.begin(); it != fonts.end(); it++)
    {
        if(it->id == _id)
        {
            it->load();
            return;
        }
    }
    LOG::console("[MemBank]&e[Warning] Tried loading non-registered font");
}
void DataBank::FontUnload(std::string _id)
{
    for(std::list<Font>::iterator it = fonts.begin(); it != fonts.end(); it++)
    {
        if(it->id == _id)
        {
            it->unload();
            return;
        }
    }
    LOG::console("[MemBank]&e[Warning] Tried unloading non-registered font");
}
sf::Font* DataBank::FontGet(std::string _id)
{
    for(std::list<Font>::iterator it = fonts.begin(); it != fonts.end(); it++)
    {
        if(it->id == _id)
        {
            return it->getFont();
        }
    }
    LOG::console("[MemBank]&c[Error] Trying to load non-registered font. In this case no recovery routine is available and the game might crash right after this message");
}

void DataBank::SoundRegister(std::string _id, std::string _path)
{
    for(std::list<Sound>::iterator it = sounds.begin(); it != sounds.end(); it++)
    {
        if(it->id == _id)
        {
            LOG::console("[MemBank]&e[Warning] Sound ID conflict. Recovery routine aborts registration");
            return;
        }
    }
    sounds.push_back(Sound(_id, _path));
}
void DataBank::SoundErase(std::string _id)
{
    for(std::list<Sound>::iterator it = sounds.begin(); it != sounds.end(); it++)
    {
        if(it->id == _id)
        {
            it->unload();
            sounds.erase(it);
            return;
        }
    }
    LOG::console("[MemBank]&e[Warning] Tried erasing non-registered sound");
}
void DataBank::SoundLoad(std::string _id)
{
    for(std::list<Sound>::iterator it = sounds.begin(); it != sounds.end(); it++)
    {
        if(it->id == _id)
        {
            it->load();
            return;
        }
    }
    LOG::console("[MemBank]&e[Warning] Tried loading non-registered sound");
}
void DataBank::SoundUnload(std::string _id)
{
    for(std::list<Sound>::iterator it = sounds.begin(); it != sounds.end(); it++)
    {
        if(it->id == _id)
        {
            it->unload();
            return;
        }
    }
    LOG::console("[MemBank]&e[Warning] Tried unloading non-registered sound");
}
sf::SoundBuffer* DataBank::SoundGet(std::string _id)
{
    for(std::list<Sound>::iterator it = sounds.begin(); it != sounds.end(); it++)
    {
        if(it->id == _id)
        {
            return it->getSound();
        }
    }
    LOG::console("[MemBank]&c[Error] Trying to load non-registered sound. In this case no recovery routine is available and the game might crash right after this message");
}

void DataBank::TrackRegister(std::string _id, std::string _path)
{
    for(std::list<Track>::iterator it = tracks.begin(); it != tracks.end(); it++)
    {
        if(it->id == _id)
        {
            LOG::console("[MemBank]&e[Warning] Track ID conflict. Recovery routine aborts registration");
            return;
        }

    }
    tracks.push_back(Track(_id, _path));
}
void DataBank::TrackErase(std::string _id)
{
    for(std::list<Track>::iterator it = tracks.begin(); it != tracks.end(); it++)
    {
        if(it->id == _id)
        {
            it->unload();
            tracks.erase(it);
            return;
        }
    }
    LOG::console("[MemBank]&e[Warning] Tried erasing non-registered track");
}
void DataBank::TrackLoad(std::string _id)
{
    for(std::list<Track>::iterator it = tracks.begin(); it != tracks.end(); it++)
    {
        if(it->id == _id)
        {
            it->load();
            return;
        }
    }
    LOG::console("[MemBank]&e[Warning] Tried loading non-registered track");
}
void DataBank::TrackUnload(std::string _id)
{
    for(std::list<Track>::iterator it = tracks.begin(); it != tracks.end(); it++)
    {
        if(it->id == _id)
        {
            it->unload();
            return;
        }
    }
    LOG::console("[MemBank]&e[Warning] Tried unloading non-registered track");
}
sf::SoundBuffer* DataBank::TrackGet(std::string _id)
{
    for(std::list<Track>::iterator it = tracks.begin(); it != tracks.end(); it++)
    {
        if(it->id == _id)
        {
            return it->getTrack();
        }
    }
    LOG::console("[MemBank]&c[Error] Trying to load non-registered track. In this case no recovery routine is available and the game might crash right after this message");
}
void DataBank::saveDataBank(std::string _path) //confusion
{
    std::ofstream filehandle("SAVE.USG");
    //level objects
    int x = level.activeSystem.SpaceObjectList.size();
    filehandle.write((char*) &x,sizeof(int));
    for (std::list<SpaceObject>::iterator it = level.activeSystem.SpaceObjectList.begin(); it != level.activeSystem.SpaceObjectList.end(); it++)
    {
        it->saveme(&filehandle);
    }
    filehandle.close();
}
void DataBank::loadDataBank(std::string _path) //confusion
{
    std::list<SpaceObject> save;
    std::ifstream filehandle("SAVE.USG");
    int y;
    filehandle.read((char*) &y,sizeof(int));
    for (int z = 0; z < y; z++)
    {
        SpaceObject obj;
        obj.loadme(&filehandle);
        save.push_back(obj);
    }
    filehandle.close();
}

void DataBank::pushEvent(std::list<std::string> _args)
{
    debug.eventCount++;
    softEvents.push_back(_args);
}
std::list<std::string> DataBank::pullEvent()
{
    std::list<std::string> result = *softEvents.begin();
    softEvents.pop_front();
    return result;
}

void DataBank::pushTask(std::list<std::string> _args)
{
    debug.taskCount++;
    softTasks.push_back(_args);
}
std::list<std::string> DataBank::pullTask()
{
    std::list<std::string> result = *softTasks.begin();
    softTasks.pop_front();
    return result;
}
