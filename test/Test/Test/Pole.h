#pragma once

#include "Defenition.h"

#define ITER_BEGIN -2
#define ITER_END -3

class Pole_Dest {

private:

	Pole* ptr_pole;

public:

	~Pole_Dest();
	void Initial(Pole*);
};

class Pole {

private:

	static Pole* ptr_pole;
	static Pole_Dest destroyer;

	Cell** data;
	short width;
	short height;

	//-------------------------

	Pole(const char*);

	Pole(const Pole&);
	Pole& operator = (const Pole&);

	void destr();
	bool get_HW(const char*);
	bool Read_Pole(const char*);

protected:

	friend class Pole_Dest;
	friend class Pole_Iter;

public:

	static Pole* get_Pole(const char*);

	Pole(Pole&&) noexcept;
	Pole& operator = (Pole&&) noexcept;

	//-------------------------

	Pole_Iter get_Iter_Begin();
	Pole_Iter get_Iter_End();
};

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