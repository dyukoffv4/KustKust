#pragma once

#include "Button.h"

namespace mgl {

	class Toggle_B : public Button {

	public:
		Toggle_B();
		Toggle_B(int i, vect<short> p, vect<byte_2> s, Image*);

		virtual char getSN();
		virtual void draw(layout&);
		virtual bool getStat();

		// 40 (-0) size
	};
}