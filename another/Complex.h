#pragma once

#include <iostream>
#include <cmath>

struct s_complex {
	double real;
	double imag;
};

class complex {

public:

	complex();
	complex(s_complex init);
	complex(double real, double imag);

	complex& operator- ();

	complex& operator+= (complex add);

	complex& operator-= (complex add);

	complex& operator*= (double mul);
	complex& operator*= (complex mul);

	complex& operator/= (double div);
	complex& operator/= (complex div);

	complex operator+ (complex add);

	complex operator- (complex dif);

	complex operator* (double mul);
	complex operator* (complex mul);

	complex operator/ (double div);
	complex operator/ (complex div);

	complex operator^ (int inc);

	bool operator== (complex var);
	bool operator!= (complex var);

	double operator~ ();

	operator bool() const;

	friend std::ostream& operator<< (std::ostream& out, const complex& point);

private:

	s_complex self;
};