#ifndef _Label_hpp_
#define _Label_hpp_

#include <string.h>
#include "MemoryBank/DataBank.hpp"

extern DataBank* dLink;

class Label
{
    //MEMBERS
private:
    sf::Text displayText;
public:
    int X;
    int Y;
    std::string DisplayText;
    bool isHover;
    bool isActive;

    sf::Color TextColorInactive;
    sf::Color TextColorActive;
    sf::Color TextColorHover;
    int TextScale;
    std::string FontID;

    //CONSTRUCTORS

    //DESTRUCTORS

    //METHODS
    void Setup();
    void Update(int _x, int _y, std::string _id, std::string _mID);
    void Render(int _x, int _y, std::string _id, std::string _mID);
    void handleEvent(sf::Event* _event, int _x, int _y, std::string _id, std::string _mID);
    void handleSoftEvent(std::list<std::string> _args, int _x, int _y, std::string _id, std::string _mID);
    void handleTask(std::list<std::string> _args, int _x, int _y, std::string _id, std::string _mID);
};

#endif
