#ifndef _EventHandler_hpp_
#define _EventHandler_hpp_

#include <Input\Delegate.hpp>

#include <list>

#include <Utilities\Logger.hpp>
#include <Utilities\Conversion.hpp>

template<class TEventType>
class EventHandler
{
private:
	std::list<Delegate<TEventType> > delegates;
public:
	EventHandler()
	{
		EXP::log("[Info]EventHandler has been constructed: " + utils::tostring(this));
	}
	~EventHandler()
	{
		EXP::log("[Info]EventHandler has been destructed: " + utils::tostring(this));
	}

	void operator+=(Delegate<TEventType> _delegate)
	{
		for (Delegate<TEventType> it : delegates)
		{
			if (it.getObject() == _delegate.getObject())
			{
				return;
			}
		}
		delegates.push_back(_delegate);
	}
	void operator-=(Delegate<TEventType> _delegate)
	{
		delegates.remove(_delegate);
	}
	void operator()(EventPublisher* sender, TEventType eventArgs)
	{
		for (Delegate<TEventType> it : delegates)
		{
			it(sender, eventArgs);
		}
	}
};

#endif // !_EventHandler_hpp_