#pragma once

#include "../definitions.hpp"

namespace MGL {
	class Object {
	public:
		Object();
		Object(int, Vector<short>);
		virtual ~Object() {};

		int getID();
		void setPosition(Vector<short>);
		Vector<short> getPosition(void);

		virtual char getSN() = 0;
		virtual void setSize(Vector<byte_2>) = 0;
		virtual Vector<byte_2> getSize(void) = 0;

		virtual void draw(layout&) = 0;
		virtual void update(sf::Event&) = 0;
		virtual bool getStat() = 0;

		enum SN {SIM_B, TOG_B, SIM_G, TOG_G};

	protected:
		int id;
		Vector<short> cord;
	};
}