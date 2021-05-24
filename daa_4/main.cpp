#include "daa_func.h"
#include <iostream>

int main() {

	using namespace daa_4;

	daa_str a = "abab";
	daa_str b = "aaabababbabababcababaabcabbabaababbacbbbacaabababacabbabacaacbababaccaaabcbacbabbabcabccaabbbabcabbbababacbcbababcabbababcbcacababababbbabaababababababaababaaabbbabbbababababcaabbcbabababcbacbbacbabaababbababab";
	daa_vec c = get_entry(b, a);
	if (c.empty()) c.push_back(-1);

	std::cout << a << "\n";
	for (int i = 0; i < b.size(); i++) {

		if (i % 10 == 0) std::cout << ' ';
		if (i % 30 == 0) std::cout << '\n';
		std::cout << b[i];
	}
	std::cout << "\n\n";
	for (int i = 0; i < c.size() - 1; i++) std::cout << c[i] << ", ";
	std::cout << c[c.size() - 1] << '\n';
	
	return 0;
}