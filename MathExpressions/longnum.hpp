#ifndef LONGNUM_HPP_SENTRY
#define LONGNUM_HPP_SENTRY

#include <iostream>
#include <memory>
#include "array.hpp"

#define CAPACITY 1000000000
#define NUM_SYMBOLS 9

class LongNum {

	std::shared_ptr<Array<int>> number;
	int power;
	bool sign; // 0 - positive; 1 - negative

public:

	//LongNum(int num = 0, int pow = 0) : number(1), power(pow) { number[0] = num; }
	LongNum(double);
	LongNum(std::shared_ptr<Array<int>> arr, int pow, bool s = 0) : number(arr),
		power(pow), sign(s) {}
	friend std::ostream& operator<<(std::ostream&, const LongNum&);
	int getPower() const { return power; }
	void setPower(int newpow) { power = newpow; }
	void setSign(int s) { sign = s; }

	friend std::shared_ptr<LongNum> reducePower(std::shared_ptr<LongNum>, int);

	friend std::shared_ptr<LongNum> operator*(std::shared_ptr<LongNum>, int);
	friend std::shared_ptr<LongNum> addSamePower(std::shared_ptr<LongNum>,
			std::shared_ptr<LongNum>);
	friend std::shared_ptr<LongNum> operator+(std::shared_ptr<LongNum>, 
			std::shared_ptr<LongNum>);
	friend std::shared_ptr<LongNum> operator*(std::shared_ptr<LongNum>, 
			std::shared_ptr<LongNum>);
	friend std::shared_ptr<LongNum> operator/(std::shared_ptr<LongNum>, int);

	//TODO
	
	friend std::shared_ptr<LongNum> transformPower(std::shared_ptr<LongNum>, int);
	friend bool firstIsGreater(std::shared_ptr<LongNum>,
			std::shared_ptr<LongNum>);
	friend std::shared_ptr<LongNum> subtractSamePower(std::shared_ptr<LongNum>,
			std::shared_ptr<LongNum>);
	friend std::shared_ptr<LongNum> subtract(std::shared_ptr<LongNum>,
			std::shared_ptr<LongNum>);
	friend std::shared_ptr<LongNum> operator-(std::shared_ptr<LongNum>,
			std::shared_ptr<LongNum>);

	
	~LongNum() {}
};
#endif
