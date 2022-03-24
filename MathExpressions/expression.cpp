#include <cassert>
#include "expression.hpp"
#include "math.h"

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
	/* assert((arg1->expressionVariable->getName() != "" ||
			arg2->expressionVariable->getName() != "") &&
			"Expression cnst somehow got 2 unnamed Variables");*/
	if (arg2) {
		if ((arg1->expressionVariable->getName() != "")
				&& (arg2->expressionVariable->getName() != "")
				&& (arg1->expressionVariable->getName() !=
					arg2->expressionVariable->getName())) {
			std::cout << "ERROR: Multiple variable expression!" << std::endl;
			exit(1);
		}
		expressionVariable = arg1->expressionVariable->getName() != "" ?
			arg1->expressionVariable : arg2->expressionVariable;
	} else 
		expressionVariable = arg1->expressionVariable;
	left = arg1;
	right = arg2;
	operation = op;
}

std::ostream& operator<<(std::ostream& cout, const Expression& ex)
{
	//if (!ex.left && !ex.right)
	if (!ex.operation) {
		cout << *ex.expressionVariable;
	} else 
		if (ex.operation == 's' || ex.operation == 'c' ||
				ex.operation == 'l' || ex.operation == 'e' || ex.operation == 'a') {
			std::string str = ex.operation == 's' ?
				"sin" : ex.operation == 'c' ?
				"cos" : ex.operation == 'l' ?
				"log" : ex.operation == 'e' ?
				"exp" : ex.operation == 'a' ? "asin" : "";
			cout << str << '(' << *ex.left << ')';
		}
		else 
			cout << '(' << *ex.left << ' ' << ex.operation << ' ' << *ex.right << ')';
	return cout;
}

std::ostream& operator<<(std::ostream& cout, std::shared_ptr<Expression> e)
{
	cout << *e;
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
	if (operation == 's' || operation == 'c' || operation == 'l' || operation == 'e'
			|| operation == 'a') {
		auto copied_left = left->deepCopy();
		std::shared_ptr<Expression> copied_right;
		return std::make_shared<Expression>(copied_left, copied_right, operation); 
	} else {
		auto copied_left = left->deepCopy();
		auto copied_right = right->deepCopy();
		return std::make_shared<Expression>(copied_left, copied_right, operation); 
	}
}

/* Computing Expression like f(y), f(x * x - 2 * x) */
void Expression::changeDependencies(std::shared_ptr<Expression> newE)
{
	assert((left || right) && "Variable Expression in changeDependencies");
	bool left_named = left->expressionVariable->getName() != "";
	if (operation == 's' || operation == 'c' || operation == 'l' || operation == 'e'
			|| operation == 'a') {
		if (!left->operation && left_named)
			left = newE;
		else if (left->operation) 
			left->changeDependencies(newE);
		return;
	}
	bool right_named = right->expressionVariable->getName() != "";

	if (!left->operation && left_named)
		left = newE;
	else if (left->operation)
		left->changeDependencies(newE);
	if (!right->operation && right_named)
		right = newE;
	else if (right->operation)
		right->changeDependencies(newE);
}

std::shared_ptr<Expression> Expression::interceptPropagation(std::shared_ptr<Expression> e)
{
	if (!operation) {
		if (expressionVariable->getName() != "")
			return e;
		else 
			return std::make_shared<Expression>(expressionVariable);
	}
	auto copy = this->deepCopy();	
	copy->expressionVariable = e->expressionVariable;
	copy->changeDependencies(e);
	return copy;
}

std::shared_ptr<Expression> Expression::interceptPropagation(const Variable& var)
{
	return interceptPropagation(std::make_shared<Expression>(var));
}

std::shared_ptr<Expression> sin(std::shared_ptr<Expression> e)
{
	std::shared_ptr<Expression> tmp_right;
	return std::make_shared<Expression>(e, tmp_right, 's');
}

std::shared_ptr<Expression> cos(std::shared_ptr<Expression> e)
{
	std::shared_ptr<Expression> tmp_right;
	return std::make_shared<Expression>(e, tmp_right, 'c');
}

std::shared_ptr<Expression> log(std::shared_ptr<Expression> e)
{
	std::shared_ptr<Expression> tmp_right;
	return std::make_shared<Expression>(e, tmp_right, 'l');
}

std::shared_ptr<Expression> exp(std::shared_ptr<Expression> e)
{
	std::shared_ptr<Expression> tmp_right;
	return std::make_shared<Expression>(e, tmp_right, 'e');
}

std::shared_ptr<Expression> atan(std::shared_ptr<Expression> e)
{
	std::shared_ptr<Expression> tmp_right;
	return std::make_shared<Expression>(e, tmp_right, 'a');
}

std::shared_ptr<LongNum> computeExpression(std::shared_ptr<Expression> e,
		std::shared_ptr<LongNum> x)
{
	if (!e->operation && e->expressionVariable->getName() != "")
		return x;
	if (!e->operation)
		return e->expressionVariable->getNumValue();
	if (e->operation == '+')
		return computeExpression(e->left, x) + computeExpression(e->right, x);
	if (e->operation == '-')
		return computeExpression(e->left, x) - computeExpression(e->right, x);
	if (e->operation == '*')
		return computeExpression(e->left, x) * computeExpression(e->right, x);
	if (e->operation == 's')
		return sin(computeExpression(e->left, x));
	if (e->operation == 'c')
		return cos(computeExpression(e->left, x));
	if (e->operation == 'l')
		return log(computeExpression(e->left, x));
	if (e->operation == 'e')
		return exp(computeExpression(e->left, x));
	return asin(computeExpression(e->left, x));
}
