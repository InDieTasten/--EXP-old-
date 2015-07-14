#include <Input\Delegate.hpp>

template <class TEventType>
Delegate<TEventType>::Delegate()
{
	object = nullptr;
	methPtr = nullptr;
}

template <class TEventType>
template <class TReceiver>
Delegate<TEventType>::Delegate(TReceiver* _receiver, void (TReceiver::* _methPtr)(EventPublisher*, TEventType))
{
	object = reinterpret_cast<Generic*>(_receiver);
	methPtr = reinterpret_cast<void (Generic::*)(EventPublisher*, TEventType)>(_methPtr);
}

template <class TEventType>
template <class TReceiver>
void Delegate<TEventType>::setObject(TReceiver* _receiver)
{
	object = reinterpret_cast<Generic*>(_receiver);
}

template <class TEventType>
template <class TReceiver>
void Delegate<TEventType>::setMethod(void (TReceiver::* _methPtr)(EventPublisher*, TEventType))
{
	methPtr = reinterpret_cast<void (Generic::*)(EventPublisher*, TEventType)>(_methPtr);
}

template <class TEventType>
Generic* Delegate<TEventType>::getObject()
{
	return object;
}

template <class TEventType>
void Delegate<TEventType>::operator()(EventPublisher* sender, TEventType eventArgs)
{
	(object->*methPtr)(sender, eventArgs);
}
