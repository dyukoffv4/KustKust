#include "../Headers/Title.h"
#include "../Headers/TitleObject.h"

Title::Title(short x, short y) : object(nullptr), x_coord(x), y_coord(y) {}

Title::~Title() {

	if (object) delete object;
}

void Title::setObj(Object* _object) {

	if (object) delete object;
	object = _object;
}

Object* Title::getObj() {

	return this->object;
}

std::ostream& operator<<(std::ostream& out, Title* title) {

	if (!title->getObj()) out << "Free";
	else
		switch (title->getObj()->getName()) {
		case START:
			out << "Start";
			break;
		case WALL:
			out << "Wall";
			break;
		case EXIT:
			out << "Exit";
			break;
		case APPLE:
			out << "Apple";
			break;
		case PIE:
			out << "Plate";
			break;
		case KEY:
			out << "Rock";
			break;
		}
	out << " title at x: " << title->x_coord << " y: " << title->y_coord << " is";
	return out;
}