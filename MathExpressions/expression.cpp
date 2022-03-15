#include "expression.hpp"

Expression::Expression(const Variable& var) :
	expressionVariable(std::make_unique<Variable>(var)), operation(0)
{
	// Initializing with nullptr 
	std::unique_ptr<Expression> empty_left;
	std::unique_ptr<Expression> empty_right;

	left = std::move(empty_left);
	right = std::move(empty_right);
}

Expression::Expression(std::unique_ptr<Expression> arg1,
		std::unique_ptr<Expression> arg2, char op)
{
	if ((arg1->expressionVariable) && (arg1->expressionVariable)
			&& (arg1->expressionVariable->getName() !=
				arg2->expressionVariable->getName())) {
		std::cout << "ERROR: Multiple variable expression!" << std::endl;
		exit(1);
	}	
	expressionVariable = std::make_unique<Variable>(*arg1->expressionVariable);
	left = std::move(arg1);
	right = std::move(arg2);
	operation = op;
}

std::ostream& operator<<(std::ostream& cout, const Expression& ex)
{
	//if (!ex.left && !ex.right)
	if (!ex.operation) {
		cout << *ex.expressionVariable;
	} else {
		cout << *ex.left << ' ' << ex.operation << ' ' << *ex.right;
	}
	return cout;
}

/*
std::unique_ptr<Expression> operator+(std::unique_ptr<Expression> arg1,
		std::unique_ptr<Expression> arg2)
{
	return std::make_unique<Expression>(std::move(arg1), std::move(arg2), '+');
}
*/
std::unique_ptr<Expression> operator+(std::unique_ptr<Expression> arg1,
		const Variable& arg2)
{
	return std::make_unique<Expression>(std::move(arg1),
			std::make_unique<Expression>(arg2), '+');
}

Expression::~Expression() {}
