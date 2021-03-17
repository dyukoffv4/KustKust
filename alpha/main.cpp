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
}

int main() {

	byte	size = 5;
	ydep	map(size);
	list	cont;
	list	temp;
	short	numb = size * size + 1;

	/* time start */
	time_t tick = clock();
	/* time start */

	rbt(size, map, cont, numb, temp, 1);

	/* time end */
	std::cout << double(clock() - tick) / 1000 << '\n';
	/* time end */
	
	std::cout << numb << '\n';
	for (auto i = cont.begin(); i != cont.end(); ++i)
		std::cout << (*i) << '\n';
	
	
	return 0;
}