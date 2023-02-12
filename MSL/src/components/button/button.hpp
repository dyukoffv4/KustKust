#pragma once

#include "../object/object.hpp"
#include "../texture/texture.hpp"

namespace MGL {
	class Button : public Object {
	public:
		Button();
		Button(int id, Vector<short>, Vector<byte_2>, Texture_I*);

		/// <defined>
		/// 	int getID();
		/// 
		///		void setPosition(Vector<short>);
		///		Vector<short> getPosition(void);
		/// </defined>

		virtual void setSize(Vector<byte_2>);
		virtual Vector<byte_2> getSize(void);

		void setImage(Texture_I*);
		Texture_I* getImage(void);
		void setKey(short);
		short getKey(void);

	protected:
		Texture_I* image;
		Vector<byte_2> size;
		Vector<bool> stat;
		short key;

		// 32 (-0) size
	};
}