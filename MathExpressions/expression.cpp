#include "expression.hpp"

Expression::Expression(std::unique_ptr<Expression> arg1,
		std::unique_ptr<Expression> arg2, char op)
{
	if ((arg1->expressionVariable) && (arg1->expressionVariable)
			&& (arg1->expressionVariable != arg2->expressionVariable)) {
		std::cout << "ERROR: Multiple variable expression!" << std::endl;
		exit(1);
	}	
	expressionVariable = std::move(arg1->expressionVariable);
	left = std::move(arg1);
	right = std::move(arg2);
	std::unique_ptr<Variable> tmp;
	var = std::move(tmp);
	operation = op;
}

std::ostream& operator<<(std::ostream& cout, const Expression& ex)
{
	if (ex.var)
		cout << *ex.var;
	else 
		cout << *ex.left << ex.operation << *ex.right;
	return cout;
}

std::unique_ptr<Expression> operator+(std::unique_ptr<Expression> arg1,
		std::unique_ptr<Expression> arg2)
{
	return std::make_unique<Expression>(arg1, arg2, '+');
}
