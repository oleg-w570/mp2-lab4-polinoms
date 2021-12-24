#include "polinom.h"
#include "INPUT.h"

void main()
{
	Polinom A, B, res;

	res = A * B;
	A += B;

	A.Print();
	res.Print();

	std::cout << "end" << std::endl;
}