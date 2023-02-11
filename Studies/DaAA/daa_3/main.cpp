#include "daa_func.h"
#include "daa_oper.h"

int main() {

	using namespace daa_3;

	cci_map map;
	cc__arc arc;
	int non, ch3;
	char ch1, ch2;

	std::cout << "Welcome. This program is designed to find the maximum flow.\n";

	while (1) {

		std::cout << "\nEnter the source and destination nodes: ";
		std::cin >> arc;
		std::cout << "\nEnter the number of edges of the graph: ";
		std::cin >> non;
		std::cout << "\nEnter the edges of the graph (<first node> <second node> <length>):\n";
		for (int i = 0; i < non; i++) {

			std::cin >> ch1 >> ch2 >> ch3;
			map[ch1][ch2] = ch3;
		}

		std::cout << "\n\nMaximum flow in the graph: " << findflow(arc, map);
		std::cout << "\n\nMinimum graph used:\n" << map;

		std::cout << "\nDo you want to continue (Y / N): ";
		while (1) {

			std::cin >> ch1;
			if (ch1 == 'Y' || ch1 == 'N' || ch1 == 'y' || ch1 == 'n') break;
			std::cout << "\nWrong input. Please, try again.\n";
		}
		if (ch1 == 'N' || ch1 == 'n') break;
	}
	
	std::cout << "\nExit from programm.\n";

	return 0;
}