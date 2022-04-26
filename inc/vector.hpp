/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesoeuv <mdesoeuv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 14:12:39 by mdesoeuv          #+#    #+#             */
/*   Updated: 2022/04/26 15:12:06 by mdesoeuv         ###   ########lyon.fr   */
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
		// typedef std::iterator_traits<std::iterator<std::random_access_iterator_tag, value_type> > iterator; // to replace by ft::iterator_traits<It>
		// typedef std::iterator_traits<std::iterator<std::random_access_iterator_tag, const value_type> > const_iterator; // to replace by ft::iterator_traits<It>
		// typedef std::reverse_iterator<std::iterator> reverse_iterator;
		// typedef std::reverse_iterator<std::const_iterator> const_reverse_iterator;
		
		private:

			T*				c;
			size_type		_size;
			size_type		allocated_size;
			allocator_type	alloc;
		
		public:

			class Iterator
			{
				private:

					vector<T, Allocator>&		v;
					size_type					size;
					size_type					offset;
					T*							ptr;
					

				public:

					Iterator(vector<T, Allocator>& vector, size_type size) : v(vector), size(size), offset(0)
					{
						ptr = vector.data();
					}

					Iterator(vector<T, Allocator>& vector, size_type size, size_type offset) : v(vector), size(size), offset(offset)
					{
						ptr = vector.data() + offset;
					}
					
					Iterator(const Iterator& other) : v(other.v), size(other.size), offset(other.offset), ptr(other.ptr)
					{}
					
					~Iterator(void)
					{}
					
					Iterator&	operator=(const Iterator& rhs)
					{
						v = rhs.v;
						size = rhs.size;
						offset = rhs.offset;
						ptr = rhs.ptr;
					}

					Iterator	operator++(void)
					{
						ptr++;
						offset++;
						return (*this);
					}
				
			};
		
		/* ---------- constructors + destructor ---------- */
		
			vector(void) : c(NULL), _size(0), allocated_size(0)
			{}

			explicit vector(const Allocator& alloc) : c(NULL), _size(0), allocated_size(0), alloc(alloc)
			{	
			}

			explicit vector( size_type count, const T& value = T(), const Allocator& alloc = Allocator()) : _size(count), allocated_size(count), alloc(alloc)
			{
				try
				{
					c = alloc.allocate(count);
					for (size_type i = 0; i < count; ++i)
					{
						c[i] = value;
					}
				}
				catch(const std::bad_alloc& e)
				{
					std::cerr << e.what() << std::endl;
					_size = 0;
					allocated_size = 0;
				}
			}
			
			explicit vector(size_type count) : allocated_size(count)
			{
				try
				{
					c = alloc.allocate(count);
				}
				catch(const std::bad_alloc& e)
				{
					std::cerr << e.what() << std::endl;
					_size = 0;
					allocated_size = 0;
				}
			}
			
			template <class InputIt>
			vector( InputIt first, InputIt last, const Allocator& alloc = Allocator() ) : alloc(alloc)
			{
				size_type	range = 0;
				size_type	i = 0;
				
				for (InputIt inc = first; inc != last; ++inc)
				{
					range++;
				}
				_size = range;
				allocated_size = range;
				try
				{
					c = alloc.allocate(range);
					for (InputIt inc = first; inc != last; ++inc)
					{
						c[i++] = *inc;
					}
				}
				catch(const std::bad_alloc& e)
				{
					std::cerr << e.what() << '\n';
					_size = 0;
					allocated_size = 0;
				}
				
			}

			vector(const vector& other) : _size(other._size), allocated_size(other.allocated_size)
			{
				try
				{
					c = alloc.allocate(allocated_size);
					for (size_type i = 0; i < _size; ++i)
					{
						c[i] = other.c[i];
					}
				}
				catch(const std::bad_alloc& e)
				{
					std::cerr << e.what() << std::endl;
					_size = 0;
					allocated_size = 0;
				}
			}

			~vector(void)
			{
				alloc.deallocate(c, allocated_size);
			}

		/* ---------- basic functions ---------- */

			vector&	operator=(const vector& other)
			{
				T*	old_c = c;
				
				try
				{
					c = alloc.allocate(allocated_size);
					for (size_t i = 0; i < other._size; ++i)
					{
						c[i] = other.c[i];
					}
					_size = other._size;
					allocated_size = other.allocated_size;
					alloc.deallocate(old_c, allocated_size);
				}
				catch (const std::bad_alloc& e)
				{
					std::cerr << e.what() << std::endl;
					c = old_c;
				}
				return (*this);
			}

			void	assign(size_type count, const T& value)
			{
				T*	old_c = c;

				try
				{
					c = alloc.allocate(count);
					for (size_t i = 0; i < count; ++i)
					{
						c[i] = value;
					}
					alloc.deallocate(old_c, allocated_size);
					_size = count;
					allocated_size = count;
				}
				catch (const std::bad_alloc& e)
				{
					std::cerr << e.what() << std::endl;
					c = old_c;
				}
			}

			template <class InputIt>
			void assign(InputIt first, InputIt last)
			{
				size_type	range = 0;
				size_type	i = 0;
				T*			old_c = c;
				
				try
				{
					for (InputIt inc = first; inc != last; ++inc)
					{
						range++;
					}
					c = alloc.allocate(range);
					for (InputIt inc = first; inc != last; ++inc)
					{
						c[i++] = *inc;
					}
					alloc.deallocate(old_c, allocated_size);
					_size = range;
					allocated_size = range;
				}
				catch (const std::bad_alloc& e)
				{
					std::cerr << e.what() << std::endl;
					c = old_c;
				}
			}

			allocator_type get_allocator(void) const
			{
				return (this->allocator_type);
			}
		
		/* ---------- element access ---------- */

			reference	at(size_type pos)
			{
				if (pos >= _size)
					throw std::out_of_range("position out of vector's range");
				return (c[pos]);
			}
			
			const_reference	at(size_type pos) const
			{		
				if (pos >= _size)
					throw std::out_of_range("position out of vector's range");
				return (c[pos]);	
			}
			
			reference	operator[](size_type pos)
			{
				return (c[pos]);
			}

			const_reference	operator[](size_type pos) const
			{
				return (c[pos]);
			}

			reference	front(void)
			{
				// if (_size == 0)	// to avoid undefined behavior
				// 	return (0);
				return (c[0]);
			}

			const_reference	front(void) const
			{
				// if (_size == 0)
				// 	return (0);
				return (c[0]);
			}

			reference	back(void)
			{
				// if (_size == 0)	// to avoid undefined behavior
				// 	return (0);
				return (c[_size - 1]);
			}

			const_reference	back(void) const
			{
				// if (_size == 0)	// to avoid undefined behavior
				// 	return (0);
				return (c[_size - 1]);
			}

			T*	data(void)
			{
				return (c);
			}

			const T*	data(void) const
			{
				return (c);
			}

		/* ---------- Iterators ---------- */

			Iterator	begin(void)
			{
				Iterator it(*this, _size, 0);
				return (it);
			}
			
			// const_iterator begin(void) const
			// {
			// 	Iterator It(*this, size, 0);
			// 	return (It);
			// }

			Iterator	end(void)
			{
				Iterator it(*this, _size, _size);
				return (it);
			}

			// const_iterator	end(void)
			// {
			// 	Iterator It(*this, size, size);
			// 	return (It);
			// }

			// reverse_iterator	rbegin(void)
			// {
			// 	reverse_iterator	it(*this, size, 0);
			// 	return (it)
			// }

			// const_reverse_iterator rbegin() const
			// {
			// 	const_reverse_iterator	it(*this, size, 0);
			// 	return (it)
			// }

			// reverse_iterator	rend(void)
			// {
			// 	reverse_iterator	it(*this, size, size);
			// 	return (it)
			// }

			// const_reverse_iterator	rend(void)
			// {
			// 	const_reverse_iterator	it(*this, size, size);
			// 	return (it)
			// }

		/* ---------- Capacity ---------- */

			bool	empty(void) const
			{
				if (_size == 0)
					return (true);
				return (false);
			}
			
			size_type	size(void) const
			{
				return (_size);
			}
			
			size_type	max_size(void) const
			{
				return (std::numeric_limits<difference_type>::max());
			}

			void	reserve(size_type new_cap)
			{
				T*	old_c = c;
				
				if (new_cap <= allocated_size)
					return ;
				try
				{
					if (new_cap > max_size())
						throw std::length_error("requested capacity exceeds max capacity");
					c = alloc.allocate(new_cap);
					for (size_type i = 0; i < _size; ++i)
					{
						c[i] = old_c[i];
					}
					alloc.deallocate(old_c, allocated_size);
					allocated_size = new_cap;
				}
				catch (std::length_error& e)
				{
					std::cout << e.what() << std::endl;
				}
				catch  (std::bad_alloc& e)
				{
					std::cout << e.what() << std::endl;
					c = old_c;
				}
			}

			size_type	capacity(void) const
			{
				return (allocated_size);
			}

		/* ---------- Modifiers ---------- */
			
			void	clear(void)
			{
				// for (size_type i = 0; i < size; ++i)
				// {
				// 	c[i] = 0;
				// }
				_size = 0;
			}

			Iterator	insert(Iterator pos, const T& value)
			{
				T*	old_c = c;
				size_type	index = 0;
				
				if (_size == allocated_size)
				{
					try
					{
						if (allocated_size != 0)
							c = alloc.allocate(allocated_size * 2);
						else
							c = alloc.allocate(1);
						for (Iterator iter = this->begin(); iter != pos; ++iter)
						{
							index++;
						}
						for (size_type i = 0; i < index; ++i)
						{
							c[i] = old_c[i];
						}
						c[index] = value;
						for (size_type i = index + 1; i < _size + 1; ++i)
						{
							c[i] = old_c[i - 1];
						}
						alloc.deallocate(old_c, allocated_size);
						if (_size != 0)
							allocated_size = allocated_size * 2;
						else
							allocated_size = 1;
						_size++;
					}
					catch (std::bad_alloc& e)
					{
						std::cout << e.what() << std::endl;
						c = old_c;
						return (pos);
					}
				}
				else
				{
					for (Iterator iter = this->begin(); iter != pos; ++iter)
					{
						index++;
					}
					for (size_type i = 0; i < index; ++i)
					{
						c[i] = old_c[i];
					}
					c[index] = value;
					for (size_type i = index + 1; i < _size + 1; ++i)
					{
						c[i] = old_c[i - 1];
					}
					_size++;
				}
				return (--pos);
			}
			
			void insert(Iterator pos, size_type count, const T& value)
			{
				T*	old_c = c;
				size_type	index = 0;
				
				if (_size + count < allocated_size)
				{
					try
					{
						if (allocated_size != 0)
							c = alloc.allocate(allocated_size + count);
						else
							c = alloc.allocate(count);
						for (Iterator iter = this->begin(); iter != pos; ++iter)
						{
							index++;
						}
						for (size_type i = 0; i < index; ++i)
						{
							c[i] = old_c[i];
						}
						for (size_type i = 0; i < count; ++i)
						{
							c[index++] = value;
						}
						for (size_type i = index; i < _size + count; ++i)
						{
							c[i] = old_c[i - count];
						}
						alloc.deallocate(old_c, allocated_size);
						if (_size != 0)
							allocated_size += count;
						else
							allocated_size = count;
						_size += count;
					}
					catch (std::bad_alloc& e)
					{
						std::cout << e.what() << std::endl;
						c = old_c;
					}
				}
				else
				{
					for (Iterator iter = this->begin(); iter != pos; ++iter)
					{
						index++;
					}
					for (size_type i = 0; i < index; ++i)
					{
						c[i] = old_c[i];
					}
					for (size_type i = 0; i < count; ++i)
					{
						c[index++] = value;
					}
					for (size_type i = index; i < _size + count; ++i)
					{
						c[i] = old_c[i - count];
					}
					_size += count;
				}
			}

			template< class InputIt >
			void insert( Iterator pos, InputIt first, InputIt last )
			{
				size_type	count = 0;
				T*			old_c = c;
				size_type	index = 0;

				for (InputIt iter = first; iter != last; ++iter)
				{
					count++;
				}
				if (_size + count < allocated_size)
				{
					try
					{
						if (allocated_size != 0)
							c = alloc.allocate(allocated_size + count);
						else
							c = alloc.allocate(count);
						for (Iterator iter = this->begin(); iter != pos; ++iter)
						{
							index++;
						}
						for (size_type i = 0; i < index; ++i)
						{
							c[i] = old_c[i];
						}
						for (size_type i = 0; i < count; ++i)
						{
							c[index++] = *first;
							first++;
						}
						for (size_type i = index; i < _size + count; ++i)
						{
							c[i] = old_c[i - count];
						}
						alloc.deallocate(old_c, allocated_size);
						if (_size != 0)
							allocated_size += count;
						else
							allocated_size = count;
						_size += count;
					}
					catch (std::bad_alloc& e)
					{
						std::cout << e.what() << std::endl;
						c = old_c;
					}
				}
				else
				{
					for (Iterator iter = this->begin(); iter != pos; ++iter)
					{
						index++;
					}
					for (size_type i = 0; i < index; ++i)
					{
						c[i] = old_c[i];
					}
					for (size_type i = 0; i < count; ++i)
					{
						c[index++] = *first;
						first++;
					}
					for (size_type i = index; i < _size + count; ++i)
					{
						c[i] = old_c[i - count];
					}
					_size += count;
				}
				
			}

			Iterator erase(Iterator pos)
			{
				Iterator	index = this->begin();
				Iterator	save_pos = pos;

				if (pos == this->end())
				{
					std::cout << "invalid iterator pos" << std::endl;
					return (pos);
				}
				while (index != pos)
					index++;
				++pos;
				while (pos != this->end())
				{
					*index = *pos;
					++index;
					++pos;
				}
				_size--;
				return (save_pos);
			}

			Iterator erase(Iterator first, Iterator last)
			{
				Iterator	index = this->begin();
				Iterator	save_pos = last;
				size_type	range = 0;

				if (first == last)
					return (last);
				for (Iterator iter = first; iter != last; ++iter)
				{
					range++;
				}
				if (first == this->end())
				{
					std::cout << "invalid iterator pos" << std::endl;
					return (this->end());
				}
				while (index != first)
					index++;
				while (last != this->end())
				{
					*first = *last;
					++first;
					++last;
				}
				_size -= range;
				return (save_pos);
			}

			void	push_back(const T& value)
			{
				T*	old_c = c;
				
				if (_size == allocated_size)
				{
					try
					{
						if (allocated_size != 0)
						{
							if (allocated_size * 2 > max_size())
								throw std::length_error("requested capacity exceeds max capacity");
							c = alloc.allocate(allocated_size * 2);
						}
						else
							c = alloc.allocate(1);
						for (size_type i = 0; i < _size; ++i)
						{
							c[i] = old_c[i];
						}
						alloc.deallocate(old_c, allocated_size);
						if (_size != 0)
							allocated_size = allocated_size * 2;
						else
							allocated_size = 1;
					}
					catch (std::length_error& e)
					{
						std::cout << e.what() << std::endl;
						return ;
					}
					catch (std::bad_alloc& e)
					{
						std::cout << e.what() << std::endl;
						c = old_c;
						return ;
					}
				}
				c[_size] = value;
				_size++;
			}

			void	pop_back(void)
			{
				if (_size == 0)
					return ;
				// c[size - 1] = 0;
				_size--;
			}

			void resize(size_type count, T value = T() )
			{
				T*	old_c = c;
				
				if (_size >= count)
				{
					_size = count;
					return ;
				}
				if (allocated_size < count)
				{
				try
					{
						if (allocated_size != 0)
						{
							if (allocated_size * 2 > max_size())
								throw std::length_error("requested capacity exceeds max capacity");
							c = alloc.allocate(allocated_size * 2);
						}
						else
							c = alloc.allocate(count);
						for (size_type i = 0; i < _size; ++i)
						{
							c[i] = old_c[i];
						}
						alloc.deallocate(old_c, allocated_size);
						if (_size != 0)
							allocated_size = allocated_size * 2;
						else
							allocated_size = count;
					}
					catch (std::length_error& e)
					{
						std::cout << e.what() << std::endl;
						return ;
					}
					catch (std::bad_alloc& e)
					{
						std::cout << e.what() << std::endl;
						c = old_c;
						return ;
					}
					for (size_type i = _size; i < count; ++i)
					{
						c[i] = value;
					}
					_size = count;
				}
			}

			void	swap(vector& other)
			{
				T*	temp = other.c;

				other.c = this->c;
				this->c = temp;
			}

	};
}

#endif
