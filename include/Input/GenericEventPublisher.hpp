#ifndef _GenericEventPublisher_hpp_
#define _GenericEventPublisher_hpp_

#include <Input\EventPublisher.hpp>

class GenericEventPublisher : public EventPublisher
{
public:
	GenericEventPublisher();
	~GenericEventPublisher();

	virtual std::string who();
};

#endif // !_GenericEventPublisher_hpp_
