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
    sf::Image img;
    img.LoadFromFile(path);
    img.SetSmooth(false);
    image.push_back(img);
}
void Texture::unload()
{
    if(image.size() == 1)
    {
        image.pop_front();
    }
}
sf::Image* Texture::getImage()
{
    return &(*image.begin());
}
