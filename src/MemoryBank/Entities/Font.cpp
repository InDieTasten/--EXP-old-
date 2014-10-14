#include "MemoryBank/Entities/Font.hpp"
//CONSTRUCTOR
Font::Font(std::string _id, std::string _path)
{
    id = _id;
    path = _path;
}
//METHODS
void Font::load()
{
    if(font.size() == 0)
    {
        sf::Font temp;
        temp.loadFromFile(path);
        font.push_back(temp);
    }
}
void Font::unload()
{
    if(font.size() == 1)
    {
        font.pop_back();
    }
}
sf::Font* Font::getFont()
{
    if(font.size() == 0)
        load();
    return &(*font.begin());
}
