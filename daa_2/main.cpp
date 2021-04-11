#include <fstream>
#include "daa_func.h"
#include "daa_oper.h"

int main() {

	using namespace daa_2;

	std::ifstream file;
	dmap_cs map;
	doub_cc arc;
	dvec_c_ vec;

	//map_gen(map);

	file.open("..\\file_test.txt");
	if (!file.is_open()) return 0;

	/**
	file << "a e\n";
	file << map;
	/**/
	file >> arc;
	file >> map;
	/**/

	file.close();

	std::cout << arc.first << ' ' << arc.second << '\n';
	std::cout << map << '\n';

	/**
	vec.push_back(arc.first);
	if (greedy(arc, map, vec)) std::cout << vec;
	else std::cout << "no path";
	/**/
	if (dijkstra(arc, map, vec)) std::cout << vec;
	else std::cout << "no path";
	/**
	if (a_star(arc, map, vec)) std::cout << vec;
	else std::cout << "no path";
	/**/

	return 0;
}