#include <iostream>
#include <vector>

namespace baaa_1 {

	typedef unsigned char			byte;
	typedef std::pair<byte, byte>	posi;
	typedef std::pair<byte, posi>	elem;

	typedef std::vector<elem>		list;
	typedef std::vector<byte>		bmap;

	std::ostream& operator<< (std::ostream& out, const elem& data) {

		out << (int)data.second.first + 1 << ' ' << (int)data.second.second + 1 << ' ' << (int)data.first;
		return out;
	}

	list operator* (const list& left, const byte& right) {

		list data = left;
		for (auto i = data.begin(); i != data.end(); ++i) {

			(*i).first *= right;
			(*i).second.first *= right;
			(*i).second.second *= right;
		}
		return data;
	}

	byte factfind(byte number) {

		for (byte i = 2; i <= number / 4 + 1; i++)
			if (number % i == 0) return i;
		return 1;
	}

	elem rbt_count(const byte real_s, bmap& real_m) {

		elem data;

		data.second.second = real_s;
		data.second.first = 0;
		for (int i = 0; i < real_s; i++)
			if (real_m[i] < data.second.second) {

				data.second.second = real_m[i];
				data.second.first = i;
			}
		data.first = real_s - (((data.second.first + data.second.second) + abs(data.second.first - data.second.second)) >> 1);
		if (data.first == real_s) data.first--;
		for (int i = data.second.first; i < data.second.first + data.first; i++)
			if (real_m[i] > data.second.second) {

				data.first = i - data.second.first;
				break;
			}

		return data;
	};

	void rbt_fill(const byte x, const byte s, bmap& real_m) {

		for (int i = x; i < x + s; i++) real_m[i] += s;
	}

	void rbt_free(const byte x, const byte s, bmap& real_m) {

		for (int i = x; i < x + s; i++) real_m[i] -= s;
	}

	void rbt_mainy(const byte real_s, bmap& real_m, list& best_l, byte& best_c, list& curr_l, byte curr_c = 0) {

		elem d = rbt_count(real_s, real_m);
		bool end;

		curr_l.push_back(d);
		for (int i = d.first; i > 0; i--) {

			end = true;

			rbt_fill(d.second.first, i, real_m);
			for (int j = 0; j < real_s; j++) if (real_m[j] != real_s) end = false;
			(*(--curr_l.end())).first = i;

			if (end) {

				best_c = curr_c;
				best_l = curr_l;
			}
			else {

				if (curr_c + 1 < best_c)
					rbt_mainy(real_s, real_m, best_l, best_c, curr_l, curr_c + 1);
			}
			rbt_free(d.second.first, i, real_m);
		}
		curr_l.pop_back();
	}

	list rbt(const byte size) {

		byte fact = factfind(size);
		bmap temp_m;
		list temp_l;
		list best_l;
		byte best_c;

		if (fact == 1) fact = size;
		best_c = fact + 3;
		temp_m.assign(fact, 0);

		rbt_fill(0, (fact + 1) / 2, temp_m);
		rbt_fill(0, (fact - 1) / 2, temp_m);
		rbt_fill((fact + 1) / 2, (fact - 1) / 2, temp_m);
		temp_l.push_back(elem{ byte((fact + 1) / 2), { 0, 0 } });
		if (fact != 2) temp_l.push_back(elem{ byte((fact - 1) / 2), { (fact + 1) / 2, 0 } });
		if (fact != 2) temp_l.push_back(elem{ byte((fact - 1) / 2), { 0, (fact + 1) / 2 } });

		rbt_mainy(fact, temp_m, best_l, best_c, temp_l);
		best_l = best_l * byte(size / fact);

		return best_l;
	}
}

int main() {

	using namespace baaa_1;
	list	data;
	int		numb;
	time_t	tick;

	while (1) {

		std::cin >> numb;
		if (numb < 2) break;
		tick = clock();

		data = rbt(numb);

		system("cls");
		std::cout << double(clock() - tick) / 1000 << '\n';
		std::cout << data.size() << '\n';
		for (auto i = data.begin(); i != data.end(); ++i)
			std::cout << (*i) << '\n';
	}

	return 0;
}