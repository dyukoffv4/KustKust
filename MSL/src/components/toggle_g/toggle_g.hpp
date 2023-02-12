#pragma once

#include "../group/group.hpp"

namespace MGL {
	class Toggle_G : public Group {
	public:
		Toggle_G();
		Toggle_G(int, Vector<short>, Vector<byte_2>);

		/// <defined>
		/// 	int getID();
		/// 
		///		void setPosition(vect<short>);
		///		vect<short> getPosition(void);
		/// 
		///		void setSize(vect<byte_2>);
		///		vect<byte_2> getSize(void);
		/// 
		///		void draw(layout&);
		///		void update(sf::Event&);
		/// </defined>

		virtual char getSN();
		virtual bool getStat();

		// 48 (-0) size.
	};
}