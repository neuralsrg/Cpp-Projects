#include "namespace.h"
#include "Env.h"
#include <algorithm>

static std::vector<std::string> TW { "setf", "defun", "quote", "eval", "if", "cond",
	"list", "car", "cdr", "cadr", "cdar", "caar", "cddr", "first", "second", "third",
	"rest", "#t", "#f", "nil", "bye" };

static bool check_ident(const std::string & s)
{
	if ((s[0] != '_') && (s[0] < 'a' || s[0] > 'z') && (s[0] < 'A' || s[0] > 'Z'))
		return false;
	if (std::find(TW.begin(), TW.end(), s) != TW.end())
		return false;
	return true;
}

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
	throw "unknown symbol " + var;
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

void lisp::Env::map_constants()
{
    (*this)["nil"]  = nil;   (*this)["#f"] = false_sym;  (*this)["#t"] = true_sym;
    (*this)["car"]  = Exp(&proc_car);        (*this)["cdr"]  = Exp(&proc_cdr);
	(*this)["caar"] = Exp(&proc_caar);       (*this)["cadr"] = Exp(&proc_cadr);
	(*this)["cdar"] = Exp(proc_cdar);        (*this)["cddr"] = Exp(&proc_cddr);
	(*this)["caddr"]= Exp(&proc_caddr);      (*this)["first"]= Exp(&proc_car);
	(*this)["second"]= Exp(&proc_cadr);      (*this)["third"]= Exp(&proc_caddr);
	(*this)["rest"] = Exp(&proc_cdr);        (*this)["list"] = Exp(&proc_list);
	(*this)["+"]    = Exp(&proc_add);        (*this)["-"]    = Exp(&proc_sub);
	(*this)["*"]    = Exp(&proc_mul);        (*this)["/"]    = Exp(&proc_div);
	(*this)[">"]    = Exp(&proc_greater);    (*this)[">="]   = Exp(&proc_greater_equal);
	(*this)["="]    = Exp(&proc_equal);      (*this)["/="]   = Exp(&proc_not_equal);
    (*this)["<"]    = Exp(&proc_less);       (*this)["<="]   = Exp(&proc_less_equal);
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
		if (x.list[0].val == "if") {
			auto cnd = eval(x.list[1], env);
			return eval((cnd.val == "#f" || cnd.val == "nil") ?
					(x.list.size() < 4 ? nil : x.list[3]) : x.list[2], env);
		}
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
		if (x.list[0].val == "setf") {
			if (!check_ident(x.list[1].val))
				throw "bad ident";
			return (*env)[x.list[1].val] = eval(x.list[2], env);
		}
		if (x.list[0].val == "lambda" || x.list[0].val == "defun") {
			x.type = Lambda;
			x.env = env;
			if (x.list[0].val == "defun") {
				if (!check_ident(x.list[1].val))
					throw "bad ident";
				x.list.erase(x.list.begin());
				if (x.list.size() != 3)
					throw "bad syntax";
				(*env)[x.list[0].val] = x;
			}
			if (x.list.size() != 3)
				throw "bad syntax";
			return x;
		}
    }

	Exp proc(eval(x.list[0], env));
	ExpVector exps;
	for (auto exp = x.list.begin() + 1; exp != x.list.end(); ++exp)
		exps.push_back(eval(*exp, env));
	if (proc.type == Lambda) {
		if (proc.list[1].list.size() != exps.size())
			throw "wrong argument list";
		return eval(proc.list[2],
				std::make_shared<Env>(proc.list[1].list, exps, proc.env));
	}
	else if (proc.type == Proc)
		return proc.proc(exps);

	throw "unknown proc";
}
