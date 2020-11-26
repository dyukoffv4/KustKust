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
	delete data;
}

Area& Area::getPG(std::string path) {

	static Area instance(path);
	return instance;
}

std::list<CommonObject*> Area::getObjects() {

	return this->objects;
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

Tile& Area::getTitle(short x, short y) {

	return data[y][x];
}

short Area::getStartX() {

	for (std::list<CommonObject*>::iterator i = objects.begin(); i != objects.end(); i++) {

		if ((*i)->getName() == START) return (*i)->getX();
	}
}

short Area::getStartY() {

	for (std::list<CommonObject*>::iterator i = objects.begin(); i != objects.end(); i++) {

		if ((*i)->getName() == START) return (*i)->getY();
	}
}


void Area::read(std::istream& in) {

	bool start = false;

	in >> width >> height;

	if (width < 5 || height < 5) return;
	
	data = new Tile * [height];
	for (int i = 0; i < height; i++)
		data[i] = new Tile[width];

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

		if (id == APPLE) factory = (Factory*)new Apple_F;
		if (id == PIE) factory = (Factory*)new Pie_F;
		if (id == KEY) factory = (Factory*)new Key_F;
		if (id == WALL) factory = (Factory*)new Wall_F;
		if (id == EXIT) factory = (Factory*)new Exit_F;
		if (id == START && !start) factory = (Factory*)new Start_F;

		if (factory) {

			for (int i = y0; i < y1; i++)
				for (int j = x0; j < x1; j++) {

					data[i][j].setObj(factory->getObject(j, i));
					if (data[i][j].getObj()->getName() == START) start = true;
					objects.push_back(data[i][j].getObj());
				}

			delete factory;
		}
	}

	if (!start) {

		for (int i = 0; i < height; i++)
			delete[] data[i];
		delete data;
		data = nullptr;
	}
}