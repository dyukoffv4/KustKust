#include "../../Headers/Object/Object.h"

mgl::Object::Object(int i, vect<short> c) {

	id = i;
	pos = c;
};

int mgl::Object::getId() {

	return id;
}

void mgl::Object::setCoord(vect<short> c) {

	pos = c;
}

mgl::vect<short> mgl::Object::getCoord() {

	return pos;
}