#include "Complex.h"


complex::complex() {
	
	this->self = { 0, 0 };
}

complex::complex(s_complex init) {

	this->self = init;
}

complex::complex(double real, double imag) {

	this->self.real = real;
	this->self.imag = imag;
}


complex& complex::operator- () {

	self.imag *= -1;
	self.real *= -1;
	return *this;
}

complex& complex::operator+= (complex add) {
	
	return *this = *this + add;
}

complex& complex::operator-= (complex dif) {

	return *this = *this - dif;
}

complex& complex::operator*= (complex mul) {

	return *this = *this * mul;
}

complex& complex::operator*= (double mul) {

	return *this = *this * mul;
}

complex& complex::operator/= (complex div) {

	return *this = *this / div;
}

complex& complex::operator/= (double div) {

	return *this = *this / div;
}


complex complex::operator+ (complex add) {

	return complex(self.real + add.self.real, self.imag + add.self.imag);
}

complex complex::operator- (complex dif) {

	return *this + -dif;
}

complex complex::operator* (complex mul) {

	return complex(self.real * mul.self.real - self.imag * mul.self.imag, self.real * mul.self.imag + self.imag * mul.self.real);
}

complex complex::operator* (double mul) {

	return complex(self.real * mul, self.imag * mul);
}

complex complex::operator/ (complex div) {

	if (~div == 0) {

		printf("Zero division error\n");
		return *this;
	}

	return *this * (div ^ -1);
}

complex complex::operator/ (double div) {

	if (div == 0) {

		printf("Zero division error\n");
		return *this;
	}

	return complex(self.real / div, self.imag / div);
}

complex complex::operator^ (int inc) {

	complex result = { 1, 0 };

	for (int i = 0; i < abs(inc); i++) result = result * (*this);

	if (inc < 0) {

		result.self.imag *= -1;
		result = result / (pow(result.self.real, 2) + pow(result.self.imag, 2));
	}

	return result;
}


bool complex::operator== (complex var) {
	
	return ((self.real == var.self.real) && (self.imag == var.self.imag));
}

bool complex::operator!= (complex var) {
	
	return !((self.real == var.self.real) && (self.imag == var.self.imag));
}


double complex::operator~() {
	
	return sqrt(pow(self.real, 2) + pow(self.imag, 2));
}


complex::operator bool() const {

	complex check = *this;
	if (~check == 0) return false;
	return true;
}


std::ostream& operator<< (std::ostream& out, const complex& val) {

	if (val.self.imag < 0) out << val.self.real << " - " << -1 * val.self.imag << "i";
	if (val.self.imag >= 0) out << val.self.real << " + " << val.self.imag << "i";

	return out;
}