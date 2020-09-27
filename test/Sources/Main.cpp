#include "../Headers/Cell.h"
#include "../Headers/PG.h"
#include "../Headers/PG_it.h"

int main(int argc, char* argv[]) {

	PlayGround* ptr = PlayGround::get_Pole(argv[1]);
	/*
	puts("\n");
	
	for (PG_Iter i = ptr->get_Iter_Begin(); !i.is_End(); ++i) {

		std::cout << i.get_Curent();
		if (i.Line_End()) std::cout << '\n';
	}
	*/
	puts("\n");
	
	std::cout << *ptr;
	
	puts("\n");

	return 0;
}
