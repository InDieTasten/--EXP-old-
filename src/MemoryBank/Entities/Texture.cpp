#include "Texture.hpp"
//CONSTRUCTORS
Texture::Texture(std::string _id, std::string _path)
{
    id = _id;
    path = _path;
}

//DESTRUCTORS

//METHODS
void Texture::load()
{
    sf::Texture img;
    img.loadFromFile(path);
    img.setSmooth(false);
    image.push_back(img);
}
void Texture::unload()
{
    if(image.size() == 1)
    {
        image.pop_front();
    }
}
sf::Texture* Texture::getImage()
{
    if(image.size() == 0)
        load();
    return &(*image.begin());
}
