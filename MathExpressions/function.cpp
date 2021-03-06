#include "function.hpp"

Function::Function(const Variable& var)
{
	exprs = std::make_shared<Expression>(var);	
}

Function::Function(double d)
{
	auto var = std::make_shared<Variable>(d);
	exprs = std::make_shared<Expression>(var);	
}

std::ostream& operator<<(std::ostream& cout, const Function& f)
{
	cout << *f.exprs << std::endl;
	return cout;
}

void Function::operator=(std::shared_ptr<Expression> e)
{
	exprs = e;
}

std::shared_ptr<Expression> Function::operator()(std::shared_ptr<Expression> ex)
{
	return exprs->interceptPropagation(ex);
}

std::shared_ptr<Expression> Function::operator()(const Variable& var)
{
	return exprs->interceptPropagation(var);
}

std::shared_ptr<Expression> Function::operator()(const Function& f)
{
	return exprs->interceptPropagation(f.exprs);
}

std::shared_ptr<LongNum> Function::operator()(double x)
{
	return computeExpression(exprs, std::make_shared<LongNum>(x));
}

std::shared_ptr<Expression> operator+(const Function& f, const Function& g)
{
	return std::make_shared<Expression>(f.exprs, g.exprs, '+');
}
std::shared_ptr<Expression> operator-(const Function& f, const Function& g)
{
	return std::make_shared<Expression>(f.exprs, g.exprs, '-');
}
std::shared_ptr<Expression> operator*(const Function& f, const Function& g)
{
	return std::make_shared<Expression>(f.exprs, g.exprs, '*');
}

std::shared_ptr<Expression> sin(const Function& f)
{
	return std::make_shared<Expression>(f.exprs, std::shared_ptr<Expression>(), 's');
}
std::shared_ptr<Expression> cos(const Function& f)
{
	return std::make_shared<Expression>(f.exprs, std::shared_ptr<Expression>(), 'c');
}
std::shared_ptr<Expression> log(const Function& f)
{
	return std::make_shared<Expression>(f.exprs, std::shared_ptr<Expression>(), 'l');
}
std::shared_ptr<Expression> exp(const Function& f)
{
	return std::make_shared<Expression>(f.exprs, std::shared_ptr<Expression>(), 'e');
}
std::shared_ptr<Expression> asin(const Function& f)
{
	return std::make_shared<Expression>(f.exprs, std::shared_ptr<Expression>(), 'a');
}
