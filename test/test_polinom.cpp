#include <gtest.h>
#include "polinom.h"
#include "monom.h"
// тесты мономов и полиномов

TEST(Monom, can_create_Monom_with_possitive_deg_less_999)
{
	ASSERT_NO_THROW(Monom m(5, 111));
}

TEST(Monom, cant_create_Monom_with_possitive_deg_gr_999)
{
	ASSERT_ANY_THROW(Monom m(5, 1111));
}

TEST(Monom, cant_create_Monom_with_negative_deg)
{
	ASSERT_ANY_THROW(Monom m(5, -111));
}

TEST(MonomList, can_create_MonomList) {
	EXPECT_NO_THROW(MonomList M);
}

TEST(MonomList, insert_monom_correct) {
	MonomList M;
	auto it = M.begin();

	M.Insert(Monom(5, 10));
	M.Insert(Monom(5, 50));
	M.Insert(Monom(5, 100));
	++it; ++it;

	EXPECT_EQ(50, (*it).deg);
}

TEST(MonomList, copy_new_memory) {
	MonomList M;
	auto it1 = M.begin();
	M.Insert(Monom(5, 10));
	M.Insert(Monom(5, 50));
	M.Insert(Monom(5, 100));
	++it1; ++it1;

	MonomList L(M);
	auto it2 = L.begin();
	++it2; ++it2;
	(*it2).deg = 1;

	EXPECT_NE((*it1).deg, (*it2).deg);
}

TEST(MonomList, assigment_new_memory) {
	MonomList M;
	auto it1 = M.begin();
	M.Insert(Monom(5, 10));
	M.Insert(Monom(5, 50));
	M.Insert(Monom(5, 100));
	++it1; ++it1;

	MonomList L = M;
	auto it2 = L.begin();
	++it2; ++it2;
	(*it2).deg = 1;

	EXPECT_NE((*it1).deg, (*it2).deg);
}

TEST(Polinom, add_less_deg_monom)
{
	Polinom A, B;
	Monom m(5, 100);

	A.str_to_poly("x^2 + 1");
	B.str_to_poly("x^2 + 5x + 1");
	A += m;

	EXPECT_EQ(B, A);
}

TEST(Polinom, add_gr_deg_monom)
{
	Polinom A, B;
	Monom m(1, 200);

	A.str_to_poly("5x + 1");
	B.str_to_poly("x^2 + 5x + 1");
	A += m;

	EXPECT_EQ(B, A);
}

TEST(Polinom, add_eq_deg_monom)
{
	Polinom A, B;
	Monom m(1, 200);

	A.str_to_poly("x^2 + 5x + 1");
	B.str_to_poly("2x^2 + 5x + 1");
	A += m;

	EXPECT_EQ(B, A);
}

TEST(Polinom, sub_less_deg_monom)
{
	Polinom A, B;
	Monom m(5, 100);

	A.str_to_poly("x^2 + 1");
	B.str_to_poly("x^2 - 5x + 1");
	A -= m;

	EXPECT_EQ(B, A);
}

TEST(Polinom, sub_gr_deg_monom)
{
	Polinom A, B;
	Monom m(1, 200);

	A.str_to_poly("5x + 1");
	B.str_to_poly("-x^2 + 5x + 1");
	A -= m;

	EXPECT_EQ(B, A);
}

TEST(Polinom, sub_eq_deg_monom)
{
	Polinom A, B;
	Monom m(1, 200);

	A.str_to_poly("x^2 + 5x + 1");
	B.str_to_poly("5x + 1");
	A -= m;

	EXPECT_EQ(B, A);
}

TEST(Polinom, add_scalar)
{
	Polinom A, B;
	A.str_to_poly("x^2 + 1");
	B.str_to_poly("x^2 + 6.1");

	A += 5.1;

	EXPECT_EQ(B, A);
}

TEST(Polinom, sub_scalar)
{
	Polinom A, B;
	A.str_to_poly("x^2 + 1");
	B.str_to_poly("x^2 - 4.1");

	A -= 5.1;

	EXPECT_EQ(B, A);
}

TEST(Polinom, add_poly_eq_deg)
{
	Polinom A, B, res;

	A.str_to_poly("5.43x^5y^4z^3 + 3.21x^3y^2z^1 - 1.23x^3 - 10.1");
	B.str_to_poly("5.43x^5y^4z^3 + 3.21x^3y^2z^1 - 1.23x^3 - 10.1");
	res.str_to_poly("10.86x^5y^4z^3 + 6.42x^3y^2z^1 - 2.46x^3 - 20.2");

	EXPECT_EQ(res, A + B);
}

TEST(Polinom, add_poly_ne_deg)
{
	Polinom A, B, res;

	A.str_to_poly("y^9 + y^7 + y^5 + 5");
	B.str_to_poly("y^8 + y^6 + y^4 + y");
	res.str_to_poly("y^8 + y^6 + y^4 + y + y^9 + y^7 + y^5 + 5");

	EXPECT_EQ(res, A + B);
}

TEST(Polinom, sub_poly_eq_deg)
{
	Polinom A, B, res;

	A.str_to_poly("5.43x^5y^4z^3 + 3.21x^3y^2z^1 - 1.23x^3 - 10.1");
	B.str_to_poly("4.43x^5y^4z^3 + 3.21x^3y^2z^1 - .23x^3 - 20.2");
	res.str_to_poly("1x^5y^4z^3 - x^3 + 10.1");

	EXPECT_EQ(res, A - B);
}

TEST(Polinom, sub_poly_ne_deg)
{
	Polinom A, B, res;

	A.str_to_poly("y^9 + y^7 + y^5 + 5");
	B.str_to_poly("y^8 + y^6 + y^4 + y");
	res.str_to_poly("-y^8 - y^6 - y^4 - y + y^9 + y^7 + y^5 + 5");

	EXPECT_EQ(res, A - B);
}

TEST(Polinom, mult_poly1)
{
	Polinom A, B, res;

	A.str_to_poly("x^3y^2z - x^4z^2");
	B.str_to_poly("x^3y^2z + x^4z^2");
	res.str_to_poly("x^6y^4z^2 - x^8z^4");

	EXPECT_EQ(res, A * B);
}

TEST(Polinom, mult_poly2)
{
	Polinom A, B, res;

	A.str_to_poly("z");
	B.str_to_poly("z");
	res.str_to_poly("z^2");

	EXPECT_EQ(res, A * B);
}

TEST(Polinom, cant_mult_poly_with_big_deg)
{
	Polinom A, B;

	A.str_to_poly("z^5");
	B.str_to_poly("z^5");

	ASSERT_ANY_THROW(A * B);
}

TEST(PolinomInput, throw_two_or_more_points)
{
	Polinom A;

	ASSERT_ANY_THROW(A.str_to_poly("3.1x^5 + 4.5.1y"));
}

TEST(PolinomInput, no_throw_correct_points)
{
	Polinom A;

	ASSERT_NO_THROW(A.str_to_poly("3.1x + 4.2x + 5.1xyz + .23"));
}

TEST(PolinomInput, throw_two_or_more_variables)
{
	Polinom A;

	ASSERT_ANY_THROW(A.str_to_poly("x^5y + yz + zz"));
}

TEST(PolinomInput, throw_two_or_more_operation_signs)
{
	Polinom A;

	ASSERT_ANY_THROW(A.str_to_poly("x + - y"));
}

TEST(PolinomInput, no_throw_first_operation_sign)
{
	Polinom A;

	ASSERT_NO_THROW(A.str_to_poly("+ x + y"));
}

TEST(PolinomInput, throw_big_degree)
{
	Polinom A;

	ASSERT_ANY_THROW(A.str_to_poly("x^5yz^10 + 1"));
}

TEST(PolinomInput, throw_negative_degree)
{
	Polinom A;

	ASSERT_ANY_THROW(A.str_to_poly("x^-5yz + 1"));
}

TEST(PolinomInput, throw_wrong_symbols)
{
	Polinom A;

	ASSERT_ANY_THROW(A.str_to_poly("xyz + 1 + M"));
}

TEST(PolinomInput, correct_input_only_scalar)
{
	Polinom A, B;

	A.str_to_poly("5.1");
	B += 5.1;

	EXPECT_EQ(B, A);
}

TEST(PolinomInput, correct_input_only_one_variable)
{
	Polinom A, B;

	A.str_to_poly("y^5");
	B += Monom(1, 50);

	EXPECT_EQ(B, A);
}

TEST(PolinomInput, correct_input_variables_with_first_degree)
{
	Polinom A, B;

	A.str_to_poly("1+xyz");
	B += 1;
	B += Monom(1, 111);

	EXPECT_EQ(B, A);
}

TEST(PolinomInput, correct_input_variables_with_zero_degree)
{
	Polinom A, B;

	A.str_to_poly("1+xyz+x^0y^5z^0");
	B += 1;
	B += Monom(1, 111);
	B += Monom(1, 50);

	EXPECT_EQ(B, A);
}

TEST(PolinomInput, correct_input_monoms_with_same_degree)
{
	Polinom A, B;

	A.str_to_poly("1 + xyz + x^1y^1z^1 + 10.1 - 0.7xyz");
	B += 11.1;
	B += Monom(1.3, 111);

	EXPECT_EQ(B, A);
}

TEST(PolinomInput, correct_input_monom_with_zero_cf)
{
	Polinom A, B;

	A.str_to_poly("1 + xyz - x^1y^1z^1 + 10.1");
	B += 11.1;

	EXPECT_EQ(B, A);
}