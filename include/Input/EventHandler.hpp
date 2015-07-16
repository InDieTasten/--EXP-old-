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
	sf::Mutex confmtx;
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

	void clear()
	{
		confmtx.lock();
		delegates.clear();
		confmtx.unlock();
	}
	size_t size()
	{
		confmtx.lock();
		size_t result = delegates.size();
		confmtx.unlock();
		return result;
	}

	// Adds Delegate to EventHandler
	void operator+=(Delegate<TEventType> _delegate)
	{
		confmtx.lock();
		for (Delegate<TEventType> it : delegates)
		{
			if (it.getObject() == _delegate.getObject())
			{
				confmtx.unlock();
				return;
			}
		}
		delegates.push_back(_delegate);
		confmtx.unlock();
	}

	// Removes Delegate from EventHandler
	void operator-=(Delegate<TEventType> _delegate)
	{
		confmtx.lock();
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
		confmtx.unlock();
	}
	void operator()(EventPublisher* sender, TEventType eventArgs)
	{
		confmtx.lock();
		for (Delegate<TEventType> it : delegates)
		{
			it(sender, eventArgs);
		}
		confmtx.unlock();
	}
};

#endif // !_EventHandler_hpp_