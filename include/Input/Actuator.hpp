#ifndef _Actuator_hpp_
#define _Actuator_hpp_

#include <Utilities\Logger.hpp>
#include <Utilities\Conversion.hpp>


class Actuator
{
private:
	virtual float getRawVector() = 0;
	float multiplier;
	float adjustment;
public:
	Actuator();
	~Actuator();
	
	float getControlVector();

	void setMultiplier(float);
	void setAdjustment(float);
	float getMultiplier();
	float getAdjustment();
};



#endif // !_Actuator_hpp_
