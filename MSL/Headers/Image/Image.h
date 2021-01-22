#pragma once

#include "../mgll.h"

namespace mgl {

	class Image {

	public:
		Image(int i, vect<short> s, vect<byte> c, sf::Texture* t = &standart_t);

		virtual sf::Sprite getSpr();
		virtual void setCurr(vect<byte> c);
		virtual vect<byte> getCurr();

		virtual void setSize(vect<short> s);
		virtual vect<short> getSize();

		virtual void setSpeed(float s) {};
		virtual void update() {};

	protected:
		sf::Texture* texture;
		vect<short> size;
		vect<byte> curr;
		// 2 byte
	};

	static Image standart_s = mgl::Image(0, { 64, 64 }, { 0, 0 }, &standart_t);
}