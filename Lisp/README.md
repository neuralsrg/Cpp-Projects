# Common Lisp Interpreter

Inspired by Peter Norvig's [article](http://norvig.com/lispy.html).

### Exp:
`Expression` is either atom or list.

### Atom:
`symbol` is interpreted as a variable name; its value is the variable's value.
`number` evaluates to itself

### List:
`List` is any sequence of expressions in parentheses.

### Env:
`Environment` s a mapping of {variable: value}.

Every program must be `bye`-terminated!

### Testing:
```
./output < test1.lisp
./output < test2.lisp
./output < test3.lisp
./output < test4.lisp
./output < test5.lisp
```
