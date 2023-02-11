#include "vector.hpp"

template <class T>
mgl::vect<T> mgl::vect<T>::operator+(const vect<T>& v) {

	return { T(this->x + v.x), T(this->y + v.y) };
}

template <class T>
mgl::vect<T> mgl::vect<T>::operator-(const vect<T>& v) {

	return { T(this->x - v.x), T(this->y - v.y) };
}

template <class T>
mgl::vect<T> mgl::vect<T>::operator*(const T& m) {

	return { T(this->x * m), T(this->y * m) };
}

template <class T>
mgl::vect<T> mgl::vect<T>::operator/(const T& d) {

	return { T(this->x / d), T(this->y / d) };
}

template <class T>
mgl::vect<T> mgl::vect<T>::operator!() {

	return { (T)!this->x, (T)!this->y };
}

template <class T>
mgl::vect<T>& mgl::vect<T>::operator+=(const vect<T>& v) {

	return *this = *this + v;
}

template <class T>
mgl::vect<T>& mgl::vect<T>::operator-=(const vect<T>& v) {

	return *this = *this - v;
}

template <class T>
mgl::vect<T>& mgl::vect<T>::operator*=(const T& m) {

	return *this = *this * m;
}

template <class T>
mgl::vect<T>& mgl::vect<T>::operator/=(const T& d) {

	return *this = *this / d;
}

template <class T>
bool mgl::vect<T>::operator==(const vect<T>& v) {

	return (x == v.x) && (y == v.y);
}

template <class T>
bool mgl::vect<T>::operator!=(const vect<T>& v) {

	return (x != v.x) || (y != v.y);
}

template <class T>
bool mgl::vect<T>::operator<<(const vect<T>& v) {

	return (y < v.y) && (x < v.x);
}

template <class T>
bool mgl::vect<T>::operator>>(const vect<T>& v) {

	return (y > v.y) && (x > v.x);
}

template <class T> template <class U>
mgl::vect<T>::operator vect<U>() const{

	return vect<U>(U(this->x), U(this->y));
}