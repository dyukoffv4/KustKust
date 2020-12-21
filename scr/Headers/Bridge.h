#pragma once

#include "Defines.h"
#include <string>
class Observer;
class Publisher;

//

class Bridge {

private:
	Observer* observer;

public:
	Bridge(Observer*);
	void transUpdate(Publisher*, std::string);
	bool operator==(Bridge&) { return false; };
};