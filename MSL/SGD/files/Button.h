#pragma once

#include "Object.h"
#include "Image.h"

namespace mgl {

	class Button : public Object {

	public:
		Button();
		Button(int, vect<short>, vect<byte_2>, Image*);

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
		vect<vect<byte_1>> im_pos;
		short key;

		// 48 (-4) size
	};
}