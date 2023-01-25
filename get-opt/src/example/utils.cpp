#include <cmath>
#include "utils.hpp"

int str_int(std::string str) {
	int num = 0;
	if (!str.empty()) {
		bool minus = false;
		for (int i = 0; i < str.size(); i++) {
			if (str[i] == '-') {
				minus = true;
				continue;
			}
			if (str[i] < 48 || str[i] > 57) throw std::domain_error("str_num: Invalid number format!");
			num = num * 10 + (str[i] - 48);
		}
		if (minus) num *= -1;
	}
	return num;
}

std::string int_str(int num) {
	std::string str;
	bool minus = (num < 0) ? true : false;
	for (int i = num; i > 0; i /= 10) str = char(i % 10 + 48) + str;
	if (num == 0) str = "0" + str;
	if (minus) str = "-" + str;
	return str;
}