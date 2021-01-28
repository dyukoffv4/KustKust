#pragma once

#include "vect.h"

namespace mgl {

	class Label {

	public:
		Label();
		Label(std::string s, sf::Color c, sf::Font* f);

		virtual sf::Text getText();

		virtual void setString(std::string s);
		virtual std::string getString();
		virtual void setFont(sf::Font* f);
		virtual sf::Font* getFont();
		virtual void setOutpart(vect<byte_1> o);
		virtual vect<byte_1> getOutpart();
		virtual void setKeg(byte_1 k);
		virtual byte_1 getKeg();
		virtual void setColor(sf::Color c);
		virtual sf::Color getColor();

	protected:
		sf::Font* font;
		std::string string;
		sf::Color color;
		vect<byte_1> out_p;
		byte_1 keg;
	};
}