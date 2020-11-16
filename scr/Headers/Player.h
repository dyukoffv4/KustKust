#pragma once

#include "Def.h"

class Player{

private:
	short x_pos;
	short y_pos;
	short x_prepos;
	short y_prepos;
	unsigned char apple;
	unsigned char pie;
	unsigned char key;

public:
	Player(short, short);

	short getX();
	short getY();
	unsigned char getApple();
	unsigned char getPie();
	unsigned char getKey();
	void Move(char);
	void moveBack();

	friend void operator+=(Player&, Object*);

	friend std::ostream& operator<<(std::ostream&, Player*);
};