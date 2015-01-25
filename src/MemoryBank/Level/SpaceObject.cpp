#include <MemoryBank/Level/SpaceObject.hpp>
#include <MemoryBank/DataBank.hpp>

//CONSTRUCTORS
SpaceObject::SpaceObject()
{
	TextureID = "$_missing";
	flyByLocal = false;
}

//DESTRUCTORS

//METHODS

void SpaceObject::saveToStream(std::ofstream& output)
{
	util::toStream(ID, output);
	util::toStream(PositionTarget, output);
	util::toStream(ShootdownTarget, output);
	output.write((char*)&Rotation, sizeof(Rotation));
	output.write((char*)&RotationSpeed, sizeof(RotationSpeed));
	output.write((char*)&Mass, sizeof(Mass));
	util::toStream(TextureID, output);
	output.write((char*)&flyByLocal, sizeof(flyByLocal));
	output.write((char*)&AI, sizeof(AI));
	output.write((char*)&movable, sizeof(movable));
	output.write((char*)&collidable, sizeof(collidable));
	output.write((char*)&gravity, sizeof(gravity));
	output.write((char*)&visible, sizeof(visible));
	Position.saveToStream(output);
	Velocity.saveToStream(output);
}
void SpaceObject::loadFromStream(std::ifstream& input)
{
	ID = util::fromStream(input);
	PositionTarget = util::fromStream(input);
	ShootdownTarget = util::fromStream(input);
	input.read((char*)&Rotation, sizeof(Rotation));
	input.read((char*)&RotationSpeed, sizeof(RotationSpeed));
	input.read((char*)&Mass, sizeof(Mass));
	TextureID = util::fromStream(input);
	input.read((char*)&flyByLocal, sizeof(flyByLocal));
	input.read((char*)&AI, sizeof(AI));
	input.read((char*)&movable, sizeof(movable));
	input.read((char*)&collidable, sizeof(collidable));
	input.read((char*)&gravity, sizeof(gravity));
	input.read((char*)&visible, sizeof(visible));
	Position.loadFromStream(input);
	Velocity.loadFromStream(input);
}
