#ifndef LONGNUM_HPP_SENTRY
#define LONGNUM_HPP_SENTRY

#include <iostream>
#include "array.hpp"

#define CAPACITY 1000000000

class LongNum {

	Array<int> number;
	int power;

public:

	LongNum(int num = 0, int pow = 0) : number(1), power(pow) { number[0] = num; }
	LongNum(double);
};
#endif
