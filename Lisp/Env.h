#ifndef ENV_H_SENTRY
#define ENV_H_SENTRY

#include "namespace.h"
#include "Exp.h"
#include <memory>

using namespace lisp;

class lisp::Env {
    map env_; // inner env
    std::shared_ptr<Env> outer_; // outer inv

public:
    Env(std::shared_ptr<Env> outer = nullptr) : outer_(outer) {}
    Env(const ExpVector &parms, const ExpVector &args, Env *outer);

    Exp & operator[] (const std::string &str) { return env_[str]; }

    map& find(const std::string & var);
	void map_constants(Env & env);
};

Exp eval(Exp x, Env * env);
#endif
