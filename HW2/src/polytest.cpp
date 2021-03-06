//
//  polytest.cpp
//  Created by Hans Dulimarta
//  Copyright (c) 2014 SoCIS. All rights reserved.
//
#include "Polynom.h"
#include "gvcatch.h"
#include <limits>
using namespace gvsu;

class PolyTest {

public:
	gvsu::Polynom zero;
	Polynom linear { { 9, 4 }, { 1, 0 }, }; /* 9x + 4 */
	Polynom p4 { /* 10 x^5 - 4x^2 + 8 */
	{ 10, -4, 8 }, { 5, 2, 0 } };
	Polynom negp4 { /* 10 x^5 - 4x^2 + 8 */
	{ -10, 4, -8 }, { 5, 2, 0 }, };
	Polynom poly_1 { { 2, 8, -1 }, { 3, 2, 1 } };
	Polynom poly_2 { { -1, 4, 5 }, { 2, 1, 0 } };
	Polynom lin { { 1, -3 }, { 1, 0 } };
	Polynom cubic { { 1, 3, 9, 27 }, { 3, 2, 1, 0 } };

};

TEST_CASE_METHOD(PolyTest, "num_terms") {
	REQUIRE(zero.number_of_terms() == 0);
	REQUIRE(linear.number_of_terms() == 2);
}

TEST_CASE_METHOD(PolyTest, "term index") {
	REQUIRE(Catch::Detail::Approx(linear[0].first) == 9.0);
	REQUIRE(linear[0].second == 1);
	REQUIRE(Catch::Detail::Approx(linear[1].first) == 4.0);
	REQUIRE(linear[1].second == 0);

	REQUIRE(Catch::Detail::Approx(p4[0].first) == 10.0);
	REQUIRE(p4[0].second == 5);
	REQUIRE(Catch::Detail::Approx(p4[1].first) == -4.0);
	REQUIRE(p4[1].second == 2);
	REQUIRE(Catch::Detail::Approx(p4[2].first) == 8.0);
	REQUIRE(p4[2].second == 0);
}

TEST_CASE_METHOD(PolyTest, "addition") {
	Polynom sum;
	sum = linear + zero;
	REQUIRE(Catch::Detail::Approx(linear[0].first) == 9.0);
	REQUIRE(linear[0].second == 1);
	REQUIRE(Catch::Detail::Approx(linear[1].first) == 4.0);
	REQUIRE(linear[1].second == 0);

	sum = p4 + p4;
	REQUIRE(Catch::Detail::Approx(sum[0].first) == 20.0);
	REQUIRE(sum[0].second == 5);
	REQUIRE(Catch::Detail::Approx(sum[1].first) == -8.0);
	REQUIRE(sum[1].second == 2);
	REQUIRE(Catch::Detail::Approx(sum[2].first) == 16.0);
	REQUIRE(sum[2].second == 0);

	sum = p4 + negp4;
	REQUIRE(sum.number_of_terms() == 0);
}

TEST_CASE_METHOD(PolyTest, "subtraction") {
	Polynom result;
	result = p4 - p4;
	REQUIRE(result.number_of_terms() == 0);
	result = p4 - zero;
	REQUIRE(result.number_of_terms() == p4.number_of_terms());
	result = p4 - linear;
	REQUIRE(result.number_of_terms() == 4);
	REQUIRE(Catch::Detail::Approx(result[0].first) == 10.0);
	REQUIRE(result[0].second == 5);
	REQUIRE(Catch::Detail::Approx(result[1].first) == -4);
	REQUIRE(result[1].second == 2);
	REQUIRE(Catch::Detail::Approx(result[2].first) == -9);
	REQUIRE(result[2].second == 1);
	REQUIRE(Catch::Detail::Approx(result[3].first) == 4);
	REQUIRE(result[3].second == 0);
}

TEST_CASE_METHOD(PolyTest, "scalar multiple, polynom as LHS") {
	Polynom result;
	SECTION("Non zero scalar"){
	result = p4 * 3;
	REQUIRE(Catch::Detail::Approx(result[0].first) == 30.0);
	REQUIRE(result[0].second == 5);
	REQUIRE(Catch::Detail::Approx(result[1].first) == -12.0);
	REQUIRE(result[1].second == 2);
	REQUIRE(Catch::Detail::Approx(result[2].first) == 24.0);
	REQUIRE(result[2].second == 0);
}

	SECTION("Multiply by one"){
	result = p4 * 1;
	REQUIRE(result.number_of_terms() == p4.number_of_terms());

	for (int k = 0; k < result.number_of_terms(); k++)
	{
		REQUIRE(result[k].first == p4[k].first);
		REQUIRE(result[k].second == p4[k].second);
	}
}
	SECTION("Multiply by zero"){
	result = p4 * 0;
	REQUIRE(result.number_of_terms() == 0);
}
}

TEST_CASE_METHOD(PolyTest, "scalar multiple, polynom as RHS") {
	Polynom sum = 3 * p4;
	REQUIRE(Catch::Detail::Approx(sum[0].first) == 30.0);
	REQUIRE(sum[0].second == 5);
	REQUIRE(Catch::Detail::Approx(sum[1].first) == -12.0);
	REQUIRE(sum[1].second == 2);
	REQUIRE(Catch::Detail::Approx(sum[2].first) == 24.0);
	REQUIRE(sum[2].second == 0);
}

TEST_CASE_METHOD(PolyTest, "scalar multiple and assign") {
	p4 *= 2.5;
	REQUIRE(Catch::Detail::Approx(p4[0].first) == 25.0);
	REQUIRE(p4[0].second == 5);
	REQUIRE(Catch::Detail::Approx(p4[1].first) == -10.0);
	REQUIRE(p4[1].second == 2);
	REQUIRE(Catch::Detail::Approx(p4[2].first) == 20.0);
	REQUIRE(p4[2].second == 0);
}

TEST_CASE_METHOD(PolyTest, "multiply two polynomials") {
	Polynom prod;

	SECTION ("Two null polynomial"){
	prod = zero * zero;
	REQUIRE(prod.number_of_terms() == 0);
}

	SECTION("Two linear polynomial"){
	prod = linear * linear;
	REQUIRE(prod.number_of_terms() == 3);
	REQUIRE(Catch::Detail::Approx(prod[0].first) == 81);
	REQUIRE(prod[0].second == 2);
	REQUIRE(Catch::Detail::Approx(prod[1].first) == 72);
	REQUIRE(prod[1].second == 1);
	REQUIRE(Catch::Detail::Approx(prod[2].first) == 16);
	REQUIRE(prod[2].second == 0);

}

	SECTION("Product with vanishing terms"){
	prod = poly_1 * poly_2;
	//  cout << "poly1: " << poly_1 << endl;
	//   cout << "poly2: " << poly_2 << endl;
	//   cout << "prod : " << prod << endl;
	REQUIRE(prod.number_of_terms() == 4);
	REQUIRE(Catch::Detail::Approx(prod[0].first) == -2);
	REQUIRE(prod[0].second == 5);
	REQUIRE(Catch::Detail::Approx(prod[1].first) == 43);
	REQUIRE(prod[1].second == 3);
	REQUIRE(Catch::Detail::Approx(prod[2].first) == 36);
	REQUIRE(prod[2].second == 2);
	REQUIRE(Catch::Detail::Approx(prod[3].first) == -5);
	REQUIRE(prod[3].second == 1);

	prod = lin * cubic;
//        cout << "lin: " << lin << endl;
//        cout << "cubic: " << cubic << endl;
//        cout << "prod : " << prod << endl;
	REQUIRE(prod.number_of_terms() == 2);
	REQUIRE(Catch::Detail::Approx(prod[0].first) == 1);
	REQUIRE(prod[0].second == 4);
	REQUIRE(Catch::Detail::Approx(prod[1].first) == -81);
	REQUIRE(prod[1].second == 0);
}
}

TEST_CASE_METHOD(PolyTest, "output stream") {
	ostringstream log;

	/*
	 The following statement should output  9x  4  (or 9x + 4)
	 */
	log.clear();
	log << linear;
	REQUIRE(log.str().length() >= 4);

// To see the output of your "stream push", uncomment the following statement:
//cout << linear << endl;

	/*
	 The following statement should output  10x^5  -4x^2  8  (or 10x^5  -4x^2 + 8)
	 */
	log.clear();
	log << p4;
	REQUIRE(log.str().length() >= 10);
}

TEST_CASE_METHOD(PolyTest, "Commutative operations") {
	Polynom aa, bb;

	SECTION("Commutative Addition"){
	aa = p4 + cubic;
	bb = cubic + p4;
	REQUIRE(aa.number_of_terms() == bb.number_of_terms());
	for (int k = 0; k < aa.number_of_terms(); k++)
	{
		REQUIRE(aa[k].first == bb[k].first);
		REQUIRE(aa[k].second == bb[k].second);
	}
}
	SECTION(("Commutative subtraction")){
	aa = p4 - cubic;
	bb = cubic - p4;
	REQUIRE(aa.number_of_terms() == bb.number_of_terms());
	for (int k = 0; k < aa.number_of_terms(); k++)
	{
		REQUIRE(aa[k].first == -bb[k].first);
		REQUIRE(aa[k].second == bb[k].second);
	}
}

	SECTION("Commutative multiplication"){
	aa = p4 * cubic;
	bb = cubic * p4;
	REQUIRE(aa.number_of_terms() == bb.number_of_terms());
	for (int k = 0; k < aa.number_of_terms(); k++)
	{
		REQUIRE(aa[k].first == bb[k].first);
		REQUIRE(aa[k].second == bb[k].second);
	}
}
}

TEST_CASE_METHOD(PolyTest, "Evaluation polynom") {
	for (float x = -50; x < 50; x += 0.5) {
		REQUIRE(zero(x) == 0);
	}
	for (float x = -50; x < 50; x += 0.5) {
		/* Use lambda function/expression to evaluate the expected RHS */
		REQUIRE(linear(x) == [] (float x) -> float {return 9*x + 4;}(x));
	}
	for (float x = -50; x < 50; x += 0.5) {
		/* Use lambda function/expression to evaluate the expected RHS */
		REQUIRE(p4(x) == [] (float x) -> double
		{
			return 10 * std::pow(x,5) - 4 * std::pow(x,2) + 8;
		}(x));
	}

}
