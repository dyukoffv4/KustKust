#pragma once

#include "Button.h"

namespace mgl {

	class Toggle_B : public Button {

	public:
		Toggle_B(int i, rect<short, short> r, Image* i_l = &standart_s);

		virtual char getName();
		virtual void draw(sf::RenderWindow&);
		virtual bool getSignal();
	};
}