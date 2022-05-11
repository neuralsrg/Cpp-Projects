#ifndef NAMESPACE_H_SENTRY
#define NAMESPACE_H_SENTRY

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <list>
#include <map>
#include <memory>

namespace lisp
{
	class Exp;
	class Env;
	class Parser;

	enum exp_type { Symbol, Number, List, Proc, Lambda };
	typedef Exp (*proc_type)(const std::vector<Exp> &);
	typedef std::map<std::string, Exp> map;
	typedef std::vector<Exp> ExpVector;
	Exp eval(Exp x, std::shared_ptr<Env> env);
}

#endif
