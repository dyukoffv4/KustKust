#pragma once

#include "../object/object.hpp"
#include "../texture/texture.hpp"

namespace mgl {

	class Button : public Object {

	public:
		Button();
		Button(int id, vect<short>, vect<byte_2>, Texture_I*);

		/// <defined>
		/// 	int getID();
		/// 
		///		void setPosition(vect<short>);
		///		vect<short> getPosition(void);
		/// </defined>

		virtual void setSize(vect<byte_2>);
		virtual vect<byte_2> getSize(void);

		void setImage(Texture_I*);
		Texture_I* getImage(void);
		void setKey(short);
		short getKey(void);

	protected:
		Texture_I* image;
		vect<byte_2> size;
		vect<bool> stat;
		short key;

		// 32 (-0) size
	};
}