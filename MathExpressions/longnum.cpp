#include "longnum.hpp"
#include <cmath>
#include <math.h>

//#define NDEBUG

LongNum::LongNum(double x) : number(std::make_shared<Array<int>>()),
	power(0), sign(x < 0)
{
	x = x >= 0 ? x : -1 * x;
	double frac_part, int_part;

	while ((frac_part = modf(x, &int_part)) > 0) {
		x *= 10;
		power--;
	}
	long long llpart = (long long) int_part;
	do {
		number->insertAtEnd(llpart % CAPACITY);
	} while ((llpart /= CAPACITY) > 0);
}

std::ostream& operator<<(std::ostream& cout, const LongNum &ln)
{
	ln.sign ? cout << '-' << *ln.number << "E(" << ln.power << ")\n" : 
		cout << *ln.number << "E(" << ln.power << ")\n";
	return cout;
}
	
std::shared_ptr<LongNum> operator*(std::shared_ptr<LongNum> ln, int x)
{
	long long part_product = 0;
	auto newLn = std::make_shared<LongNum>(ln->number->copy(), ln->power);

	if ((!ln->sign && x >= 0) || (ln->sign && x < 0))
		newLn->sign = 0;
	else 
		newLn->sign = 1;

	x = x >= 0 ? x : -1 * x;

	for (int i = 0; i < newLn->number->getLength(); ++i) {
		part_product = (*newLn->number)[i] * (long long)x + part_product;
		(*newLn->number)[i] = part_product % CAPACITY;
		part_product /= CAPACITY;
	}
	if (part_product)
		newLn->number->insertAtEnd(part_product);
	return newLn;
}

std::shared_ptr<LongNum> reducePower(std::shared_ptr<LongNum> ln, int delta)
{
	for (int i = 0; i < delta / NUM_SYMBOLS; ++i) {
		ln = ln * CAPACITY;
		ln->setPower(ln->getPower() - NUM_SYMBOLS);
	}
	if (delta % NUM_SYMBOLS > 0) {
		int mod = delta % NUM_SYMBOLS, k = 1;
		for (int i = 0; i < mod; ++i)
			k *= 10;
		ln = ln * k;
		ln->setPower(ln->getPower() - mod);
	}
	return ln;
}

std::shared_ptr<LongNum> addSamePower(std::shared_ptr<LongNum> ln1,
		std::shared_ptr<LongNum> ln2)
{
	assert(!ln1->sign && !ln2->sign && "addSamePower got negative term!");
	long long sum = 0;
	if (ln1->number->getLength() > ln2->number->getLength()) {
		std::shared_ptr<LongNum> tmp_ln = ln1;
		ln1 = ln2;
		ln2 = tmp_ln;
	}
	auto newLn = std::make_shared<LongNum>(ln2->number->copy(), ln2->power);
	for (int i1 = 0; i1 < ln1->number->getLength(); ++i1) {
		sum = (*newLn->number)[i1] + (*ln1->number)[i1];
		(*newLn->number)[i1] = sum % CAPACITY;
		sum /= CAPACITY;
		for (int i2 = i1 + 1; i2 < newLn->number->getLength(); ++i2) {
			sum += (*newLn->number)[i2];
			(*newLn->number)[i2] = sum % CAPACITY;
			sum /= CAPACITY;
		}
		while (sum) {
			newLn->number->insertAtEnd(sum % CAPACITY);
			sum /= CAPACITY;
		}
	}
	return newLn;
}

std::shared_ptr<LongNum> operator+(std::shared_ptr<LongNum> ln1, 
		std::shared_ptr<LongNum> ln2)
{
	int power1 = ln1->getPower();
	int power2 = ln2->getPower();
	if (power1 == power2)
		return addSamePower(ln1, ln2);
	if (power1 > power2) {
		auto newLn = reducePower(ln1, power1 - power2);
		return addSamePower(newLn, ln2);
	}
	auto newLn = reducePower(ln2, power2 - power1);
	return addSamePower(ln1, newLn);
}

std::shared_ptr<LongNum> operator*(std::shared_ptr<LongNum> ln1, 
		std::shared_ptr<LongNum> ln2)
{
	bool sign = ln1->sign == ln2->sign ? 0 : 1;
	auto result = std::make_shared<LongNum>(0);
	int tmp_power = 0;
	
	for (int i = 0; i < ln1->number->getLength(); ++i) {
		auto int_product = ln2 * (*ln1->number)[i];
		int_product->setPower(int_product->getPower() + tmp_power);
		std::cout << *int_product << std::endl;
		result = result + int_product;
		tmp_power += NUM_SYMBOLS;
	}
	result->setSign(sign);
	return result;
}

std::shared_ptr<LongNum> operator/(std::shared_ptr<LongNum> ln, int x)
{
	auto newLn = std::make_shared<LongNum>(ln->number->copy(), ln->power);
	if ((!ln->sign && x >= 0) || (ln->sign && x < 0))
		newLn->sign = 0;
	else 
		newLn->sign = 1;

	x = x >= 0 ? x : -1 * x;

	for (int i = ln->number->getLength() - 1; i >= 0; --i) {
		int ln_term = (*ln->number)[i];
		(*newLn->number)[i] = ln_term / x;
		if (i)
			(*newLn->number)[i - 1] += ln_term % x;
	}
	int i = newLn->number->getLength() - 1;
	if (!(*newLn->number)[i])
		newLn->number->remove(i);
	return newLn;
}
