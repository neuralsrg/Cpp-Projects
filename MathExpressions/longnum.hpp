#ifndef LONGNUM_HPP_SENTRY
#define LONGNUM_HPP_SENTRY

#include <iostream>
#include <memory>
#include "array.hpp"
#include "constants.hpp"

class LongNum {

	std::shared_ptr<Array<int>> number;
	int power;
	bool sign; // 0 - positive; 1 - negative

public:

	LongNum(double);
	LongNum(std::shared_ptr<Array<int>> arr, int pow, bool s = 0) : number(arr),
		power(pow), sign(s) {}
	friend std::ostream& operator<<(std::ostream&, std::shared_ptr<LongNum>);
	friend std::ostream& operator<<(std::ostream&, const LongNum&);
	int getPower() const { return power; }
	void setPower(int newpow) { power = newpow; }
	void setSign(int s) { sign = s; }

	friend std::shared_ptr<LongNum> reducePower(std::shared_ptr<LongNum>, int);
	friend std::shared_ptr<LongNum> increasePower(std::shared_ptr<LongNum>, int);

	friend std::shared_ptr<LongNum> operator*(std::shared_ptr<LongNum>, int);
	friend std::shared_ptr<LongNum> operator*(double, std::shared_ptr<LongNum>);
	friend std::shared_ptr<LongNum> operator*(std::shared_ptr<LongNum>, double);
	friend std::shared_ptr<LongNum> multiply(std::shared_ptr<LongNum>, int);

	friend std::shared_ptr<LongNum> addSamePower(std::shared_ptr<LongNum>,
			std::shared_ptr<LongNum>);
	friend std::shared_ptr<LongNum> operator+(std::shared_ptr<LongNum>, 
			std::shared_ptr<LongNum>);
	friend std::shared_ptr<LongNum> operator+(double, std::shared_ptr<LongNum>);
	friend std::shared_ptr<LongNum> operator+(std::shared_ptr<LongNum>, double);
	friend std::shared_ptr<LongNum> add(std::shared_ptr<LongNum>, 
			std::shared_ptr<LongNum>);
	friend std::shared_ptr<LongNum> operator*(std::shared_ptr<LongNum>, 
			std::shared_ptr<LongNum>);
	friend std::shared_ptr<LongNum> multiply(std::shared_ptr<LongNum>, 
			std::shared_ptr<LongNum>);
	friend std::shared_ptr<LongNum> operator/(std::shared_ptr<LongNum>, int);
	friend std::shared_ptr<LongNum> divide(std::shared_ptr<LongNum>, int);
	friend bool operator>(std::shared_ptr<LongNum>,
			std::shared_ptr<LongNum>);
	friend std::shared_ptr<LongNum> subtractSamePower(std::shared_ptr<LongNum>,
			std::shared_ptr<LongNum>);
	friend std::shared_ptr<LongNum> operator-(std::shared_ptr<LongNum>,
			std::shared_ptr<LongNum>);
	friend std::shared_ptr<LongNum> subtract(std::shared_ptr<LongNum>,
			std::shared_ptr<LongNum>);

	friend bool isZero(std::shared_ptr<LongNum>);
	friend std::shared_ptr<LongNum> sin(std::shared_ptr<LongNum>);
	friend std::shared_ptr<LongNum> cos(std::shared_ptr<LongNum>);
	friend std::shared_ptr<LongNum> exp(std::shared_ptr<LongNum>);
	friend std::shared_ptr<LongNum> log(std::shared_ptr<LongNum>);
	friend std::shared_ptr<LongNum> asin(std::shared_ptr<LongNum>);

	friend void printFloat(std::shared_ptr<LongNum>);

	friend std::shared_ptr<LongNum> checkForPrecision(std::shared_ptr<LongNum> ln,
			bool print = false)
	{
		int prec;
		if (!print)
			prec = -1 * (std::cout.precision() + NUM_SYMBOLS);
		else
			prec = -1 * (std::cout.precision());
		if (ln->getPower() == prec) {
			return std::make_shared<LongNum>(ln->number->copy(), ln->power,
					ln->sign);
		}
		if (ln->getPower() > prec) {
			return reducePower(ln, ln->getPower() - prec);
		}
		return increasePower(ln, prec - ln->getPower());
	}
	void intsToPower(); 
	
	~LongNum() {}
};

#endif
