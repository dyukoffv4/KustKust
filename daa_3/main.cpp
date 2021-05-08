#include "daa_func.h"
#include "daa_oper.h"

int main() {

	using namespace daa_3;

	cci_map map;
	cc__arc arc;
	c___vec vec;

	arc = { 'a', 'b' };
	map['a']['d'] = 11;
	map['a']['c'] = 10;
	map['c']['d'] = 11;
	map['c']['b'] = 10;
	map['d']['b'] = 11;
	
	std::cout << arc << '\n';
	std::cout << map << '\n';

	std::cout << findflow(arc, map) << '\n';
	std::cout << map << '\n';
	
	return 0;
}