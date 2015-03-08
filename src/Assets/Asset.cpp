#include <Assets\Asset.hpp>

Asset::Asset(string* _id, string _path)
{
	id = _id;
	path = _path;
	lastget = chrono::steady_clock::now();
	ug::log("An asset has been constructed");
}
Asset::~Asset()
{
	ug::log("An asset has been destructed");
}