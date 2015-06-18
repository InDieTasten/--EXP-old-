#include <GUI\Responsive.hpp>

Responsive::Responsive(AssetManager* _assets)
{
	assets = _assets;
	EXP::log("[Info]Responsive has been constructed: " + utils::tostring(this));
}
Responsive::~Responsive()
{

	EXP::log("[Info]Responsive has been destructed: " + utils::tostring(this));
}
