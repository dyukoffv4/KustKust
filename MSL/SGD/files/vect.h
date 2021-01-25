#pragma once

#include "mgl.h"

namespace mgl {

	template <class T>
	class vect {

	public:
		vect();
		vect(T, T);

		vect operator +(const vect&);
		vect operator -(const vect&);
		vect operator *(const T&);
		vect operator /(const T&);
		vect operator !();

		vect& operator +=(const vect&);
		vect& operator -=(const vect&);
		vect& operator *=(const T&);
		vect& operator /=(const T&);

		template <class U>
		explicit operator vect<U>() const;

		T x;
		T y;
	};
}