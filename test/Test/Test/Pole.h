#pragma once

#include "Defenition.h"

class PG_Dest {

private:

	PlayGround* ptr_pole;

public:

	~PG_Dest();
	void Initial(PlayGround*);
};

class PlayGround {

private:

	static PlayGround* ptr_pole;
	static PG_Dest destroyer;

	Cell** data;
	short width;
	short height;

	//-------------------------

	PlayGround(const char*);

	PlayGround(const PlayGround&);
	PlayGround& operator = (const PlayGround&);

	void destr();
	bool get_HW(const char*);
	bool Read_Pole(const char*);

protected:

	friend class PG_Dest;
	friend class PG_Iter;

public:

	static PlayGround* get_Pole(const char*);

	PlayGround(PlayGround&&) noexcept;
	PlayGround& operator = (PlayGround&&) noexcept;

	//-------------------------

	PG_Iter get_Iter_Begin();
	PG_Iter get_Iter_End();
};