#include "daa_oper.h"

std::istream& daa_2::operator>>(std::istream& in, doub_cc& data) {

	return in >> data.first >> data.second;
}

std::istream& daa_2::operator>>(std::istream& in, dmap_cs& data) {

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

std::ostream& daa_2::operator<<(std::ostream& out, dmap_cs& data) {

	for (auto i = data.begin(); i != data.end(); ++i)
		for (auto j = (*i).second.begin(); j != (*i).second.end(); ++j)
			out << (*i).first << ' ' << (*j).second << ' ' << (*j).first << '\n';
	return out;
}

std::ostream& daa_2::operator<<(std::ostream& out, dvec_c_& data) {

	for (auto i = data.begin(); i != data.end(); ++i)
		out << (*i);
	return out;
}