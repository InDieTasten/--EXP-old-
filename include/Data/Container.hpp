#ifndef _Container_hpp_
#define _Container_hpp_

#include <Data\Attachable.hpp>
#include <Data\Taggable.hpp>
#include <Utilities\Logger.hpp>

class Container : public Attachable, public Taggable
{
private:
public:
	Container();
	~Container();
};

#endif // !_Container_hpp_