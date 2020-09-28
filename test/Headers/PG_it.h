#pragma once

#include "Def.h"

#define ITER_BEGIN -2
#define ITER_END -3

class PG_Iter {

private:

	short h_counter;
	short w_counter;
	PlayGround* ptr_PG;

public:

	PG_Iter(PlayGround*, short h, short w);

	PG_Iter& operator++();
	PG_Iter& operator--();

	bool Line_End();
	bool is_End();
	bool is_Begin();

	Cell& get_Current();
};