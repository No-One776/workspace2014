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
	for (auto iter : coeff_expon){
		iter.first *= m;
	}
	return *this;
}

/* basic polynomial arithmetic between two polynomials: "*this" and "other" */
Polynom Polynom::operator+(const Polynom& other) const {
	Polynom temp;
	vector<float> coef[num_terms + other.num_terms];
	vector<int> exp[num_terms + other.num_terms];
	int l = 0;
	//If the exponents are equal add the coeff.
	for (int a = 0; a < this->num_terms; a++) {
		for (int x = 0; x < other.num_terms; x++) {
			if (other[x].second == coeff_expon.at(a).second) {
				this->coeff_expon.push_back(2.0 , 1);// coeff_expon.at(a).second);
				//coef[l]. other[x].first + coeff_expon.at(a).first;
				//exp[l] = coeff_expon.at(a).second;
			} else if (other[x].second < coeff_expon.at(a).second) {
			//	coef[l] = coeff_expon.at(a).first;
				//exp[l] = coeff_expon.at(a).second;
			}
		}
	}

	return temp;
}

}
