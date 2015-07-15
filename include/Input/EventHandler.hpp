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

	// Adds Delegate to EventHandler
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

	// Removes Delegate from EventHandler
	void operator-=(Delegate<TEventType> _delegate)
	{
		typename std::list< Delegate<TEventType> >::iterator it = delegates.begin();
		for (int index = 0; index < delegates.size(); index++)
		{
			if (*it == _delegate)
			{
				delegates.erase(it);
				*this -= _delegate;
			}
			it++;
		}
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