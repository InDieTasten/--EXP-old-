#ifndef _Thruster_hpp_
#define _Thruster_hpp_

#include <Data\ResourceType.hpp>
#include <Data\Attachable.hpp>

class Thruster : public Attachable
{
private:
	float thrust;
	ResourceType fuel;
	float isp;
public:
	Thruster();
	~Thruster();



	//SET
	void setThrust(float _thrust);
	void setFuel(ResourceType _resourceType);
	void setISP(float _isp);
	//GET
	float getThrust();
	ResourceType getFuel();
	float getISP();
};

#endif // !_Thruster_hpp_