#include <iostream>
#include <vector>
#include <string>
#include <keyparser/terminal.hpp>

using namespace KP;

int atoi(std::string str) {
	int num = 0;
	if (!str.empty()) {
		for (int i = 0; i < str.size(); i++) {
			if (str[i] > 47 && str[i] < 58) num = num * 10 + (str[i] - 48);
			else throw std::domain_error("str_num: Invalid number format!");
		}
	}
	return num;
}

namespace Main {
	std::vector<int> sums;
	
	int brackets(Args args);
	
	void increase(Args args) {
		if (args.size() == 1) sums[sums.size() - 1] += atoi(args[0]);
		else sums[sums.size() - 1] += brackets(args);
	}
	
	void decrease(Args args) {
		if (args.size() == 1) sums[sums.size() - 1] -= atoi(args[0]);
		else sums[sums.size() - 1] -= brackets(args);
	}
	
	void multiply(Args args) {
		if (args.size() == 1) sums[sums.size() - 1] *= atoi(args[0]);
		else sums[sums.size() - 1] *= brackets(args);
	}
	
	void division(Args args) {
		if (args.size() == 1) sums[sums.size() - 1] /= atoi(args[0]);
		else sums[sums.size() - 1] /= brackets(args);
	}
	
	int brackets(Args args) {
		sums.push_back(0);
		
		Terminal terminal;
		terminal.setKey(Key("s+", 1, 0xFFFFFFFF), increase);
		terminal.setKey(Key("s-", 1, 0xFFFFFFFF), decrease);
		terminal.setKey(Key("s.", 1, 0xFFFFFFFF), multiply);
		terminal.setKey(Key("s:", 1, 0xFFFFFFFF), division);
		terminal.execute(args);
		int sum = sums[sums.size() - 1];
		
		sums.pop_back();
		return sum;
	}
	
	int execute(int argc, char* argv[]) {
		std::string text = "";
		for (int i = 1; i < argc; i++) text += std::string(argv[i]);
		
		Args data;
		int level = 0, open = true;
		for (int i = 0; i < text.size(); i++) {
			if (text[i] == '[') {
				if (open) data.push_back(std::string(level, '-') + "--s+");
				level++;
				open = true;
			}
			else {
				if (text[i] == ']') level--;
				else if (text[i] > 47 && text[i] < 58) {
					if (open) data.push_back(std::string(level, '-') + "--s+");
					if (data[data.size() - 1][0] == '-') data.push_back("");
					data[data.size() - 1] += text[i];
				}
				else data.push_back(std::string(level, '-') + "--s" + text[i]);
				open = false;
			}
			if (level < 0) throw std::invalid_argument("Invalid input format!");
		}
		if (level > 0) throw std::invalid_argument("Invalid input format!");
		
		return brackets(data);
	}
}

int main(int argc, char* argv[]) {
	try {
		std::cout << Main::execute(argc, argv) << "\n";
	}
	catch (std::invalid_argument e) {
		std::cout << e.what() << "\n";
	}
	
	return 0;
}
