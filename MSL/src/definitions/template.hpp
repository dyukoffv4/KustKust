#pragma once

#include "../components/vector/vector.hpp"
#include "../components/vector/vector.cpp"

namespace mgl {
	template class vect<byte_1>;
	template class vect<byte_2>;
	template class vect<byte_4>;
	template class vect<byte_8>;

	template class vect<char>;
	template class vect<short>;
	template class vect<int>;
	template class vect<long>;

	template class vect<float>;
	template class vect<double>;
}