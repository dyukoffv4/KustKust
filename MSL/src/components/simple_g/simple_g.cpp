#include "simple_g.hpp"

MGL::Simple_G::Simple_G() : Group() {};

MGL::Simple_G::Simple_G(int i, Vector<short> p, Vector<byte_2> s) : Group(i, p, s) {};

char MGL::Simple_G::getSN() {
	return Object::SN::SIM_G;
}

bool MGL::Simple_G::getStat() {
	for (int i = 0; i < size.y; i++) {
		for (int j = 0; j < size.x; j++) if (grid[i][j] && grid[i][j]->getStat()) return true;
	}
	return false;
}