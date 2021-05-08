#include "daa_oper.h"

std::istream& daa_3::operator>>(std::istream& in, cc__arc& data) {

	return in >> data.first >> data.second;
}

std::istream& daa_3::operator>>(std::istream& in, ci__arc& data) {

	return in >> data.first >> data.second;
}

std::istream& daa_3::operator>>(std::istream& in, cci_map& data) {

	char	temp_c;
	ci__arc	temp_a;
	while (1) {

		while (1) {

			temp_c = in.get();
			if (in.eof()) return in;
			if (temp_c != '\n' && temp_c != ' ') break;
		}
		in >> temp_a;
		data[temp_c][temp_a.first] = temp_a.second;
	}
	return in;
}


std::ostream& daa_3::operator<<(std::ostream& out, cc__arc& data) {

	return out << data.first << ' ' << data.second;
}

std::ostream& daa_3::operator<<(std::ostream& out, cci_map& data) {

	for (auto i = data.begin(); i != data.end(); ++i)
		for (auto j = (*i).second.begin(); j != (*i).second.end(); ++j)
			out << (*i).first << ' ' << (*j).first << ' ' << (*j).second << '\n';
	return out;
}

std::ostream& daa_3::operator<<(std::ostream& out, c___vec& data) {

	for (auto i = data.begin(); i != data.end(); ++i)
		out << (*i);
	return out;
}