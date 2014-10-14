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

void SpaceObject::saveToStream(std::ofstream* output)
{
    output->write((char*) &ID, sizeof(ID));
    output->write((char*) &Rotation, sizeof(Rotation));
    output->write((char*) &Mass, sizeof(Mass));
    output->write((char*) &TextureID, sizeof(TextureID));
    output->write((char*) &flyByLocal, sizeof(flyByLocal));
    Position.saveToStream(output);
    Velocity.saveToStream(output);
}
