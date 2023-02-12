#pragma once

#include "../definitions.hpp"

namespace MGL {
	class Texture_I {
	public:
		Texture_I();
		Texture_I(Vector<byte_2>, Vector<byte_2>, sf::Texture*);

		virtual sf::RectangleShape getImage(Vector<byte_2>);
		virtual char getSN();

		virtual void setCurr(Vector<byte_2>);
		virtual Vector<byte_2> getCurr();
		virtual void setSize(Vector<byte_2>);
		virtual Vector<byte_2> getSize();
		virtual void setTexture(sf::Texture*);

		enum SN {SIM_I, SPR_I};

	protected:
		sf::Texture* texture;
		Vector<byte_2> size;
		Vector<byte_2> curr;
	};
}