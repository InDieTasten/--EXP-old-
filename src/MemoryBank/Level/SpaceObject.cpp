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
    output.write((char*) &Rotation, sizeof(Rotation));
    output.write((char*) &Mass, sizeof(Mass));
    util::toStream(TextureID, output);
    output.write((char*) &flyByLocal, sizeof(flyByLocal));
    Position.saveToStream(output);
    Velocity.saveToStream(output);
}
void SpaceObject::loadFromStream(std::ifstream& input)
{
    ID = util::fromStream(input);
    input.read((char*) &Rotation, sizeof(Rotation));
    input.read((char*) &Mass, sizeof(Mass));
    TextureID = util::fromStream(input);
    input.read((char*) &flyByLocal, sizeof(flyByLocal));
    Position.loadFromStream(input);
    Velocity.loadFromStream(input);
}
