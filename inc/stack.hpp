/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesoeuv <mdesoeuv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 14:45:49 by mdesoeuv          #+#    #+#             */
/*   Updated: 2022/05/24 20:01:38 by mdesoeuv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP

#include "../inc/vector.hpp"

namespace ft
{
	template <class T, class Container = ft::vector<T> >
	class stack
	{
	public:
		typedef Container container_type;
		typedef typename Container::value_type value_type;
		typedef typename Container::size_type size_type;
		typedef typename Container::reference reference;
		typedef typename Container::const_reference const_reference;

		friend bool operator==(const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs)
		{
			return (lhs.c == rhs.c);
		}
		friend bool operator<(const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs)
		{
			return (lhs.c < rhs.c);
		}

	protected:

		Container c;

	public:

		explicit stack(const Container& cont = Container() ) : c(cont)
		{
		}

		stack(const stack& other) : c(other.c)
		{
		}

		~stack(void)
		{
		}

		stack&	operator=(const stack& other)
		{
			c = other.c;
		}

		T&			top(void)
		{
			return (c.back());
		}

		const T&	top(void) const
		{
			return (c.back());
		}

		bool		empty(void) const
		{
			return (c.empty());
		}

		size_type	size(void) const
		{
			return (c.size());
		}

		void		push(const value_type& value)
		{
			c.push_back(value);
		}

		void		pop(void)
		{
			c.pop_back();
		}

	};

	template <class T, class Container>
	bool operator!=(const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs)
	{
		return (!(lhs == rhs));
	}
	
	template <class T, class Container>
	bool operator<=(const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs)
	{
		return (lhs < rhs || lhs == rhs);
	}

	template <class T, class Container>
	bool operator>(const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs)
	{
		return (!(lhs < rhs || lhs == rhs));
	}

	template <class T, class Container>
	bool operator>=(const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs)
	{
		return (!(lhs < rhs));
	}
}

#endif