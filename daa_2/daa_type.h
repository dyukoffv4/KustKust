#pragma once

#include <vector>
#include <map>

namespace daa_2 {

	typedef std::pair<char, char>		doub_cc;
	typedef std::map<char, char>		dmap_cc;
	typedef std::pair<float, char>		doub_fc;
	typedef std::multimap<float, char>	mmap_fc;
	typedef std::map<char, mmap_fc>		dmap_cs;
	typedef std::map<char, float>		dmap_cf;
	typedef std::vector<char>			dvec_c_;
}