/* Variable class contains the information about Variable object such as: 
 * 		variable name 
 * Overloads functions:
 * 		cout << 
 */

#ifndef VARIABLE_HPP_SENTRY
#define VARIABLE_HPP_SENTRY

#include <iostream>
#include <memory>
#include "expression.hpp"

class Variable {
	
	std::string name;
	double numValue;

public:

	/* Variable can have a name */
	Variable(std::string);
	/* Or it can be a nameless number */
	Variable(double);

	/* Prints information about Variable */
	friend std::ostream& operator<<(std::ostream&, const Variable&);

	/* Overloading operations */
	friend std::unique_ptr<Expression> operator+(const Variable&, const Variable&);
	friend std::unique_ptr<Expression> operator-(const Variable&, const Variable&);
	friend std::unique_ptr<Expression> operator*(const Variable&, const Variable&);
	friend std::unique_ptr<Expression> operator/(const Variable&, const Variable&);

};

#endif
