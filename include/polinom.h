// класс Полином - упорядоченный односвязный список Мономов
// поддерживает операции Печать, Вставка монома, Удаление монома,
// Поиск монома, Сложение полиномов(слияние упорядоченных списков),
// Умножение полиномов
#pragma once
#include "monom.h"
#include <vector>
#include <string>

class Polinom :
	protected MonomList
{
	std::vector<std::string> Lexs;

	void parser(const std::string& input);
	bool check_vars() const;
	bool check_points() const;
	bool isCorrect() const;
	void converter();

public:
	Polinom& operator+=(const Monom& monom);
	Polinom& operator-=(const Monom& monom);
	Polinom operator+(const Monom& monom) const;
	Polinom operator-(const Monom& monom) const;
	Polinom operator*(const Monom& monom) const;
	Polinom& operator*=(const Monom& monom);
	Polinom& operator+=(double scalar);
	Polinom& operator-=(double scalar);
	Polinom operator+(double scalar) const;
	Polinom operator-(double scalar) const;
	Polinom operator*(double scalar) const;
	Polinom& operator*=(double scalar);
	Polinom& operator+=(const Polinom& poly);
	Polinom& operator-=(const Polinom& poly);
	Polinom operator+(const Polinom& poly) const;
	Polinom operator-(const Polinom& poly) const;
	Polinom operator*(const Polinom& poly) const;
	bool operator==(const Polinom& poly) const;
	void str_to_poly(const std::string& _input);
	void Print() const;
};