#include "daa_func.h"
#include "daa_oper.h"

int main() {

	using namespace daa_2;

	dmap_cs map;
	doub_cc arc;
	dvec_c_ vec;

	/**/
	arc = { 'a', 'y' };
	map_ze_gen(map);
	/**
	arc = { 'a', 'e' };
	map_md_gen(map);
	/**
	arc = { 'e', 'u' };
	map_sd_gen(map);
	/**/

	std::cout << arc.first << ' ' << arc.second << '\n';
	std::cout << map << '\n';

	/**/
	vec.push_back(arc.first);
	if (greedy(arc, map, vec)) std::cout << vec << '\n';
	else std::cout << "no path\n";
	/**/
	if (dijkstra(arc, map, vec)) std::cout << vec << '\n';
	else std::cout << "no path\n";
	/**/
	if (a_star(arc, map, vec)) std::cout << vec << '\n';
	else std::cout << "no path\n";
	/**/

	return 0;
}