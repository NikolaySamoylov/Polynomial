#include "polynomial.h"
#include <gtest.h>

TEST(Monomial, can_create_empty_monomial)
{
	ASSERT_NO_THROW(Monomial m);
}

TEST(Monomial, can_create_initialized_monomial)
{
	ASSERT_NO_THROW(Monomial m(1, 111));
}

TEST(Monomial, can_copy_monomial)
{
	Monomial m1(1, 111);

	ASSERT_NO_THROW(Monomial m2(m1));
}

TEST(Monomial, correctness_of_the_degree_of_monomial)
{
	ASSERT_ANY_THROW(Monomial m(10, 101010));
}

TEST(Monomial, can_compare_monomials)
{
	Monomial m1(1, 111);
	Monomial m2(m1);

	EXPECT_TRUE(m1 == m2);
}

TEST(Monomial, can_add_monomials_correctly)
{
	Monomial m1(1, 111);
	Monomial m2(2, 111);
	Monomial m3(3, 111);

	EXPECT_EQ(m1 + m2, m3);
}

TEST(Monomial, correctness_of_addition_of_monomials)
{
	Monomial m1(1, 111);
	Monomial m2(2, 222);

	ASSERT_ANY_THROW(m1 + m2);
}

TEST(Monomial, can_mult_monomials_correctly)
{
	Monomial m1(1, 111);
	Monomial m2(2, 222);
	Monomial m3(2, 333);

	EXPECT_EQ(m1 * m2, m3);
}

TEST(Monomial, correctness_of_multiplication_of_monomials)
{
	Monomial m1(1, 999);
	Monomial m2(2, 111);

	ASSERT_ANY_THROW(m1 * m2);
}

TEST(Monomial, can_mult_monomial_by_polynomial_correctly)
{
	Monomial m(1, 111);
	Monomial pm(2, 222);
	Monomial resm(2, 333);
	Polynomial p(pm);
	Polynomial res(resm);

	EXPECT_EQ(m * p, res);
}

TEST(Monomial, can_mult_polynomial_by_monomial_correctly)
{
	Monomial m(1, 111);
	Monomial pm(2, 222);
	Monomial resm(2, 333);
	Polynomial p(pm);
	Polynomial res(resm);

	EXPECT_EQ(p * m, res);
}

TEST(Polynomial, can_create_empty_polynomial)
{
	ASSERT_NO_THROW(Polynomial p);
}

TEST(Polynomial, can_create_initialized_polynomial)
{
	Monomial m(1, 111);

	ASSERT_NO_THROW(Polynomial p(m));
}

TEST(Polynomial, can_copy_polynomial)
{
	Monomial m(1, 111);
	Polynomial p(m);

	ASSERT_NO_THROW(Polynomial p1(p));
}

TEST(Polynomial, can_assign_polynomials_correctly)
{
	Monomial m1(1, 111);
	Monomial m2(2, 222);
	Polynomial p1(m1);
	Polynomial p2(m2);
	Polynomial res;
	res = p1 + p2;

	EXPECT_EQ(p1 + p2, res);
}

TEST(Polynomial, can_add_polynomials_correctly)
{
	Monomial m1(1, 111);
	Monomial m2(2, 222);
	Polynomial p1(m1);
	Polynomial p2(m2);
	Polynomial p3;
	p3.push_front(m2);
	p3.push_front(m1);

	EXPECT_EQ(p1 + p2, p3);
}

TEST(Polynomial, can_mult_polynomials_correctly)
{
	Monomial m1(1, 111);
	Monomial m2(2, 222);
	Monomial m3(2, 333);
	Polynomial p1(m1);
	Polynomial p2(m2);
	Polynomial p3(m3);

	EXPECT_EQ(p1 * p2, p3);
}