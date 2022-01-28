#pragma once
#include <map>
#include <string>
//Event.h

#include "EventCallback.h"  
#include <vector>
class Event
{
public:
	Event();
	~Event();

	void addListener(IEventCallback* action);
	void removeListener(IEventCallback* action);
	void fire();

private:
	typedef std::vector<IEventCallback*> CallbackArray;
	CallbackArray actions;
};