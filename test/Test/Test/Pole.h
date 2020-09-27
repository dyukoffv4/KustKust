#pragma once

#include "Defenition.h"

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