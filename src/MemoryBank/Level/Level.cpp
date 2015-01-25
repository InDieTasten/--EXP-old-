#include <MemoryBank/Level/Level.hpp>

//CONSTRUCTORS
Level::Level()
{
	name = "Default";
	description = "description of level 'default'";

	SolarSystem x;
	x.Description = "description of system 'default'";
	x.ID = "default";
	x.Name = "Default";

	SpaceObject obj1;
	obj1.ID = "default";
	obj1.Position = Vector(0.0, 0.0);
	obj1.Velocity = Vector(0.0, 0.0);
	obj1.Mass = 15.0;
	obj1.TextureID = "$_missing";
	obj1.flyByLocal = true;

	/*SpaceObject obj2;
	obj2.ID = "default2";
	obj2.Position = Vector(-200.0, 0.0);
	obj2.Velocity = Vector(0.0, 0.0);
	obj2.Mass = 15.0;
	obj2.TextureID = "$_missing";
	obj2.flyByLocal = true;*/

	/*SpaceObject obj3;
	obj3.ID = "default3";
	obj3.Position = Vector(200.0, 0.0);
	obj3.Velocity = Vector(0.0, 0.0);
	obj3.Mass = 15.0;
	obj3.TextureID = "$_missing";
	obj3.flyByLocal = true;*/

	x.SpaceObjectList.push_back(obj1);
	//x.SpaceObjectList.push_back(obj2);
	//x.SpaceObjectList.push_back(obj3);

	for (int i = -1000; i <= 1000; i++)
	{
		SpaceObject obji;
		obji.ID = "default-" + util::toString(i);
		obji.Position = Vector(0.0, i*1.0);
		obji.Velocity = Vector(0.0, 0.0);
		obji.Mass = 15.0;
		obji.TextureID = "$_missing";
		obji.flyByLocal = true;
		x.SpaceObjectList.push_back(obji);
	}

	activeSystem = x;
}

//DESTRUCTORS

//METHODS

void Level::saveToStream(std::ofstream& output)
{
	util::toStream(name, output);
	util::toStream(description, output);
	activeSystem.saveToStream(output);
	unsigned int x = inactiveSystems.size();
	output.write((char*)&x, sizeof(x));
	for (std::list<SolarSystem>::iterator it = inactiveSystems.begin(); it != inactiveSystems.end(); it++)
	{
		it->saveToStream(output);
	}
}
void Level::loadFromStream(std::ifstream& input)
{
	name = util::fromStream(input);
	description = util::fromStream(input);
	activeSystem.loadFromStream(input);
	/*unsigned int x;
	input.read((char*) &x, sizeof(x));
	inactiveSystems.clear();
	for(unsigned int i = 0; i < x; i++)
	{
	SolarSystem tmp;
	tmp.loadFromStream(input);
	inactiveSystems.push_back(tmp);
	}*/
}
