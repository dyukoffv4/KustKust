#pragma once

#include <iostream>
#include "daa_type.h"

namespace daa_2 {

	std::istream& operator>>(std::istream& in, doub_cc& data);

	std::istream& operator>>(std::istream& in, dmap_cs& data);

	std::ostream& operator<<(std::ostream& out, dmap_cs& data);

	std::ostream& operator<<(std::ostream& out, dvec_c_& data);
}