#pragma once

namespace ft
{
	template <typename Iterator>
	class	Reverse_Iterator
	{
		protected:

			Iterator	current;

		public:

			typedef typename Iterator::difference_type difference_type;
			typedef typename Iterator::reference_type reference_type;
			typedef typename Iterator::value_type value_type;
			typedef typename Iterator::pointer pointer;

			Reverse_Iterator(void)
			{}

			Reverse_Iterator(Iterator iter) : current(iter)
			{}

			Reverse_Iterator(const Reverse_Iterator& other) : current(other.current)
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

			reference_type	operator*(void)
			{
				return (*(current - 1));
			}

			pointer	operator->(void)
			{
				return (&(operator*()));
			}

			bool	operator==(const Reverse_Iterator& rhs) // non-member functions ??
			{
				return (current == rhs.current);
			}

			bool	operator!=(const Reverse_Iterator& rhs)
			{
				return (!(current == rhs.current));
			}

			Reverse_Iterator operator+ (difference_type n) const
			{
				Reverse_Iterator	iter(current - n);
				return (iter);
			}

			friend Reverse_Iterator operator+ (difference_type n, const Reverse_Iterator& rhs)
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

			friend difference_type	operator-(const Reverse_Iterator& lhs, const Reverse_Iterator& rhs)
			{
				return (rhs.current - lhs.current);
			}

			reference_type	operator[](difference_type n) const
			{
				return (*(current - n - 1));
			}

			template< class Iterator1, class Iterator2 >
			friend	bool operator== (const Reverse_Iterator<Iterator1>& lhs, const Reverse_Iterator<Iterator2>& rhs)
			{
				return (lhs.base() == rhs.base());
			}

			template< class Iterator1, class Iterator2 >
			friend	bool operator!= (const Reverse_Iterator<Iterator1>& lhs, const Reverse_Iterator<Iterator2>& rhs)
			{
				return (lhs.base() != rhs.base());
			}

			template< class Iterator1, class Iterator2 >
			friend	bool operator< (const Reverse_Iterator<Iterator1>& lhs, const Reverse_Iterator<Iterator2>& rhs)
			{
				return (lhs.base() > rhs.base());
			}

			template< class Iterator1, class Iterator2 >
			friend	bool operator<= (const Reverse_Iterator<Iterator1>& lhs, const Reverse_Iterator<Iterator2>& rhs)
			{
				return (lhs.base() >= rhs.base());
			}

			template< class Iterator1, class Iterator2 >
			friend	bool operator> (const Reverse_Iterator<Iterator1>& lhs, const Reverse_Iterator<Iterator2>& rhs)
			{
				return (lhs.base() < rhs.base());
			}

			template< class Iterator1, class Iterator2 >
			friend	bool operator>= (const Reverse_Iterator<Iterator1>& lhs, const Reverse_Iterator<Iterator2>& rhs)
			{
				return (lhs.base() <= rhs.base());
			}
			
			

	};
}
