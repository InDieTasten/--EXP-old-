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
	Delegate();
	template <class TReceiver>
	Delegate(TReceiver* _receiver, void (TReceiver::* _methPtr)(EventPublisher*, TEventType));

	template <class TReceiver>
	void setObject(TReceiver* _receiver);

	template <class TReceiver>
	void setMethod(void (TReceiver::* _methPtr)(EventPublisher*, TEventType));

	void operator()(Publisher* sender, TEventType eventArgs)
	{
		(object->*methPtr)(sender, eventArgs);
	}
};

#endif // !_Delegate_hpp_
