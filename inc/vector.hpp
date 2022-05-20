/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesoeuv <mdesoeuv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 14:12:39 by mdesoeuv          #+#    #+#             */
/*   Updated: 2022/05/20 17:55:39 by mdesoeuv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP
# include "enable_if.hpp"
# include "Reverse_Iterator.hpp"
# include "is_integral.hpp"

namespace ft
{
	
	template <class T, class Allocator = std::allocator<T> >
	class vector
	{
		/* ---------- forward declarations ---------- */
		
		class Iterator;
		class Const_Iterator;
		
		/* ---------- member types ---------- */
		
		public:
		
			typedef	T value_type;
			typedef Allocator allocator_type;
			typedef std::size_t size_type;
			typedef std::ptrdiff_t difference_type;
			typedef value_type& reference;
			typedef const value_type& const_reference;
			typedef typename Allocator::pointer pointer;
			typedef typename Allocator::const_pointer const_pointer;
			typedef Iterator iterator;
			typedef Const_Iterator const_iterator;
			typedef typename ft::Reverse_Iterator<Iterator> reverse_iterator;
			typedef typename ft::Reverse_Iterator<Const_Iterator> const_reverse_iterator;
		
		private:

			T*				c;
			size_type		_size;
			size_type		allocated_size;
			allocator_type	alloc;
		
			template <typename BidirectionalItA, typename InputItB>
			void init(BidirectionalItA start_a, InputItB start_b, InputItB end_b, Allocator& alloc) {
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
			void init(BidirectionalItA start, BidirectionalItA end, T value, Allocator& alloc) {
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
			void destroy(BidirectionalItA start, BidirectionalItA end, Allocator& alloc)
			{
				BidirectionalItA cursor = end;
				while (cursor != start)
					alloc.destroy(&*--cursor);
			}

			void	prepare_alloc(size_type required_size)
			{
				if (allocated_size < required_size)
					reserve(std::max(allocated_size * 2, required_size));
			}

		private:

			class Iterator
			{
				protected:

					T*		ptr;
					

				public:

					typedef T									value_type;
					typedef T&									reference;
					typedef const T& 							const_reference;
					typedef T*									pointer;
					typedef std::random_access_iterator_tag 	iterator_category;
					typedef typename vector::difference_type	difference_type;
					
					explicit Iterator(T* ptr = NULL) : ptr(ptr)
					{
					}

					Iterator(const Iterator& other) : ptr(other.ptr)
					{}
					
					Iterator(const Const_Iterator& other) : ptr(other.ptr)
					{}
					
					~Iterator(void)
					{}
					
					Iterator&	operator=(const Iterator& rhs)
					{
						ptr = rhs.ptr;

						return (*this);
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

					friend Iterator	operator+(const Iterator lhs, difference_type n)
					{
						Iterator	iter(lhs);
						
						iter += n;
						return (iter);
					}

					friend Iterator	operator+(difference_type n, const Iterator rhs)
					{
						Iterator	iter(rhs);
						
						iter += n;
						return (iter);
					}

					friend Iterator	operator-(const Iterator lhs, difference_type n)
					{
						Iterator	iter(lhs);
						
						iter -= n;
						return (iter);
					}

					friend difference_type	operator-(const Iterator lhs, const Iterator rhs)
					{
						return (lhs.ptr - rhs.ptr);
					}

					T&	operator*(void)
					{
						return (*ptr);
					}

					T*	operator->(void)
					{
						return (ptr);
					}

					friend bool	operator==(const Iterator lhs, const Iterator rhs)
					{
						return (lhs.ptr == rhs.ptr);
					}

					friend bool	operator!=(const Iterator lhs, const Iterator rhs)
					{
						return (!(lhs.ptr == rhs.ptr));
					}

					friend bool	operator<(const Iterator lhs, const Iterator rhs)
					{
						return (lhs.ptr < rhs.ptr);
					}

					friend bool	operator<=(const Iterator lhs, const Iterator rhs)
					{
						return (lhs.ptr <= rhs.ptr);
					}

					friend bool	operator>(const Iterator lhs, const Iterator rhs)
					{
						return (lhs.ptr > rhs.ptr);
					}

					friend bool	operator>=(const Iterator lhs, const Iterator rhs)
					{
						return (lhs.ptr >= rhs.ptr);
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

					typedef const T								value_type;
					typedef const T&							reference;
					typedef const T*							pointer;
					typedef std::random_access_iterator_tag		iterator_category;
					typedef typename vector::difference_type	difference_type;


					explicit Const_Iterator(const T* ptr = NULL) : ptr(ptr)
					{
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

					friend bool	operator==(const Const_Iterator lhs, const Const_Iterator rhs)
					{
						return (lhs.ptr == rhs.ptr);
					}

					friend bool	operator!=(const Const_Iterator lhs, const Const_Iterator rhs)
					{
						return (!(lhs.ptr == rhs.ptr));
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

					friend Const_Iterator	operator+(const Const_Iterator lhs, difference_type n)
					{
						Const_Iterator	iter(lhs);
						
						iter += n;
						return (iter);
					}

					friend Const_Iterator	operator+(difference_type n, const Const_Iterator rhs)
					{
						Const_Iterator	iter(rhs);
						
						iter += n;
						return (iter);
					}


					friend Const_Iterator	operator-(const Const_Iterator lhs, difference_type n)
					{
						Const_Iterator	iter(lhs);
						
						iter -= n;
						return (iter);
					}

					friend difference_type	operator-(const Const_Iterator lhs, const Const_Iterator rhs)
					{
						return (lhs.ptr - rhs.ptr);
					}


					friend bool	operator<(const Const_Iterator lhs, const Const_Iterator rhs)
					{
						return (lhs.ptr < rhs.ptr);
					}

					friend bool	operator<=(const Const_Iterator lhs, const Const_Iterator rhs)
					{
						return (lhs.tr <= rhs.ptr);
					}

					friend bool	operator>(const Const_Iterator lhs, const Const_Iterator rhs)
					{
						return (lhs.ptr > rhs.ptr);
					}

					friend bool	operator>=(const Const_Iterator lhs, const Const_Iterator rhs)
					{
						return (lhs.ptr >= rhs.ptr);
					}

					const T&	operator[](difference_type	n)
					{
						return (*(ptr + n));
					}

			};

			

	public:
		
		/* ---------- constructors + destructor ---------- */
		
			vector(void) : c(NULL), _size(0), allocated_size(0)
			{
			}

			explicit vector(const Allocator& alloc) : c(NULL), _size(0), allocated_size(0), alloc(alloc)
			{	
			}

			explicit vector( size_type count, const T& value = T(), const Allocator& alloc = Allocator()) : _size(count), allocated_size(count), alloc(alloc)
			{
				c = this->alloc.allocate(count);
				try
				{
					init(this->begin(), this->begin() + count, value, this->alloc);
				}
				catch(...)
				{
					this->alloc.deallocate(c, count);
					throw ;
				}
			}
			
			template <class InputIt>
			vector( InputIt first, InputIt last, const Allocator& alloc = Allocator() ) : alloc(alloc)
			{
				size_type	count = 0;
				
				for (InputIt inc = first; inc != last; ++inc)
					count++;
				c = this->alloc.allocate(count);
				try
				{
					init(this->begin(), first, last, this->alloc);
				}
				catch(...)
				{
					this->alloc.deallocate(c, count);
					throw ;
				}
				allocated_size = count;
				_size = count;
				
			}


			vector(const vector& other) : _size(0), allocated_size(other.allocated_size), alloc(other.alloc)
			{
				c = this->alloc.allocate(allocated_size);
				try
				{
					init(begin(), other.begin(), other.end(), this->alloc);
				} 
				catch (...)
				{
					this->alloc.deallocate(c, allocated_size);
					throw ;
				}
				_size = other.size();
			}

			~vector(void)
			{
				destroy(this->begin(), this->end(), this->alloc);
				alloc.deallocate(c, allocated_size);
			}

		/* ---------- basic functions ---------- */

			/* original alloc is preserved */
			vector&	operator=(const vector& other)
			{
				assign(other.begin(), other.end());
				_size = other._size;
				return (*this);
			} 

			void	assign(size_type count, const T& value)
			{
				prepare_alloc(count);
				if (_size > count)
					destroy(begin() + count, end(), alloc);
				size_type i = 0;
				for (; i < count && i < _size; ++i)
					c[i] = value;
				for (; i < count; ++i)
					alloc.construct(&c[i], value);
				_size = count;
				return ;
			}

			/* enable_if to prevent mistaking InputIt with int or size_t */
			template <class InputIt>
			void assign(typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type first, InputIt last)
			{
				size_type	count = 0;
				
				for (InputIt inc = first; inc != last; ++inc)
					count++;
				prepare_alloc(count);

				Iterator this_iter = this->begin();
				InputIt iter = first;
				for (; iter != last && this_iter != end(); ++iter)
				{
					*this_iter = *iter;
					++this_iter;
				}
				for (; iter != last; ++iter)
				{
					alloc.construct(&*this_iter, *iter);
					*this_iter = *iter;
					++this_iter;
				}
				
				if (_size > count)
					destroy(this_iter, this->end(), alloc);					
				_size = count;
				return ;
			}

			allocator_type get_allocator(void) const
			{
				return (this->allocator_type);
			}
		
		/* ---------- element access ---------- */

			reference	at(size_type pos)
			{
				if (pos >= _size)
					throw std::out_of_range("vector");
				return (c[pos]);
			}
			
			const_reference	at(size_type pos) const
			{
				if (pos >= _size)
					throw std::out_of_range("vector");
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
				Iterator it(this->data());
				return (it);
			}
			
			Const_Iterator begin(void) const
			{
				Const_Iterator It(this->data());
				return (It);
			}

			Iterator	end(void)
			{
				Iterator it(this->data() + _size);
				return (it);
			}

			Const_Iterator	end(void) const
			{
				Const_Iterator It(this->data() + _size);
				return (It);
			}

			reverse_iterator	rbegin(void)
			{
				reverse_iterator	it(this->end());
				return (it);
			}

			const_reverse_iterator rbegin() const
			{
				const_reverse_iterator	it(this->end());
				return (it);
			}

			reverse_iterator	rend(void)
			{
				reverse_iterator	it(this->begin());
				return (it);
			}

			const_reverse_iterator	rend(void) const
			{
				const_reverse_iterator	it(this->begin());
				return (it);
			}

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
				c = alloc.allocate(new_cap);
				try
				{
					init(c, old_c, old_c + _size, this->alloc);
					destroy(old_c, old_c + _size, this->alloc);
					alloc.deallocate(old_c, allocated_size);
					allocated_size = new_cap;
				}
				catch  (...)
				{
					alloc.deallocate(c, new_cap);
					c = old_c;
					throw ;
				}
			}

			size_type	capacity(void) const
			{
				return (allocated_size);
			}

		/* ---------- Modifiers ---------- */
			
			void	clear(void)
			{
				for (size_type i = _size; i != 0 ;)
				{
					alloc.destroy(&c[--i]);
				}
				_size = 0;

			}

			Iterator	insert(Iterator pos, const T& value)
			{
				T*				old_c = c;
				size_type		index = std::distance(begin(), pos);
				size_type		count;
				
				if (_size == allocated_size)
				{
					if (allocated_size != 0)
						count = allocated_size * 2;
					else
						count = 1;
					c = alloc.allocate(count);
					try
					{
						init(c, old_c, old_c + index, this->alloc);
						for (size_type end = _size; end != index; --end)
						{
							if (end != _size)
								alloc.destroy(&c[end]);
							alloc.construct(&c[end], c[end - 1]);
						}
						if (index != _size)
							alloc.destroy(&c[index]);
						alloc.construct(&c[index], value);
						alloc.deallocate(old_c, allocated_size);
						allocated_size = count;
					}
					catch (...)
					{
						alloc.deallocate(c, count);
						c = old_c;
						throw ;
					}
				}
				else
				{
					for (size_type end = _size; end != index; --end)
					{
						if (end != _size)
							alloc.destroy(&c[end]);
						alloc.construct(&c[end], c[end - 1]);
					}
					if (index != _size)
						alloc.destroy(&c[index]);
					alloc.construct(&c[index], value);
				}
				_size++;
				Iterator insert_pos(this->data() + index);
				return (insert_pos);
			}
			
			void insert(Iterator pos, size_type count, const T& value)
			{
				T*			old_c = c;
				size_type	index = 0;
				size_type	count_alloc;
				
				for (Iterator iter = this->begin(); iter != pos; ++iter)
				{
					index++;
				}
				size_type	nb_to_move = _size - index;		
				if (_size + count > allocated_size)
				{
					if (allocated_size != 0)
						count_alloc = allocated_size + count;
					else
						count_alloc = count;
					c = alloc.allocate(count_alloc);
					try
					{
						init(c, old_c, old_c + index, this->alloc);
						for (size_type i = 0; i < count; ++i)
						{
							alloc.construct(&c[index], value);
							index++;
						}
						for (size_type end = _size + count - 1; nb_to_move > 0; --end)
						{
							alloc.construct(&c[end], old_c[end - count]);
							nb_to_move--;
						}
						destroy(old_c, old_c + _size, alloc);
						alloc.deallocate(old_c, allocated_size);
						allocated_size = count_alloc;
					}
					catch (...)
					{
						alloc.deallocate(c, count_alloc);
						c = old_c;
						throw ;
					}
				}
				else
				{
					for (size_type end = _size + count - 1; nb_to_move > 0; --end)
					{
						alloc.destroy(c + end - count);
						alloc.construct(&c[end], c[end - count]);
						nb_to_move--;
					}
					for (size_type i = 0; i < count; ++i)
					{
						alloc.construct(&c[index], value);
						index++;
					}
				}
				_size += count;
			}

			
			template <class InputIt>
			void insert(Iterator pos, InputIt first, InputIt last)
			{
				T*			old_c = c;
				size_type	index = 0;
				size_type	count = 0;
				size_type	count_alloc;
				size_type	nb_to_move;
				
				for (Iterator iter = this->begin(); iter != pos; ++iter)
					index++;
				nb_to_move = _size - index;
				for (InputIt cursor = first; cursor != last; ++cursor)
					count++;
				if (_size + count > allocated_size)
				{
					if (allocated_size != 0)
						count_alloc = allocated_size + count;
					else
						count_alloc = count;
					c = alloc.allocate(count_alloc);
					try
					{
						init(c, old_c, old_c + index, this->alloc);
						for (size_type i = 0; i < count; ++i)
						{
							alloc.construct(&c[index], *first);
							index++;
							++first;
						}
						for (size_type end = _size + count - 1; nb_to_move > 0; --end)
						{
							alloc.construct(&c[end], old_c[end - count]);
							nb_to_move--;
						}
						destroy(old_c, old_c + _size, alloc);
						alloc.deallocate(old_c, allocated_size);
						allocated_size = count_alloc;
					}
					catch (...)
					{
						alloc.deallocate(c, count_alloc);
						c = old_c;
						throw ;
					}
				}
				else
				{
					for (size_type end = _size + count; nb_to_move > 0; --end)
					{
						if (end != _size)
							alloc.destroy(&c[end]);
						alloc.construct(&c[end], c[end - 1]);
						nb_to_move--;
					}
						for (size_type i = 0; i < count; ++i)
						{
							if (index != _size)
								alloc.destroy(&c[index]);
							alloc.construct(&c[index], *first);
							++first;
							index++;
						}
				}
				_size += count;
			}

			Iterator erase(Iterator pos)
			{
				Iterator	index = this->begin();
				Iterator	save_pos = pos;

				if (pos == this->end())
					return (pos);
				while (index != pos)
					++index;
				++pos;
				while (pos != this->end())
				{
					*index = *pos;
					++index;
					++pos;
				}
				alloc.destroy(&(*index));
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
					return (this->end());
				}
				while (index != first)
					++index;
				while (last != this->end())
				{
					*index = *last;
					++index;
					++last;
				}
				while (index != this->end())
				{
					alloc.destroy(&(*index));
					++index;
				}
				_size -= range;
				return (save_pos);
			}

			void	push_back(const T& value)
			{
				T*			old_c = c;
				size_type	count;
				
				if (_size == allocated_size)
				{
					if (allocated_size != 0)
						count = allocated_size * 2;
					else
						count = 1;
					c = alloc.allocate(count);
					try
					{
						init(c, old_c, old_c + _size, this->alloc);
						destroy(old_c, old_c + _size, this->alloc);
						alloc.deallocate(old_c, allocated_size);
						allocated_size = count;
					}
					catch (...)
					{
						alloc.deallocate(c, count);
						c = old_c;
						throw ;
					}
				}
				alloc.construct(&c[_size], value);
				_size++;
			}

			void	pop_back(void)
			{
				if (_size == 0)
					return ;
				alloc.destroy(&c[_size - 1]);
				_size--;
			}

			void resize(size_type count, T value = T() )
			{
				T*	old_c = c;
				
				if (_size >= count)
				{
					for (size_type i = count; i < _size; ++i)
						alloc.destroy(&c[i]);
					_size = count;
					return ;
				}
				if (allocated_size < count)
				{
				try
					{
						if (allocated_size != 0)
						{
							c = alloc.allocate(allocated_size * 2);
						}
						else
							c = alloc.allocate(count);
						init(c, old_c, old_c + _size, this->alloc);
						destroy(old_c, old_c + _size, this->alloc);
						alloc.deallocate(old_c, allocated_size);
						if (allocated_size != 0)
							allocated_size = allocated_size * 2;
						else
							allocated_size = count;
					}
					catch (...)
					{
						c = old_c;
						throw ;
						return ;
					}
				}
				for (size_type i = _size; i < count; ++i)
				{
					alloc.construct(&c[i], value);
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
		typename ft::vector<T, Alloc>::const_iterator	start_l = lhs.begin();
		typename ft::vector<T, Alloc>::const_iterator	start_r = rhs.begin();
		typename ft::vector<T, Alloc>::const_iterator	end_l = lhs.end();
		
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
  	bool	operator<(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) // revient a utilser lexigraphical compare
	{
		typename ft::vector<T, Alloc>::const_iterator	start_l = lhs.begin();
		typename ft::vector<T, Alloc>::const_iterator	start_r = rhs.begin();
		typename ft::vector<T, Alloc>::const_iterator	end_l = lhs.end();
		typename ft::vector<T, Alloc>::const_iterator	end_r = rhs.end();
		
		
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
