#pragma once

#include "Button.h"

namespace mgl {

	class Timer_B : public Button {

	public:
		Timer_B(rect r, int i, Image* l_i, short sec);

		virtual char getName();
		virtual bool getSignal();

	protected:
		int timer;
		bool end;
		// 3 byte
	};
}