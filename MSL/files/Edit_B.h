#pragma once

#include "Button.h"
#include "Label.h"

namespace mgl {

	class Edit_B : public Button {

	public:
		Edit_B();
		Edit_B(int, vect<short>, vect<byte_2>, Image*, Label*);
		virtual ~Edit_B();

		virtual char getSN();
		virtual void draw(layout&);

		virtual void setLabel(Label*);
		virtual Label* getLabel();
		virtual void setColor(sf::Color);
		virtual sf::Color getColor();

		virtual void update(sf::Event&);
		virtual bool getStat();

	protected:
		Label* label;
		short crs;
		sf::Color crs_c;

		// 56 (-2) size.
	};
}