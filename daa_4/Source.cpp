#include "daa_func.h"
#include <iostream>

int main() {

	using namespace daa_4;

	daa_str circ_s, main_s;
	std::cin >> circ_s >> main_s;

	std::cout << get_circentry(circ_s, main_s);

	return 0;
}