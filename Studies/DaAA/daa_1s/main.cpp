#include "daa.h"

using namespace daa_1;

void special_print(int size, const list& data) {
	bool space = true;

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			for (int k = 0; k < data.size(); k++) {
				if (data[k].second.first == i && data[k].second.second == j) {
					if (data[k].first == 1) std::wcout << L"■ ";
					else std::wcout << L"┌─";
					space = false;
					break;
				}
				if (data[k].second.first == i && data[k].second.second + data[k].first - 1 == j) {
					std::wcout << L"┐ ";
					space = false;
					break;
				}
				if (data[k].second.first + data[k].first - 1 == i && data[k].second.second == j) {
					std::wcout << L"└─";
					space = false;
					break;
				}
				if (data[k].second.first + data[k].first - 1 == i && data[k].second.second + data[k].first - 1 == j) {
					std::wcout << L"┘ ";
					space = false;
					break;
				}

				if (data[k].second.second + data[k].first > j && data[k].second.second <= j) {
					if (data[k].second.first == i || data[k].second.first + data[k].first - 1 == i) {
						std::wcout << L"──";
						space = false;
						break;
					}
				}
				if (data[k].second.first + data[k].first > i && data[k].second.first <= i) {
					if (data[k].second.second == j || data[k].second.second + data[k].first - 1 == j) {
						std::wcout << L"│ ";
						space = false;
						break;
					}
				}
			}
			if (space) std::wcout << L"  ";
			space = true;
		}
		std::wcout << '\n';
	}
}

int main() {
	std::locale::global(std::locale("en_US.UTF-8"));

	list	data;
	int		numb;
	double	tick;

	while (1) {
		std::cin >> numb;
		if (numb < 2) break;

		tick = clock();
		data = rbt(numb);
		tick = double(clock() - tick) / 1000;

		system("clear");
		std::wcout << "Work time (ms): " << tick << '\n';
		std::wcout << "Input: " << numb << "   Output: " << data.size() << '\n';
		std::wcout << "Squares placing:\n";
		special_print(numb, data);
	}

	return 0;
}