/* Expression class contains the information about Expressions such as:
 * 		variable
 * 			used in expression (in case to prevent multiple
 * 			variable expression)
 * Overloads functions:
 * 		cout
 * 		math functions
 */

#ifndef EXPRESSION_HPP_SENTRY
#define EXPRESSION_HPP_SENTRY

class Variable;

#include <iostream>
#include <memory>
#include <utility>
#include "variable.hpp"

class Expression {
	
public:
	/* We calculate the expression of this Variable*/
	/* This ptr is passed to the last term of the Expression */
	std::shared_ptr<Variable> expressionVariable;
	/* It can contain either operation arguments */
	std::shared_ptr<Expression> left, right;
	/* The operation sign */
	char operation;

	/* Variable to Expression */
	Expression(const Variable&);
	Expression(std::shared_ptr<Variable>);
	/* 2 Expressions and operation in-between can be converted to Expression */
	Expression(std::shared_ptr<Expression>, std::shared_ptr<Expression>, char);

	/* Prints the Expression */
	friend std::ostream& operator<<(std::ostream&, const Expression&);

	/* Overloading operators */
	friend std::shared_ptr<Expression> operator+(std::shared_ptr<Expression>,
			std::shared_ptr<Expression>);
	friend std::shared_ptr<Expression> operator+(std::shared_ptr<Expression>,
			const Variable&);
	friend std::shared_ptr<Expression> operator+(const Variable&,
			std::shared_ptr<Expression>);

	friend std::shared_ptr<Expression> operator-(std::shared_ptr<Expression>,
			std::shared_ptr<Expression>);
	friend std::shared_ptr<Expression> operator-(std::shared_ptr<Expression>,
			const Variable&);
	friend std::shared_ptr<Expression> operator-(const Variable&,
			std::shared_ptr<Expression>);

	friend std::shared_ptr<Expression> operator*(std::shared_ptr<Expression>,
			std::shared_ptr<Expression>);
	friend std::shared_ptr<Expression> operator*(std::shared_ptr<Expression>,
			const Variable&);
	friend std::shared_ptr<Expression> operator*(const Variable&,
			std::shared_ptr<Expression>);

	/* Copies Expression */
	std::shared_ptr<Expression> deepCopy() const;

	/* Handles calls like f(y), f(x * x - 2 * x) */
	void changeDependencies(std::shared_ptr<Expression>);
	std::shared_ptr<Expression> interceptPropagation(std::shared_ptr<Expression>);
	std::shared_ptr<Expression> interceptPropagation(const Variable&);

	~Expression() {}
};

std::shared_ptr<Expression> sin(std::shared_ptr<Expression>);
std::shared_ptr<Expression> cos(std::shared_ptr<Expression>);
std::shared_ptr<Expression> log(std::shared_ptr<Expression>);
std::shared_ptr<Expression> exp(std::shared_ptr<Expression>);
std::shared_ptr<Expression> atan(std::shared_ptr<Expression>);

#endif
