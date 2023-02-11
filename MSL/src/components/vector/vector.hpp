#pragma once

#include "../../definitions/mgl.hpp"

namespace mgl {

	template <class T>
	class vect {

	public:

		vect operator +(const vect&);
		vect operator -(const vect&);
		vect operator *(const T&);
		vect operator /(const T&);
		vect operator !();

		vect& operator +=(const vect&);
		vect& operator -=(const vect&);
		vect& operator *=(const T&);
		vect& operator /=(const T&);

		bool operator ==(const vect<T>&);
		bool operator !=(const vect<T>&);
		bool operator <<(const vect<T>&);
		bool operator >>(const vect<T>&);

		template <class U>
		explicit operator vect<U>() const;

		T x;
		T y;
	};
}