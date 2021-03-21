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

		for (byte i = 2; i <= number / 2; i++)
			if (number % i == 0) return i;
		return 1;
	}

	void rbt_count(const byte real_s, bmap& real_m, list& best_l, short& best_c, list& curr_l, short curr_c = 0) {

		/* search for current square data */
		byte y = real_s;
		byte x = 0;
		for (int i = 0; i < real_s; i++)
			if (real_m[i] < y) {

				y = real_m[i];
				x = i;
			}
		byte s = real_s - (((x + y) + abs(x - y)) >> 1);
		if (s == real_s) s--;
		for (int i = x; i < x + s; i++)
			if (real_m[i] > y) {

				s = i - x;
				break;
			}

		/* main tail of 'rbt' */
		bool end;
		curr_l.push_back(elem{ s, {x, y} });
		for (int i = s; i > 0; i--) {

			end = true;
			for (int j = x; j < x + i; j++) real_m[j] += i;
			for (int j = 0; j < real_s; j++) if (real_m[j] != real_s) end = false;
			(*(--curr_l.end())).first = i;

			if (end) {

				best_c = curr_c;
				best_l = curr_l;
			}
			else {

				if (curr_c + 1 < best_c)
					rbt_count(real_s, real_m, best_l, best_c, curr_l, curr_c + 1);
			}

			for (int j = x; j < x + i; j++) real_m[j] -= i;
		}
		curr_l.pop_back();
	}

	list rbt(const byte size, const byte maxs = 0) {

		byte fact = factfind(size);
		bmap temp_m;
		list temp_l;
		list best_l;
		short best_c = maxs;
		if (fact == 1) {

			if (!best_c) best_c = size * size + 1;
			temp_m.assign(size, 0);
			for (int i = 0; i < (size - 1) / 2; i++) temp_m[i] = size;
			temp_m[(size - 1) / 2] = (size + 1) / 2;
			for (int i = (size + 1) / 2; i < size; i++) temp_m[i] = (size - 1) / 2;
			temp_l.push_back(elem{ byte((size + 1) / 2), { 0, 0} });
			temp_l.push_back(elem{ byte((size - 1) / 2), { (size + 1) / 2, 0} });
			temp_l.push_back(elem{ byte((size - 1) / 2), { 0, (size + 1) / 2} });
			rbt_count(size, temp_m, best_l, best_c, temp_l);
		}
		else {

			if (!best_c) best_c = fact * fact + 1;
			temp_m.assign(fact, 0);
			rbt_count(fact, temp_m, best_l, best_c, temp_l);
			best_l = best_l * (size / fact);
		}
		return best_l;
	}
}

int main() {

	using namespace baaa_1;

	// time start //
	time_t tick = clock();

	list l = rbt(33);

	std::cout << double(clock() - tick) / 1000 << '\n';
	// time end //

	std::cout << l.size() << '\n';
	for (auto i = l.begin(); i != l.end(); ++i)
		std::cout << (*i) << '\n';

	return 0;
}