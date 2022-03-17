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

/* Also possible to overload all these operators as friend functions
 * of Expression. But this doesn't make any considerable changes */

std::shared_ptr<Expression> operator+(const Variable& left, const Variable& right)
{
	return std::make_shared<Expression>(std::make_shared<Expression>(left),
			std::make_shared<Expression>(right), '+');
}

std::shared_ptr<Expression> operator-(const Variable& left, const Variable& right)
{
	return std::make_shared<Expression>(std::make_shared<Expression>(left),
			std::make_shared<Expression>(right), '-');
}

std::shared_ptr<Expression> operator*(const Variable& left, const Variable& right)
{
	return std::make_shared<Expression>(std::make_shared<Expression>(left),
			std::make_shared<Expression>(right), '*');
}

std::shared_ptr<Expression> sin(const Variable& var)
{
	auto tmp_left = std::make_shared<Expression>(var);
	std::shared_ptr<Expression> tmp_right;
	return std::make_shared<Expression>(tmp_left, tmp_right, 's');
}

std::shared_ptr<Expression> cos(const Variable& var)
{
	auto tmp_left = std::make_shared<Expression>(var);
	std::shared_ptr<Expression> tmp_right;
	return std::make_shared<Expression>(tmp_left, tmp_right, 'c');
}

std::shared_ptr<Expression> log(const Variable& var)
{
	auto tmp_left = std::make_shared<Expression>(var);
	std::shared_ptr<Expression> tmp_right;
	return std::make_shared<Expression>(tmp_left, tmp_right, 'l');
}

std::shared_ptr<Expression> exp(const Variable& var)
{
	auto tmp_left = std::make_shared<Expression>(var);
	std::shared_ptr<Expression> tmp_right;
	return std::make_shared<Expression>(tmp_left, tmp_right, 'e');
}

std::shared_ptr<Expression> atan(const Variable& var)
{
	auto tmp_left = std::make_shared<Expression>(var);
	std::shared_ptr<Expression> tmp_right;
	return std::make_shared<Expression>(tmp_left, tmp_right, 'a');
}
