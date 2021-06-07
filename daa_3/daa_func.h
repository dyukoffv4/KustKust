#pragma once

#include "daa_type.h"

namespace daa_3 {

	template <class T>
	void turn_vect(std::vector<T>& data) {

		T temp;
		for (int i = 0; i < data.size() / 2; i++) {

			temp = data[i];
			data[i] = data[data.size() - 1 - i];
			data[data.size() - 1 - i] = temp;
		}
	}

	bool greedy(cc__arc arc, cci_map& map, c___vec& vec);

	void clearmap(cci_map& map);

	long findflow(cc__arc arc, cci_map& map);
}