#include <cassert>
#include "expression.hpp"

// #define NDEBUG

Expression::Expression(const Variable& var) :
	expressionVariable(std::make_shared<Variable>(var)),
	left(), right(), operation(0) {}

Expression::Expression(std::shared_ptr<Variable> var) :
	expressionVariable(var),
	left(), right(), operation(0) {}

Expression::Expression(std::shared_ptr<Expression> arg1,
		std::shared_ptr<Expression> arg2, char op)
{
	/* Strange situation, IDK whether it's possible or not */
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
	left = arg1;
	right = arg2;
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

std::shared_ptr<Expression> operator+(std::shared_ptr<Expression> arg1,
		std::shared_ptr<Expression> arg2)
{
	return std::make_shared<Expression>(arg1, arg2, '+');
}

std::shared_ptr<Expression> operator+(std::shared_ptr<Expression> arg1,
		const Variable& arg2)
{
	return std::make_shared<Expression>(arg1,
			std::make_shared<Expression>(arg2), '+');
}

std::shared_ptr<Expression> operator+(const Variable& arg1,
		std::shared_ptr<Expression> arg2)
{
	return std::make_shared<Expression>(std::make_shared<Expression>(arg1),
			arg2, '+');
}

/* Operator - */

std::shared_ptr<Expression> operator-(std::shared_ptr<Expression> arg1,
		std::shared_ptr<Expression> arg2)
{
	return std::make_shared<Expression>(arg1, arg2, '-');
}

std::shared_ptr<Expression> operator-(std::shared_ptr<Expression> arg1,
		const Variable& arg2)
{
	return std::make_shared<Expression>(arg1,
			std::make_shared<Expression>(arg2), '-');
}

std::shared_ptr<Expression> operator-(const Variable& arg1,
		std::shared_ptr<Expression> arg2)
{
	return std::make_shared<Expression>(std::make_shared<Expression>(arg1),
			arg2, '-');
}

/* Operator * */

std::shared_ptr<Expression> operator*(std::shared_ptr<Expression> arg1,
		std::shared_ptr<Expression> arg2)
{
	return std::make_shared<Expression>(arg1, arg2, '*');
}

std::shared_ptr<Expression> operator*(std::shared_ptr<Expression> arg1,
		const Variable& arg2)
{
	return std::make_shared<Expression>(arg1,
			std::make_shared<Expression>(arg2), '*');
}

std::shared_ptr<Expression> operator*(const Variable& arg1,
		std::shared_ptr<Expression> arg2)
{
	return std::make_shared<Expression>(std::make_shared<Expression>(arg1),
			arg2, '*');
}

std::shared_ptr<Expression> Expression::deepCopy() const
{
	if (!left && !right)
		return std::make_shared<Expression>(expressionVariable);
	auto copied_left = left->deepCopy();
	auto copied_right = right->deepCopy();
	return std::make_shared<Expression>(copied_left, copied_right, operation); 
}

/* Computing Expression like f(y), f(x * x - 2 * x) */
void Expression::changeDependencies(std::shared_ptr<Expression> newE)
{
	/* Looks like impossible, but... */
	assert(left && right && "changeDependencies got Variable-like Expression!");
	if (!left->operation && !right->operation) {
		left = newE;
		right = newE;
		return;
	}
	if (!left->operation) {
		left = newE;
		right->changeDependencies(newE);
		return;
	}
	if (!right->operation) {
		right = newE;
		left->changeDependencies(newE);
		return;
	}
	left->changeDependencies(newE);
	right->changeDependencies(newE);
}

std::shared_ptr<Expression> Expression::interceptPropagation(std::shared_ptr<Expression> e)
{
	auto copy = this->deepCopy();	
	if (!copy->operation)
		return e;
	copy->changeDependencies(e);
	return copy;
}
