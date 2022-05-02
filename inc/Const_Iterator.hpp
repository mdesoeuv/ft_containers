#pragma once

template < class Container, class T>
class Const_Iterator
{
	protected:

		const T*		ptr;
		

	public:

		typedef	T value_type;
		typedef std::ptrdiff_t difference_type;
		// typedef Category iterator_category;
		typedef T* pointer;
		typedef T& reference;
		typedef std::size_t size_type;


		Const_Iterator(void)
		{
			ptr = NULL;
		}

		Const_Iterator(const Container& container)
		{
			ptr = container.data();
		}

		Const_Iterator(const Container& container, size_type offset)
		{
			ptr = container.data() + offset;
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

		friend difference_type	operator-(const Const_Iterator& lhs, const Const_Iterator& rhs)
		{
			difference_type	n = 0;
			Const_Iterator	lhs_iter(lhs);
			Const_Iterator	rhs_iter(rhs);
			
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
