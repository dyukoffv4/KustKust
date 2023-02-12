#include "object.hpp"

MGL::Object::Object() {
	id = 0;
	cord = { 0, 0 };
}

MGL::Object::Object(int i, Vector<short> p) {
	id = i;
	cord = p;
}

int MGL::Object::getID() {
	return id;
}

void MGL::Object::setPosition(Vector<short> p) {
	cord = p;
}

MGL::Vector<short> MGL::Object::getPosition(void) {
	return cord;
}