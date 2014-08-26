#ifndef _KeyBind_hpp_
#define _KeyBind_hpp_

#include <string>

struct KeyBind
{
    std::string ID;

    int keyCode;

    bool rControl;
    bool lControl;
    bool rShift;
    bool lShift;
    bool alt;
};

#endif
