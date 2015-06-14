#include <Data\PhysicalInfo.hpp>

PhysicalInfo::PhysicalInfo()
{
	EXP::log("[Info]PhysicalInfo has been constructed: " + utils::tostring(this));
}
PhysicalInfo::~PhysicalInfo()
{
	EXP::log("[Info]PhysicalInfo has been destructed: " + utils::tostring(this));
}

void PhysicalInfo::setPosition(Vector _position)
{
	position = _position;
}
void PhysicalInfo::setVelocity(Vector _velocity)
{
	velocity = _velocity;
}
void PhysicalInfo::setMass(float _mass)
{
	mass = _mass;
}
void PhysicalInfo::setCollisionMesh(Mesh _collisionMesh)
{
	collisionMesh = _collisionMesh;
}
Vector PhysicalInfo::getPosition()
{
	return position;
}
Vector PhysicalInfo::getVelocity()
{
	return velocity;
}
float PhysicalInfo::getMass()
{
	return mass;
}
Mesh PhysicalInfo::getCollisionMesh()
{
	return collisionMesh;
}
void PhysicalInfo::draw(sf::RenderTarget* _target, sf::Color _color)
{
	sf::Transformable tmp;
	tmp.setPosition((float)position.getX(), (float)position.getY());
	tmp.setRotation(position.getR());
	//draw Mesh
	collisionMesh.draw(_target, tmp, _color);

	////draw velocity line
	//sf::Vertex line[3]{
	//	sf::Vertex(tmp.getPosition(), sf::Color::Blue),
	//	sf::Vertex(tmp.getPosition(), sf::Color::Blue),
	//	sf::Vertex(tmp.getPosition(), sf::Color::Blue)
	//};
	//_target->draw(line, 3, sf::PrimitiveType::LinesStrip);
}
