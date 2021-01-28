#pragma once

#include "Object.h"
#include "Sprite_I.h"

namespace mgl {

	class Button : public Object {

	public:
		Button();
		Button(int, vect<short>, vect<byte_2>, Image*);
		virtual ~Button();

		virtual char getSN();

		virtual void setSize(vect<byte_2>);
		virtual vect<byte_2> getSize(void);
		virtual void setImage(Image*);
		virtual Image* getImage(void);
		virtual void setKey(short k);

		virtual void draw(layout&);

		virtual void update(sf::Event&);
		virtual bool getStat();

	protected:
		Image* image;
		vect<float> scale;
		vect<byte_2> size;
		vect<bool> stat;
		short key;

		// 40 (-0) size
	};
}