#ifndef _Delegate_hpp_
#define _Delegate_hpp_


#include <string>
#include <list>


class Publisher
{
private:
public:
	virtual std::string who() { return "Generic"; }
};


class Generic;
template <class TEventType>
class Delegate
{
private:
	Generic* object;
	void (Generic::*methPtr)(Publisher*, TEventType);
public:
	Delegate()
	{
		object = nullptr;
		methPtr = nullptr;
	}
	template <class TReceiver>
	Delegate(TReceiver* _receiver, void (TReceiver::* _methPtr)(Publisher*, TEventType))
	{
		object = reinterpret_cast<Generic*>(_receiver);
		methPtr = reinterpret_cast<void (Generic::*)(Publisher*, TEventType)>(_methPtr);
	}

	template <class TReceiver>
	void setObject(TReceiver* _receiver)
	{
		object = reinterpret_cast<Generic*>(_receiver);
	}

	template <class TReceiver>
	void setMethod(void (TReceiver::* _methPtr)(Publisher*, TEventType))
	{
		methPtr = reinterpret_cast<void (Generic::*)(Publisher*, TEventType)>(_methPtr);
	}

	void operator()(Publisher* sender, TEventType eventArgs)
	{
		(object->*methPtr)(sender, eventArgs);
	}
};

class Pub1 : public Publisher
{
private:
	Delegate<int> del;
public:
	Pub1(Delegate<int> del1) : del(del1)
	{
		del(this, 15);
	}
	virtual std::string who() { return "Pub1"; }
};

class Receiver
{
public:
	Delegate<int> getDelegate()
	{
		return Delegate<int>(this, &Receiver::handle);
	}
	void handle(Publisher*, int value)
	{
		std::cout << "Receiver got: " << value << std::endl;
	}
};

Receiver rec;
Pub1 pub1(rec.getDelegate());

#endif // !_Delegate_hpp_
