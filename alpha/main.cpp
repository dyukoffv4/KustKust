#include <iostream>
#include <vector>

typedef unsigned char			byte;
typedef std::pair<byte, byte>	posi;
typedef std::pair<byte, posi>	elem;

typedef std::vector<elem>		list;
typedef std::vector<byte>		ydep;

std::ostream& operator<< (std::ostream& out, const elem& data) {

	out << (int)data.second.first << ' ' << (int)data.second.second << ' ' << (int)data.first;
	return out;
}

void rbt(const byte real_s, ydep& real_m, list& best_l, short& best_c, list& curr_l, short curr_c) {

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
				rbt(real_s, real_m, best_l, best_c, curr_l, curr_c + 1);
		}

		for (int j = x; j < x + i; j++) real_m[j] -= i;
	}
	curr_l.pop_back();
}

int main() {

	byte	size = 35;
	ydep	map(size);
	list	cont;
	list	temp;
	short	numb = size * size + 1;

	/* time start */
	time_t tick = clock();

	rbt(size, map, cont, numb, temp, 1);

	std::cout << double(clock() - tick) / 1000 << '\n';
	/* time end */

	std::cout << numb << '\n';
	for (auto i = cont.begin(); i != cont.end(); ++i)
		std::cout << (*i) << '\n';


	return 0;
}