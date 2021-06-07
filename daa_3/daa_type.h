#pragma once

#include <vector>
#include <map>

namespace daa_3 {

	typedef std::pair<char, char>		cc__arc;
	typedef std::map<char, char>		cc__map;
	typedef std::map<char, cc__map>		ccc_map;
	typedef std::pair<char, int>		ci__arc;
	typedef std::map<char, int>			ci__map;
	typedef std::map<char, ci__map>		cci_map;
	typedef std::vector<char>			c___vec;
	typedef std::pair<c___vec, int>		cvi_arc;
	typedef std::vector<cvi_arc>		cvi_vec;
}