#ifndef EXP_H_SENTRY
#define EXP_H_SENTRY

#include "namespace.h"
#include <memory>

using namespace lisp;

class lisp::Exp
{
public:
    exp_type type;
	std::string val;
	std::vector<Exp> list;
	proc_type proc;
	std::shared_ptr<Env> env;
    Exp(exp_type type = Symbol) : type(type), env(nullptr) {}
    Exp(exp_type type, const std::string & val) : type(type), val(val), env(nullptr) {}
    Exp(proc_type proc) : type(Proc), proc(proc), env(nullptr) {}
};

#endif
