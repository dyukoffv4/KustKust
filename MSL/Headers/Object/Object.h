#pragma once

#include "../mgll.h"

namespace mgl {

	class Object {

	public:
		Object(int i, vect<short> c);

		int getId();
		virtual void setCoord(vect<short> c);
		virtual vect<short> getCoord();

		virtual char getName() = 0;
		virtual void draw(sf::RenderWindow&) = 0;
		virtual void setSize(vect<short> s) = 0;
		virtual vect<short> getSize() = 0;

	protected:
		vect<short> pos;
		int id;
	};
}