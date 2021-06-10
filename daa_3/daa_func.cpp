#include "daa_func.h"
#include "daa_oper.h"

bool daa_3::greedy(cc__arc arc, cci_map& map, c___vec& vec) {

	ccc_map que;
	for (auto& i : map[arc.first]) {

		int k = 0;
		for (k; k < vec.size() - 1; k++) if (vec[k] == arc.first && vec[k + 1] == i.first) break;
		if (k != vec.size() - 1) continue;

		char diff = abs(arc.first - i.first);
		if (i.second) que[diff][i.first] = 0;
	}

	for (auto& i : que) {
		for (auto& j : i.second) {

			vec.push_back(j.first);
			if (j.first == arc.second) return true;
			if (greedy({ j.first, arc.second }, map, vec)) return true;
			vec.pop_back();
		}
	}

	return false;
}

void daa_3::clearmap(cci_map& map) {

	for (auto& i : map)
		for (auto& j : i.second)
			j.second = 0;
}

long daa_3::findflow(cc__arc arc, cci_map& omap) {

	c___vec vec;
	cvi_vec mem;
	cci_map map = omap;
	int sum = 0;

	vec.push_back(arc.first);
	while (greedy(arc, map, vec)) {

		int min = map[vec[0]][vec[1]];
		for (int i = 1; i < vec.size() - 1; i++)
			if (min > map[vec[i]][vec[i + 1]]) min = map[vec[i]][vec[i + 1]];

		for (int i = 0; i < vec.size() - 1; i++)
			map[vec[i]][vec[i + 1]] -= min;
		for (int i = vec.size() - 2; i > 1; i--)
			map[vec[i]][vec[i - 1]] = min;

		mem.push_back(cvi_arc(vec, min));
		sum += min;

		vec.clear();
		vec.push_back(arc.first);
	}

	clearmap(omap);
	for (auto& i : mem)
		for (int j = 0; j < i.first.size() - 1; j++) {

			if (omap[i.first[j]].count(i.first[j + 1])) omap[i.first[j]][i.first[j + 1]] += i.second;
			else if (omap.count(i.first[j + 1]) && omap[i.first[j + 1]].count(i.first[j])) omap[i.first[j + 1]][i.first[j]] -= i.second;
		}

	return sum;
}