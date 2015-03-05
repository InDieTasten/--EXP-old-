#ifndef _PhysicalInstance_hpp_
#define _PhysicalInstance_hpp_

#include <Level\Vector.hpp>
#include <SFML\System.hpp>
#include <Level\CollisionMesh.hpp>

class PhysicalInstance
{
private:
	Vector* position;
	Vector* velocity;

	Vector* gravityForce;
	sf::Clock lastupdate;

	Vector* relGhostForce;
	Vector* absGhostForce;
	double* mass;

	CollisionMesh* collMesh;

public:
	PhysicalInstance();
	~PhysicalInstance();

};

#endif // !_PhysicalInstance_hpp_