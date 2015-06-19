#include <GUI\Responsive.hpp>

Responsive::Responsive(AssetManager* _assets)
{
	EXP::log("[Info]Constructing Responsive... " + utils::tostring(this));
	assets = _assets;
	EXP::log("[Info]Responsive has been constructed: " + utils::tostring(this));
}
Responsive::~Responsive()
{
	EXP::log("[Info]Destructing Responsive... " + utils::tostring(this));
	EXP::log("[Info]Responsive has been destructed: " + utils::tostring(this));
}
