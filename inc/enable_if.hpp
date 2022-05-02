#pragma once

namespace ft
{
	template <bool B, class T = void>
	struct enable_if
	{};
	
	template <class T>
	struct enable_if<true, T>
	{
		typedef T type;
	};
	
	template <class T>
	struct enable_if<false, T>
	{
	};

	template <class A, class B>
	struct is_same
	{
		const static bool value = false;
	};

	template <class T>
	struct is_same<T, T>
	{
		const static bool value = true;
	};


}
