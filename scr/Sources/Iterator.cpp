#include "../Headers/Iterator.h"
#include "../Headers/Tile.h"

DrawIterator::DrawIterator(Tile* data, short height, short width, int data_len) : i_height(height), i_width(width) {

	h_count = 0;
	w_count = 0;
	container = data;
	length = data_len;
	iter_end = false;
	line_end = false;
}

DrawIterator& DrawIterator::operator++() {

	iter_end = false;
	line_end = false;
	w_count++;
	if (w_count == i_width) {

		h_count++;
		line_end = true;
		if (h_count == i_height) {

			h_count--;
			iter_end = true;
		}
		else w_count = 0;
	}
	return *this;
}

DrawIterator& DrawIterator::operator--() {

	iter_end = false;
	line_end = false;
	w_count--;
	if (w_count == -1) {

		h_count--;
		line_end = true;
		if (h_count == -1) {

			h_count++;
			iter_end = true;
		}
		else w_count = i_width - 1;
	}
	return *this;
}

DrawIterator DrawIterator::operator++(int) {

	DrawIterator iter = *this;

	iter_end = false;
	line_end = false;
	w_count++;
	if (w_count == i_width) {

		h_count++;
		line_end = true;
		if (h_count == i_height) {

			h_count--;
			iter_end = true;
		}
		else w_count = 0;
	}
	return iter;
}

DrawIterator DrawIterator::operator--(int) {

	DrawIterator iter = *this;

	iter_end = false;
	line_end = false;
	w_count--;
	if (w_count == -1) {

		h_count--;
		line_end = true;
		if (h_count == -1) {

			h_count++;
			iter_end = true;
		}
		else w_count = i_width - 1;
	}
	return iter;
}

void DrawIterator::setX(short x) {

	x < 0 ? x = 0 : x;
	x >= i_width ? x = i_width - 1 : x;
	w_count = x;
}

void DrawIterator::setY(short y) {

	y < 0 ? y = 0 : y;
	y >= i_width ? y = i_height - 1 : y;
	h_count = y;
}

void DrawIterator::setBegin() {
	
	h_count = 0;
	w_count = 0;
}

void DrawIterator::setEnd() {

	h_count = i_height - 1;
	w_count = i_width - 1;
}

bool DrawIterator::iterEnd() {

	return iter_end;
}

bool DrawIterator::lineEnd() {

	return line_end;
}

short DrawIterator::getX() {

	return w_count;
}

short DrawIterator::getY() {

	return h_count;
}

Tile* DrawIterator::getCurr() {

	Tile tile(w_count, h_count);
	for (int i = 0; i < length; i++) {

		if (container[i] == tile) return &container[i];
	}
	return nullptr;
}