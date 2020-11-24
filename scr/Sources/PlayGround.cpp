#include "../Headers/PlayGround.h"
#include "../Headers/Iterator.h"
#include "../Headers/Title.h"
#include "../Headers/TitleFactory.h"

PlayGround::PlayGround(std::string path) : x_start(-1), y_start(-1), width(0), height(0), data(nullptr) {

	if (path == "") return;
	std::ifstream file(path);
	if (!file.fail()) {

		file >> *this;
		file.close();

		if (x_start == -1) good = false;
		else good = true;
	}
	else good = false;
}

PlayGround::~PlayGround() {

	if (!data) return;
	for (int i = 0; i < height; i++)
		delete[] data[i];
	delete data;
}

PlayGround& PlayGround::getPG(std::string path) {

	static PlayGround instance(path);
	return instance;
}


bool PlayGround::isGood() {

	return good;
}

short PlayGround::getWidth() {

	return width;
}

short PlayGround::getHeight() {

	return height;
}

IteratorPG PlayGround::getIterator() {

	IteratorPG iterator(data, height, width);
	return iterator;
}

Title& PlayGround::getTitle(short x, short y) {

	return data[y][x];
}

short PlayGround::getStartX() {

	return x_start;
}

short PlayGround::getStartY() {

	return y_start;
}
 

std::istream& operator>>(std::istream& in, PlayGround& data) {

	in >> data.width >> data.height;

	if (data.width < 5 || data.height < 5) return in;

	data.data = new Title * [data.height];
	for (int i = 0; i < data.height; i++) {

		data.data[i] = new Title[data.width];
		for (int j = 0; j < data.width; j++)
			data.data[i][j] = Title(j, i);
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
		if (x1 > data.width || y1 > data.height) continue;

		Factory* factory = nullptr;

		if (id == APPLE) factory = (Factory*)new Apple_F;
		if (id == PIE) factory = (Factory*)new Pie_F;
		if (id == KEY) factory = (Factory*)new Key_F;
		if (id == WALL) factory = (Factory*)new Wall_F;
		if (id == EXIT) factory = (Factory*)new Exit_F;
		if (id == START && data.x_start == -1) {

			factory = (Factory*)new Start_F;
			data.x_start = x0;
			data.y_start = y0;
		}

		if (factory) {

			for (int i = y0; i < y1; i++)
				for (int j = x0; j < x1; j++)
					data.data[i][j].setObj(factory->getObject());

			delete factory;
		}
	}

	return in;
}