#include "../Headers/Area.h"
#include "../Headers/Iterator.h"
#include "../Headers/Tile.h"
#include "../Headers/TileFactory.h"
#include "../Headers/TileObject.h"

Area::Area(std::string path) : width(0), height(0), data(nullptr) {

	if (path == "") return;
	std::ifstream file(path);
	if (!file.fail()) {

		this->read(file);
		file.close();
	}
}

Area::~Area() {

	if (!data) return;

	for (int i = 0; i < height; i++)
		delete[] data[i];
	delete[] data;
}

Area& Area::getArea(std::string path) {

	static Area instance(path);
	return instance;
}

bool Area::isGood() {

	return data != nullptr;
}

short Area::getWidth() {

	return width;
}

short Area::getHeight() {

	return height;
}

Iterator Area::getIterator() {

	Iterator iterator(data, height, width);
	return iterator;
}

Tile* Area::getTile(short x, short y) {

	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			if (x == data[i][j].getX() && y == data[i][j].getY())
				return &data[i][j];
	return nullptr;
}

short Area::getStartX() {

	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			if (data[i][j].getThg() && data[i][j].getThg()->getName() == START)
				return data[i][j].getX();
}

short Area::getStartY() {

	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			if (data[i][j].getThg() && data[i][j].getThg()->getName() == START)
				return data[i][j].getY();
}


void Area::read(std::istream& in) {

	bool start = false;

	in >> width >> height;

	if (width < 5 || height < 5) return;

	data = new Tile * [height];
	for (int i = 0; i < height; i++) {
		data[i] = new Tile[width];
		for (int j = 0; j < width; j++)
			data[i][j] = Tile(j, i);
	}

	while (!in.eof()) {

		char id, buff;
		short x0, x1, y0, y1;

		in >> buff;
		if (buff != '(') continue;
		in >> id >> buff;
		if (buff != ',') continue;
		in >> x0 >> buff;
		if (buff == '-') in >> x1 >> buff;
		else x1 = x0;
		if (buff != ',') continue;
		in >> y0 >> buff;
		if (buff == '-') in >> y1 >> buff;
		else y1 = y0;
		if (buff != ')') continue;
		y0--;
		x0--;

		if (x0 < 0 || y0 < 0) continue;
		if (x1 > width || y1 > height) continue;

		Factory* factory = nullptr;

		if (id == COIN) factory = (Factory*)new Coin_F;
		if (id == BAG) factory = (Factory*)new Bag_F;
		if (id == KEY) factory = (Factory*)new Key_F;
		if (id == WALL) factory = (Factory*)new Wall_F;
		if (id == EXIT) factory = (Factory*)new Exit_F;
		if (id == START && !start) factory = (Factory*)new Start_F;

		if (factory) {

			for (int i = y0; i < y1; i++)
				for (int j = x0; j < x1; j++) {

					Object* object = factory->getObject(j, i);
					if (object->getName() == START) {

						data[i][j].setSom(new Player_O(j, i));
						start = true;
					}
					data[i][j].delThg();
					data[i][j].setThg(object);
				}
			delete factory;
		}
	}

	if (!start) {

		for (int i = 0; i < height; i++) delete[] data[i];
		delete[] data;
		data = nullptr;
	}
}