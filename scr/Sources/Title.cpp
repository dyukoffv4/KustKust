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

	out << "Title at x: " << title->x_coord << " y: " << title->y_coord << " is ";
	if (!title->getObj()) out << "Free now\n";
	else
		switch (title->getObj()->getName()) {
		case START:
			out << "Start title\n";
			break;
		case WALL:
			out << "Wall title\n";
			break;
		case EXIT:
			out << "Exit title\n";
			break;
		case APPLE:
			out << "Apple title\n";
			break;
		case PIE:
			out << "Plate title\n";
			break;
		case KEY:
			out << "Rock title\n";
			break;
		}
	return out;
}