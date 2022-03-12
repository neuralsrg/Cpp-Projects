/* Variable class contains the information about Variable object such as: 
 * 		variable name 
 * Overloads functions:
 * 		cout << 
 */

#ifndef VARIABLE_HPP_SENTRY
#define VARIABLE_HPP_SENTRY

#include <iostream>

class Variable {
	
	std::string name;

public:

	/* Each Variable must have a name */
	Variable(std::string);
	/* Prints information about Variable */
	friend std::ostream& operator<<(std::ostream&, const Variable&);

};

#endif
