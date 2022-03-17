#include "longnum.hpp"
#include <cmath>
#include <math.h>

LongNum::LongNum(double x) : number(), power(0)
{
	double frac_part, int_part;

	while ((frac_part = modf(x, &int_part)) > 0) {
		x *= 10;
		power--;
	}
	std::cout << (long long)int_part << ' ' << power << std::endl;
}
