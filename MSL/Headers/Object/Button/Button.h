#pragma once

#include "../Object.h"

namespace mgl {

	class Button : public Object {

	public:
		Button(rect r, int i, Image* i_l);

		void update(sf::Event::MouseButtonEvent e, bool p);

		virtual void setSize(coord s);
		virtual coord getSize();

		virtual char getName();
		virtual void setImage(Image* l_i);
		virtual void draw(sf::RenderWindow&);
		virtual bool getSignal();

	protected:
		Image* image_line;
		coord size;
		bool start;
		bool click;
		// 2 byte
	};
}