/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesoeuv <mdesoeuv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 14:12:39 by mdesoeuv          #+#    #+#             */
/*   Updated: 2022/04/25 14:56:18 by mdesoeuv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

namespace ft
{
	template <class T, class Allocator = std::allocator<T> >
	class vector
	{
		
		typedef	T value_type;
		typedef Allocator allocator_type;
		typedef std::size_t size_type;
		typedef std::ptrdiff_t difference_type;
		typedef value_type& reference;
		typedef const value_type& const_reference;
		typedef typename Allocator::pointer pointer;
		typedef typename Allocator::const_pointer const_pointer;
		typedef std::iterator_traits<std::iterator<std::random_access_iterator_tag, value_type> > iterator; // to replace by ft::iterator_traits<It>
		typedef std::iterator_traits<std::iterator<std::random_access_iterator_tag, const value_type> > const_iterator; // to replace by ft::iterator_traits<It>
		typedef std::reverse_iterator<iterator> reverse_iterator;
		typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
		
		
	};
}

#endif
