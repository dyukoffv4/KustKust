#include "../Headers/Area.h"
#include "../Headers/Iterator.h"
#include "../Headers/Tile.h"
#include "../Headers/TileFactory.h"
#include "../Headers/TileObject.h"
#include "../Headers/List.h"

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

	if (x >= width || y >= height || x < 0 || y < 0) return nullptr;
	return &data[y][x];
}

Object* Area::getPlr() {

	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			for (int k = 0; data[i][j].getObjs()[k] != nullptr; k++)
				if (data[i][j].getObjs()[k]->getName() == PLR)
					return data[i][j].getObjs()[k];
	return nullptr;
}

List* Area::getWarr() {

	List* list = new List;

	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			for (int k = 0; data[i][j].getObjs()[k] != nullptr; k++) {

				if (data[i][j].getObjs()[k]->getName() == SWAR) list->push(data[i][j].getObjs()[k]);
				if (data[i][j].getObjs()[k]->getName() == RWAR) list->push(data[i][j].getObjs()[k]);
				if (data[i][j].getObjs()[k]->getName() == TWAR) list->push(data[i][j].getObjs()[k]);
			}

	return list;
}

void Area::read(std::istream& in) {

	bool start = false;

	in >> width >> height;

	if (width < 5 || height < 5) return;
	
	data = new Tile * [height];
	for (int i = 0; i < height; i++) {

		data[i] = new Tile[width];
		for (int j = 0; j < width; j++) data[i][j] = Tile(j, i);
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
		if (id == SWAR) factory = (Factory*)new Warrior_F<stan>;
		if (id == RWAR) factory = (Factory*)new Warrior_F<rndm>;
		if (id == TWAR) factory = (Factory*)new Warrior_F<towr>;

		if (factory) {

			for (int i = y0; i < y1; i++)
				for (int j = x0; j < x1; j++) {

					data[i][j].getObjs().push(factory->getObject(&data[i][j]));
					if (data[i][j].getObjs().isin(START) && !start) {

						factory = (Factory*)new Player_F;
						data[i][j].getObjs().push(factory->getObject(&data[i][j]));
						start = true;
					}
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