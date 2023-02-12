#pragma once

#include "../object/object.hpp"

namespace MGL {
	class Group : public Object {
	public:
		Group();
		Group(int id, Vector<short>, Vector<byte_2>);
		virtual ~Group();

		/// <defined>
		/// 	int getID();
		/// 
		///		void setPosition(Vector<short>);
		///		Vector<short> getPosition(void);
		/// </defined>
		
		virtual void setSize(Vector<byte_2>);
		virtual Vector<byte_2> getSize(void);
		virtual void draw(layout&);
		virtual void update(sf::Event&);

		bool resized();

		Object*& operator[](byte_4);

	protected:
		Object*** grid;
		Vector<byte_2>** chest_s;
		Vector<byte_2> size;
		Vector<byte_2> osize;
		byte_4 n;

		// 48 (-4) size.
	};
}