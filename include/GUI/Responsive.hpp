#ifndef _Responsive_hpp_
#define _Responsive_hpp_

#include <SFML\Graphics.hpp>

#include <Utilities\Logger.hpp>
#include <Utilities\Conversion.hpp>

class Responsive
{
private:
public:
	Responsive();
	~Responsive();

	virtual void handleEvent(sf::Event* _event) const = 0;
};

#endif // !_Responsive_hpp_