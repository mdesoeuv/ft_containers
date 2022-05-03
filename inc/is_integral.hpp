#pragma once

#define IS_INTEGRAL(TYPE)             \
	template <>                       \
	struct is_integral<TYPE>          \
	{                                 \
		enum { value = true };        \
		typedef std::true_type type;  \
	}

namespace ft
{
	template <class T>
	struct is_integral
	{
		enum { value = false };
		typedef std::false_type type; 
	};

	IS_INTEGRAL(bool);
	
	IS_INTEGRAL(char);
	
	IS_INTEGRAL(char16_t);

	IS_INTEGRAL(char32_t);

	IS_INTEGRAL(wchar_t);

	IS_INTEGRAL(signed char);

	IS_INTEGRAL(short int);

	IS_INTEGRAL(int);

	IS_INTEGRAL(long int);

	IS_INTEGRAL(long long);

	IS_INTEGRAL(unsigned char);

	IS_INTEGRAL(unsigned short int);

	IS_INTEGRAL(unsigned int);

	IS_INTEGRAL(unsigned long int);

	IS_INTEGRAL(unsigned long long int);
}