#include "variable.hpp"

Variable::Variable(std::string variable_name) : name(variable_name), numValue(0) {}

Variable::Variable(double value) : name(""), numValue(value) {}

std::ostream& operator<<(std::ostream& cout, const Variable& var)
{
	if (var.name != "")
		cout << var.name;
	else
		cout << var.numValue;
	return cout;
}


std::unique_ptr<Expression> operator+(const Variable& left, const Variable& right)
{
	return std::make_unique<Expression>(std::make_unique<Expression>(left),
			std::make_unique<Expression>(right), '+');
}

/*
Variable operator+(const Variable& left, const Variable& right)
{
	return Variable(12);
}
*/

