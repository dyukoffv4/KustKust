#include "Cell.h"
#include "Pole.h"
#include "Pole_Iter.h"

int main() {

	PlayGround* ptr = PlayGround::get_Pole("C:\\Games\\hello.txt");

	for (PG_Iter i = ptr->get_Iter_Begin(); !i.is_End(); ++i) {

		std::cout << i.get_Cell();
		if (i.Line_End()) std::cout << '\n';
	}

	puts("\n");

	for (PG_Iter i = ptr->get_Iter_End(); !i.is_Begin(); --i) {

		if (i.Line_End()) std::cout << '\n';
		std::cout << i.get_Cell();
	}

	return 0;
}