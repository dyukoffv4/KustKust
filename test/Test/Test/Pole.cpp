#define _CRT_SECURE_NO_WARNINGS

#include "Pole.h"
#include "Cell.h"
#include "Pole_Iter.h"

Pole* Pole::ptr_pole = nullptr;
Pole_Dest Pole::destroyer;

// -------- Pole defenition

Pole::Pole(const char* path) : width(0), height(0), data(nullptr) {

	if (get_HW(path)) return;

	if (Read_Pole(path)) data = nullptr;
}

bool Pole::get_HW(const char* path) {

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

bool Pole::Read_Pole(const char* path) {

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

Pole* Pole::get_Pole(const char* path) {

	if (!ptr_pole) {

		ptr_pole = new Pole(path);
		destroyer.Initial(ptr_pole);
	}
	return ptr_pole;
}

void Pole::destr() {

	if (!data) return;

	for (int i = 0; i < height; i++)
		delete[] data[i];
	delete data;
}

Pole::Pole(const Pole& init) : width(init.width), height(init.height) {

	data = new Cell * [height];
	for (int i = 0; i < height; i++) data[i] = new Cell[width];

	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++) data[i][j] = init.data[i][j];
}

Pole::Pole(Pole&& init) noexcept : width(init.width), height(init.height) {

	init.ptr_pole = this;

	data = init.data;
	init.data = nullptr;
}

Pole& Pole::operator = (const Pole& init) {

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

Pole& Pole::operator = (Pole&& init) noexcept {

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

Pole_Iter Pole::get_Iter_Begin() {

	Pole_Iter iterator(this, 0, 0);
	return iterator;
}

Pole_Iter Pole::get_Iter_End() {

	Pole_Iter iterator(this, height - 1, width - 1);
	return iterator;
}

// -------- Pole_Dest defenition

Pole_Dest::~Pole_Dest() {

	ptr_pole->destr();
	delete[] ptr_pole;
}

void Pole_Dest::Initial(Pole* ptr) {

	ptr_pole = ptr;
}