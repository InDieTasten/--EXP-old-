#ifndef _PhysicalInfo_hpp_
#define _PhysicalInfo_hpp_

#include <Data\Vector.hpp>
#include <Data\Mesh.hpp>
#include <Utilities\Logger.hpp>

class PhysicalInfo
{
private:
	Vector position;
	Vector velocity;
	float mass;
	Mesh collisionMesh;
public:
	PhysicalInfo();
	~PhysicalInfo();

	void setPosition(Vector _position);
	void setVelocity(Vector _velocity);
	void setMass(float _mass);
	void setCollisionMesh(Mesh _collisionMesh);

	Vector getPosition();
	Vector getVelocity();
	float getMass();
	Mesh getCollisionMesh();

	void draw(sf::RenderTarget* _target, sf::Color _color);
};

#endif // !_PhysicalInfo_hpp_
