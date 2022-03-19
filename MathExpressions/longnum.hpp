#ifndef LONGNUM_HPP_SENTRY
#define LONGNUM_HPP_SENTRY

#include <iostream>
#include <memory>
#include "array.hpp"

#define CAPACITY 1000000000
#define NUM_SYMBOLS 9

class LongNum {

	/* Moving Constructor seems incredibly powerful here */
	std::shared_ptr<Array<int>> number;
	int power;

public:

	//LongNum(int num = 0, int pow = 0) : number(1), power(pow) { number[0] = num; }
	LongNum(double);
	LongNum(std::shared_ptr<Array<int>> arr, int pow) : number(arr), power(pow) {}
	friend std::ostream& operator<<(std::ostream&, const LongNum&);
	int getPower() const { return power; }
	void setPower(int newpow) { power = newpow; }

	friend std::shared_ptr<LongNum> reducePower(std::shared_ptr<LongNum>, int);

	friend std::shared_ptr<LongNum> operator*(std::shared_ptr<LongNum>, int);
	friend std::shared_ptr<LongNum> addSamePower(std::shared_ptr<LongNum>,
			std::shared_ptr<LongNum>);
	friend std::shared_ptr<LongNum> operator+(std::shared_ptr<LongNum>, 
			std::shared_ptr<LongNum>);
	friend std::shared_ptr<LongNum> operator*(std::shared_ptr<LongNum>, 
			std::shared_ptr<LongNum>);
	
	~LongNum() {}
};
#endif
