#include "Cell.h"
#include "Pole.h"

int main() {

	Pole* ptr = Pole::get_Pole("C:\\Games\\hello.txt");

	for (Pole_Iter i = ptr->get_Iter_Begin(); !i.is_End(); ++i) {

		std::cout << i.get_Cell();
		if (i.Line_End()) std::cout << '\n';
	}

	puts("\n");

	for (Pole_Iter i = ptr->get_Iter_End(); !i.is_Begin(); --i) {

		if (i.Line_End()) std::cout << '\n';
		std::cout << i.get_Cell();
	}

	return 0;
}