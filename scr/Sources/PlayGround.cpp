#include "../Headers/PlayGround.h"
#include "../Headers/Title.h"
#include "../Headers/Iterator.h"
#include "../Headers/TitleFactory.h"

// -------- Pole defenition

PlayGround::PlayGround(const char* path) : x_start(0), y_start(0), width(0), height(0), data(nullptr) {

	if (path == "") return;
	std::ifstream file(path);
	if (!file.fail()) {

		file >> *this;
		good = true;
		file.close();
	}
	else good = false;
}

PlayGround::~PlayGround() {

	if (!data) return;
	for (int i = 0; i < height; i++)
		delete[] data[i];
	delete data;
}

std::istream& operator>>(std::istream& in, PlayGround& data) {

	std::string str;
	std::getline(in, str);
	data.width = (short)str.length();
	in.seekg(0, in.beg);

	while (!in.eof()) {

		std::getline(in, str);
		if (str != "\n") {

			data.height++;
			if (str.length() != data.width) {

				data.height = 0;
				data.width = 0;
				return in;
			}
		}
	}
	
	in.seekg(0, in.beg);
	data.data = new Title*[data.height];
	for (int i = 0; i < data.height; i++) {

		data.data[i] = new Title[data.width];
		for (int j = 0; j < data.width; j++) {

			Title title(j, i);
			data.data[i][j] = title;
			char sym = in.get();
			if (sym == '\n') sym = in.get();
			Factory* factory = nullptr;

			if (sym == WALL) factory = (Factory*)new Wall_F;
			if (sym == EXIT) factory = (Factory*)new Exit_F;
			if (sym == START) {

				data.x_start = j;
				data.y_start = i;
				factory = (Factory*)new Start_F;
			}
			if (sym == APPLE) factory = (Factory*)new Apple_F;
			if (sym == PIE) factory = (Factory*)new Plate_F;
			if (sym == KEY) factory = (Factory*)new Rock_F;

			if (factory) {

				data.data[i][j].setObj(factory->getObject());
				delete factory;
			}
		}
	}

	return in;
}

PlayGround& PlayGround::getPG(const char* path) {

	static PlayGround instance(path);
	return instance;
}

PlayGround::PlayGround(const PlayGround& init) : x_start(init.x_start), y_start(init.y_start), width(init.width), height(init.height) {

	good = init.good;
	data = new Title * [height];
	for (int i = 0; i < height; i++) data[i] = new Title[width];

	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++) data[i][j] = init.data[i][j];
}

PlayGround::PlayGround(PlayGround&& init) noexcept : x_start(init.x_start), y_start(init.y_start), width(init.width), height(init.height) {

	good = init.good;
	data = init.data;
	init.data = nullptr;
}

PlayGround& PlayGround::operator = (const PlayGround& init) {

	if (this == &init) return *this;

	for (int i = 0; i < height; i++) delete[] data[i];
	delete[] data;

	width = init.width;
	height = init.height;

	data = new Title * [height];
	for (int i = 0; i < height; i++) data[i] = new Title[width];

	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++) data[i][j] = init.data[i][j];

	return *this;
}

PlayGround& PlayGround::operator = (PlayGround&& init) noexcept {

	if (this == &init) return *this;

	for (int i = 0; i < height; i++) delete[] data[i];
	delete[] data;
	
	width = init.width;
	height = init.height;

	data = init.data;
	init.data = nullptr;

	return *this;
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