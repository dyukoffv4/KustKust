#pragma once

#include "daa_type.h"

namespace daa_2 {

	void map_md_gen(dmap_cs& data);

	void map_sd_gen(dmap_cs& data);

	template <class T>
	void turn_vect(std::vector<T>& data) {

		T temp;
		for (int i = 0; i < data.size() / 2; i++) {

			temp = data[i];
			data[i] = data[data.size() - 1 - i];
			data[data.size() - 1 - i] = temp;
		}
	}

	bool greedy(doub_cc arc, dmap_cs& map, dvec_c_& vec);

	bool dijkstra(doub_cc arc, dmap_cs& map, dvec_c_& vec);

	bool a_star(doub_cc arc, dmap_cs& map, dvec_c_& vec);
}