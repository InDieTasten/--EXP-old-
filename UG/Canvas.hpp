#ifndef _Canvas_hpp_
#define _Canvas_hpp_

#include <string.h>
#include "DataBank.hpp"

struct line
{
    sf::Vertex line[2];
};

class Canvas
{
    //MEMBERS
private:
public:
    int X;
    int Y;
    int Height;
    int Width;
    std::string ID;

    bool isActive;

    std::list<sf::ConvexShape> shapes;
    std::list<sf::ConvexShape> shapebuffer;

    std::list<line> vertex;
    std::list<line> vertexbuffer;
    sf::Color fillColor;
    sf::Color outlineColor;


    //CONSTRUCTORS

    //DESTRUCTORS

    //METHODS
    void Show();
    void Hide();

    void Setup();
    void Update(int _x, int _y, std::string _id);
    void Render(int _x, int _y, std::string _id);
    void handleEvent(sf::Event* _event, int _x, int _y, std::string _id);
    void handleSoftEvent(std::list<std::string> _args, int _x, int _y, std::string _id);
    void handleTask(std::list<std::string> _args, int _x, int _y, std::string _id);
};

#endif
