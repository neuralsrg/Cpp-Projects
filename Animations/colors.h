#ifndef COLORS_H_CENTRY
#define COLORS_H_CENTRY

#include <ostream>
#include <iostream>

namespace ansi
{
	template<class CharT, class Traits>
	constexpr
		std::basic_ostream<CharT, Traits>& reset(std::basic_ostream<CharT, Traits>& os)
	{
		return os << "\033[0m";
	}

	template <class CharT, class Traits>
	constexpr
		std::basic_ostream<CharT, Traits>& foreground_red(std::basic_ostream<CharT, Traits>& os)
	{
		return os << "\033[31m";
	}

	template <class CharT, class Traits>
	constexpr
		std::basic_ostream<CharT, Traits>& foreground_green(std::basic_ostream<CharT, Traits>& os)
	{
		return os << "\033[32m";
	}

	template <class CharT, class Traits>
	constexpr
		std::basic_ostream<CharT, Traits>& foreground_yellow(std::basic_ostream<CharT, Traits>& os)
	{
		return os << "\033[93m";
	}

	template <class CharT, class Traits>
	constexpr
		std::basic_ostream<CharT, Traits>& foreground_blue(std::basic_ostream<CharT, Traits>& os)
	{
		return os << "\033[34m";
	}

	template <class CharT, class Traits>
	constexpr
		std::basic_ostream<CharT, Traits>& foreground_magenta(std::basic_ostream<CharT, Traits>& os)
	{
		return os << "\033[35m";
	}

	template <class CharT, class Traits>
	constexpr
		std::basic_ostream<CharT, Traits>& foreground_cyan(std::basic_ostream<CharT, Traits>& os)
	{
		return os << "\033[36m";
	}

	template <class CharT, class Traits>
	constexpr
		std::basic_ostream<CharT, Traits>& foreground_gray(std::basic_ostream<CharT, Traits>& os)
	{
		return os << "\033[90m";
	}

	template <class CharT, class Traits>
	constexpr
		std::basic_ostream<CharT, Traits>& foreground_bright_red(std::basic_ostream<CharT, Traits>& os)
	{
		return os << "\033[91m";
	}

	template <class CharT, class Traits>
	constexpr
		std::basic_ostream<CharT, Traits>& foreground_bright_green(std::basic_ostream<CharT, Traits>& os)
	{
		return os << "\033[92m";
	}

	template <class CharT, class Traits>
	constexpr
		std::basic_ostream<CharT, Traits>& foreground_bright_yellow(std::basic_ostream<CharT, Traits>& os)
	{
		return os << "\033[93m";
	}

	template <class CharT, class Traits>
	constexpr
		std::basic_ostream<CharT, Traits>& foreground_bright_blue(std::basic_ostream<CharT, Traits>& os)
	{
		return os << "\033[94m";
	}

	template <class CharT, class Traits>
	constexpr
		std::basic_ostream<CharT, Traits>& foreground_bright_magenta(std::basic_ostream<CharT, Traits>& os)
	{
		return os << "\033[95m";
	}

	template <class CharT, class Traits>
	constexpr
		std::basic_ostream<CharT, Traits>& foreground_bright_cyan(std::basic_ostream<CharT, Traits>& os)
	{
		return os << "\033[96m";
	}

}

#endif
