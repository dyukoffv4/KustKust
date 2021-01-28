#pragma once

#include "template.h"

namespace mgl {

	class Image {

	public:
		Image();
		Image(vect<byte_2> s, vect<byte_2> c, sf::Texture* t);

		virtual sf::Sprite getSpr();
		virtual char getSN();

		virtual void setCurr(vect<byte_2> c);
		virtual vect<byte_2> getCurr();
		virtual void setSize(vect<byte_2> s);
		virtual vect<byte_2> getSize();
		virtual void setTexture(sf::Texture*);

		virtual void setSpeed(float s) {};
		virtual void update() {};

		enum SN {SIM_I, SPR_I};

	protected:
		sf::Texture* texture;
		vect<byte_2> size;
		vect<byte_2> curr;
	};
}