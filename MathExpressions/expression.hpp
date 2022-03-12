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
#include "variable.hpp"

class Expression {
	
	/* We calculate the expression of this Variable*/
	/* Can be a nullptr in the Expression contains only double */
	const Variable *expressionVariable;
	/* Operation arguments (the 2nd argument can be a nullptr)
	 * Possible types:
	 * 		*Variable (then the 2nd argument is equal to nullptr, operation set to 0)
	 * 		*double (then the 1st argument is equal to nullptr, operation set to 0)
	 * 		*Expression (the 2nd argument CAN be equal to nullptr if
	 * 			the operation is set to 's' / 'c' / 'l' / 'e' / 'a')
	 */
	const void *arg1, *arg2;
	char operation;

public:

	/* Variable can be converted to Expression */	
	Expression(const Variable&);
	/* Double can be converted to Expression */
	Expression(double);
	/* 2 Expressions and operation in-between can be converted to Expression */
	Expression(const Expression&, const Expression&, char);

	/* Prints the Expression */
	friend std::ostream& operator<<(std::ostream&, const Expression&);

	/* Overloading operators */
	friend Expression operator+(const Expression&, const Expression&);

	/* If the argument has type *double, then we have to delete it */
	~Expression();
};

#endif
