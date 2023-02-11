#pragma once

#include "../object/object.hpp"

namespace mgl {

	class Group : public Object {

	public:
		Group();
		Group(int id, vect<short>, vect<byte_2>);
		virtual ~Group();

		/// <defined>
		/// 	int getID();
		/// 
		///		void setPosition(vect<short>);
		///		vect<short> getPosition(void);
		/// </defined>
		
		virtual void setSize(vect<byte_2>);
		virtual vect<byte_2> getSize(void);
		virtual void draw(layout&);
		virtual void update(sf::Event&);

		bool resized();

		Object*& operator[](byte_4);

	protected:
		Object*** grid;
		vect<byte_2>** chest_s;
		vect<byte_2> size;
		vect<byte_2> osize;
		byte_4 n;

		// 48 (-4) size.
	};
}