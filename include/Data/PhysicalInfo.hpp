#ifndef _PhysicalInfo_hpp_
#define _PhysicalInfo_hpp_

#include <Data\Vector.hpp>
#include <Data\Mesh.hpp>
#include <Utilities\Logger.hpp>

class PhysicalInfo : private sf::Transformable
{
private:
	Vector position;
	Vector velocity;
	float mass;
	Mesh collisionMesh;
public:
	PhysicalInfo();
	~PhysicalInfo();


};

#endif // !_PhysicalInfo_hpp_