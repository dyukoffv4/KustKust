#pragma once

#include <map>
#include <iostream>
#include "defines.hpp"
#include "key.hpp"


class Terminal {
private:
	std::map<Key, void (*)(Args)> binds;

public:
	Terminal();
	Terminal(const Terminal& term);

	Terminal& operator=(const Terminal& term);

	void setKey(Key key, void (*)(Args) = nullptr);
	void delKey(Key key);

	void setRoot(void (*)(Args));
	void delRoot();
	
	void execute(Args input);
};