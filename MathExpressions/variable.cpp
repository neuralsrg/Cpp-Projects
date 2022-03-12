#include "variable.hpp"

Variable::Variable(std::string variable_name) : name(variable_name) {}

std::ostream& operator<<(std::ostream& cout, const Variable& var)
{
	cout << var.name;
	return cout;
}
