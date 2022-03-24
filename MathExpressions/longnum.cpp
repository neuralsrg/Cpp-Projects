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

/* Old version */
std::ostream& operator<<(std::ostream& cout, const LongNum &ln)
{
	ln.sign ? cout << '-' << *ln.number << "E(" << ln.power << ")\n" : 
		cout << *ln.number << "E(" << ln.power << ")\n";
	return cout;
}

void printFloat(std::shared_ptr<LongNum> ln)
{
	ln = checkForPrecision(ln);
	int precision = -1 * ln->getPower();
	int extra_nodes = std::ceil((double)precision / NUM_SYMBOLS)
		- ln->number->getLength();
	extra_nodes = extra_nodes > 0 ? extra_nodes : 0;
	for (int i = 0; i < extra_nodes; ++i)
		ln->number->insertAtEnd(0);
	//std::cout << "new length = " << ln->number->getLength() << '\n';
	int i = ln->number->getLength()- 1;
	if (ln->sign)
		std::cout << '-';
	for (i = ln->number->getLength()- 1;
			i > std::ceil((double)precision / NUM_SYMBOLS) - 1; i--) {
		if (i == ln->number->getLength() - 1)
			std::cout << std::setw(1) << std::setfill('0') << (*ln->number)[i];
		else 
			std::cout << std::setw(NUM_SYMBOLS) << std::setfill('0')
				<< (*ln->number)[i];
	}

	int middle_precision = precision % NUM_SYMBOLS;
	int power = 1;
	for (int j = 0; j < middle_precision; ++j)
		power *= 10;

	if (i == ln->number->getLength() - 1) {
		std::cout << (*ln->number)[i] / power << '.';
		std::cout << std::setw(middle_precision) << std::setfill('0')
			<< (*ln->number)[i] % power;
	}
	else {
		std::cout << std::setw(NUM_SYMBOLS - middle_precision) << std::setfill('0')
			<< (*ln->number)[i] / power;
		std::cout << '.' << (*ln->number)[i] % power;
	}

	while (i > 0) {
		i--;
		std::cout << std::setw(NUM_SYMBOLS) << std::setfill('0')
			<< (*ln->number)[i];
	}

	for (int i = 0; i < extra_nodes; i++)
		ln->number->remove(ln->number->getLength() - 1 - i);
}
	
std::shared_ptr<LongNum> operator*(std::shared_ptr<LongNum> ln, int x)
{
	ln = checkForPrecision(ln);
	return multiply(ln, x);
}

std::shared_ptr<LongNum> multiply(std::shared_ptr<LongNum> ln, int x)
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
		ln = multiply(ln, CAPACITY); 
		ln->setPower(ln->getPower() - NUM_SYMBOLS);
	}
	if (delta % NUM_SYMBOLS > 0) {
		int mod = delta % NUM_SYMBOLS, k = 1;
		for (int i = 0; i < mod; ++i)
			k *= 10;
		ln = multiply(ln, k); 
		ln->setPower(ln->getPower() - mod);
	}
	return ln;
}

std::shared_ptr<LongNum> increasePower(std::shared_ptr<LongNum> ln, int delta)
{
	for (int i = 0; i < delta / NUM_SYMBOLS; ++i) {
		ln = divide(ln, CAPACITY);
		ln->setPower(ln->getPower() + NUM_SYMBOLS);
	}
	if (delta % NUM_SYMBOLS > 0) {
		int mod = delta % NUM_SYMBOLS, k = 1;
		for (int i = 0; i < mod; ++i)
			k *= 10;
		ln = divide(ln, k);
		ln->setPower(ln->getPower() + mod);
	}
	return ln;
}

std::shared_ptr<LongNum> addSamePower(std::shared_ptr<LongNum> ln1,
		std::shared_ptr<LongNum> ln2)
{
	assert(!ln1->sign && !ln2->sign && "addSamePower got negative term!");
	assert(!ln1->sign && !ln2->sign && "Negative sign in addSamePower");

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
	ln1 = checkForPrecision(ln1);
	ln2 = checkForPrecision(ln2);
	return add(ln1, ln2);
}

std::shared_ptr<LongNum> add(std::shared_ptr<LongNum> ln1, 
		std::shared_ptr<LongNum> ln2)
{
	int power1 = ln1->getPower();
	int power2 = ln2->getPower();

	if (power1 > power2)
		ln1 = reducePower(ln1, power1 - power2);
	else if (power2 > power1)
		ln2 = reducePower(ln2, power2 - power1);
	if (!ln1->sign && !ln2->sign)
		return addSamePower(ln1, ln2);
	if (ln1->sign && ln2->sign) {
		ln1 = std::make_shared<LongNum>(ln1->number->copy(), ln1->power);
		ln2 = std::make_shared<LongNum>(ln2->number->copy(), ln2->power);
		auto newLn = addSamePower(ln1, ln2);
		newLn->setSign(!newLn->sign);
		return newLn;
	}
	if (!ln1->sign && ln2->sign) {
		ln2 = std::make_shared<LongNum>(ln2->number->copy(), ln2->power);
		return subtractSamePower(ln1, ln2);
	}
	ln1 = std::make_shared<LongNum>(ln1->number->copy(), ln1->power);
	auto newLn = subtractSamePower(ln1, ln2);
	newLn->setSign(!newLn->sign);
	return newLn;
}

std::shared_ptr<LongNum> operator*(std::shared_ptr<LongNum> ln1, 
		std::shared_ptr<LongNum> ln2)
{
	ln1 = checkForPrecision(ln1);
	ln2 = checkForPrecision(ln2);
	return multiply(ln1, ln2);
}

std::shared_ptr<LongNum> multiply(std::shared_ptr<LongNum> ln1, 
		std::shared_ptr<LongNum> ln2)
{
	bool sign = ln1->sign == ln2->sign ? 0 : 1;
	auto result = std::make_shared<LongNum>(0);
	int tmp_power = 0;
	
	for (int i = 0; i < ln1->number->getLength(); ++i) {
		auto int_product = ln2 * (*ln1->number)[i];
		int_product->setPower(int_product->getPower() + tmp_power + ln1->getPower());
		//std::cout << "int_product: " << *int_product << std::endl;
		//std::cout << *int_product << std::endl;
		result = result + int_product;
		tmp_power += NUM_SYMBOLS;
	}
	result->setSign(sign);
	//std::cout << "result: " << *result;
	return result;
}

std::shared_ptr<LongNum> operator/(std::shared_ptr<LongNum> ln, int x)
{
	ln = checkForPrecision(ln);
	return divide(ln, x);
}

std::shared_ptr<LongNum> divide(std::shared_ptr<LongNum> ln, int x)
{
	auto newLn = std::make_shared<LongNum>(ln->number->copy(), ln->power);
	if ((!ln->sign && x >= 0) || (ln->sign && x < 0))
		newLn->sign = 0;
	else 
		newLn->sign = 1;

	x = x >= 0 ? x : -1 * x;

	long long ln_term = (*newLn->number)[newLn->number->getLength() - 1];
	for (int i = newLn->number->getLength() - 1; i >= 0; --i) {
		(*newLn->number)[i] = ln_term / x;
		if (i)
			ln_term = CAPACITY * (ln_term % x) + (*newLn->number)[i - 1];
	}
	for (int i = newLn->number->getLength() - 1; (*newLn->number)[i] == 0; --i) {
		if (!i)
			break;
		newLn->number->remove(i);
	}
	return newLn;
}

bool operator>(std::shared_ptr<LongNum> ln1, std::shared_ptr<LongNum> ln2)
{
	if (isZero(ln1) && isZero(ln2))
		return false;
	if (isZero(ln1) && !isZero(ln2))
		return ln2->sign;
	if (!isZero(ln1) && isZero(ln2))
		return !ln2->sign;
	assert((*ln1->number)[ln1->number->getLength() - 1] &&
			(*ln2->number)[ln2->number->getLength() - 1] &&
			"operator> got insignificant greatest int!");
	if (ln1->number->getLength() != ln2->number->getLength())
		return ln1->number->getLength() > ln2->number->getLength();
	if (ln1->power > ln2->power)
		ln1 = reducePower(ln1, ln1->power - ln2->power);
	else if (ln2->power > ln1->power)
		ln2 = reducePower(ln2, ln2->power - ln1->power);
	int i = ln1->number->getLength() - 1;
	while ((*ln1->number)[i] == (*ln2->number)[i])
		if (!i)
			return false;
		else 
			--i;
	return (*ln1->number)[i] > (*ln2->number)[i];
}

std::shared_ptr<LongNum> subtractSamePower(std::shared_ptr<LongNum> ln1,
		std::shared_ptr<LongNum> ln2)
{
	if (ln2->number->getLength() == 1 && (*ln2->number)[0] == 0)
		return std::make_shared<LongNum>(ln1->number->copy(), ln1->power);
	if (!(ln1 > ln2 || ln2 > ln1))
		return std::make_shared<LongNum>(0);
	assert((ln1->getPower() == ln2->getPower()) &&
			"Different power in subtractSamePower");
	assert(!ln1->sign && !ln2->sign && "Negative sign in subtractSamePower");
	assert((ln1 > ln2 || ln2 > ln1));
	if (ln1 > ln2) {
		auto newLn = std::make_shared<LongNum>(ln1->number->copy(), ln1->power);
		for (int i = 0; i < ln2->number->getLength(); ++i) {
			int res = (*newLn->number)[i] - (*ln2->number)[i];
			if (res < 0) {
				int j;
				for (j = i + 1; (*newLn->number)[j] == 0; ++j)
					(*newLn->number)[j] = CAPACITY - 1;
				(*newLn->number)[j] -= 1;
				res += CAPACITY;
			}
			(*newLn->number)[i] = res;
		}
		for (int i = newLn->number->getLength() - 1; (*newLn->number)[i] == 0; --i)
			newLn->number->remove(i);
		return newLn;
	}
	auto newLn = subtractSamePower(ln2, ln1);
	newLn->setSign(1);
	return newLn;
}

std::shared_ptr<LongNum> operator-(std::shared_ptr<LongNum> ln1,
		std::shared_ptr<LongNum> ln2)
{
	ln1 = checkForPrecision(ln1);
	ln2 = checkForPrecision(ln2);
	return subtract(ln1, ln2);
}

std::shared_ptr<LongNum> subtract(std::shared_ptr<LongNum> ln1,
		std::shared_ptr<LongNum> ln2)
{
	int power1 = ln1->getPower();
	int power2 = ln2->getPower();
	if (power1 > power2)
		ln1 = reducePower(ln1, power1 - power2);
	else if (power2 > power1)
		ln2 = reducePower(ln2, power2 - power1);
	if (!ln1->sign && !ln2->sign)
		return subtractSamePower(ln1, ln2);
	if (ln1->sign && ln2->sign) {
		ln1 = std::make_shared<LongNum>(ln1->number->copy(), ln1->power);
		ln2 = std::make_shared<LongNum>(ln2->number->copy(), ln2->power);
		auto newLn = subtractSamePower(ln1, ln2);
		newLn->setSign(!newLn->sign);
		return newLn;
	}
	if (!ln1->sign && ln2->sign) {
		ln2 = std::make_shared<LongNum>(ln2->number->copy(), ln2->power);
		return ln1 + ln2;
	}
	ln1 = std::make_shared<LongNum>(ln1->number->copy(), ln1->power);
	auto newLn = ln1 + ln2;
	newLn->setSign(1);
	return newLn;
}

std::shared_ptr<LongNum> checkForPrecision(std::shared_ptr<LongNum> ln)
{
	int prec = -1 * std::cout.precision();
	if (ln->getPower() == prec) {
		return std::make_shared<LongNum>(ln->number->copy(), ln->power, ln->sign);
	}
	if (ln->getPower() > prec) {
		return reducePower(ln, ln->getPower() - prec);
	}
	return increasePower(ln, prec - ln->getPower());
}

bool isZero(std::shared_ptr<LongNum> ln)
{
	for (int i = 0; i < ln->number->getLength(); ++i)
		if ((*ln->number)[i])
			return false;
	return  true;
}

std::shared_ptr<LongNum> sin(std::shared_ptr<LongNum> ln)
{
	int counter = 0;

	auto res = std::make_shared<LongNum>(0);
	auto term = std::make_shared<LongNum>(ln->number->copy(), ln->power, ln->sign);

	ln = checkForPrecision(ln);
	term = checkForPrecision(term);
	res = checkForPrecision(res);
	
	while (!isZero(term)) {
		res = res + term;
		counter++;
		term = term * ln * ln * (-1) / ((2 * counter) * (2 * counter + 1));
	}

	return res;
}

std::shared_ptr<LongNum> cos(std::shared_ptr<LongNum> ln)
{
	int counter = 0;

	auto res = std::make_shared<LongNum>(0);
	auto term = std::make_shared<LongNum>(1);

	ln = checkForPrecision(ln);
	term = checkForPrecision(term);
	res = checkForPrecision(res);
	
	while (!isZero(term)) {
		res = res + term;
		counter++;
		term = term * ln * ln * (-1) / ((2 * counter) * (2 * counter - 1));
	}

	return res;
}

std::shared_ptr<LongNum> exp(std::shared_ptr<LongNum> ln)
{
	int counter = 0;

	auto res = std::make_shared<LongNum>(0);
	auto term = std::make_shared<LongNum>(1);

	ln = checkForPrecision(ln);
	term = checkForPrecision(term);
	res = checkForPrecision(res);
	
	while (!isZero(term)) {
		res = res + term;
		counter++;
		term = term * ln / counter;
	}

	return res;
}

std::shared_ptr<LongNum> log(std::shared_ptr<LongNum> ln)
{
	int counter = 1;

	auto res = std::make_shared<LongNum>(0);
	auto x = ln - std::make_shared<LongNum>(1);
	auto term = ln - std::make_shared<LongNum>(1);

	x = checkForPrecision(ln);
	term = checkForPrecision(term);
	res = checkForPrecision(res);
	
	while (!isZero(term / counter)) {
		res = res + term / counter;
		counter++;
		term = term * x * (-1);
	}

	return res;
}

std::shared_ptr<LongNum> asin(std::shared_ptr<LongNum> ln)
{
	int counter = 0;

	auto res = std::make_shared<LongNum>(0);
	auto term = std::make_shared<LongNum>(ln->number->copy(), ln->power, ln->sign);

	ln = checkForPrecision(ln);
	term = checkForPrecision(term);
	res = checkForPrecision(res);
	
	while (!isZero(term / (2 * counter + 1))) {
		res = res + term / (2 * counter + 1);
		counter++;
		term = term * ln * ln * (2 * counter - 1) /
			(2 * counter);
	}

	return res;
}
