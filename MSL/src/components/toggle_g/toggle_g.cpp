#include "toggle_g.hpp"

mgl::Toggle_G::Toggle_G() : Group() {};

mgl::Toggle_G::Toggle_G(int i, vect<short> p, vect<byte_2> s) : Group(i, p, s) {};

char mgl::Toggle_G::getSN() {

	return Object::SN::TOG_G;
}

bool mgl::Toggle_G::getStat() {

	for (int i = 0; i < size.y; i++)
		for (int j = 0; j < size.x; j++)
			if (grid[i][j] && !grid[i][j]->getStat()) return false;
	return true;
}