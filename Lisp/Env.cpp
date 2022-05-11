#include "namespace.h"
#include "Env.h"

lisp::Env::Env(const std::vector<Exp> &parms, const std::vector<Exp> &args,
		std::shared_ptr<Env> outer)
	: outer_(outer)
{
	auto a = args.begin();
	for (auto p = parms.begin(); p != parms.end(); ++p)
		env_[p->val] = *a++;
}

map& lisp::Env::find(const std::string & var)
{
	if (env_.find(var) != env_.end())
		return env_;
	if (outer_)
		return outer_->find(var);
	std::cout << "unbound symbol '" << var << "'\n";
	exit(1);
}

/* Constants */

const Exp false_sym(Symbol, "#f");
const Exp true_sym(Symbol, "#t");
const Exp nil(Symbol, "nil");

/* Functions */

std::string str(double n) { std::ostringstream os; os << n; return os.str(); }

Exp proc_list(const ExpVector & ev)
{
    Exp result(List);
	result.list = ev;
    return result;
}

Exp proc_add(const ExpVector & ev)
{
    double n(atof(ev[0].val.c_str()));
    for (auto i = ev.begin()+1; i != ev.end(); ++i) n += atof(i->val.c_str());
    return Exp(Number, str(n));
}

Exp proc_sub(const ExpVector & ev)
{
    double n(atof(ev[0].val.c_str()));
    for (auto i = ev.begin()+1; i != ev.end(); ++i) n -= atof(i->val.c_str());
    return Exp(Number, str(n));
}

Exp proc_mul(const ExpVector & ev)
{
    double n(1);
    for (auto i = ev.begin(); i != ev.end(); ++i) n *= atof(i->val.c_str());
    return Exp(Number, str(n));
}

Exp proc_div(const ExpVector & ev)
{
    double n(atof(ev[0].val.c_str()));
    for (auto i = ev.begin()+1; i != ev.end(); ++i) n /= atof(i->val.c_str());
    return Exp(Number, str(n));
}

Exp proc_car(const ExpVector & ev) { return ev[0].list[0]; }

Exp proc_cdr(const ExpVector & ev)
{
    if (ev[0].list.size() < 2)
        return nil;
    Exp result(ev[0]);
    result.list.erase(result.list.begin());
    return result;
}

Exp proc_caar(const ExpVector & ev)
{
	if (ev[0].list[0].list.empty())
		return nil;
	return ev[0].list[0].list[0];
}

Exp proc_cadr(const ExpVector & ev)
{
    if (ev[0].list.size() < 2)
        return nil;
    return ev[0].list[1];
}

Exp proc_caddr(const ExpVector & ev)
{
    if (ev[0].list.size() < 3)
        return nil;
    return ev[0].list[2];
}

Exp proc_cdar(const ExpVector & ev)
{
    Exp result(ev[0].list[0]);
	if (result.list.size() < 2)
		return nil;
    result.list.erase(result.list.begin());
	return result;
}

Exp proc_cddr(const ExpVector & ev)
{
    if (ev[0].list.size() < 2)
        return nil;
    Exp result(ev[0]);
    result.list.erase(result.list.begin(), result.list.begin() + 1);
    return result;
}

Exp proc_append(const ExpVector & ev)
{
    Exp result(List);
    result.list = ev[0].list;
    for (auto i = ev[1].list.begin(); i != ev[1].list.end(); ++i) result.list.push_back(*i);
    return result;
}

Exp proc_cons(const ExpVector & ev)
{
    Exp result(List);
    result.list.push_back(ev[0]);
    for (auto i = ev[1].list.begin(); i != ev[1].list.end(); ++i) result.list.push_back(*i);
    return result;
}

Exp proc_greater(const ExpVector & ev)
{
    double n(atof(ev[0].val.c_str()));
    for (auto i = ev.begin()+1; i != ev.end(); ++i)
        if (n <= atof(i->val.c_str()))
            return false_sym;
    return true_sym;
}

Exp proc_greater_equal(const ExpVector & ev)
{
    double n(atof(ev[0].val.c_str()));
    for (auto i = ev.begin()+1; i != ev.end(); ++i)
        if (n < atof(i->val.c_str()))
            return false_sym;
    return true_sym;
}

Exp proc_less(const ExpVector & ev)
{
    double n(atof(ev[0].val.c_str()));
    for (auto i = ev.begin()+1; i != ev.end(); ++i)
        if (n >= atof(i->val.c_str()))
            return false_sym;
    return true_sym;
}

Exp proc_less_equal(const ExpVector & ev)
{
    double n(atof(ev[0].val.c_str()));
    for (auto i = ev.begin()+1; i != ev.end(); ++i)
        if (n > atof(i->val.c_str()))
            return false_sym;
    return true_sym;
}

Exp proc_equal(const ExpVector & ev)
{
    double n(atof(ev[0].val.c_str()));
    for (auto i = ev.begin()+1; i != ev.end(); ++i)
        if (n != atof(i->val.c_str()))
            return false_sym;
    return true_sym;
}

Exp proc_not_equal(const ExpVector & ev)
{
    double n(atof(ev[0].val.c_str()));
    for (auto i = ev.begin()+1; i != ev.end(); ++i)
        if (n == atof(i->val.c_str()))
            return false_sym;
    return true_sym;
}

Exp proc_length(const ExpVector & ev) { return Exp(Number, str(ev[0].list.size())); }
Exp proc_nullp(const ExpVector & ev)  { return ev[0].list.empty() ? true_sym : false_sym; }

void lisp::Env::map_constants()
{
    (*this)["nil"] = nil;   (*this)["#f"] = false_sym;  (*this)["#t"] = true_sym;
    (*this)["append"] = Exp(&proc_append);   (*this)["car"]  = Exp(&proc_car);
    (*this)["cdr"]    = Exp(&proc_cdr);      (*this)["caar"] = Exp(&proc_caar);
	(*this)["cadr"]   = Exp(&proc_cadr);     (*this)["cdar"] = Exp(proc_cdar);
	(*this)["cddr"]   = Exp(&proc_cddr);     (*this)["caddr"]= Exp(&proc_caddr);     
	(*this)["first"]  = Exp(&proc_car);      (*this)["second"]= Exp(&proc_cadr);
	(*this)["third"]  = Exp(&proc_caddr);    (*this)["cons"] = Exp(&proc_cons);
    (*this)["length"] = Exp(&proc_length);   (*this)["list"] = Exp(&proc_list);
    (*this)["null?"]  = Exp(&proc_nullp);    (*this)["+"]    = Exp(&proc_add);
    (*this)["-"]      = Exp(&proc_sub);      (*this)["*"]    = Exp(&proc_mul);
    (*this)["/"]      = Exp(&proc_div);      (*this)[">"]    = Exp(&proc_greater);
	(*this)[">="]     = Exp(&proc_greater_equal);
	(*this)["=="]     = Exp(&proc_equal);    (*this)["/="]   = Exp(&proc_not_equal);
    (*this)["<"]      = Exp(&proc_less);     (*this)["<="]   = Exp(&proc_less_equal);
}

Exp lisp::eval(Exp x, std::shared_ptr<Env> env)
{
	if (x.type == Symbol)
        return env->find(x.val)[x.val];
    if (x.type == Number)
        return x;
    if (x.list.empty())
        return nil;
    if (x.list[0].type == Symbol) {
        if (x.list[0].val == "quote" || x.list[0].val == "'")
            return x.list[1];
		if (x.list[0].val == "eval")
			return eval(eval(x.list[1], env), env);
        if (x.list[0].val == "if")
            return eval(eval(x.list[1], env).val == "#f" ?
					(x.list.size() < 4 ? nil : x.list[3]) : x.list[2], env);
		if (x.list[0].val == "cond") {
			for (auto it_outer = x.list.begin() + 1; it_outer != x.list.end();
					++it_outer) {
				Exp cnd = eval((*it_outer).list[0], env);
				if (cnd.val != "nil" && cnd.val != "#f") {
					if ((*it_outer).list.size() > 1) {
						for (auto it_inner = (*it_outer).list.begin() + 1;
								it_inner != (*it_outer).list.end() - 1; ++it_inner)
							eval(*it_inner, env);
						return eval(*((*it_outer).list.end() - 1), env);
					}
					return cnd;
				}
			}
			return nil;
		}
        if (x.list[0].val == "set!")        // (set! var exp)
            return env->find(x.list[1].val)[x.list[1].val] = eval(x.list[2], env);
        if (x.list[0].val == "define")      // (define var exp)
            return (*env)[x.list[1].val] = eval(x.list[2], env);
        if (x.list[0].val == "lambda" || x.list[0].val == "defun") {
            x.type = Lambda;
            x.env = env;
			if (x.list[0].val == "defun") {
				//x.list[3].type = Lambda;
				x.list.erase(x.list.begin());
            	(*env)[x.list[0].val] = x; //x.list[3];
			}
            return x;
        } /*
        if (x.list[0].val == "begin") {
            for (size_t i = 1; i < x.list.size() - 1; ++i)
                eval(x.list[i], env);
            return eval(x.list[x.list.size() - 1], env);
        }
		*/
    }

    Exp proc(eval(x.list[0], env));
    ExpVector exps;
    for (auto exp = x.list.begin() + 1; exp != x.list.end(); ++exp)
        exps.push_back(eval(*exp, env));
    if (proc.type == Lambda) { /*
		std::cout << "Params: \n";
		for (auto it = proc.list[1].list.begin(); it != proc.list[1].list.end(); ++it)
			std::cout << (*it).val << std::endl;
		std::cout << "Args: \n";
		for (auto it = exps.begin(); it != exps.end(); ++it)
			std::cout << (*it).val << std::endl;
		*/
        return eval(proc.list[2],
				std::make_shared<Env>(proc.list[1].list, exps, proc.env));
    }
    else if (proc.type == Proc)
        return proc.proc(exps);

    std::cout << "not a function\n";
    exit(1);
}
