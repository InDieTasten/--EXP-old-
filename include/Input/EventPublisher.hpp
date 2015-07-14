#ifndef _EventPublisher_hpp_
#define _EventPublisher_hpp_

#include <string>

#include <Utilities\Logger.hpp>
#include <Utilities\Conversion.hpp>

class EventPublisher
{
public:
	EventPublisher();
	~EventPublisher();

	virtual std::string who() = 0;
};

#endif // !_EventPublisher_hpp_
