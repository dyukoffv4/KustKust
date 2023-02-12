#pragma once

#include <SFML/Graphics.hpp>

namespace MGL {
	typedef unsigned char	byte_1;
	typedef unsigned short	byte_2;
	typedef unsigned int	byte_4;
	typedef unsigned long	byte_8;

	typedef sf::Event event;
	typedef sf::RenderWindow layout;

	static sf::Texture standart_t = sf::Texture();
	static sf::Font standart_f = sf::Font();
	static float SEC(1000.0);

	class Object;

	class Button;
	class Simple_B;
	class Toggle_B;

	class Group;
	class Simple_G;
	class Toggle_G;

	class Image;
	class Texture_I;
	class Sprite_I;
	
	template <class T>
	class Vector {
	public:
		T x;
		T y;

		Vector operator +(const Vector& v) {
			return { T(this->x + v.x), T(this->y + v.y) };
		}
		Vector operator -(const Vector& v) {
			return { T(this->x - v.x), T(this->y - v.y) };
		}
		Vector operator *(const T& m) {
			return { T(this->x * m), T(this->y * m) };
		}
		Vector operator /(const T& d) {
			return { T(this->x / d), T(this->y / d) };
		}
		Vector operator !() {
			return { (T)!this->x, (T)!this->y };
		}

		Vector& operator +=(const Vector& v) {
			return *this = *this + v;
		}
		Vector& operator -=(const Vector& v) {
			return *this = *this - v;
		}
		Vector& operator *=(const T& v) {
			return *this = *this * v;
		}
		Vector& operator /=(const T& v) {
			return *this = *this / v;
		}

		bool operator ==(const Vector<T>& v) {
			return (x == v.x) && (y == v.y);
		}
		bool operator !=(const Vector<T>& v) {
			return (x != v.x) || (y != v.y);
		}
		bool operator <<(const Vector<T>& v) {
			return (y < v.y) && (x < v.x);
		}
		bool operator >>(const Vector<T>& v) {
			return (y > v.y) && (x > v.x);
		}

		template <class U>
		explicit operator Vector<U>() const {
			return Vector<U>(U(this->x), U(this->y));
		}
	};

	template class Vector<byte_1>;
	template class Vector<byte_2>;
	template class Vector<byte_4>;
	template class Vector<byte_8>;

	template class Vector<char>;
	template class Vector<short>;
	template class Vector<int>;
	template class Vector<long>;

	template class Vector<float>;
	template class Vector<double>;
}