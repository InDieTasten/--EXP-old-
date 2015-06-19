#include <Data\Taggable.hpp>

Taggable::Taggable()
{
	EXP::log("[Info]Constructing Taggable... " + utils::tostring(this));
	EXP::log("[Info]Taggable has been constructed: " + utils::tostring(this));
}
Taggable::~Taggable()
{
	EXP::log("[Info]Destructing Taggable... " + utils::tostring(this));
	EXP::log("[Info]Taggable has been destructed: " + utils::tostring(this));
}

void Taggable::setTag(std::string _attribute, float _value)
{
	attributes[_attribute] = _value;
}
void Taggable::setTags(std::map<std::string, float> _tags)
{
	attributes = _tags;
}
void Taggable::cleanMap()
{
	for (std::map<std::string, float>::iterator it = attributes.begin(); it != attributes.end(); it++)
	{
		if (it->second == 0.0f)
		{
			attributes.erase(it);
		}
	}
}
void Taggable::moveTag(std::string _attribute, float _value)
{
	attributes[_attribute] += _value;
}
float Taggable::getTag(std::string _attribute)
{
	return attributes[_attribute];
}
std::map<std::string, float> Taggable::getTags()
{
	return attributes;
}
