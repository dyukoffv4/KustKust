#include "Pole.h"
#include "Pole_Iter.h"
#include "Cell.h"

Pole_Iter::Pole_Iter(Pole* pole, short h, short w) : h_counter(h), w_counter(w), ptr_pole(pole) {
}

Pole_Iter& Pole_Iter::operator++() {

	if (w_counter == ITER_BEGIN) w_counter = 0;
	if (w_counter != ITER_END) w_counter++;
	if (w_counter == ptr_pole->width) {

		h_counter++;
		w_counter = 0;
	}
	if (h_counter == ptr_pole->height) {

		h_counter--;
		w_counter = ITER_END;
	}

	return *this;
}

Pole_Iter& Pole_Iter::operator--() {

	if (w_counter == ITER_END) w_counter = ptr_pole->width - 1;
	if (w_counter != ITER_BEGIN) w_counter--;
	if (w_counter == -1) {

		h_counter--;
		w_counter = ptr_pole->width - 1;
	}
	if (h_counter == -1) {

		h_counter++;
		w_counter = ITER_BEGIN;
	}

	return *this;
}

bool Pole_Iter::Line_End() {

	if (!ptr_pole->data) return true;
	return (w_counter == ptr_pole->width - 1);
}

bool Pole_Iter::is_End() {

	return ((!ptr_pole->data) || (w_counter == ITER_END));
}

bool Pole_Iter::is_Begin() {

	return ((!ptr_pole->data) || (w_counter == ITER_BEGIN));
}

Cell& Pole_Iter::get_Cell() {

	if (!is_End()) return ptr_pole->data[h_counter][w_counter];
	return ptr_pole->data[h_counter][w_counter + ptr_pole->width];
}