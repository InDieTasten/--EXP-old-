#include "MemoryBank/Entities/Sound.hpp"
//CONSTRUCTORS
Sound::Sound(std::string _id, std::string _path)
{

}
//DESTRUCTORS

//METHODS
void Sound::load()
{

}
void Sound::unload()
{

}
sf::SoundBuffer* Sound::getSound()
{
    if(sound.size() == 1)
    {
        return &(*sound.begin());
    }
    else
    {
        load();
        return &(*sound.begin());
    }
}
