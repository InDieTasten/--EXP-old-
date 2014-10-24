#include "MemoryBank/Level/SpaceObject.hpp"
#include "MemoryBank/DataBank.hpp"

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
    util::toStream(Target, output);
    output.write((char*) &Rotation, sizeof(Rotation));
    output.write((char*) &RotationSpeed, sizeof(RotationSpeed));
    output.write((char*) &Mass, sizeof(Mass));
    util::toStream(TextureID, output);
    output.write((char*) &flyByLocal, sizeof(flyByLocal));
    output.write((char*) &AI, sizeof(AI));
    output.write((char*) &physics, sizeof(physics));
    output.write((char*) &graphics, sizeof(graphics));
    Position.saveToStream(output);
    Velocity.saveToStream(output);
}
void SpaceObject::loadFromStream(std::ifstream& input)
{
    ID = util::fromStream(input);
    Target = util::fromStream(input);
    input.read((char*) &Rotation, sizeof(Rotation));
    input.read((char*) &RotationSpeed, sizeof(RotationSpeed));
    input.read((char*) &Mass, sizeof(Mass));
    TextureID = util::fromStream(input);
    input.read((char*) &flyByLocal, sizeof(flyByLocal));
    input.read((char*) &AI, sizeof(AI));
    input.read((char*) &physics, sizeof(physics));
    input.read((char*) &graphics, sizeof(graphics));
    Position.loadFromStream(input);
    Velocity.loadFromStream(input);
}
