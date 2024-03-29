/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesoeuv <mdesoeuv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 14:45:31 by mdesoeuv          #+#    #+#             */
/*   Updated: 2022/05/06 11:37:28 by mdesoeuv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

namespace ft
{
	template <class T1, class T2>
	struct pair
	{
		/* ----- member types ----- */

		typedef T1 first_type;
		typedef T2 second_type;

		/* ----- member variables ----- */

		first_type	first;
		second_type	second;

		/* ----- member functions ----- */

		pair (void) : first(T1()), second(T2())
		{
		}

		template <class U, class V>
		pair (const pair<U, V>& pr) : first(pr.first), second(pr.second)
		{
		}

		pair (const first_type& a, const second_type& b) : first(a), second(b)
		{
		}

		pair&	operator=(const pair& pr)
		{
			first = pr.first;
			second = pr.second;

			return (*this);
		}



	};

	template <class T1, class T2>
  	bool operator== (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{
		return (lhs.first == rhs.first && lhs.second == rhs.second);
	}

	template <class T1, class T2>
  	bool operator!= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{
		return (!(lhs == rhs));
	}

	template <class T1, class T2>
	bool operator<  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{
		return (lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second));
	}

	template <class T1, class T2>
  	bool operator<= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{
		return (!(rhs < lhs));
	}

	template <class T1, class T2>
  	bool operator>  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{
		return (rhs < lhs);
	}

	template <class T1, class T2>
  	bool operator>= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{
		return (!(lhs < rhs));
	}

	template <class T1,class T2>
  	pair<T1,T2> make_pair (T1 x, T2 y)
  	{
    	return (pair<T1,T2>(x, y));
  	}

}