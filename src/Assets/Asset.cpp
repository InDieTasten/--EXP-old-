#include <Assets\Asset.hpp>

Asset::Asset()
{

}
Asset::Asset(string* _id, string _path)
{
	id = _id;
	path = _path;
	lastget = chrono::steady_clock::now();
	ug::log("[Info]An asset has been constructed");
}
Asset::~Asset()
{
	ug::log("[Info]An asset has been destructed");
}