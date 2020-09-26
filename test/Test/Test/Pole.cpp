#define _CRT_SECURE_NO_WARNINGS

#include "Pole.h"
#include "Cell.h"

Pole* Pole::ptr_pole = nullptr;
Pole_Dest Pole::destroyer;


// -------- Pole defenition


Pole::Pole(const char* path) : width(0), height(0) {

	PoleRead(path);
}

void Pole::PoleRead(const char* path) {

	FILE* file = fopen(path, "r");
	if (!file) return;

	for (char i = fgetc(file); !feof(file) && (i != '\n'); i = fgetc(file)) width++;
	rewind(file);

	char* buffer = new char[width + 2];
	while (fgets(buffer, width + 2, file)) height++;
	delete[] buffer;
	rewind(file);

	if ((height < 5) && (width < 5)) return;

	data = new Cell * [height];
	for (int i = 0; i < height; i++) data[i] = new Cell[width];

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

	if (this == &init)
		return *this;

	for (int i = 0; i < height; i++)
		delete[] data[i];
	delete[] data;

	data = init.data;
	init.data = nullptr;

	return *this;
}


// -------- Pole_Dest defenition


Pole_Dest::~Pole_Dest() {

	ptr_pole->destr();
	delete[] ptr_pole;
}

void Pole_Dest::Initial(Pole* ptr) {

	ptr_pole = ptr;
}


// -------- Pole_Iter defenition


Pole_Iter::Pole_Iter() : h_counter(0), w_counter(0) {

	ptr_pole = Pole::get_Pole(nullptr);
}

void Pole_Iter::next() {

	if (w_counter == -1) w_counter++;
	w_counter++;
	if (w_counter == ptr_pole->width) {

		h_counter++;
		w_counter = 0;
	}
	if (h_counter == ptr_pole->height) {

		h_counter = 0;
		w_counter = -1;
	}
}

bool Pole_Iter::Line_End() {

	if (!ptr_pole->data) return true;
	return (w_counter == ptr_pole->width - 1);
}

bool Pole_Iter::Iter_End() {

	if (!ptr_pole->data) return true;
	return (w_counter == -1);
}

Cell& Pole_Iter::get_Cell() {

	return ptr_pole->data[h_counter][w_counter];
}