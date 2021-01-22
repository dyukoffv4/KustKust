#pragma once

#include "Drawable.h"

namespace mgl {

	class Label : public Drawable {

	public:
		Label(int i, vect<short> k, const char* s, sf::Font* f);
		~Label();

		virtual sf::Text getText();
		virtual void setString(const char* s);

		virtual void setSize(vect<short> k);
		virtual vect<short> getSize();

	protected:
		sf::Font* font;
		char* str;
	};
}