#include "../Headers/Cell.h"
#include "../Headers/PG.h"
#include "../Headers/PG_it.h"

int main() {

	PlayGround* ptr = PlayGround::get_Pole("C:\\Games\\hello.txt");
	
	puts("\n");
	
	for (PG_Iter i = ptr->get_Iter_Begin(); !i.is_End(); ++i) {

		std::cout << i.get_Current();
		if (i.Line_End()) std::cout << '\n';
	}
	
	puts("\n");
	
	std::cout << *ptr;
	
	puts("\n");

	return 0;
}