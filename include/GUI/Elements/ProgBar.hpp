#ifndef _ProgBar_hpp_
#define _ProgBar_hpp_

#include <string.h>
#include "MemoryBank/DataBank.hpp"

class ProgBar
{
    //MEMBERS
private:
public:
    int X;
    int Y;
    int Height;
    int Width;
    std::string ID;

    //CONSTRUCTORS

    //DESTRUCTORS

    //METHODS
    void Show();
    void Hide();

    void Setup();
};

#endif
