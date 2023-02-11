#pragma once

#include "../vector/vector.hpp"

namespace mgl {

	class Texture_I {

	public:
		Texture_I();
		Texture_I(vect<byte_2>, vect<byte_2>, sf::Texture*);

		virtual sf::RectangleShape getImage(vect<byte_2>);
		virtual char getSN();

		virtual void setCurr(vect<byte_2>);
		virtual vect<byte_2> getCurr();
		virtual void setSize(vect<byte_2>);
		virtual vect<byte_2> getSize();
		virtual void setTexture(sf::Texture*);

		enum SN {SIM_I, SPR_I};

	protected:
		sf::Texture* texture;
		vect<byte_2> size;
		vect<byte_2> curr;
	};
}