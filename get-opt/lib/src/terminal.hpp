#pragma once

#include <map>
#include <iostream>
#include "key.hpp"

namespace KP {
	class Terminal {
	private:
		void (*last)(Args) = nullptr;
		std::map<Key, void (*)(Args)> binds;

	public:
		Terminal();
		Terminal(const Terminal& term);

		Terminal& operator=(const Terminal& term);

		void setKey(Key key, void (*lnr)(Args) = nullptr);
		void delKey(Key key);

		void setRoot(void (*lnr)(Args));
		void delRoot();

		void setFinal(void (*lnr)(Args));
		void delFinal();

		void cleanBinds();
		
		void execute(int argc, char* argv[]);
		void execute(Args input);
	};
}