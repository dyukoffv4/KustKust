#include <iostream>
#include <fstream>
#include <vector>
#include <map>

namespace daa_21 {

	typedef std::pair<char, char>		doub_cc;
	typedef std::map<char, char>		dmap_cc;
	typedef std::pair<float, char>		doub_fc;
	typedef std::multimap<float, char>	mmap_fc;
	typedef std::map<char, mmap_fc>		dmap_cs;
	typedef std::map<char, float>		dmap_cf;
	typedef std::vector<char>			dvec_c_;

	std::istream& operator>>(std::istream& in, doub_cc& data) {

		return in >> data.first >> data.second;
	}

	std::istream& operator>>(std::istream& in, dmap_cs& data) {

		char	temp_1;
		char	temp_2;
		float	temp_f;
		while (1) {

			while (1) {

				temp_1 = in.get();
				if (in.eof()) return in;
				if (temp_1 != '\n' && temp_1 != ' ') break;
			}
			in >> temp_2 >> temp_f;
			data[temp_1].insert(std::pair<float, char>(temp_f, temp_2));
		}
		return in;
	}

	std::ostream& operator<<(std::ostream& out, dmap_cs& data) {

		for (auto i = data.begin(); i != data.end(); ++i)
			for (auto j = (*i).second.begin(); j != (*i).second.end(); ++j)
				out << (*i).first << ' ' << (*j).second << ' ' << (*j).first << '\n';
		return out;
	}

	std::ostream& operator<<(std::ostream& out, dvec_c_& data) {

		for (auto i = data.begin(); i != data.end(); ++i)
			out << (*i);
		return out;
	}

	template <class T>
	void turn_vect(std::vector<T>& data) {

		T temp;
		for (int i = 0; i < data.size() / 2; i++) {

			temp = data[i];
			data[i] = data[data.size() - 1 - i];
			data[data.size() - 1 - i] = temp;
		}
	}

	bool greedy(doub_cc arc, dmap_cs& map, dvec_c_& vec) {

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

	bool dijkstra(doub_cc arc, dmap_cs& map, dvec_c_& vec) {

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

	bool a_star(doub_cc arc, dmap_cs& map, dvec_c_& vec) {

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
}

int main() {

	using namespace daa_21;

	std::ifstream file;
	dmap_cs map;
	doub_cc arc;
	dvec_c_ vec;

	file.open("..\\file.txt");
	if (!file.is_open()) return 0;

	file >> arc;
	file >> map;

	file.close();

	std::cout << arc.first << ' ' << arc.second << '\n';
	std::cout << map << '\n';

	/**/
	vec.push_back(arc.first);
	if (greedy(arc, map, vec)) std::cout << vec;
	else std::cout << "no path";
	/**
	if (dijkstra(arc, map, vec)) std::cout << vec;
	else std::cout << "no path";
	/**
	if (a_star(arc, map, vec)) std::cout << vec;
	else std::cout << "no path";
	/**/

	return 0;
}