#ifndef Script_hpp
#define Script_hpp

#include <string>
extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

class Script
{
    //MEMBERS
private:
public:
    std::string plugin_content;
    std::string path;
    //std::list<lError> errorlist;
    lua_State* state;

    //CONSTRUCTORS
    Script(std::string _path);

    //DECONSTRUCTORS

    //METHODS
};

#endif
