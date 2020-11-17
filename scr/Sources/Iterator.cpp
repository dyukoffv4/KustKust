#include "../Headers/PlayGround.h"
#include "../Headers/Iterator.h"
#include "../Headers/Title.h"

IteratorPG::IteratorPG(Title** data, short height, short width) : i_height(height), i_width(width) {

	h_count = 0;
	w_count = 0;
	container = data;
	iter_end = false;
	line_end = false;
}

IteratorPG& IteratorPG::operator++() {

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

IteratorPG& IteratorPG::operator--() {

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

IteratorPG IteratorPG::operator++(int) {

	IteratorPG iter = *this;

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

IteratorPG IteratorPG::operator--(int) {

	IteratorPG iter = *this;

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

void IteratorPG::setX(short x) {

	x < 0 ? x = 0 : x;
	x >= i_width ? x = i_width - 1 : x;
	w_count = x;
}

void IteratorPG::setY(short y) {

	y < 0 ? y = 0 : y;
	y >= i_width ? y = i_height - 1 : y;
	h_count = y;
}

void IteratorPG::setBegin() {
	
	h_count = 0;
	w_count = 0;
}

void IteratorPG::setEnd() {

	h_count = i_height - 1;
	w_count = i_width - 1;
}

bool IteratorPG::iterEnd() {

	return iter_end;
}

bool IteratorPG::lineEnd() {

	return line_end;
}

short IteratorPG::getX() {

	return w_count;
}

short IteratorPG::getY() {

	return h_count;
}

Title& IteratorPG::getCurr() {

	return container[h_count][w_count];
}