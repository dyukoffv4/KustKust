#include "daa_func.h"
#include "daa_oper.h"

bool daa_3::greedy(cc__arc arc, cci_map& map, c___vec& vec) {

	for (auto i = map[arc.first].end(); 1; 1) {

		if (i == map[arc.first].begin()) break;
		i--;

		if (!(*i).second) continue;

		int j = 0;
		for (j; j < vec.size(); j++) if (vec[j] == (*i).first) break;
		if (j != vec.size()) continue;

		vec.push_back((*i).first);
		if ((*i).first == arc.second) return true;
		if (greedy({ (*i).first, arc.second }, map, vec)) return true;
		vec.pop_back();
	}

	return false;
}

void daa_3::clearmap(cci_map& map) {

	for (auto& i : map)
		for (auto& j : i.second)
			j.second = 0;
}

long daa_3::findflow(cc__arc arc, cci_map& map) {

	c___vec vec;
	cvi_vec mem;
	int sum(0);

	vec.push_back(arc.first);
	while (greedy(arc, map, vec)) {

		int min = map[vec[0]][vec[1]];
		for (int i = 1; i < vec.size() - 1; i++)
			if (min > map[vec[i]][vec[i + 1]]) min = map[vec[i]][vec[i + 1]];

		for (int i = 0; i < vec.size() - 1; i++)
			map[vec[i]][vec[i + 1]] -= min;

		mem.push_back(cvi_arc(vec, min));
		sum += min;

		vec.clear();
		vec.push_back(arc.first);
	}

	clearmap(map);
	for (auto& i : mem)
		for (int j = 0; j < i.first.size() - 1; j++)
			map[i.first[j]][i.first[j + 1]] += i.second;

	return sum;
}