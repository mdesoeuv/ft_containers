#pragma once

template <class Container, class T>
class	Reverse_Iterator : public Iterator<Container, T>
{
	protected:

		Iterator<Container, T>	current;

	public:


		typedef	T value_type;
		typedef std::ptrdiff_t difference_type;
		// typedef Category iterator_category;
		typedef T* pointer;
		typedef T& reference;
		typedef std::size_t size_type;


		Reverse_Iterator(void) : Iterator<Container, T>()
		{}

		Reverse_Iterator(Iterator<Container, T> iter) : Iterator<Container, T>(iter), current(iter)
		{}

		Reverse_Iterator(const Reverse_Iterator& other) : Iterator<Container, T>(other), current(other.current)
		{}

		~Reverse_Iterator(void)
		{}

		Reverse_Iterator&	operator=(const Reverse_Iterator& rhs)
		{
			current = rhs.current;
			
			return (*this);
		}

		Iterator<Container, T>	base(void) const
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


		T*	operator->(void)
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

		reference	operator[](difference_type n) const
		{
			return (*(current - n - 1));
		}

		// a templater ??
		friend	bool operator== (const Reverse_Iterator& lhs, const Reverse_Iterator& rhs)
		{
			return (lhs.current == rhs.current);
		}

		friend	bool operator!= (const Reverse_Iterator& lhs, const Reverse_Iterator& rhs)
		{
			return (lhs.current != rhs.current);
		}

		friend	bool operator< (const Reverse_Iterator& lhs, const Reverse_Iterator& rhs)
		{
			return (lhs.current > rhs.current);
		}

		friend	bool operator<= (const Reverse_Iterator& lhs, const Reverse_Iterator& rhs)
		{
			return (lhs.current >= rhs.current);
		}

		friend	bool operator> (const Reverse_Iterator& lhs, const Reverse_Iterator& rhs)
		{
			return (lhs.current < rhs.current);
		}

		friend	bool operator>= (const Reverse_Iterator& lhs, const Reverse_Iterator& rhs)
		{
			return (lhs.current <= rhs.current);
		}
		
		

};