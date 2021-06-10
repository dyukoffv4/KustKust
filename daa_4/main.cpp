#include "daa_func.h"
#include <iostream>

int main() {

	using namespace daa_4;

	std::cout << "Welcome. This program is designed to search for a pattern in a certain string.";
	std::cout << "\nIt also sets the cyclic dependency of strings.";

	while (1) {

		char flag;
		daa_str temp_s, main_s;
		std::cout << "\n\nWhat task do you want to perform - search for patterns in a row / check the cyclic dependency of rows (P / C): ";
		while (1) {

			std::cin >> flag;
			if (flag == 'P' || flag == 'C' || flag == 'p' || flag == 'c') break;
			std::cout << "Wrong input. Please, try again: ";
		}

		if (flag == 'C' || flag == 'c') {

			std::cout << "\nEnter the first string: ";
			std::cin >> temp_s;
			std::cout << "\nEnter the second string: ";
			std::cin >> main_s;
			int i = get_circentry(temp_s, main_s);
			if (i == -1) std::cout << "\nNo row is a cyclic shift of the second one.";
			else {

				std::cout << "\nThe first line is a cyclic shift of the second.";
				std::cout << "\nIndex of the occurrence of the second in the first: " << i;
			}
		}

		if (flag == 'P' || flag == 'p') {
		
			std::cout << "\nEnter the template string: ";
			std::cin >> temp_s;
			std::cout << "\nEnter a search string: ";
			std::cin >> main_s;
			daa_vec vect = get_entrys(main_s, temp_s);
			if (vect.empty()) std::cout << "\nThe template string was not found in the search string.";
			else {

				std::cout << "\nThe template string was found in the search string " << vect.size() << " times.";
				std::cout << "\nIndexes of occurrences of the template string: ";
				for (int i = 0; i < vect.size() - 1; i++) std::cout << vect[i] << ", ";
				std::cout << vect[vect.size() - 1];
			}
		}

		std::cout << "\n\nDo you want to continue (Y / N): ";
		while (1) {

			std::cin >> flag;
			if (flag == 'Y' || flag == 'N' || flag == 'y' || flag == 'n') break;
			std::cout << "Wrong input. Please, try again: ";
		}
		if (flag == 'N' || flag == 'n') break;
	}

	std::cout << "\nExit from programm.\n";

	return 0;
}