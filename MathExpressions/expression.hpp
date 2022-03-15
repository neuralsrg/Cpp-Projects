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

#include <iostream>
#include <memory>
#include <utility>
#include "variable.hpp"

class Expression {
	
	/* We calculate the expression of this Variable*/
	/* Can be undefined for inner objects*/
	std::unique_ptr<Variable> expressionVariable;
	/* It can contain either operation arguments */
	std::unique_ptr<Expression> left, right;
	/* Or the single Variable (bottom level) */
	std::unique_ptr<Variable> var;
	/* The operation sign */
	char operation;

public:

	/* 2 Expressions and operation in-between can be converted to Expression */
	Expression(std::unique_ptr<Expression>, std::unique_ptr<Expression>, char);

	/* Prints the Expression */
	friend std::ostream& operator<<(std::ostream&, const Expression&);

	/* Overloading operators */
	friend std::unique_ptr<Expression> operator+(std::unique_ptr<Expression>,
			std::unique_ptr<Expression>);

	/* If the argument has type *double, then we have to delete it */
	~Expression();
};

#endif
