#pragma once

#include "Button.h"

namespace mgl {

	class Toggle_B : public Button {

	public:
		Toggle_B(rect r, int i, Image* i_l);

		virtual char getName();
		virtual bool getSignal();
	};
}