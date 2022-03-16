#include <cassert>
#include "expression.hpp"

// #define NDEBUG

Expression::Expression(const Variable& var) :
	expressionVariable(std::make_shared<Variable>(var)), operation(0)
{
	//std::cout << "Const for " << expressionVariable->getName() << std::endl;
	// Initializing with nullptr 
	std::unique_ptr<Expression> empty_left;
	std::unique_ptr<Expression> empty_right;

	left = std::move(empty_left);
	right = std::move(empty_right);
}

Expression::Expression(std::unique_ptr<Expression> arg1,
		std::unique_ptr<Expression> arg2, char op)
{
	/* Strange situation, IDK whether it's possible */
	assert((arg1->expressionVariable->getName() != "" ||
			arg2->expressionVariable->getName() != "") &&
			"Expression cnst somehow got 2 unnamed Variables");

	if ((arg1->expressionVariable->getName() != "")
			&& (arg2->expressionVariable->getName() != "")
			&& (arg1->expressionVariable->getName() !=
				arg2->expressionVariable->getName())) {
		std::cout << "ERROR: Multiple variable expression!" << std::endl;
		exit(1);
	}
	expressionVariable = arg1->expressionVariable->getName() != "" ?
		arg1->expressionVariable : arg2->expressionVariable;
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
		cout << '(' << *ex.left << ' ' << ex.operation << ' ' << *ex.right << ')';
	}
	return cout;
}

/* Operator + */

std::unique_ptr<Expression> operator+(std::unique_ptr<Expression> arg1,
		std::unique_ptr<Expression> arg2)
{
	return std::make_unique<Expression>(std::move(arg1), std::move(arg2), '+');
}

std::unique_ptr<Expression> operator+(std::unique_ptr<Expression> arg1,
		const Variable& arg2)
{
	return std::make_unique<Expression>(std::move(arg1),
			std::make_unique<Expression>(arg2), '+');
}

std::unique_ptr<Expression> operator+(const Variable& arg1,
		std::unique_ptr<Expression> arg2)
{
	return std::make_unique<Expression>(std::make_unique<Expression>(arg1),
			std::move(arg2), '+');
}

/* Operator - */

std::unique_ptr<Expression> operator-(std::unique_ptr<Expression> arg1,
		std::unique_ptr<Expression> arg2)
{
	return std::make_unique<Expression>(std::move(arg1), std::move(arg2), '-');
}

std::unique_ptr<Expression> operator-(std::unique_ptr<Expression> arg1,
		const Variable& arg2)
{
	return std::make_unique<Expression>(std::move(arg1),
			std::make_unique<Expression>(arg2), '-');
}

std::unique_ptr<Expression> operator-(const Variable& arg1,
		std::unique_ptr<Expression> arg2)
{
	return std::make_unique<Expression>(std::make_unique<Expression>(arg1),
			std::move(arg2), '-');
}

/* Operator * */

std::unique_ptr<Expression> operator*(std::unique_ptr<Expression> arg1,
		std::unique_ptr<Expression> arg2)
{
	return std::make_unique<Expression>(std::move(arg1), std::move(arg2), '*');
}

std::unique_ptr<Expression> operator*(std::unique_ptr<Expression> arg1,
		const Variable& arg2)
{
	return std::make_unique<Expression>(std::move(arg1),
			std::make_unique<Expression>(arg2), '*');
}

std::unique_ptr<Expression> operator*(const Variable& arg1,
		std::unique_ptr<Expression> arg2)
{
	return std::make_unique<Expression>(std::make_unique<Expression>(arg1),
			std::move(arg2), '*');
}

Expression::~Expression() {}
