#pragma once

#include "Def.h"

#define ITER_BEGIN -2
#define ITER_END -3

class PG_Iter {

private:

	int h_counter;
	int w_counter;
	PlayGround* ptr_pole;

public:

	PG_Iter(PlayGround*, short h, short w);

	PG_Iter& operator++();
	PG_Iter& operator--();

	bool Line_End();
	bool is_End();
	bool is_Begin();

	Cell& get_Curent();
};
