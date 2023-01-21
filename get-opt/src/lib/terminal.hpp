#pragma once

#include <map>
#include <iostream>
#include "defines.hpp"
#include "key.hpp"


class Terminal;

class Listener {
protected:
	Terminal* term;

public:
	explicit Listener(Terminal* _term);
	virtual Listener* getCopy() = 0;
	virtual void execute(Args) = 0;
};

class Terminal {
private:
	std::map<Key, Listener*> binds;
	std::map<std::string, std::string> data;

public:
	Terminal();
	Terminal(const Terminal& term);
	~Terminal();

	Terminal& operator=(const Terminal& term);

	std::string& Data(std::string key);

	void setKey(Key key, Listener* lnr = nullptr);
	void delKey(Key key);

	void setRoot(Listener* lnr);
	void delRoot();
	
	void execute(Args input);
};