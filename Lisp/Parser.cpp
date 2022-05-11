#include "Parser.h"

bool isdig(char c) { return isdigit(static_cast<unsigned char>(c)) != 0; }

std::list<std::string> lisp::Parser::tokenize(const std::string & str)
{
    std::list<std::string> tokens;
    const char * s = str.c_str();
    while (*s) {
        while (*s == ' ')
            ++s;
		if (*s == '`') {
			tokens.push_back("'");
			s++;
		}
        else if (*s == '(' || *s == ')')
            tokens.push_back(*s++ == '(' ? "(" : ")");
        else {
            const char * t = s;
            while (*t && *t != ' ' && *t != '(' && *t != ')')
                ++t;
            tokens.push_back(std::string(s, t));
            s = t;
        }
    }
    return tokens;
}

Exp lisp::Parser::atom(const std::string & token)
{
    if (isdig(token[0]) || (token[0] == '-' && isdig(token[1])))
        return Exp(Number, token);
    return Exp(Symbol, token);
}

Exp lisp::Parser::read_from_tokens(std::list<std::string> & tokens)
{
    const std::string token(tokens.front());
    tokens.pop_front();
    if (token == "(") {
        Exp c(List);
        while (tokens.front() != ")")
            c.list.push_back(read_from_tokens(tokens));
        tokens.pop_front();
        return c;
    }
    else
        return atom(token);
}

Exp lisp::Parser::parse(const std::string & s)
{
    std::list<std::string> tokens(tokenize(s));
    return read_from_tokens(tokens);
}

std::string lisp::Parser::schemestr(const Exp & exp)
{
    if (exp.type == List) {
        std::string s("(");
        for (auto e = exp.list.begin(); e != exp.list.end(); ++e)
            s += schemestr(*e) + ' ';
        if (s[s.size() - 1] == ' ')
            s.erase(s.size() - 1);
        return s + ')';
    }
	else if (exp.type == Lambda || exp.type == Proc)
        return "<Proc>";
    return exp.val;
}

void lisp::Parser::repl(const std::string & prompt, std::shared_ptr<Env> env)
{
    for (;;) {
        std::cout << prompt;
		std::getline(std::cin, line);
		if (line == "")
			continue;
		if (line == "bye")
			break;
        std::cout << schemestr(eval(parse(line), env)) << '\n';
    }
}
