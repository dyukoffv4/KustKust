#include <iostream>
#include <vector>

namespace daa_1 {

	typedef unsigned char		byte;
	typedef std::pair<byte, byte>	posi;
	typedef std::pair<byte, posi>	elem;

	typedef std::vector<elem>	list;
	typedef std::vector<byte>	bmap;

	std::ostream& operator<< (std::ostream& out, const elem& data);

	list operator* (const list& left, const byte& right);

	byte factfind(byte number);

	elem rbt_count(const byte real_s, bmap& real_m);

	void rbt_fill(const byte x, const byte s, bmap& real_m);

	void rbt_free(const byte x, const byte s, bmap& real_m);

	void rbt_mainy(const byte real_s, bmap& real_m, list& best_l, byte& best_c, list& curr_l, byte curr_c = 0);

	list rbt(const byte size);
}
