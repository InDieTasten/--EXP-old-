#include <MemoryBank/Entities/Script.hpp>
extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}
//CONSTRUCTORS
Script::Script(std::string _path)
{
	path = _path;
	state = luaL_newstate();
}

//DECONSTRUCTORS

//METHODS
