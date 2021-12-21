#include "monom.h"

MonomList::MonomList()
{
	Tail = new Monom;
	Tail->next = Tail;
}

MonomList::MonomList(const MonomList& poly)
{
	Tail = new Monom(poly.Tail->cf, poly.Tail->deg);

	Monom* p = Tail;
	Monom* q = poly.Tail->next;

	while (q != poly.Tail)
	{
		p->next = new Monom(q->cf, q->deg);
		p = p->next;
		q = q->next;
	}
	p->next = Tail;
}

MonomList& MonomList::operator=(const MonomList& poly)
{
	if (this != &poly)
	{
		Tail->cf = poly.Tail->cf;
		Tail->deg = poly.Tail->deg;

		Monom* p = Tail->next;
		Monom* q = Tail->next;
		while (p != Tail)
		{
			q = p->next;
			delete p;
			p = q;
		}

		q = poly.Tail->next;
		while (q != poly.Tail)
		{
			p->next = new Monom(q->cf, q->deg);
			p = p->next;
			q = q->next;
		}
		p->next = Tail;
	}
	return *this;
}

MonomList::~MonomList()
{
	Monom* p = Tail->next;
	Monom* q = Tail->next;
	while (p != Tail)
	{
		q = p->next;
		delete p;
		p = q;
	}
	delete Tail;
}

void MonomList::Insert(const Monom& monom)
{
	if (abs(monom.cf) > 1e-10)
	{
		Monom* p = Tail;
		while (monom.deg < p->next->deg)
		{
			p = p->next;
		}
		if (monom.deg == p->next->deg)
		{
			p->next->cf += monom.cf;
			if (p->next->cf < 1e-10 && p->next != Tail)
			{
				Monom* tmp = p->next;
				p->next = tmp->next;
				delete tmp;
			}
		}
		else
		{
			Monom* tmp = p->next;
			p->next = new Monom(monom.cf, monom.deg, tmp);
		}
	}
}

MonomList::Iterator MonomList::begin()
{
	return MonomList::Iterator(Tail);
}

MonomList::Iterator::Iterator(Monom* _ptr)
	:ptr(_ptr)
{
}

MonomList::Iterator& MonomList::Iterator::operator++()
{
	ptr = ptr->next;
	return *this;
}

Monom& MonomList::Iterator::operator*()
{
	return *ptr;
}