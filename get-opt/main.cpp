#include <iostream>
#include <string>
#include <vector>
#include <exception>

// functions

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
			if (str[i] < 48 || str[i] > 57) throw std::exception("# str_num: Invalid number format!");
			num = num * 10 + (str[i] - 48);
		}

		if (point) num /= pow(10, str.size() - point);
		if (minus) num *= -1;
	}

	return num;
}

std::string num_str(double num) {

	bool minus = (num < 0) ? true : false;
	int num_i = int(abs(num));
	int num_f = int((abs(num) - int(abs(num))) * 100);

	std::string str;
	if (num_f > 0) str = std::string(".") + char(num_f / 10 + 48) + char(num_f % 10 + 48);

	for (int i = num_i; i > 0; i /= 10)
		str = char(i % 10 + 48) + str;

	if (str.empty()) str = "0";
	if (minus) str = "-" + str;

	return str;
}

std::string buildCircleXML(double c_x, double c_y, double rad, int pts) {

	std::string xml;
	xml += "M" + num_str(c_x + rad) + " " + num_str(c_y) + " ";
	for (int i = 1; i < pts; i++) {

		xml += "L";
		xml += num_str(std::cos(i / double(pts) * 6.28319) * rad + c_x) + " ";
		xml += num_str(std::sin(i / double(pts) * 6.28319) * rad + c_y) + " ";
	}
	xml += "Z";
	return xml;
}

// classes

typedef std::vector<std::string> options;
typedef std::pair<std::string, options> task;

class GetOptions {

private:
	std::vector<task> tasks;
	options keys;
	options data;

	void rebuildTasks() {

		bool is_key_open = false;

		tasks.clear();
		tasks.push_back(task("", options()));
		for (auto& i : data) {

			if (i[0] == '-') is_key_open = false;

			if (!is_key_open) {

				for (auto& j : keys) {

					if (i.substr(1, i.size() - 1) == j) {

						is_key_open = true;
						break;
					}
				}
				if (is_key_open) {

					tasks.push_back(task(i.substr(1, i.size() - 1), options()));
					continue;
				}
			}

			tasks[tasks.size() - 1].second.push_back(i);
		}
	}

public:
	void setKeys(options keys) {

		for (auto& i : keys)
			if (i == "") throw std::exception("# GetOptions.setKeys: Empty keys get!");
		this->keys = keys;
		rebuildTasks();
	}

	void setData(options data) {

		this->data = data;
		rebuildTasks();
	}

	std::vector<task> getTasks() {

		return tasks;
	}
};

// main

int main(int argc, char* argv[]) {

	options data;
	for (int i = 0; i < argc; i++) data.push_back(argv[i]);
	options keys;
	keys.push_back("circle");
	keys.push_back("points");
	keys.push_back("radius");
	keys.push_back("center");

	GetOptions executer;
	try {
		executer.setKeys(keys);
		executer.setData(data);
	}
	catch(std::exception exp) {

		std::cout << exp.what() << "\n";
	}
	std::vector<task> tasks = executer.getTasks();

	// output

	std::string key_edit;
	int points = 4;
	int radius = 1;
	int center_x = 0;
	int center_y = 0;

	for (auto& i : tasks) {

		if (i.first == "circle") {

			key_edit = "circle";
			if (!i.second.empty())
				std::cout << "# main: Only keys expected after \"-circle\" key!\n";
			std::cout << "> Circle XML: " + buildCircleXML(center_x, center_y, radius, points) + "\n";
			continue;
		}

		if (i.first == "points") {

			key_edit = "points";
			if (i.second.size() != 1)
				std::cout << "# main: Only one argument expected after \"-points\" key!\n";
			else {

				try {
					points = str_num(i.second[0]);
				}
				catch (std::exception exp) {

					std::cout << exp.what() << "\n";
				}
			}
			continue;
		}

		if (i.first == "radius") {

			key_edit = "radius";
			if (i.second.size() != 1)
				std::cout << "# main: Only one argument expected after \"-radius\" key!\n";
			else {

				try {
					radius = str_num(i.second[0]);
				}
				catch (std::exception exp) {

					std::cout << exp.what() << "\n";
				}
			}
			continue;
		}

		if (i.first == "center") {

			key_edit = "center";
			if (i.second.size() != 2)
				std::cout << "# main: Only two arguments expected after \"-center\" key!\n";
			else {

				try {
					center_x = str_num(i.second[0]);
					center_y = str_num(i.second[1]);
				}
				catch (std::exception exp) {

					std::cout << exp.what() << "\n";
				}
			}
			continue;
		}
	}

	return 0;
}