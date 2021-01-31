#include "Group.h"

mgl::Group::Group() : Object() {

	grid = nullptr;
	size = { 0, 0 };
	chest_s = nullptr;
	n = 0;
	osize = { 0, 0 };
}

mgl::Group::Group(int i, vect<short> p, vect<byte_2> s) : Object(i, p) {

	size = s;
	grid = new Object **[s.y];
	chest_s = new vect<byte_2> *[s.y];
	for (int i = 0; i < s.y; i++) {

		grid[i] = new Object *[s.x];
		for (int j = 0; j < s.x; j++) grid[i][j] = nullptr;
		chest_s[i] = new vect<byte_2>[s.x];
		for (int j = 0; j < s.x; j++) chest_s[i][j] = {0, 0};
	}
	n = 0;
	osize = { 0, 0 };
}

mgl::Group::~Group() {

	if (!grid || !chest_s) return;
	for (int i = 0; i < size.y; i++) {

		delete[] grid[i];
		delete[] chest_s[i];
	}
	delete[] grid;
	delete[] chest_s;
}

void mgl::Group::setSize(vect<byte_2> s) {

	byte_2 w = size.x, h = size.y;
	if (w < s.x) w = s.x;
	if (h < s.y) h = s.y;

	Object*** n_grid = new Object **[s.y];
	for (int i = 0; i < h; i++) {

		n_grid[i] = new Object *[s.x];
		for (int j = 0; j < w; j++) n_grid[i][j] = grid[i][j];
	}
	if (grid) {

		for (int i = 0; i < size.y; i++) delete[] grid[i];
		delete[] grid;
	}
	grid = n_grid;

	vect<byte_2>** n_chest_s = new vect<byte_2> *[s.y];
	for (int i = 0; i < h; i++) {

		n_chest_s[i] = new vect<byte_2>[s.x];
		for (int j = 0; j < w; j++) n_chest_s[i][j] = chest_s[i][j];
	}
	if (chest_s) {

		for (int i = 0; i < size.y; i++) delete[] chest_s[i];
		delete[] chest_s;
	}
	chest_s = n_chest_s;

	size = s;
}

mgl::vect<mgl::byte_2> mgl::Group::getSize() {

	return size;
}

void mgl::Group::draw(layout& win) {

	if (!grid) return;
	if (resized()) {

		grid[0][0]->setPosition(cord);
		for (int i = 0; i < size.y; i++) {

			if (i + 1 != size.y && grid[i + 1][0] && grid[i][0])
				grid[i + 1][0]->setPosition(grid[i][0]->getPosition() + vect<short>{0, (short)chest_s[i][0].y});
			for (int j = 0; j < size.x - 1; j++)
				if (grid[i][j + 1] && grid[i][j])
					grid[i][j + 1]->setPosition(grid[i][j]->getPosition() + vect<short>{(short)chest_s[i][j].x, 0});
		}
	}

	for (int i = 0; i < size.y; i++)
		for (int j = 0; j < size.x; j++)
			if (grid[i][j]) grid[i][j]->draw(win);
}

void mgl::Group::update(sf::Event& e) {

	if (!grid) return;
	for (int i = 0; i < size.y; i++)
		for (int j = 0; j < size.x; j++)
			if (grid[i][j]) grid[i][j]->update(e);
}

bool mgl::Group::resized() {

	if (!grid) return false;
	if (grid[n / size.y][n % size.x] && grid[n / size.y][n % size.x]->getSize() == osize)
		return false;

	for (int i = 0; i < size.y; i++) {

		byte_2 max = 0;
		for (int j = 0; j < size.x; j++)
			if (grid[i][j] && max < grid[i][j]->getSize().y)
				max = grid[i][j]->getSize().y;
		for (int j = 0; j < size.x; j++)
			chest_s[i][j].y = max;
	}
	for (int j = 0; j < size.x; j++) {

		byte_2 max = 0;
		for (int i = 0; i < size.y; i++)
			if (grid[i][j] && max < grid[i][j]->getSize().x)
				max = grid[i][j]->getSize().x;
		for (int i = 0; i < size.y; i++)
			chest_s[i][j].x = max;
	}
	return true;
}

mgl::Object*& mgl::Group::operator[](byte_4 _n) {

	if (_n > byte_4(size.x * size.y - 1)) _n = byte_4(size.x * size.y - 1);
	if (grid[_n / size.y][_n % size.x])
		osize = grid[_n / size.y][_n % size.x]->getSize();
	n = _n;
	return grid[n / size.y][n % size.x];
}