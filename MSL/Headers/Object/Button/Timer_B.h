#pragma once

#include "Button.h"
#include "../../Image/Label.h"

namespace mgl {

	class Timer_B : public Button {

	public:
		Timer_B(int i, rect<short, short> r, short sec, Image* l_i = &standart_s);

		void update_m(sf::Event::MouseButtonEvent e, bool p);
		void update_b(sf::Event::KeyEvent e, bool p);

		virtual char getName();
		virtual void draw(sf::RenderWindow&);
		virtual bool getSignal();

	protected:
		int timer;
		int tick;
	};
}