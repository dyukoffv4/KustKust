#include "daa.h"

int main() {

	using namespace daa_1;
	
	list	data;
	int		numb;
	time_t	tick;

	while (1) {

		std::cin >> numb;
		if (numb < 2) break;
		tick = clock();

		data = rbt(numb);

		system("cls");
		std::cout << double(clock() - tick) / 1000 << '\n';
		std::cout << data.size() << '\n';
		for (auto i = data.begin(); i != data.end(); ++i)
			std::cout << (*i) << '\n';
	}

	return 0;
}
