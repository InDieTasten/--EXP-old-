#ifndef _GUIDockItem_hpp_
#define _GUIDockItem_hpp_

#include <string>
#include <SFML\Graphics.hpp>

class GUIDockItem
{
	//MEMBERS
private:
public:
	std::string ID;
	std::string ImageID;
	bool Enabled;
	bool Pressed;
	bool mouseHover;
	//CONSTRUCTORS
	GUIDockItem(std::string _id, std::string _imageid);

	//DESTRUCTORS

	//METHODS
};

#endif