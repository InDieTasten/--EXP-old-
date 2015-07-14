#ifndef _Delegate_hpp_
#define _Delegate_hpp_


#include <string>
#include <list>





class Sender
{
public:
	Sender();
	~Sender();

	virtual std::string who() = 0;
};

class Receiver
{
public:

};


template<class TEventType>
class Delegate
{
private:
	Receiver* object;
	void (Receiver::* methPtr)(Sender*, TEventType);
public:
	Delegate(Receiver* _receiver, void (Receiver::* _methPtr)(Sender*, TEventType))
	{
		object = _receiver;
		methPtr = _methPtr;
	}

	//void operator()(Sender& sender, TEventType eventArgs)
	//{
	//	(object->*methPtr)();
	//}
};
//struct ButtonClicked
//{
//	int which;
//};
//class Publisher : public Sender
//{
//public:
//
//
//	virtual std::string who()
//	{
//		return "Publisher";
//	}
//
//	Delegate<ButtonClicked> OnButtonClicked;
//
//	void triggerSomeEvent()
//	{
//
//	}
//};

#endif // !_Delegate_hpp_

template <class TReceiver>
class Delegate2
{
private:
	void* object;
	void (TReceiver::* methPtr)(Sender*, int);
public:

	Delegate2(TReceiver* _receiver, void (TReceiver::* _methPtr)(Sender*, int))
	{
		object = _receiver;
		methPtr = _methPtr;
	}

	void operator()(Sender* sender, int eventArgs)
	{
		(object->*methPtr)(sender, eventArgs);
	}
};

class Receiver2 : public Receiver
{
public:
	Receiver2()
	{
		Delegate2<Receiver2> del(this, &Receiver2::handle);
	}
	void handle(Sender*, int)
	{

	}
};

Receiver2 rec2;
