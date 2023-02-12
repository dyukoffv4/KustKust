#pragma once

#include "../button/button.hpp"

namespace MGL {
	class Simple_B : public Button {
	public:
		Simple_B();
		Simple_B(int, Vector<short>, Vector<byte_2>, Texture_I*);

		virtual char getSN();

		/// <defined>
		/// 	int getID();
		/// 
		///		void setPosition(Vector<short>);
		///		Vector<short> getPosition(void);
		/// 
		///		void setSize(Vector<byte_2>);
		///		Vector<byte_2> getSize(void);
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

		// 32 (-0);
	};
}