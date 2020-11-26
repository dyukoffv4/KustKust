#include "../Headers/Iterator.h"
#include "../Headers/Tile.h"

Iterator::Iterator(Tile** data, short height, short width) : i_height(height), i_width(width) {

	h_count = 0;
	w_count = 0;
	container = data;
	iter_end = false;
	line_end = false;
}

Iterator& Iterator::operator++() {

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

Iterator& Iterator::operator--() {

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

Iterator Iterator::operator++(int) {

	Iterator iter = *this;

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

Iterator Iterator::operator--(int) {

	Iterator iter = *this;

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

void Iterator::setX(short x) {

	x < 0 ? x = 0 : x;
	x >= i_width ? x = i_width - 1 : x;
	w_count = x;
}

void Iterator::setY(short y) {

	y < 0 ? y = 0 : y;
	y >= i_width ? y = i_height - 1 : y;
	h_count = y;
}

void Iterator::setBegin() {
	
	h_count = 0;
	w_count = 0;
}

void Iterator::setEnd() {

	h_count = i_height - 1;
	w_count = i_width - 1;
}

bool Iterator::iterEnd() {

	return iter_end;
}

bool Iterator::lineEnd() {

	return line_end;
}

short Iterator::getX() {

	return w_count;
}

short Iterator::getY() {

	return h_count;
}

Tile& Iterator::getCurr() {

	return container[h_count][w_count];
}