#ifndef _Label_hpp_
#define _Label_hpp_

#include <string.h>
#include "DataBank.hpp"

extern DataBank* dLink;

class Label
{
    //MEMBERS
private:
    sf::Text displayText;
public:
    int X;
    int Y;
    int Height;
    int Width;
    std::string DisplayText;
    bool isActive;

    //CONSTRUCTORS

    //DESTRUCTORS

    //METHODS
    void Setup();
    void Update(int _x, int _y, std::string _id);
    void Render(int _x, int _y, std::string _id);
    void handleEvent(sf::Event* _event, int _x, int _y, std::string _id);
    void handleSoftEvent(std::list<std::string> _args, int _x, int _y, std::string _id);
    void handleTask(std::list<std::string> _args, int _x, int _y, std::string _id);
};

#endif
