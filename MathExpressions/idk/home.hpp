#ifndef HOME_HPP_SENTRY
#define HOME_HPP_SENTRY

class Car;

#include <iostream>
#include "car.hpp"

class Home {
	
	std::string name;
	double numValue;
	Car *merc;

public:
	Home() : name("Kevin"), numValue(1.0), merc() {}

};

#endif
