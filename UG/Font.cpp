#include "Font.hpp"
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
        temp.LoadFromFile(path,12);
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
    return &(*font.begin());
}
