#include "polinom.h"

bool check_err_add_deg(int deg1, int deg2)
{
	int deg1_z = deg1 % 10, deg2_z = deg2 % 10;
	//std::cout << "deg1_z = " << deg1_z << ", deg2_z = " << deg2_z << std::endl;
	if (deg1_z + deg2_z > 9)
		return true;
	int deg1_y = deg1 % 100 / 10, deg2_y = deg2 % 100 / 10;
	//std::cout << "deg1_y = " << deg1_y << ", deg2_y = " << deg2_y << std::endl;
	if (deg1_y + deg2_y > 9)
		return true;
	int deg1_x = deg1 / 100, deg2_x = deg2 / 100;
	//std::cout << "deg1_x = " << deg1_x << ", deg2_x = " << deg2_x << std::endl;
	if (deg1_x + deg2_x > 9)
		return true;

	return false;
}

Polinom& Polinom::operator+=(const Monom& monom)
{
	Insert(monom);
	return *this;
}

Polinom& Polinom::operator-=(const Monom& monom)
{
	Insert(Monom(monom.cf * -1, monom.deg));
	return *this;
}

Polinom Polinom::operator+(const Monom& monom) const
{
	Polinom res(*this);
	res.Insert(monom);
	return res;
}

Polinom Polinom::operator-(const Monom& monom) const
{
	Polinom res(*this);
	res.Insert(Monom(monom.cf * -1, monom.deg));
	return res;
}

Polinom& Polinom::operator+=(double scalar)
{
	Tail->cf += scalar;
	return *this;
}

Polinom& Polinom::operator-=(double scalar)
{
	Tail->cf -= scalar;
	return *this;
}

Polinom Polinom::operator+(double scalar) const
{
	Polinom res(*this);
	res.Tail->cf += scalar;
	return res;
}

Polinom Polinom::operator-(double scalar) const
{
	Polinom res(*this);
	res.Tail->cf -= scalar;
	return res;
}

Polinom Polinom::operator*(double scalar) const
{
	Polinom res(*this);
	res.Tail->cf *= scalar;
	Monom* pRes = res.Tail->next;
	while (pRes != Tail)
	{
		pRes->cf *= scalar;
		pRes = pRes->next;
	}
	return res;
}

Polinom& Polinom::operator*=(double scalar)
{
	Tail->cf *= scalar;
	Monom* p = Tail->next;
	while (p != Tail)
	{
		p->cf *= scalar;
		p = p->next;
	}
	return *this;
}

Polinom& Polinom::operator+=(const Polinom& poly)
{
	Tail->cf += poly.Tail->cf;

	Monom* pThis = Tail;
	Monom* pPoly = poly.Tail->next;

	while (pThis->next != Tail || pPoly != poly.Tail)
	{
		if (pPoly->deg > pThis->next->deg)
		{
			Monom* tmp = pThis->next;
			pThis->next = new Monom(pPoly->cf, pPoly->deg, tmp);
			pPoly = pPoly->next;
			pThis = pThis->next;
		}
		else if (pPoly->deg < pThis->next->deg)
		{
			pThis = pThis->next;
		}
		else
		{
			pThis->next->cf += pPoly->cf;
			if (abs(pThis->next->cf) < 1e-10)
			{
				Monom* tmp = pThis->next;
				pThis->next = pThis->next->next;
				delete tmp;
			}
			else
				pThis = pThis->next;

			pPoly = pPoly->next;
		}
	}
	while (pPoly != poly.Tail)
	{
		pThis->next = new Monom(pPoly->cf, pPoly->deg, Tail);
		pPoly = pPoly->next;
		pThis = pThis->next;
	}
	return *this;
}

Polinom& Polinom::operator-=(const Polinom& poly)
{
	Tail->cf -= poly.Tail->cf;

	if (this == &poly)
	{
		Monom* p = Tail->next;
		Monom* q = Tail->next;
		while (p != Tail)
		{
			q = p->next;
			delete p;
			p = q;
		}
		Tail->next = Tail;
	}
	else
	{
		Monom* pThis = Tail;
		Monom* pPoly = poly.Tail->next;

		while (pThis->next != Tail || pPoly != poly.Tail)
		{
			if (pPoly->deg > pThis->next->deg)
			{
				Monom* tmp = pThis->next;
				pThis->next = new Monom(-pPoly->cf, pPoly->deg, tmp);
				pPoly = pPoly->next;
				pThis = pThis->next;
			}
			else if (pPoly->deg < pThis->next->deg)
			{
				pThis = pThis->next;
			}
			else
			{
				pThis->next->cf -= pPoly->cf;
				if (abs(pThis->next->cf) < 1e-10)
				{
					Monom* tmp = pThis->next;
					pThis->next = pThis->next->next;
					delete tmp;
				}
				else
					pThis = pThis->next;

				pPoly = pPoly->next;
			}
		}
		while (pPoly != poly.Tail)
		{
			pThis->next = new Monom(-pPoly->cf, pPoly->deg, Tail);
			pPoly = pPoly->next;
			pThis = pThis->next;
		}
	}
	return *this;
}

Polinom Polinom::operator+(const Polinom& poly) const
{
	Polinom res;
	res.Tail->cf = Tail->cf + poly.Tail->cf;

	Monom* pThis = Tail->next;
	Monom* pPoly = poly.Tail->next;
	Monom* pRes = res.Tail;

	while (pThis != Tail || pPoly != poly.Tail)
	{
		if (pThis->deg > pPoly->deg)
		{
			pRes->next = new Monom(pThis->cf, pThis->deg);
			pRes = pRes->next;
			pThis = pThis->next;
		}
		else if (pThis->deg < pPoly->deg)
		{
			pRes->next = new Monom(pPoly->cf, pPoly->deg);
			pRes = pRes->next;
			pPoly = pPoly->next;
		}
		else
		{
			if (abs(pPoly->cf + pThis->cf) > 1e-10)
			{
				pRes->next = new Monom(pPoly->cf + pThis->cf, pPoly->deg);
				pRes = pRes->next;
			}
			pThis = pThis->next;
			pPoly = pPoly->next;
		}
	}

	while (pThis != Tail)
	{
		pRes->next = new Monom(pThis->cf, pThis->deg);
		pRes = pRes->next;
		pThis = pThis->next;
	}
	while (pPoly != poly.Tail)
	{
		pRes->next = new Monom(pPoly->cf, pPoly->deg);
		pRes = pRes->next;
		pPoly = pPoly->next;
	}
	pRes->next = res.Tail;

	return res;
}

Polinom Polinom::operator-(const Polinom& poly) const
{
	Polinom res;
	res.Tail->cf = Tail->cf - poly.Tail->cf;

	Monom* pThis = Tail->next;
	Monom* pPoly = poly.Tail->next;
	Monom* pRes = res.Tail;

	while (pThis != Tail || pPoly != poly.Tail)
	{
		if (pThis->deg > pPoly->deg)
		{
			pRes->next = new Monom(pThis->cf, pThis->deg);
			pRes = pRes->next;
			pThis = pThis->next;
		}
		else if (pThis->deg < pPoly->deg)
		{
			pRes->next = new Monom(-pPoly->cf, pPoly->deg);
			pRes = pRes->next;
			pPoly = pPoly->next;
		}
		else
		{
			if (abs(pThis->cf - pPoly->cf) > 1e-10)
			{
				pRes->next = new Monom(pThis->cf - pPoly->cf, pPoly->deg);
				pRes = pRes->next;
			}
			pThis = pThis->next;
			pPoly = pPoly->next;
		}
	}

	while (pThis != Tail)
	{
		pRes->next = new Monom(pThis->cf, pThis->deg);
		pRes = pRes->next;
		pThis = pThis->next;
	}
	while (pPoly != poly.Tail)
	{
		pRes->next = new Monom(-pPoly->cf, pPoly->deg);
		pRes = pRes->next;
		pPoly = pPoly->next;
	}
	pRes->next = res.Tail;

	return res;
}

Polinom Polinom::operator*(const Polinom& poly) const
{
	Polinom res;
	Monom* pThis = Tail;
	Monom* pPoly = poly.Tail;

	do
	{
		do
		{
			if (check_err_add_deg(pThis->deg, pPoly->deg))
				throw std::exception("Wrong degree");
			Monom tmp(pThis->cf * pPoly->cf, pThis->deg + pPoly->deg);
			res.Insert(tmp);
			pPoly = pPoly->next;
		} while (pPoly != poly.Tail);
		pThis = pThis->next;
	} while (pThis != Tail);

	return res;
}

bool Polinom::operator==(const Polinom& poly) const
{
	Monom* pThis = Tail;
	Monom* pPoly = poly.Tail;
	do
	{
		if (*pThis != *pPoly)
			return false;
		pThis = pThis->next;
		pPoly = pPoly->next;
	} while (pThis != Tail || pPoly != poly.Tail);

	if (pThis != Tail || pPoly != poly.Tail)
		return false;

	return true;
}

void Polinom::str_to_poly(const std::string& input)
{
	parser(input);
	if (isCorrect())
		converter();
	else
		throw std::exception("Error!");
}

void Polinom::parser(const std::string& input)
{
	Lexs.clear();
	int state = 0;
	std::string lexema;

	for (size_t i = 0; i < input.length(); i++)
	{
		if (input[i] != ' ')
		{
			char current = input[i];

			switch (state)
			{
			case 0: {
				if (current == '+' || current == '-')
					state = 1;
				else if (std::isdigit(current) || current == '.')
					state = 2;
				else if (current == 'x' || current == 'y' || current == 'z')
					state = 3;
				else
					throw std::exception("Wrong symbol!!!");
				lexema.append(1, current);
				break;
			}
			case 1: {
				if (std::isdigit(current) || current == '.')
					state = 2;
				else if (current == 'x' || current == 'y' || current == 'z')
					state = 3;
				else
					throw std::exception("Wrong symbol!!!");

				lexema.append(1, current);
				break;
			}
			case 2: {
				if (current == '+' || current == '-')
				{
					state = 1;
					Lexs.push_back(lexema);
					lexema.clear();
				}
				else if (std::isdigit(current) || current == '.')
					state = 2;
				else if (current == 'x' || current == 'y' || current == 'z')
					state = 3;
				else
					throw std::exception("Wrong symbol!!!");

				lexema.append(1, current);
				break;
			}
			case 3: {
				if (current == '+' || current == '-')
				{
					state = 1;
					Lexs.push_back(lexema);
					lexema.clear();
				}
				else if (current == 'x' || current == 'y' || current == 'z')
					state = 3;
				else if (current == '^')
					state = 4;
				else
					throw std::exception("Wrong symbol!!!");

				lexema.append(1, current);
				break;
			}
			case 4: {
				if (std::isdigit(current) || current == '.')
				{
					state = 5;
					lexema.append(1, current);
				}
				else
					throw std::exception("Wrong symbol!!!");

				break;
			}
			case 5: {
				if (current == '+' || current == '-')
				{
					state = 1;
					Lexs.push_back(lexema);
					lexema.clear();
				}
				else if (current == 'x' || current == 'y' || current == 'z')
					state = 3;
				else
					throw std::exception("Wrong symbol!!!");

				lexema.append(1, current);
				break;
			}
			default:
				break;
			}
		}
	}

	if (state == 2 || state == 3 || state == 5)
		Lexs.push_back(lexema);
	else
		throw std::exception("Wrong symbol!!!");
}

bool Polinom::check_vars() const
{
	for (size_t i = 0; i < Lexs.size(); i++)
	{
		size_t pX = Lexs[i].find_first_of('x');
		pX = Lexs[i].find_first_of('x', pX + 1);
		size_t pY = Lexs[i].find_first_of('y');
		pY = Lexs[i].find_first_of('y', pY + 1);
		size_t pZ = Lexs[i].find_first_of('z');
		pZ = Lexs[i].find_first_of('z', pZ + 1);
		if (pX != Lexs[i].npos || pY != Lexs[i].npos || pZ != Lexs[i].npos)
			return false;
	}
	return true;
}

bool Polinom::check_points() const
{
	for (size_t i = 0; i < Lexs.size(); i++)
	{
		size_t p = Lexs[i].find_first_of('.');
		p = Lexs[i].find_first_of('.', p + 1);
		if (p != Lexs[i].npos)
			return false;
	}
	return true;
}

bool Polinom::isCorrect() const
{
	return check_points() && check_vars();
}

void Polinom::converter()
{
	for (size_t i = 0; i < Lexs.size(); i++)
	{
		int state = 0;
		std::string cf;
		int degree = 0;

		for (size_t j = 0; j < Lexs[i].length(); j++)
		{
			const char current = Lexs[i][j];

			switch (state)
			{
			case 0: {
				if (std::isdigit(current) || current == '.')
				{
					state = 2;
					cf.append(1, current);
				}
				else if (current == '-' || current == '+')
				{
					state = 1;
					cf.append(1, current);
				}
				else
				{
					state = 3;
					cf.append("1");
				}

				break;
			}
			case 1: {
				if (std::isdigit(current) || current == '.')
				{
					state = 2;
					cf.append(1, current);
				}
				else
				{
					state = 3;
					cf.append("1");
				}
				break;
			}
			case 2: {
				if (std::isdigit(current) || current == '.')
				{
					state = 2;
					cf.append(1, current);
				}
				else
				{
					state = 3;
				}
				break;
			}
			case 3: {
				if (current == '^')
				{
					if (Lexs[i][j - 1] == 'x')
						degree += std::stoi(&Lexs[i][j + 1]) * 100;
					else if (Lexs[i][j - 1] == 'y')
						degree += std::stoi(&Lexs[i][j + 1]) * 10;
					else
						degree += std::stoi(&Lexs[i][j + 1]);
					j++;
				}
				else
				{
					if (Lexs[i][j - 1] == 'x')
						degree += 100;
					else if (Lexs[i][j - 1] == 'y')
						degree += 10;
					else if (Lexs[i][j - 1] == 'z')
						degree += 1;
				}
				break;
			}
			default:
				break;
			}
		}

		if (Lexs[i].back() == 'x')
			degree += 100;
		else if (Lexs[i].back() == 'y')
			degree += 10;
		else if (Lexs[i].back() == 'z')
			degree += 1;

		Insert(Monom(std::stod(cf), degree));
	}
}

void Polinom::Print() const
{
	Monom* p = Tail->next;
	while (p != Tail)
	{
		std::cout << p->cf << "x^" << p->deg / 100 << "y^" << (p->deg % 100) / 10 << "z^" << p->deg % 10 << " + ";
		p = p->next;
	}
	std::cout << Tail->cf;
	std::cout << std::endl;
}