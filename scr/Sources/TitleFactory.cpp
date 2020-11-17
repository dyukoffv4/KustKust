#include "../Headers/TitleFactory.h"
#include "../Headers/TitleObject.h"

Object* Apple_F::getObject() {

	return new Apple_O;
}

Object* Rock_F::getObject() {

	return new Rock_O;
}

Object* Plate_F::getObject() {

	return new Plate_O;
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