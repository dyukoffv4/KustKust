#include "daa_func.h"
#include "daa_oper.h"

int main() {

	using namespace daa_3;

	cci_map map;
	cc__arc arc = {'a', 'd'};
	map['a']['b'] = 100;
	map['a']['c'] = 500;
	map['b']['d'] = 500;
	map['c']['d'] = 100;
	map['c']['b'] = 500;
	
	std::cout << arc << '\n';
	std::cout << map << '\n';

	std::cout << findflow(arc, map) << '\n';
	std::cout << map << '\n';
	
	return 0;
}