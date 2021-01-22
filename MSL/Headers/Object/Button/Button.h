#pragma once

#include "../Object.h"
#include "../../Image/Image.h"

namespace mgl {

	class Button : public Object {

	public:
		Button(int i, rect<short, short> r, Image* i_l = &standart_s);

		void update_m(sf::Event::MouseButtonEvent e, bool p);
		void update_b(sf::Event::KeyEvent e, bool p);

		virtual void setSize(vect<short> s);
		virtual vect<short> getSize();

		virtual char getName();
		virtual void setImage(Image* l_i);
		virtual void draw(sf::RenderWindow&);
		virtual bool getSignal();

	protected:
		Image* image;
		vect<short> size;
		bool start;
		bool click;
		short key;
	};
}