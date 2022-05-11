#include "namespace.h"
#include "Exp.h"
#include "Env.h"
#include "Parser.h"

int main()
{
	Parser p;
	auto global = std::make_shared<Env>();
	global->map_constants();
	p.repl("$ ", global);
}
