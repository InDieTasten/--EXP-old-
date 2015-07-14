#include <Input\Delegate.hpp>

template <class TReceiver>
Delegate::Delegate()
{
	object = nullptr;
	methPtr = nullptr;
}
template <class TReceiver>
Delegate::Delegate(TReceiver* _receiver, void (TReceiver::* _methPtr)(EventPublisher*, TEventType))
{
	object = reinterpret_cast<Generic*>(_receiver);
	methPtr = reinterpret_cast<void (Generic::*)(EventPublisher*, TEventType)>(_methPtr);
}

template <class TReceiver>
void Delegate::setObject(TReceiver* _receiver)
{
	object = reinterpret_cast<Generic*>(_receiver);
}

template <class TReceiver>
void Delegate::setMethod(void (TReceiver::* _methPtr)(EventPublisher*, TEventType))
{
	methPtr = reinterpret_cast<void (Generic::*)(EventPublisher*, TEventType)>(_methPtr);
}

void Delegate::operator()(EventPublisher* sender, TEventType eventArgs)
{
	(object->*methPtr)(sender, eventArgs);
}
