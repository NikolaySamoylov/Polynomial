#pragma once

#include "list.h"

class Polynomial;

class Monomial
{
protected:
	double cf; // коэффициент перед мономом
	size_t deg; // степень монома
public:
	// конструктор без параметров
	Monomial() : cf(0), deg(-1) {};
	// конструктор с параметрами
	Monomial(double c, size_t d) : cf(c), deg(d) {};
	// конструктор копирования
	Monomial(const Monomial& m)
	{
		cf = m.cf;
		deg = m.deg;
	}
	// степень первой переменной x
	size_t xd() const
	{
		return deg / 100;
	}
	// степень второй переменной y
	size_t yd() const
	{
		return (deg % 100) / 10;
	}
	// степень третьей переменной z
	size_t zd() const
	{
		return deg % 10;
	}
	// проверка степени монома на корректность
	bool deg_is_cor() 
	{
		if (xd() < 10 && yd() < 10 && zd() < 10)
			return true;
		else
			return false;
	}
	// получить степень монома
	size_t get_deg() const
	{
		return deg;
	}
	// получить коэффициент монома
	double get_cf() const
	{
		return cf;
	}
	// проверка мономов на равенство
	bool operator==(Monomial& m)
	{
		if (cf == m.cf && deg == m.deg)
			return true;
		else
			return false;
	}
	// проверка мономов на неравенство
	bool operator !=(Monomial& m)
	{
		return !(*this == m);
	}
	// сложение двух мономов
	Monomial operator+(Monomial& m)
	{
		Monomial res;
		if (deg == m.deg)
		{
			res.cf = cf + m.cf;
			res.deg = deg;
		}
		else throw "Impossible to add!";
		return res;
	}
	// умножение двух мономов
	Monomial operator*(Monomial& m)
	{
		Monomial res;
		if (xd() + m.xd() < 10 && yd() + m.yd() < 10 && zd() + m.zd() < 10)
		{
			res.cf = cf * m.cf;
			res.deg = deg + m.deg;
		}
		else throw "Impossible degree of result monom!";
		return res;
	}
	// умножение монома на полином 
	Polynomial operator*(Polynomial& p);
	// умножение полинома на моном
	friend Polynomial operator*(Polynomial& p, Monomial& m);
	// вывод монома на экран
	friend std::ostream& operator<<(std::ostream& os, Monomial& m)
	{
		os << m.cf;
		if (m.xd() != 1)
			os << "x^" << m.xd() << '*';
		else
			os << 'x' << '*';
		if (m.yd() != 1)
			os << "y^" << m.yd() << '*';
		else
			os << 'y' << '*';
		if (m.zd() != 1)
			os << "z^" << m.xd();
		else
			os << 'z';
		return os;
	}
};

class Polynomial : public List<Monomial>
{
public:
	// конструктор без параметров
	Polynomial() : List<Monomial>() {};
	// конструктор с параметрами
	Polynomial(Monomial m) : List<Monomial>(m, NULL) {};
	// конструктор копирования
	Polynomial(const Polynomial& p) : List<Monomial>(p) {};
	// деструктор
	~Polynomial() {List::~List<Monomial>();}
	// присваивание
	Polynomial operator=(Polynomial& p)
	{ 
		while (!empty())
			pop_front();
		for (Iterator i = p.begin(); i != p.end(); i++)
			push_back(i->data);
		return *this;
	}
	// сложение полиномов
	Polynomial operator+ (Polynomial& p)
	{
	//	Monomial m;
	//	Node<Monomial>* r = new Node<Monomial>(m, NULL);
	//	r->pNext = r;
		Polynomial res;
		Iterator this_it = begin();
		Iterator p_it = p.begin();
		Iterator res_it = res.head;
		while ((this_it != end()) && (p_it != p.end()))
		{
			if (this_it->data.get_deg() < p_it->data.get_deg())
			{
				res.insert(*res_it, this_it->data);
				this_it++;
				res_it++;
			}
			 else if (this_it->data.get_deg() > p_it->data.get_deg())
			{
				res.insert(*res_it, p_it->data);
				p_it++;
				res_it++;
			}
			else if (this_it->data.get_deg() == p_it->data.get_deg())
			{
				res.insert(*res_it, this_it->data + p_it->data);
				this_it++;
				p_it++;
				res_it++;
			}
		}
		while (this_it != end())
		{
			res.insert(*res_it, this_it->data);
			this_it++;
			res_it++;
		}
		while (p_it != p.end())
		{
			res.insert(*res_it, p_it->data);
			p_it++;
			res_it++;
		}
		return res;
	}
	// умножение полиномов
	Polynomial operator*(Polynomial& p)
	{
		Polynomial res;
		Iterator this_it = begin();
		while (this_it != end())
		{
			res = res + this_it->data * p;
			this_it++;
		}
		return res;
	}
	// вывести полином на экран
	friend std::ostream& operator<<(std::ostream& os, Polynomial& pol)
	{
		for (Polynomial::Iterator pol_it = pol.begin(); pol_it != pol.end(); pol_it++)
		{
			if (pol_it != pol.begin())
				os << "+";
			os << pol_it->data;
		}
		return os;
	}
};

// умножение монома на полином
Polynomial Monomial::operator*(Polynomial& p)
{
	Polynomial res;
	Polynomial::Iterator p_it = p.begin();
	Polynomial::Iterator res_it = res.begin();
	while (p_it != p.end())
	{
		res.insert(*res_it, (*this) * p_it->data);
		p_it++;
		res_it++;
		if (!res_it->data.deg_is_cor())
			throw "Wrong degree of resulting polynomial!";
	}
	return res;
}

// умножение полинома на моном
Polynomial operator*(Polynomial& p, Monomial& m)
{
	Polynomial res;
	res = m * p;
	return res;
}