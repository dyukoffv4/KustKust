#pragma once

#include "../Object.h"

namespace mgl {

	class Group : public Object {

	public:
		Group(rect r, int i, bool c = 0, bool e = 0);

		void push(Object* o);
		void resize();

		virtual char getName();
		virtual bool getSignal(int& id);
		virtual void setSize(coord s);
		virtual coord getSize();
		virtual void draw(sf::RenderWindow&);

	protected:
		Object** cont;
		coord size;
		bool center;
		bool expand;
	};
}