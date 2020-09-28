#include "../Headers/PG.h"
#include "../Headers/PG_it.h"
#include "../Headers/Cell.h"

PG_Iter::PG_Iter(PlayGround* pole, short h, short w) : h_counter(h), w_counter(w), ptr_PG(pole) {
}

PG_Iter& PG_Iter::operator++() {

	if (w_counter == ITER_BEGIN) w_counter = 0;
	if (w_counter != ITER_END) w_counter++;
	if (w_counter == ptr_PG->width) {

		h_counter++;
		w_counter = 0;
	}
	if (h_counter == ptr_PG->height) {

		h_counter--;
		w_counter = ITER_END;
	}

	return *this;
}

PG_Iter& PG_Iter::operator--() {

	if (w_counter == ITER_END) w_counter = ptr_PG->width - 1;
	if (w_counter != ITER_BEGIN) w_counter--;
	if (w_counter == -1) {

		h_counter--;
		w_counter = ptr_PG->width - 1;
	}
	if (h_counter == -1) {

		h_counter++;
		w_counter = ITER_BEGIN;
	}

	return *this;
}

bool PG_Iter::Line_End() {

	if (!ptr_PG->data) return true;
	return (w_counter == ptr_PG->width - 1);
}

bool PG_Iter::is_End() {

	return ((!ptr_PG->data) || (w_counter == ITER_END));
}

bool PG_Iter::is_Begin() {

	return ((!ptr_PG->data) || (w_counter == ITER_BEGIN));
}

Cell& PG_Iter::get_Current() {

	if (!is_End()) return ptr_PG->data[h_counter][w_counter];
	return ptr_PG->data[h_counter][w_counter + ptr_PG->width];
}