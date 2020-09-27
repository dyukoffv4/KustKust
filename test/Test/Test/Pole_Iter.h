#pragma once

#include "Defenition.h"

#define ITER_BEGIN -2
#define ITER_END -3

class Pole_Iter {

private:

	int h_counter;
	int w_counter;
	Pole* ptr_pole;

public:

	Pole_Iter(Pole*, short h, short w);

	Pole_Iter& operator++();
	Pole_Iter& operator--();

	bool Line_End();
	bool is_End();
	bool is_Begin();

	Cell& get_Cell();
};