#include "polinom.h"

void main()
{
	Polinom A, B, res;
	A.str_to_poly("x - y");
	B.str_to_poly("-x + y");

	res = A * B;
	A += B;

	A.Print();
	res.Print();

	std::cout << "end" << std::endl;
}