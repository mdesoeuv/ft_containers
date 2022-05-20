/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Reverse_Iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesoeuv <mdesoeuv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 14:45:44 by mdesoeuv          #+#    #+#             */
/*   Updated: 2022/05/20 17:26:40 by mdesoeuv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "iterator_traits.hpp"

namespace ft
{
	template <typename Iter>
	class	Reverse_Iterator
	{
		protected:

			Iter	current;

		public:

			typedef typename ft::iterator_traits<Iter>::iterator_category	iterator_category;
			typedef typename ft::iterator_traits<Iter>::value_type			value_type;
			typedef typename ft::iterator_traits<Iter>::difference_type		difference_type;
			typedef typename ft::iterator_traits<Iter>::pointer				pointer;
			typedef typename ft::iterator_traits<Iter>::reference			reference;	

			Reverse_Iterator(void) : current()
			{}

			Reverse_Iterator(Iter iter) : current(iter)
			{}

			Reverse_Iterator(const Reverse_Iterator& other) : current(other.current)
			{}

			template <class U>
			Reverse_Iterator(const Reverse_Iterator<U>& other) : current(other.current)
			{}

			~Reverse_Iterator(void)
			{}

			Reverse_Iterator&	operator=(const Reverse_Iterator& rhs)
			{
				current = rhs.current;
				
				return (*this);
			}

			Iter	base(void) const
			{
				return (current);
			}

			Reverse_Iterator&	operator++(void)
			{
				--current;
				return (*this);
			}

			Reverse_Iterator	operator++(int)
			{
				Reverse_Iterator	temp(*this);
				
				--current;
				return (temp);
			}

			Reverse_Iterator&	operator--(void)
			{
				++current;
				return (*this);
			}

			Reverse_Iterator	operator--(int)
			{
				Reverse_Iterator	temp(*this);
				
				++current;
				return (temp);
			}

			reference	operator*(void)
			{
				Iter temp(current);
				
				temp--;
				return (*(temp));
			}

			pointer	operator->(void)
			{
				return (&(operator*()));
			}

			Reverse_Iterator operator+ (difference_type n) const
			{
				Reverse_Iterator	iter(current - n);
				return (iter);
			}

			friend Reverse_Iterator operator+ (difference_type n, const Reverse_Iterator rhs)
			{
				return (rhs + n);
			}

			Reverse_Iterator&	operator+=(difference_type n)
			{
				current -= n;
				return (*this);
			}

			Reverse_Iterator&	operator-=(difference_type n)
			{
				current += n;
				return (*this);
			}

			Reverse_Iterator	operator-(difference_type n) const
			{
				Reverse_Iterator	iter(current + n);
				return (iter);
			}

			friend difference_type	operator-(const Reverse_Iterator lhs, const Reverse_Iterator rhs)
			{
				return (rhs.current - lhs.current);
			}

			reference	operator[](difference_type n) const
			{
				return (*(current - n - 1));
			}

			template< class Iterator1, class Iterator2 >
			friend	bool operator== (const Reverse_Iterator<Iterator1> lhs, const Reverse_Iterator<Iterator2> rhs)
			{
				return (lhs.base() == rhs.base());
			}

			template< class Iterator1, class Iterator2 >
			friend	bool operator!= (const Reverse_Iterator<Iterator1> lhs, const Reverse_Iterator<Iterator2> rhs)
			{
				return (lhs.base() != rhs.base());
			}

			template< class Iterator1, class Iterator2 >
			friend	bool operator< (const Reverse_Iterator<Iterator1> lhs, const Reverse_Iterator<Iterator2> rhs)
			{
				return (lhs.base() > rhs.base());
			}

			template< class Iterator1, class Iterator2 >
			friend	bool operator<= (const Reverse_Iterator<Iterator1> lhs, const Reverse_Iterator<Iterator2> rhs)
			{
				return (lhs.base() >= rhs.base());
			}

			template< class Iterator1, class Iterator2 >
			friend	bool operator> (const Reverse_Iterator<Iterator1> lhs, const Reverse_Iterator<Iterator2> rhs)
			{
				return (lhs.base() < rhs.base());
			}

			template< class Iterator1, class Iterator2 >
			friend	bool operator>= (const Reverse_Iterator<Iterator1> lhs, const Reverse_Iterator<Iterator2> rhs)
			{
				return (lhs.base() <= rhs.base());
			}
			
			

	};
}
