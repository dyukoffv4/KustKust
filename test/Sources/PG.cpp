#define _CRT_SECURE_NO_WARNINGS

#include "../Headers/PG.h"
#include "../Headers/Cell.h"
#include "../Headers/PG_it.h"

PlayGround* PlayGround::ptr_pole = nullptr;
PG_Dest PlayGround::destroyer;

// -------- Pole defenition

PlayGround::PlayGround(const char* path) : width(0), height(0), data(nullptr) {

	if (get_HW(path)) return;

	if (Read_Pole(path)) data = nullptr;
}

bool PlayGround::get_HW(const char* path) {

	FILE* file = fopen(path, "r");
	if (!file) return true;

	for (char i = fgetc(file); !feof(file) && (i != '\n'); i = fgetc(file)) width++;
	rewind(file);

	char* buffer = new char[width + 2];
	while (fgets(buffer, width + 2, file)) height++;
	delete[] buffer;

	fclose(file);

	if ((width < 5) && (height < 5)) {

		width = 0;
		height = 0;
		return true;
	}

	return false;
}

bool PlayGround::Read_Pole(const char* path) {

	if (!(data = new Cell * [height])) return true;
	for (int i = 0; i < height; i++) if (!(data[i] = new Cell[width])) return true;

	FILE* file = fopen(path, "r");
	if (!file) return true;

	for (int i = 0; i < height; i++) {
		for (int j = 0; j <= width; j++) {

			switch (fgetc(file))
			{
			case ' ':
				data[i][j].setFree();
				break;
			case '#':
				data[i][j].setWall();
				break;
			case 's':
				data[i][j].setStart();
				break;
			case 'f':
				data[i][j].setExit();
				break;
			default:
				break;
			}
		}
	}

	fclose(file);

	return false;
}

PlayGround* PlayGround::get_Pole(const char* path) {

	if (!ptr_pole) {

		ptr_pole = new PlayGround(path);
		destroyer.Initial(ptr_pole);
	}
	return ptr_pole;
}

void PlayGround::destr() {

	if (!data) return;

	for (int i = 0; i < height; i++)
		delete[] data[i];
	delete data;
}

PlayGround::PlayGround(const PlayGround& init) : width(init.width), height(init.height) {

	data = new Cell * [height];
	for (int i = 0; i < height; i++) data[i] = new Cell[width];

	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++) data[i][j] = init.data[i][j];
}

PlayGround::PlayGround(PlayGround&& init) noexcept : width(init.width), height(init.height) {

	init.ptr_pole = this;

	data = init.data;
	init.data = nullptr;
}

PlayGround& PlayGround::operator = (const PlayGround& init) {

	if (this == &init) return *this;

	for (int i = 0; i < height; i++) delete[] data[i];
	delete[] data;

	width = init.width;
	height = init.height;

	data = new Cell * [height];
	for (int i = 0; i < height; i++) data[i] = new Cell[width];

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
	init.ptr_pole = this;

	data = init.data;
	init.data = nullptr;

	return *this;
}

PG_Iter PlayGround::get_Iter_Begin() {

	PG_Iter iterator(this, 0, 0);
	return iterator;
}

PG_Iter PlayGround::get_Iter_End() {

	PG_Iter iterator(this, height - 1, width - 1);
	return iterator;
}

std::ostream& operator<< (std::ostream& out, const PlayGround& PG) {

	for (int i = 0; i < PG.height; i++) {

		for (int j = 0; j < PG.width; j++)
			if (PG.data[i][j].ifWall()) out << char(220) << char(254);
			else out << "  ";
		out << '\n';
		for (int j = 0; j < PG.width; j++)
			if (PG.data[i][j].ifWall()) out << char(220) << PG.data[i][j];
			else out << " " << PG.data[i][j];
		out << '\n';
	}

	return out;
}

// -------- Pole_Dest defenition

PG_Dest::~PG_Dest() {

	ptr_pole->destr();
	delete[] ptr_pole;
}

void PG_Dest::Initial(PlayGround* ptr) {

	ptr_pole = ptr;
}
