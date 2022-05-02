#pragma once

#include <cstddef>

template <class Container, class T>
class Iterator
{
	protected:

		T*		ptr;
		

	public:

		typedef	T value_type;
		typedef std::ptrdiff_t difference_type;
		// typedef Category iterator_category;
		typedef T* pointer;
		typedef T& reference;
		typedef std::size_t size_type;

		Iterator(void)
		{
			ptr = NULL;
		}

		Iterator(Container& container)
		{
			ptr = container.data();
		}

		Iterator(Container& container, size_type offset)
		{
			ptr = container.data() + offset;
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

		friend difference_type	operator-(const Iterator& lhs, const Iterator& rhs)
		{
			difference_type	n = 0;
			Iterator lhs_iter(lhs);
			Iterator rhs_iter(rhs);
			
			if (lhs_iter.ptr == rhs_iter.ptr)
				return (0);
			if (lhs_iter.ptr < rhs_iter.ptr)
			{
				while (lhs_iter.ptr != rhs_iter.ptr)
				{
					lhs_iter.ptr++;
					n++;
				}
			}
			else
			{
				while (lhs_iter.ptr != rhs_iter.ptr)
				{
					lhs_iter.ptr--;
					n++;
				}
			}
			return (n);
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