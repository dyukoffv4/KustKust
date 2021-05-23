#include "daa_func.h"
#include "daa_oper.h"
#include <fstream>

int main() {

	using namespace daa_3;

	cci_map map;
	cc__arc arc;
	c___vec vec;

	std::ifstream file("file1.txt");
	file >> arc.first >> arc.second;
	file >> map;
	file.close();
	
	std::cout << arc << '\n';
	std::cout << map << '\n';

	std::cout << findflow(arc, map) << '\n';
	std::cout << map << '\n';
	
	return 0;
}