#include "toggle_g.hpp"

MGL::Toggle_G::Toggle_G() : Group() {};

MGL::Toggle_G::Toggle_G(int i, Vector<short> p, Vector<byte_2> s) : Group(i, p, s) {};

char MGL::Toggle_G::getSN() {
	return Object::SN::TOG_G;
}

bool MGL::Toggle_G::getStat() {
	for (int i = 0; i < size.y; i++) {
		for (int j = 0; j < size.x; j++) if (grid[i][j] && !grid[i][j]->getStat()) return false;
	}
	return true;
}