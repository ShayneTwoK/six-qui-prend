#pragma once
// EventCallback.h
class IEventCallback
{
public:
	virtual void operator() () = 0;
	virtual bool operator == (IEventCallback* other) = 0;
};

template<typename T>
class EventCallback : public IEventCallback
{
public:
	EventCallback(T* instance, void (T::* function)())
		: instance(instance), function(function) {}
	virtual bool operator == (IEventCallback* other) override
	{
		return true;
		/*EventCallback* otherEventCallback = dynamic_cast<EventCallback>(other);
		if (otherEventCallback == nullptr)
			return false;

		return 	(this->function == otherEventCallback->function) &&
			(this->instance == otherEventCallback->instance);*/
	}
	virtual void operator () () override { (instance->*function)(); }
private:
	void (T::* function)();
	T* instance;
};