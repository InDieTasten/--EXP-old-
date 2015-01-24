#ifndef _LocalControl_hpp_
#define _LocalControl_hpp_

#include <iostream>
#include <MemoryBank/Level/Vector.hpp>
#include <list>

class LocalControl
{
public:
    LocalControl();
    void analyzeAction(std::list<std::string> _action);

    Vector targetPoint; // 0 -> 359
    float translateForward; // 0 -> 100
    float translateBack; // 0 -> 100
    float translateLeft; // 0 -> 100
    float translateRight; // 0 -> 100
};

#endif // _LocalControl_hpp_
