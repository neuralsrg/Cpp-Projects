#ifndef FUNCTION_HPP_SENTRY
#define FUNCTION_HPP_SENTRY

#include <iostream>
#include "expression.hpp"
#include "variable.hpp"

class Function {

	std::shared_ptr<Expression> exprs;

public:

	Function(std::shared_ptr<Expression> e) : exprs(e) {}
	Function(const Variable&);

	friend std::ostream& operator<<(std::ostream&, const Function&);

	void operator=(std::shared_ptr<Expression>);

	std::shared_ptr<Expression> operator()(std::shared_ptr<Expression>);
	std::shared_ptr<Expression> operator()(const Variable&);
	std::shared_ptr<Expression> operator()(const Function&);
	double operator()(double);

	friend std::shared_ptr<Expression> operator+(const Function&, const Function&);
	friend std::shared_ptr<Expression> operator-(const Function&, const Function&);
	friend std::shared_ptr<Expression> operator*(const Function&, const Function&);

	friend std::shared_ptr<Expression> sin(const Function&);
	friend std::shared_ptr<Expression> cos(const Function&);
	friend std::shared_ptr<Expression> log(const Function&);
	friend std::shared_ptr<Expression> exp(const Function&);
	friend std::shared_ptr<Expression> atan(const Function&);

};


#endif
