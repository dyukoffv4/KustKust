#include "../Headers/Cell.h"

void Cell::setFree() { condition = 0; }
void Cell::setWall() { condition = 1; }
void Cell::setStart() { condition = 2; }
void Cell::setExit() { condition = 3; }

bool Cell::ifFree() { return condition == 0; }
bool Cell::ifWall() { return condition == 1; }
bool Cell::ifStart() { return condition == 2; }
bool Cell::ifExit() { return condition == 3; }

std::ostream& operator<< (std::ostream& out, const Cell& cell) {

	switch (cell.condition) {
	case 0:
		out << ".";
		break;
	case 1:
		out << char(254);
		break;
	case 2:
		out << 'O';
		break;
	case 3:
		out << 'X';
		break;
	}

	return out;
}
