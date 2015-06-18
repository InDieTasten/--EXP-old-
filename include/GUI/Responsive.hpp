#ifndef _Responsive_hpp_
#define _Responsive_hpp_

#include <SFML\Graphics.hpp>
#include <Assets\AssetManager.hpp>

#include <Utilities\Logger.hpp>
#include <Utilities\Conversion.hpp>

class Responsive
{
private:
	AssetManager* assets;
public:
	Responsive(AssetManager* _assets);
	~Responsive();

	virtual void handleEvent(sf::Event* _event) = 0;
};

#endif // !_Responsive_hpp_
