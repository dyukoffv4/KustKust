#include "object.hpp"

mgl::Object::Object() {

	id = 0;
	cord = { 0, 0 };
}

mgl::Object::Object(int i, vect<short> p) {

	id = i;
	cord = p;
}

int mgl::Object::getID() {

	return id;
}

void mgl::Object::setPosition(vect<short> p) {

	cord = p;
}

mgl::vect<short> mgl::Object::getPosition(void) {

	return cord;
}