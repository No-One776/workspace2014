//
//  Polynom.h
//

#ifndef __CS263_POLYNOM_H__
#define __CS263_POLYNOM_H__

#include <iostream>
#include <vector>
#include <initializer_list>
using namespace std;

namespace gvsu {
class Polynom {
	/* the ostream "push out" operation shall print the polynomial using "x"
	 * as its variable.
	 * Example for coefficients  -3.518  2.74  -9.096   and exponents  6  2   0
	 * it shall print one of the following output strings:
	 *      -3.518x^6  2.74x^2  -9.096x^0
	 *      -3.518x^6  2.74x^2  -9.096
	 *
	 *      -3.52x^6 + 2.74x^2 - 9.10 (extra credit +3 points for the prettiest output)
	 */

	friend ostream& operator<<(ostream& os, const Polynom& poly);

private:
	int num_terms;
	vector<pair<float, int>> coeff_expon;

public:
	Polynom();

	/* initializer list are from HIGHEST to LOWEST exponent */
	Polynom(initializer_list<float> coef_list, initializer_list<int> expo_list);

	Polynom(vector<float> coeff, vector<int> exp);

	int number_of_terms() const; /* number of terms */

	/* Retrieve the term at the given index as a (float,int) pair*/
	pair<float, int> operator[](int index) const;

	/* modify this poly by multiplying all coefficents by m */
	Polynom& operator *=(float m);

	/* return a polynom as the result of multiplying all coefficiets of this polynom by m */
	Polynom operator*(float m) const;

	/* basic polynomial arithmetic between two polynomials: "*this" and "other" */
	Polynom operator+(const Polynom& other) const;
	Polynom operator-(const Polynom& other) const;
	Polynom operator* (const Polynom& other) const;

	double operator() (double val) const; /* evaluate polynom at the given x-value */

};

/* multiply a scalar "val" with Polynomial "p" */
Polynom operator*(float val, const Polynom& p);
}

#endif
