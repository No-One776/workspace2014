//
//  Created by Hans Dulimarta
//  Copyright (c) 2014 SoCIS. All rights reserved.
//

#include "Polynom.h"
#include <limits>
#include <cmath>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>
#include <initializer_list>
#include <string>
namespace gvsu {
using namespace std;

Polynom::Polynom() {
	num_terms = 0;
}

Polynom::Polynom(initializer_list<float> coef_list,
		initializer_list<int> expo_list) {
	if (coef_list.size() != expo_list.size())
		throw invalid_argument("Inputs of different length");
	num_terms = 0;
	/* the following for-loops show how to work with std::initializer_list */
	auto ex = expo_list.begin();
	for (auto iter = coef_list.begin(); iter != coef_list.end(); ++iter) {
		num_terms++; //Increase Number of Terms
		coeff_expon.push_back(std::make_pair(*iter, *ex)); // Inserting into vector
		cout << "Coefficient: " << *iter << " & Exponent: " << *ex << endl;
		ex++;
	}
}

Polynom::Polynom(vector<float> coeff, vector<int> exp) {
	auto ex = exp.begin();
	for (auto iter = coeff.begin(); iter != coeff.end(); ++iter) {
		num_terms++; //Increase Number of Terms
		coeff_expon.push_back(std::make_pair(*iter, *ex)); // Inserting into vector
		cout << "Coefficient: " << *iter << " & Exponent: " << *ex << endl;
		ex++;
	}
}

/* TODO: Add more function below this line as you uncover more test methods
 in polytest.cpp and the required functions in Polynom.h
 */

ostream& operator<<(ostream& out, const Polynom& p) {
	string outputBuilder = "";

	for (int i = p.number_of_terms(); i >= 0; i--) { // Access things in reverse
		string sign;
		if (p[i].first < 0)
			sign = " - ";
		else
			sign = " + ";

		if (p[i].second <= 1) { // Exponent of 1 or 0
			outputBuilder.append(sign);
			//outputBuilder.append(std::to_string(p[i].first));
			outputBuilder.append("X^");
			//outputBuilder.append(std::to_string(p[i].second));
//			} else {      On second though, it should still probably accurately represent
//				if (){     any given input.  However, the equations will need to account for
//					       the rules for exponents of 1 and 0.
//				} else {
//
//				}
//				output = output + sign +
		}

	}
	//ostream & out(outputBuilder);
	return out;
}

int Polynom::number_of_terms() const {
	return num_terms;
}

/*
 * A Polynom method that returns a call to its vector<pair> variable.
 */
pair<float, int> Polynom::operator[](int index) const {
	return coeff_expon.at(index);
}

Polynom& Polynom::operator*=(float m) {
	for (auto iter : coeff_expon) {
		iter.first *= m;
	}
	return *this;
}

/* basic polynomial arithmetic between two polynomials: "*this" and "other" */
Polynom Polynom::operator+(const Polynom& other) const {
	//Polynom temp;
	int max = num_terms + other.num_terms;
	std::vector<float> coef[max];
	vector<int> exp[max];
	//int l = 0;
	//std::vector<float>::iterator c = coef.begin();
	for (auto iter = coef.begin(); iter < coef.end(); iter++){

	}
	//auto e = exp.begin();
	//If the exponents are equal add the coeff.
	for (int a = 0; a < this->num_terms; a++) {
		for (int x = 0; x < other.num_terms; x++) {
			if (other[x].second == coeff_expon.at(a).second) {

				//this->coeff_expon.at(l) = std::make_pair(other[x].first + coeff_expon.at(a).first, coeff_expon.at(a).second);
				//.push_back(2.0 , 1);// coeff_expon.at(a).second);
				//c.push_back(2.0);
				//c.at(1) = 2.0;
				//e.push_back(1);
				//e++;
				//c++;
				//pushback(other[x].first + coeff_expon.at(a).first);
				//exp[l] = coeff_expon.at(a).second;
			} else if (other[x].second < coeff_expon.at(a).second) {
				//this->coeff_expon.insert(c,
				//		make_pair(other[x].first, other[x].second));
				//coef[l] = coeff_expon.at(a).first;
				//exp[l] = coeff_expon.at(a).second;
			}
		}
	}

	int a = 0, x = 0;
	for (auto t = coeff_expon.begin(); t < coeff_expon.end(); t++)
		for (auto o = other.coeff_expon.begin(); o < other.coeff_expon.end();
				o++) {
			if (coeff_expon.at(a).second == other[x].second)
				coeff_expon.insert(t, std::make_pair(other[x].first + coeff_expon.at(a).first, coeff_expon.at(a).second));
			coeff_expon.in
		}

	return Polynom(*coef, *exp);
}

}
