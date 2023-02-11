#include "simple_g.hpp"

mgl::Simple_G::Simple_G() : Group() {};

mgl::Simple_G::Simple_G(int i, vect<short> p, vect<byte_2> s) : Group(i, p, s) {};

char mgl::Simple_G::getSN() {

	return Object::SN::SIM_G;
}

bool mgl::Simple_G::getStat() {

	for (int i = 0; i < size.y; i++)
		for (int j = 0; j < size.x; j++)
			if (grid[i][j] && grid[i][j]->getStat()) return true;
	return false;
}