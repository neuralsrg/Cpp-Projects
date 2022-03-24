/* Variable class contains the information about Variable object such as: 
 * 		variable name 
 * Overloads functions:
 * 		cout << 
 */

#ifndef VARIABLE_HPP_SENTRY
#define VARIABLE_HPP_SENTRY

class Expression;

#include <iostream>
#include <memory>
#include "expression.hpp"
#include "longnum.hpp"

class Variable {
	
	std::string name;
	//double numValue;
	std::shared_ptr<LongNum> numValue;

public:

	/* Variable can have a name */
	Variable(std::string);
	/* Or it can be a nameless number */
	Variable(double);

	/* Prints information about Variable */
	friend std::ostream& operator<<(std::ostream&, const Variable&);
	/* Get Variable name */
	std::string getName() const { return name; }
	std::shared_ptr<LongNum> getNumValue() const { return numValue; }

	/* Overloading operations */
	friend std::shared_ptr<Expression> operator+(const Variable&, const Variable&);
	friend std::shared_ptr<Expression> operator-(const Variable&, const Variable&);
	friend std::shared_ptr<Expression> operator*(const Variable&, const Variable&);
};

std::shared_ptr<Expression> sin(const Variable&);
std::shared_ptr<Expression> cos(const Variable&);
std::shared_ptr<Expression> log(const Variable&);
std::shared_ptr<Expression> exp(const Variable&);
std::shared_ptr<Expression> asin(const Variable&);

#endif
