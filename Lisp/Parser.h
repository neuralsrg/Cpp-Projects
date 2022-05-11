#ifndef PARSER_H_SENTRY
#define PARSER_H_SENTRY

#include "namespace.h"
#include "Exp.h"
#include "Env.h"

class lisp::Parser
{
	std::string line;
public:

	std::list<std::string> tokenize(const std::string & str);
	Exp atom(const std::string & token);
	Exp read_from_tokens(std::list<std::string> & tokens);
	Exp parse(const std::string & s);
	std::string schemestr(const Exp & exp);
	void repl(const std::string & prompt, std::shared_ptr<Env> env);
};

#endif
