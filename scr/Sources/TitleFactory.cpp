#include "../Headers/TitleFactory.h"
#include "../Headers/TitleObject.h"

Object* Apple_F::getObject() {

	return new Apple_O;
}

Object* Key_F::getObject() {

	return new Key_O;
}

Object* Pie_F::getObject() {

	return new Pie_O;
}

Object* Wall_F::getObject() {

	return new Wall_O;
}

Object* Start_F::getObject() {

	return new Start_O;
}

Object* Exit_F::getObject() {

	return new Exit_O;
}