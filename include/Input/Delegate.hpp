#ifndef _Delegate_hpp_
#define _Delegate_hpp_

#include <Input\EventPublisher.hpp>

#include <string>
#include <list>

class Generic;
template <class TEventType>
class Delegate
{
private:
	Generic* object;
	void (Generic::*methPtr)(EventPublisher*, TEventType);
public:
	Delegate()
	{
		object = nullptr;
		methPtr = nullptr;
	}
	template <class TReceiver>
	Delegate(TReceiver* _receiver, void (TReceiver::* _methPtr)(EventPublisher*, TEventType))
	{
		object = reinterpret_cast<Generic*>(_receiver);
		methPtr = reinterpret_cast<void (Generic::*)(EventPublisher*, TEventType)>(_methPtr);
	}

	template <class TReceiver>
	void setObject(TReceiver* _receiver)
	{
		object = reinterpret_cast<Generic*>(_receiver);
	}

	template <class TReceiver>
	void setMethod(void (TReceiver::* _methPtr)(EventPublisher*, TEventType))
	{
		methPtr = reinterpret_cast<void (Generic::*)(EventPublisher*, TEventType)>(_methPtr);
	}

	Generic* getObject()
	{
		return object;
	}

	void (Generic::*getMethod())(EventPublisher*, TEventType)
	{
		return methPtr;
	}

	void operator()(EventPublisher* sender, TEventType eventArgs)
	{
		(object->*methPtr)(sender, eventArgs);
	}

	bool operator==(Delegate<TEventType>& rhs)
	{
		return (rhs.object == object && rhs.methPtr == methPtr);
	}
};

#endif // !_Delegate_hpp_
