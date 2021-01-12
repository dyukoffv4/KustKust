#include "../../Headers/Object/Object.h"

mgl::Object::Object(coord c, int i) {

	id = i;
	pos = c;
};

int mgl::Object::getId() {

	return id;
}

void mgl::Object::setCoord(coord c) {

	pos = c;
}

mgl::coord mgl::Object::getCoord() {

	return pos;
}