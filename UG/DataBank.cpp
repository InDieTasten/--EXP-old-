#include "DataBank.hpp"
//CONSTRUCTORS
DataBank::DataBank()
{
    runGraphics = true;
    runPhysics = true;
    runModules = true;
    guiMode = true;
    loadPlugins();
}

//DESTRUCTORS

//METHODS
void DataBank::loadPlugins(void)
{
    Loader pLoader;
    std::list<std::string> folder = pLoader.getFolderContent("./content/stock/scripts");
    for (std::list<std::string>::iterator it = folder.begin(); it != folder.end(); it++)
    {
        std::cout << "Found script: ./content/stock/scripts/" << *it << std::endl;
        scripts.push_back(Script("./content/stock/scripts/"+ *it));
    }
}
std::list<Script>* DataBank::GetScripts()
{
    return &scripts;
}

void DataBank::TextureRegister(std::string _id, std::string _path)
{
    for(std::list<Texture>::iterator it = textures.begin(); it != textures.end(); it++)
    {
        if(it->id == _id)
        {
            log("MemBank   ", "Texture ID conflict. Recovery routine aborts registration");
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
    log("MemBank   ", "Tried erasing non-registered texture");
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
    log("MemBank   ", "Tried loading non-registered texture");
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
    log("MemBank   ", "Tried unloading non-registered texture");
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
    log("MemBank   ", "Trying to load non-registered texture. In this case no recovery routine is available and the game might crash right after this message");
}

void DataBank::FontRegister(std::string _id, std::string _path)
{
    for(std::list<Font>::iterator it = fonts.begin(); it != fonts.end(); it++)
    {
        if(it->id == _id)
        {
            log("MemBank   ", "Font ID conflict. Recovery routine aborts registration");
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
    log("MemBank   ", "Tried erasing non-registered font");
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
    log("MemBank   ", "Tried loading non-registered font");
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
    log("MemBank   ", "Tried unloading non-registered font");
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
    log("MemBank   ", "Trying to load non-registered font. In this case no recovery routine is available and the game might crash right after this message");
}

void DataBank::SoundRegister(std::string _id, std::string _path)
{
    for(std::list<Sound>::iterator it = sounds.begin(); it != sounds.end(); it++)
    {
        if(it->id == _id)
        {
            log("MemBank   ", "Sound ID conflict. Recovery routine aborts registration");
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
    log("MemBank   ", "Tried erasing non-registered sound");
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
    log("MemBank   ", "Tried loading non-registered sound");
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
    log("MemBank   ", "Tried unloading non-registered sound");
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
    log("MemBank   ", "Trying to load non-registered sound. In this case no recovery routine is available and the game might crash right after this message");
}

void DataBank::TrackRegister(std::string _id, std::string _path)
{
    for(std::list<Track>::iterator it = tracks.begin(); it != tracks.end(); it++)
    {
        if(it->id == _id)
        {
            log("MemBank   ", "Track ID conflict. Recovery routine aborts registration");
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
    log("MemBank   ", "Tried erasing non-registered track");
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
    log("MemBank   ", "Tried loading non-registered track");
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
    log("MemBank   ", "Tried unloading non-registered track");
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
    log("MemBank   ", "Trying to load non-registered track. In this case no recovery routine is available and the game might crash right after this message");
}

void DataBank::CameraRegister(std::string _id, Vector _position, float _rotation)
{
    for (std::list<Camera>::iterator it = cameras.begin(); it != cameras.end(); it++)
    {
        if (it->id == _id)
        {
            //FEHLER
            return;
        }
    }
    cameras.push_back(Camera(_id, _position, _rotation));
}
void DataBank::CameraErase(std::string _id)
{
    for(std::list<Camera>::iterator it = cameras.begin(); it != cameras.end(); it++)
    {
        if(_id == it->id)
        {
            cameras.erase(it);
        }
    }
}
void DataBank::CameraSetActive(std::string _id)
{
    activeCameraID = _id;
}
Camera* DataBank::CameraGetActive()
{
    for (std::list<Camera>::iterator it = cameras.begin(); it != cameras.end(); it++)
    {
        if (it->id == activeCameraID)
        {
            return &(*it);
        }
    }
    printf("No active Camera found :'(\n");
}
Camera* DataBank::CameraGet(std::string _id)
{
    for (std::list<Camera>::iterator it = cameras.begin(); it != cameras.end(); it++)
    {
        if (it->id == _id)
        {
            return &(*it);
        }
    }
}

void DataBank::saveDataBank(std::string _path) //confusion
{
    std::ofstream filehandle("SAVE.USG");
    //level objects
    int x = Level.SpaceObjectList.size();
    filehandle.write((char*) &x,sizeof(int));
    for (std::list<SpaceObject>::iterator it = Level.SpaceObjectList.begin(); it != Level.SpaceObjectList.end(); it++)
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
    softTasks.push_back(_args);
}
std::list<std::string> DataBank::pullTask()
{
    std::list<std::string> result = *softTasks.begin();
    softTasks.pop_front();
    return result;
}
