#include "../Headers/TileObject.h"

CommonObject::CommonObject(short x, short y) {

	this->x_pos = x;
	this->y_pos = y;
	this->x_prepos = x;
	this->y_prepos = y;
}

short CommonObject::getX() {

	return x_pos;
}

short CommonObject::getY() {

	return y_pos;
}

char Apple_CO::getName() {

	return APPLE;
}

char Key_CO::getName() {

	return KEY;
}

char Pie_CO::getName() {

	return PIE;
}

char Wall_CO::getName() {

	return WALL;
}

char Start_CO::getName() {

	return START;
}

char Exit_CO::getName() {

	return EXIT;
}