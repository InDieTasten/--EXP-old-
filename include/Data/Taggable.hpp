#ifndef _Taggable_hpp_
#define _Taggable_hpp_

#include <string>
#include <map>
#include <Utilities\Logger.hpp>
#include <Utilities\Conversion.hpp>

class Taggable
{
private:
	std::map<std::string, float> attributes;
public:
	Taggable();
	~Taggable();

	//SET
	void setTag(std::string _attributes);
	void clearTag(std::string _attribute);
	void clearTags();
	//MOVE
	void moveTag(std::string _attribute, float _value);
	//GET
	float getTag(std::string _attribute);
	std::map<std::string, float> getTags();
};

#endif // !_Taggable_hpp_