# Math Expressions App 
computes some basic math functions with a high precision;
### Available operators: + - * sin cos exp log asin
##### precision: unlimited!
## Examples:

	Variable x("x"), u("u");

	Function f = 3*x*x - 2*x;
	std::cout << f;
	std::cout << f(x) << std::endl; 
	std::cout << f(2 + x*x) << std::endl;
	std::cout << f(u) << std::endl;
	std::cout << std::endl;

	Function w = 1 - x*x + exp(x - 2*x + 1) + asin(x);
	std::cout << w(0.777) << std::endl;
	Function v = (log(sin(asin(x))) + cos(exp(x)) + x*x*x - x);
	std::cout << v(0.88507) << std::endl;
	std::cout << std::endl;
	
	Function func = 3*x*x - 2*x;
	std::cout.precision(7);
	std::cout << func(u) << std::endl;
	std::cout << func(sin(u)) << std::endl;
	std::cout << std::endl;

	Function h = exp (u) + log (1 + u*u);
	h = h + 2.5 * exp (h(u*u)) * cos (sin(h)) * u;
	std::cout << f(1) + 1 << ' ' << h(0) * 1 << std::endl;
	std::cout << 1 + f(1) << ' ' << 1 * h(0) << std::endl;
	std::cout << std::endl;

	Function g = exp(x);
	f = asin(x);
	std::cout << "Prints constants pi and e:\n";
	std::cout << 6*f(0.5) << ' ' << g(1) << std::endl;
	std::cout << std::endl;

	h = 6 * f(0.5 * g(x) + x * x * g(f(x)));
	std::cout << "Prints pi with 100 significant digits:\n";
	std::cout.precision(100);
	std::cout << h(0) << std::endl;
	std::cout << std::endl;

	g = f(sin(u));
	std::cout.precision(17);
	std::cout << g(0.15) << std::endl;
	std::cout << std::endl;

	Function foo = sin(x)*sin(x) + cos(x)*cos(x);
	std::cout << foo(0.9576576758) << std::endl;
	std::cout << std::endl;

	/* Exception will be thrown, the program will terminate */
	//Function ban = asin(x) + 2*x*x + log(u);
	
	Function m = 10 * foo;
	std::cout << m(0.9576576758) << std::endl;
	std::cout << std::endl;

	Function huge = 1;
	for (int i = 0; i < 1000; ++i)
		huge = huge * 10;
	Function sum = huge + 1;

	/*They take ~10 seconds */

	std::cout.precision(1002);
	std::cout << "Wait about 20 sec...\n";
	std::cout << sum(0) << std::endl;

	Function dif = sum - huge;
	std::cout.precision(6);
	std::cout << "And again :(\n";
	std::cout << dif(0) << std::endl;
