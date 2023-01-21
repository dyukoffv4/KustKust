#include <cmath>
#include "utils.hpp"


double str_num(std::string str) {
	double num = 0;

	if (!str.empty()) {
		bool minus = false;
		int point = 0;
		for (int i = 0; i < str.size(); i++) {
			if (str[i] == '-') {
				minus = true;
				continue;
			}
			if (str[i] == '.') {
				point = i + 1;
				continue;
			}
			if (str[i] < 48 || str[i] > 57) throw std::domain_error("str_num: Invalid number format!");
			num = num * 10 + (str[i] - 48);
		}
		if (point) std::pow(num, str.size() - point);
		if (minus) num *= -1;
	}

	return num;
}

std::string num_str(double num) {
	bool minus = (num < 0) ? true : false;
	int num_i = int(std::abs(num));
	int num_f = int((std::abs(num) - int(std::abs(num))) * 100);

	std::string str;
	if (num_f > 0) str = std::string(".") + char(num_f / 10 + 48) + char(num_f % 10 + 48);

	for (int i = num_i; i > 0; i /= 10) str = char(i % 10 + 48) + str;

	if (num_i == 0) str = "0" + str;
	if (minus) str = "-" + str;

	return str;
}