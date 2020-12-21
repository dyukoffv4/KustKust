#include "../Headers/Bridge.h"
#include "../Headers/Tile.h"
#include "../Headers/TileObject.h"

Tile::Tile(short _x, short _y) : x(_x), y(_y) {}

Tile::~Tile() {

	for (std::list<Bridge*>::iterator i = observers.begin(); i != observers.end(); i++)
		delete (*i);

	for (int i = 0; objects[i] != nullptr; i++)
		delete objects.pop(objects[i]);
}

List& Tile::getObjs() {

	return objects;
}

short Tile::getx() {

	return x;
}

short Tile::gety() {

	return y;
}

void Tile::attach(Bridge* _observer) {

	observers.push_back(_observer);
}

void Tile::detach(Bridge* _observer) {

	observers.remove(_observer);
}

void Tile::notify(std::string message) {

	for (std::list<Bridge*>::iterator i = observers.begin(); i != observers.end(); i++)
		(*i)->transUpdate(this, message);
}

std::ostream& operator<<(std::ostream& out, Tile* tile) {

	if (tile->getObjs().empty()) out << "empty" << " [" << tile->x << " " << tile->y << "]";
	else
		for (int i = 0; tile->getObjs()[i] != nullptr; i++) {
			switch (tile->getObjs()[i]->getName()) {

			case PLR:
				out << "player";
				break;
			case COIN:
				out << "coin";
				break;
			case BAG:
				out << "bag";
				break;
			case KEY:
				out << "key";
				break;
			case WALL:
				out << "wall";
				break;
			case START:
				out << "start";
				break;
			case EXIT:
				out << "exit";
				break;
			}
			out << " [" << tile->x << " " << tile->y << "]";
		}
	return out;
}