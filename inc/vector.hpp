/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesoeuv <mdesoeuv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 14:12:39 by mdesoeuv          #+#    #+#             */
/*   Updated: 2022/04/25 15:47:41 by mdesoeuv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

namespace ft
{
	template <class T, class Allocator = std::allocator<T> >
	class vector
	{
		
		/* ---------- member types ---------- */
		
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
		
		private:

			T*			c;
			size_type	size;
			size_type	allocated_size;
		
		public:

		/* ---------- constructors + destructor ---------- */
		
			vector(void)
			{
				
			}

			explicit vector(const Allocator& alloc)
			{
				
			}

			explicit vector( size_type count, const T& value = T(), const Allocator& alloc = Allocator())
			{
				
			}
			
			explicit vector(size_type count)
			{
				allocated_size = count;
				c = new T[count];
			}
			
			template< class InputIt >
			vector( InputIt first, InputIt last, const Allocator& alloc = Allocator() )
			{
				
			}

			vector( const vector& other )
			{
				
			}

			~vector(void)
			{
				delete[] c;
			}

		/* ---------- basic functions ---------- */

			vector&	operator=(const vector& other)
			{
				delete[] c;
				size = other.size;
				allocated_size = other.allocated_size;
				c = new T[allocated_size];
				for (size_t i = 0; i < size; ++i)
				{
					c[i] = other.c[i];
				}
			}

			void	assign(size_type count, const T& value)
			{
				delete[] c;
				size = count;
				allocated_size = count;
				c = new T[count];
				for (size_t i = 0; i < count; ++i)
				{
					c[i] = value;
				}
			}

			template< class InputIt >
			void assign(InputIt first, InputIt last)
			{
				size_type	range = 0;
				size_type	i = 0;
				
				delete[] c;
				for (InputIt inc = first; inc != last; ++inc)
				{
					range++;
				}
				size = range;
				allocated_size = range;
				c = new T[range];
				for (InputIt inc = first; inc != last; ++inc)
				{
					c[i++] = *inc;
				}
			}

			allocator_type get_allocator() const
			{
				return (allocator_type);
			}
		
		/* ---------- element access ---------- */

		
	};
}

#endif
