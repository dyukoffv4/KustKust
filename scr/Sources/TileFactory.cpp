#include "../Headers/TileFactory.h"
#include "../Headers/TileObject.h"

CommonObject* Apple_F::getObject(short x, short y) {

	return new Apple_CO(x, y);
}

CommonObject* Key_F::getObject(short x, short y) {

	return new Key_CO(x, y);
}

CommonObject* Pie_F::getObject(short x, short y) {

	return new Pie_CO(x, y);
}

CommonObject* Wall_F::getObject(short x, short y) {

	return new Wall_CO(x, y);
}

CommonObject* Start_F::getObject(short x, short y) {

	return new Start_CO(x, y);
}

CommonObject* Exit_F::getObject(short x, short y) {

	return new Exit_CO(x, y);
}