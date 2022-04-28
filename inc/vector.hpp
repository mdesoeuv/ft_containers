/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesoeuv <mdesoeuv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 14:12:39 by mdesoeuv          #+#    #+#             */
/*   Updated: 2022/04/28 17:27:55 by mdesoeuv         ###   ########lyon.fr   */
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
		
			template <typename BidirectionalItA, typename InputItB>
			void init(BidirectionalItA start_a, InputItB start_b, InputItB end_b, Allocator alloc) {
				BidirectionalItA cursor = start_a;
				try {
					for (; start_b != end_b; ++cursor, ++start_b)
						alloc.construct(&*cursor, *start_b);
				} catch (...) {
					while (cursor != start_a)
						alloc.destroy(&*--cursor);
					throw ;
				}
			}
		
			template <typename BidirectionalItA>
			void init(BidirectionalItA start, BidirectionalItA end, T value = T(), Allocator alloc = Allocator()) {
				BidirectionalItA cursor = start;
				try {
					for (; cursor != end; ++cursor)
					{
						alloc.construct(&*cursor, value);
					}
				} catch (...) {
					while (cursor != start)
						alloc.destroy(&*--cursor);
					throw ;
				}
			}
		
			template <typename BidirectionalItA>
			void destroy(BidirectionalItA start, BidirectionalItA end, Allocator alloc = Allocator())
			{
				BidirectionalItA cursor = end;
				while (cursor != start)
					alloc.destroy(&*--cursor);
			}

		public:

			class Iterator
			{
				protected:

					T*		ptr;
					

				public:

					Iterator(void)
					{
						ptr = NULL;
					}

					Iterator(vector& vector)
					{
						ptr = vector.data();
					}

					Iterator(vector& vector, size_type offset)
					{
						ptr = vector.data() + offset;
					}
					
					Iterator(const Iterator& other) : ptr(other.ptr)
					{}
					
					~Iterator(void)
					{}
					
					Iterator&	operator=(const Iterator& rhs)
					{
						ptr = rhs.ptr;

						return (*this);
					}

					bool	operator==(const Iterator& rhs)
					{
						return (ptr == rhs.ptr);
					}

					bool	operator!=(const Iterator& rhs)
					{
						return (!(ptr == rhs.ptr));
					}

					Iterator&	operator++(void)
					{
						ptr++;
						return (*this);
					}

					Iterator	operator++(int)
					{
						Iterator	it_temp = *this;
						
						ptr++;
						return (it_temp);
					}

					Iterator&	operator--(void)
					{
						ptr--;
						return (*this);
					}

					Iterator	operator--(int)
					{
						Iterator	it_temp = *this;

						ptr--;
						return (it_temp);
					}

					Iterator&	operator+=(difference_type n)
					{
						ptr += n;
						return (*this);
					}

					Iterator&	operator-=(difference_type n)
					{
						ptr -= n;
						return (*this);
					}

					friend Iterator	operator+(const Iterator& lhs, difference_type n)
					{
						Iterator	iter(lhs);
						
						iter += n;
						return (iter);
					}

					friend Iterator	operator+(difference_type n, const Iterator& rhs)
					{
						Iterator	iter(rhs);
						
						iter += n;
						return (iter);
					}

					friend Iterator	operator-(const Iterator& lhs, difference_type n)
					{
						Iterator	iter(lhs);
						
						iter -= n;
						return (iter);
					}

					friend Iterator	operator-(const Iterator& lhs, const Iterator& rhs)
					{
						Iterator	iter(lhs);
						
						iter.ptr -= rhs.ptr;
						return (iter);
					}

					T&	operator*(void)
					{
						return (*ptr);
					}

					T*	operator->(void)
					{
						return (ptr);
					}

					bool	operator<(const Iterator& rhs)
					{
						return (ptr < rhs.ptr);
					}

					bool	operator<=(const Iterator& rhs)
					{
						return (ptr <= rhs.ptr);
					}

					bool	operator>(const Iterator& rhs)
					{
						return (ptr > rhs.ptr);
					}

					bool	operator>=(const Iterator& rhs)
					{
						return (ptr >= rhs.ptr);
					}

					T&		operator[](difference_type	n)
					{
						return (*(ptr + n));
					}
					
				
			};
		
			class Const_Iterator
			{
				protected:

					const T*		ptr;
					

				public:

					Const_Iterator(void)
					{
						ptr = NULL;
					}

					Const_Iterator(const vector& vector)
					{
						ptr = vector.data();
					}

					Const_Iterator(const vector& vector, size_type offset)
					{
						ptr = vector.data() + offset;
					}
					
					Const_Iterator(const Const_Iterator& other) : ptr(other.ptr)
					{}
					
					~Const_Iterator(void)
					{}
					
					Const_Iterator&	operator=(const Const_Iterator& rhs)
					{
						ptr = rhs.ptr;

						return (*this);
					}

					bool	operator==(const Const_Iterator& rhs)
					{
						return (ptr == rhs.ptr);
					}

					bool	operator!=(const Const_Iterator& rhs)
					{
						return (!(ptr == rhs.ptr));
					}

					Const_Iterator&	operator++(void)
					{
						ptr++;
						return (*this);
					}
					
					Const_Iterator	operator++(int)
					{
						Const_Iterator	it_temp = *this;
						
						ptr++;
						return (it_temp);
					}

					Const_Iterator&	operator--(void)
					{
						ptr--;
						return (*this);
					}
					
					Const_Iterator	operator--(int)
					{
						Const_Iterator	it_temp = *this;
						
						ptr--;
						return (it_temp);
					}

					const T&	operator*(void)
					{
						return (*ptr);
					}

					const T*	operator->(void)
					{
						return (ptr);
					}
					
					Const_Iterator&	operator+=(difference_type n)
					{
						ptr += n;
						return (*this);
					}

					Const_Iterator&	operator-=(difference_type n)
					{
						ptr -= n;
						return (*this);
					}

					friend Const_Iterator	operator+(const Const_Iterator& lhs, difference_type n)
					{
						Const_Iterator	iter(lhs);
						
						iter += n;
						return (iter);
					}

					friend Const_Iterator	operator+(difference_type n, const Const_Iterator& rhs)
					{
						Const_Iterator	iter(rhs);
						
						iter += n;
						return (iter);
					}


					friend Const_Iterator	operator-(const Const_Iterator& lhs, difference_type n)
					{
						Const_Iterator	iter(lhs);
						
						iter -= n;
						return (iter);
					}

					friend Const_Iterator	operator-(const Const_Iterator& lhs, const Const_Iterator& rhs)
					{
						Const_Iterator	iter(lhs);
						
						iter.ptr -= rhs.ptr;
						return (iter);
					}


					bool	operator<(const Const_Iterator& rhs)
					{
						return (ptr < rhs.ptr);
					}

					bool	operator<=(const Const_Iterator& rhs)
					{
						return (ptr <= rhs.ptr);
					}

					bool	operator>(const Const_Iterator& rhs)
					{
						return (ptr > rhs.ptr);
					}

					bool	operator>=(const Const_Iterator& rhs)
					{
						return (ptr >= rhs.ptr);
					}

					const T&	operator[](difference_type	n)
					{
						return (*(ptr + n));
					}

			};

			class	Reverse_Iterator : public Iterator
			{
				protected:

					Iterator	current;

				public:

					Reverse_Iterator(void) : Iterator()
					{}

					Reverse_Iterator(Iterator iter) : Iterator(iter), current(iter)
					{}

					Reverse_Iterator(const Reverse_Iterator& other) : Iterator(other), current(other.current)
					{}

					~Reverse_Iterator(void)
					{}

					Reverse_Iterator&	operator=(const Reverse_Iterator& rhs)
					{
						current = rhs.current;
						
						return (*this);
					}

					Iterator	base(void) const
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

					T&	operator*(void)
					{
						return (*(current - 1));
					}

					bool	operator==(const Reverse_Iterator& rhs)
					{
						return (current == rhs.current);
					}

					bool	operator!=(const Reverse_Iterator& rhs)
					{
						return (!(current == rhs.current));
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
					c = this->alloc.allocate(count);
					
					Iterator	start = this->begin();
					
					init(start, start + count, value, alloc);
				}
				catch(...)
				{
					_size = 0;
					allocated_size = 0;
				}
			}
			
			template <class InputIt>
			vector( InputIt first, InputIt last, const Allocator& alloc = Allocator() ) : alloc(alloc)
			{
				size_type	count = 0;
				
				for (InputIt inc = first; inc != last; ++inc)
				{
					count++;
				}
				try
				{
					c = this->alloc.allocate(count);
					Iterator start = this->begin();
					init(start, first, last, this->alloc);
				}
				catch(...)
				{
					_size = 0;
					allocated_size = 0;
				}
				allocated_size = count;
				_size = count;
				
			}


			vector(const vector& other) : _size(0), allocated_size(other.allocated_size), alloc(other.alloc)
			{
				try
				{
					c = alloc.allocate(allocated_size);
					init(begin(), other.begin(), other.end(), alloc);
				} 
				catch (...)
				{
					alloc.deallocate(c, allocated_size);
					throw ;
				}
				_size = other.size();
			}

			~vector(void)
			{
				Iterator	start = this->begin();
				Iterator	end = this->end();
				destroy(start, end, alloc);
				alloc.deallocate(c, allocated_size);
			}

		/* ---------- basic functions ---------- */

			vector&	operator=(const vector& other)
			{
				// operator= devrait seulement allouer si besion
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

			// Attention dans le cas d'un vector<size_t>
			// l'appelle de la fonction assign d'au dessus de ne se fera jamais
			// if faut ruser a coup de enable_if (ou autre astuce....) :^)
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
				return (c[0]);
			}

			const_reference	front(void) const
			{
				return (c[0]);
			}

			reference	back(void)
			{
				return (c[_size - 1]);
			}

			const_reference	back(void) const
			{
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
				Iterator it(*this, 0);
				return (it);
			}
			
			Const_Iterator begin(void) const
			{
				Const_Iterator It(*this, 0);
				return (It);
			}

			Iterator	end(void)
			{
				Iterator it(*this, _size);
				return (it);
			}

			Const_Iterator	end(void) const
			{
				Const_Iterator It(*this, _size);
				return (It);
			}

			Reverse_Iterator	rbegin(void)
			{
				Reverse_Iterator	it(this->end());
				return (it);
			}

			// const_reverse_iterator rbegin() const
			// {
			// 	const_reverse_iterator	it(*this, size, 0);
			// 	return (it);
			// }

			Reverse_Iterator	rend(void)
			{
				Reverse_Iterator	it(this->begin());
				return (it);
			}

			// const_reverse_iterator	rend(void)
			// {
			// 	const_reverse_iterator	it(*this, size, size);
			// 	return (it);
			// }

		/* ---------- Capacity ---------- */

			bool	empty(void) const
			{
				return (_size == 0);
			}
			
			size_type	size(void) const
			{
				return (_size);
			}
			
			size_type	max_size(void) const
			{
				return (alloc.max_size());
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
				for (size_type i = 0; i < _size; ++i)
				{
					alloc.destroy(&c[i]);
				}
				_size = 0;

			}

			Iterator	insert(Iterator pos, const T& value)
			{
				T*	old_c = c;
				size_type	index = 0;
				T			temp_value;
				T			temp_value_bis;
				
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
					temp_value = c[index];
					c[index] = value;
					for (size_type i = index + 1; i < _size + 1; ++i)
					{
						temp_value_bis = c[i];
						c[i] = temp_value;
						temp_value = c[i + 1];
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

			Iterator erase(Iterator pos) // detruire elements avec alloc.destroy
			{
				Iterator	index = this->begin();
				Iterator	save_pos = pos;

				if (pos == this->end())
				{
					std::cout << "invalid iterator pos" << std::endl;
					return (pos);
				}
				while (index != pos)
					++index;
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

			Iterator erase(Iterator first, Iterator last) // alloc.destroy
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
					++index;
				while (last != this->end())
				{
					*first = *last;
					++first;
					++last;
				}
				_size -= range;
				return (save_pos);
			}

			void	push_back(const T& value) // ne desallouer qu'a la toute fin pour pouvoir revenir en arriere 
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

			void	pop_back(void) // alloc.destroy
			{
				if (_size == 0)
					return ;
				// c[size - 1] = 0;
				_size--;
			}

			void resize(size_type count, T value = T() ) // alloc.construct alloc.destroy catch constructor
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
						if (allocated_size != 0)
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
				}
				for (size_type i = _size; i < count; ++i)
				{
					c[i] = value;
				}
				_size = count;
			}

			void	swap(vector& other)
			{
				T*	temp_data = other.c;
				size_type allocated_size_temp = other.allocated_size;
				size_type size_temp = other._size;

				
				other.c = this->c;
				this->c = temp_data;

				other.allocated_size = this->allocated_size;
				this->allocated_size = allocated_size_temp;

				other._size = this->_size;
				this->_size = size_temp;
			}

	};

	template <class T, class Alloc>
  	bool	operator==(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		typename ft::vector<T, Alloc>::Const_Iterator	start_l = lhs.begin();
		typename ft::vector<T, Alloc>::Const_Iterator	start_r = rhs.begin();
		typename ft::vector<T, Alloc>::Const_Iterator	end_l = lhs.end();
		
		if (lhs.size() != rhs.size())
			return (false);
		while (start_l != end_l)
		{
			if (!(*start_l == *start_r))
				return (false);
			++start_l;
			++start_r;
		}
		return (true);
	}

	template <class T, class Alloc>
  	bool	operator!=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (!(lhs == rhs));
	}

	template <class T, class Alloc>
  	bool	operator<(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		typename ft::vector<T, Alloc>::Const_Iterator	start_l = lhs.begin();
		typename ft::vector<T, Alloc>::Const_Iterator	start_r = rhs.begin();
		typename ft::vector<T, Alloc>::Const_Iterator	end_l = lhs.end();
		typename ft::vector<T, Alloc>::Const_Iterator	end_r = rhs.end();
		
		
		while (start_l != end_l && start_r != end_r)
		{
			if (start_r == end_r || *start_r < *start_l)
				return (false);
			else if (*start_l < *start_r)
				return (true);
			++start_l;
			++start_r;
		}
		return (start_r != end_r); // returns true if lhs is shorter than rhs
	}

	template <class T, class Alloc>
  	bool	operator<=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (!(rhs < lhs));
	}

	template <class T, class Alloc>
  	bool	operator>(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (rhs < lhs);
	}

	template <class T, class Alloc>
  	bool	operator>=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (!(lhs < rhs));
	}
	
}

#endif
