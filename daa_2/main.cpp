#include <iostream>
#include <fstream>
#include <vector>
#include <map>

namespace daa_21 {

	typedef std::pair<char, char>	d_arc;
	typedef std::map<float, char>	d_tab;
	typedef std::map<char, d_tab>	d_map;
	typedef std::vector<char>		d_vec;

	std::istream& operator>>(std::istream& in, d_arc& data) {

		return in >> data.first >> data.second;
	}

	std::istream& operator>>(std::istream& in, d_map& data) {

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
			data[temp_1][temp_f] = temp_2;
		}
		return in;
	}

	std::ostream& operator<<(std::ostream& out, d_map& data) {

		for (auto i = data.begin(); i != data.end(); ++i)
			for (auto j = (*i).second.begin(); j != (*i).second.end(); ++j)
				out << (*i).first << ' ' << (*j).second << ' ' << (*j).first << '\n';
		return out;
	}

	std::ostream& operator<<(std::ostream& out, d_vec& data) {

		for (auto i = data.begin(); i != data.end(); ++i)
			out << (*i);
		return out;
	}

	bool find_path(d_arc arc, d_map& map, d_vec& vec) {

		for (auto i = map[arc.first].begin(); i != map[arc.first].end(); ++i) {

			int j;
			for (j = 0; j < vec.size() - 1; j++)
				if (vec[j] == arc.first && vec[j + 1] == (*i).second) break;
			if (j != vec.size() - 1) continue;

			arc.first = (*i).second;
			vec.push_back(arc.first);
			if (arc.first == arc.second) return true;
			if (find_path(arc, map, vec)) return true;
			arc.first = vec[vec.size() - 2];
			vec.pop_back();
		}

		return false;
	}
}

int main() {

	using namespace daa_21;

	std::ifstream file;
	d_map map;
	d_arc arc;
	d_vec vec;

	file.open("..\\file.txt");
	if (!file.is_open()) return 0;

	file >> arc;
	file >> map;

	file.close();

	std::cout << arc.first << ' ' << arc.second << '\n';
	std::cout << map << '\n';

	vec.push_back(arc.first);
	if (find_path(arc, map, vec)) std::cout << vec;
	else std::cout << "no path";

	return 0;
}