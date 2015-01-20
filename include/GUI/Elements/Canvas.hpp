#ifndef _Canvas_hpp_
#define _Canvas_hpp_

#include <string.h>
#include <MemoryBank/DataBank.hpp>

struct line
{
    sf::Vertex line[2];
};

class Canvas
{
    //MEMBERS
private:
    sf::RectangleShape rect;
public:
    int X;
    int Y;
    int Height;
    int Width;
    std::string ID;

    bool isActive;
    sf::View view;

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
    void Update(int _x, int _y, std::string _id, std::string _mID);
    void Render(int _x, int _y, std::string _id, std::string _mID);
    void handleEvent(sf::Event* _event, int _x, int _y, std::string _id, std::string _mID);
    void handleSoftEvent(std::list<std::string> _args, int _x, int _y, std::string _id, std::string _mID);
    void handleTask(std::list<std::string> _args, int _x, int _y, std::string _id, std::string _mID);
};

#endif
