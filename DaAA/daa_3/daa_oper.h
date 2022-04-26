#pragma once

#include <iostream>
#include "daa_type.h"

namespace daa_3 {

	std::istream& operator>>(std::istream& in, cc__arc& data);

	std::istream& operator>>(std::istream& in, ci__arc& data);

	std::istream& operator>>(std::istream& in, cci_map& data);

	std::ostream& operator<<(std::ostream& out, cc__arc& data);

	std::ostream& operator<<(std::ostream& out, cci_map& data);

	std::ostream& operator<<(std::ostream& out, c___vec& data);
}