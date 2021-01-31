#pragma once

#include "template.h"

namespace mgl {

	class Object {

	public:
		Object();
		Object(int, vect<short>);
		virtual ~Object() {};

		int getID();
		void setPosition(vect<short>);
		vect<short> getPosition(void);

		virtual char getSN() = 0;
		virtual void setSize(vect<byte_2>) = 0;
		virtual vect<byte_2> getSize(void) = 0;

		virtual void draw(layout&) = 0;
		virtual void update(sf::Event&) = 0;
		virtual bool getStat() = 0;

		enum SN {SIM_B, TOG_B, SIM_G, TOG_G};

	protected:
		int id;
		vect<short> cord;
	};
}