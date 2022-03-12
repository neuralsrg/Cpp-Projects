#include "expression.hpp"

Expression::Expression(const Variable& var) : expressionVariable(&var),
	arg1(&var), arg2(nullptr), operation(0) {}

Expression::Expression(double val) : expressionVariable(nullptr),
	arg1(nullptr), arg2(new double(val)), operation(0) {}

Expression::Expression(const Expression &a1, const Expression &a2, char op)
{
	if (a1.expressionVariable != a2.expressionVariable) {
		std::cout << "ERROR: Multiple variable expression!" << std::endl;
		return;
	}	
	expressionVariable = a1.expressionVariable;
	arg1 = &a1;
	arg2 = &a2;
	operation = op;
}

std::ostream& operator<<(std::ostream& cout, const Expression& ex)
{
	if (!ex.operation) {
		if (!ex.arg1)
			cout << ' ' << *(double *)ex.arg2 << ' ';
		else 
			cout << ' ' << *(Variable *)ex.arg1 << ' ';
	} else 
		cout << *(Expression *)ex.arg1 << ex.operation << *(Expression *)ex.arg2;
	return cout;
}

Expression operator+(const Expression& ex1, const Expression& ex2)
{
	return Expression(ex1, ex2, '+');
}

Expression::~Expression()
{
	if ((operation == 0) && (!arg1))
		delete (double *)arg2;
}
