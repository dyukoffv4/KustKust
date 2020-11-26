#include "../Headers/Area.h"
#include "../Headers/Iterator.h"
#include "../Headers/Tile.h"
#include "../Headers/TileFactory.h"
#include "../Headers/TileObject.h"

Area::Area(std::string path) : data_len(0), width(0), height(0), data(nullptr) {

	if (path == "") return;
	std::ifstream file(path);
	if (!file.fail()) {

		this->read(file);
		file.close();
	}
}

Area::~Area() {

	if (data) delete[] data;
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

DrawIterator Area::getIterator() {

	DrawIterator iterator(data, height, width, data_len);
	return iterator;
}

Tile* Area::getTile(short x, short y) {

	Tile tile(x, y);
	for (int i = 0; i < data_len; i++) {

		if (data[i] == tile) return &data[i];
	}
	return nullptr;
}

short Area::getStartX() {

	for (int i = 0; i < data_len; i++) {

		if (data[i].getObj()->getName() == START) return data[i].getObj()->getX();
	}
}

short Area::getStartY() {

	for (int i = 0; i < data_len; i++) {

		if (data[i].getObj()->getName() == START) return data[i].getObj()->getY();
	}
}


void Area::read(std::istream& in) {

	bool start = false;

	in >> width >> height;

	if (width < 5 || height < 5) return;

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

					Tile tile(j, i);
					tile.setObj(factory->getObject(j, i));
					if (tile.getObj()->getName() == START) start = true;
					this->pushTile(tile);
				}
			delete factory;
		}
	}

	if (!start) {

		delete data;
		data = nullptr;
	}
}

void Area::pushTile(Tile p_tile) {

	bool similar = false;
	for (int i = 0; i < data_len; i++) {

		if (p_tile == data[i]) {

			similar = true;
			break;
		}
	}
	if (!similar) {

		int push_i = data_len;

		Tile* n_data = new Tile[data_len + 1];
		for (int i = 0; i < data_len; i++) {

			if (data[i].getNum() < p_tile.getNum()) n_data[i] = data[i];
			if (data[i].getNum() >= p_tile.getNum()) {

				if (data_len == push_i) push_i = i;
				n_data[i + 1] = data[i];
			}
		}
		n_data[push_i] = p_tile;
		delete[] this->data;
		this->data = n_data;
		data_len++;
	}
}

void Area::popTile(Tile p_tile) {

	bool pop_i = false;
	for (int i = 0; i < data_len; i++) {

		if (p_tile == data[i]) {

			data[i].setObj(nullptr);
			pop_i = true;
		}
		if (pop_i && i != data_len - 1) data[i] = data[i + 1];
	}
	if (pop_i) {

		this->data_len--;
		Tile* n_data = new Tile[data_len];

		for (int i = 0; i < data_len; i++)
			n_data[i] = data[i];

		delete[] this->data;
		this->data = n_data;
	}
}