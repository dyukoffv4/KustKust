#include "../Headers/Cell.h"
#include "../Headers/PG.h"
#include "../Headers/PG_it.h"

int main(int argc, char* argv[]) {

	PlayGround* ptr = PlayGround::get_Pole(argv[1]);

	for (PG_Iter i = ptr->get_Iter_Begin(); !i.is_End(); ++i) {

		std::cout << i.get_Cell();
		if (i.Line_End()) std::cout << '\n';
	}

	puts("\n");

	for (PG_Iter i = ptr->get_Iter_End(); !i.is_Begin(); --i) {

		if (i.Line_End()) std::cout << '\n';
		std::cout << i.get_Cell();
	}
	
	puts("\n");

	return 0;
}
