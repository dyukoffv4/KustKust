#include "Cell.h"
#include "Pole.h"

int main() {

	const Pole* ptr = Pole::get_Pole("C:\\Games\\hello.txt");

	for (Pole_Iter i; !i.Iter_End(); i.next()) {

		std::cout << i.get_Cell();
		if (i.Line_End()) std::cout << '\n';
	}

	return 0;
}