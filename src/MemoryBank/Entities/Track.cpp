#include <MemoryBank/Entities/Track.hpp>
//CONSTRUCTORS
Track::Track(std::string _id, std::string _path)
{
    id = _id;
    path = _path;
}

//DESTRUCTORS

//METHODS
void Track::load()
{

}
void Track::unload()
{

}
sf::SoundBuffer* Track::getTrack()
{
    if(buffer.size() == 1)
    {
        return &(*buffer.begin());
    }
    else
    {
        load();
        return &(*buffer.begin());
    }
}
