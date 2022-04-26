#include "daa_func.h"

void daa_2::map_ze_gen(dmap_cs& data) {

	for (char i = 'a'; i < 'z'; i++) {

		if ((i - 'a') % 5 != 0) data[i].insert({ 1, i - 1 });
		if ((i - 'a') % 5 != 4) data[i].insert({ 1, i + 1 });
		if (i - 5 >= 'a') data[i].insert({ 1, i - 5 });
		if (i + 5 <= 'y') data[i].insert({ 1, i + 5 });
	}
}

void daa_2::map_md_gen(dmap_cs& data) {

	for (char i = 'a'; i < 'z'; i++) {

		float temp = float((i - 'a') % 5) - float((i - 'a') / 5);
		if ((i - 'a') % 5 != 0) data[i].insert({ abs(temp - 1) + 1, i - 1 });
		if ((i - 'a') % 5 != 4) data[i].insert({ abs(temp + 1) + 1, i + 1 });
		if (i - 5 >= 'a') data[i].insert({ abs(temp + 1) + 1, i - 5 });
		if (i + 5 <= 'y') data[i].insert({ abs(temp - 1) + 1, i + 5 });
	}
}

void daa_2::map_sd_gen(dmap_cs& data) {

	for (char i = 'a'; i < 'z'; i++) {

		float temp = float((i - 'a') % 5) + float((i - 'a') / 5) - 4;
		if ((i - 'a') % 5 != 0) data[i].insert({ abs(temp - 1) + 1, i - 1 });
		if ((i - 'a') % 5 != 4) data[i].insert({ abs(temp + 1) + 1, i + 1 });
		if (i - 5 >= 'a') data[i].insert({ abs(temp - 1) + 1, i - 5 });
		if (i + 5 <= 'y') data[i].insert({ abs(temp + 1) + 1, i + 5 });
	}
}


bool daa_2::greedy(doub_cc arc, dmap_cs& map, dvec_c_& vec) {

	for (auto i = map[arc.first].begin(); i != map[arc.first].end(); ++i) {

		int j;
		for (j = 0; j < vec.size(); j++)
			if (vec[j] == (*i).second) break;
		if (j != vec.size()) continue;

		arc.first = (*i).second;
		vec.push_back(arc.first);
		if (arc.first == arc.second) return true;
		if (greedy(arc, map, vec)) return true;
		arc.first = vec[vec.size() - 2];
		vec.pop_back();
	}

	return false;
}

bool daa_2::dijkstra(doub_cc arc, dmap_cs& map, dvec_c_& vec) {

	mmap_fc que;
	que.insert({ 0, arc.first });
	dmap_cf len;
	len[arc.first] = 0;
	dmap_cc path;
	path[arc.second] = 0;
	doub_fc curr;

	while (!que.empty()) {

		curr = *que.begin();
		que.erase(que.begin());

		if (curr.second == arc.second) break;

		for (auto i = map[curr.second].begin(); i != map[curr.second].end(); ++i) {

			float newlen = len[curr.second] + (*i).first;
			if (!len.count((*i).second) || newlen < len[(*i).second]) {

				len[(*i).second] = newlen;
				que.insert({ newlen, (*i).second });
				path[(*i).second] = curr.second;
			}
		}
	}

	if (path[arc.second] == 0) return false;
	vec.clear();
	vec.push_back(arc.second);
	while (1) {

		arc.second = path[arc.second];
		vec.push_back(arc.second);
		if (arc.second == arc.first) break;
	}
	turn_vect<char>(vec);

	return true;
};

bool daa_2::a_star(doub_cc arc, dmap_cs& map, dvec_c_& vec) {

	mmap_fc que;
	que.insert({ 0, arc.first });
	dmap_cf len;
	len[arc.first] = 0;
	dmap_cc path;
	path[arc.second] = 0;
	doub_fc curr;

	while (!que.empty()) {

		curr = *que.begin();
		que.erase(que.begin());

		if (curr.second == arc.second) break;

		for (auto i = map[curr.second].begin(); i != map[curr.second].end(); ++i) {

			float newlen = len[curr.second] + (*i).first;
			if (!len.count((*i).second) || newlen < len[(*i).second]) {

				len[(*i).second] = newlen;
				que.insert({ newlen + abs((*i).second - arc.second), (*i).second });
				path[(*i).second] = curr.second;
			}
		}
	}

	if (path[arc.second] == 0) return false;
	vec.clear();
	vec.push_back(arc.second);
	while (1) {

		arc.second = path[arc.second];
		vec.push_back(arc.second);
		if (arc.second == arc.first) break;
	}
	turn_vect<char>(vec);

	return true;
};