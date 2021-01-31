#pragma once

#include "Button.h"

namespace mgl {

	class Toggle_B : public Button {

	public:
		Toggle_B();
		Toggle_B(int i, vect<short> p, vect<byte_2> s, Texture_I*);

		virtual char getSN();

		/// <defined>
		/// 	int getID();
		/// 
		///		void setPosition(vect<short>);
		///		vect<short> getPosition(void);
		/// 
		///		void setSize(vect<byte_2>);
		///		vect<byte_2> getSize(void);
		/// 
		///		void setImage(Image*);
		///		Image* getImage(void);
		/// 
		///		void setKey(short);
		///		short getKey(void);
		/// </defined>
		 
		virtual void draw(layout&);
		virtual void update(sf::Event&);
		virtual bool getStat();

		// 32 (-0) size
	};
}