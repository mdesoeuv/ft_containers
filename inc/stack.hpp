#ifndef STACK_HPP
# define STACK_HPP

# include <deque> // to remove for use with ft::vector

namespace ft
{
	template <class T, class Container = std::deque<T> > // change the underlying container by ft::vector
	class stack
	{

		typedef Container container_type;  //typename or not typename ?
		typedef typename Container::value_type value_type;
		typedef typename Container::size_type size_type;
		typedef typename Container::reference reference;
		typedef typename Container::const_reference const_reference;

	private:

		friend bool operator==(const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs)
		{
			return (lhs.c == rhs.c);
		}
		friend bool operator!=(const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs)
		{
			return (lhs.c != rhs.c);
		}
		friend bool operator<(const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs)
			{
			return (lhs.c < rhs.c);
		}
		friend bool operator<=(const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs)
		{
			return (lhs.c <= rhs.c);
		}
		friend bool operator>(const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs)
		{
			return (lhs.c > rhs.c);
		}
		friend bool operator>=(const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs)
		{
			return (lhs.c >= rhs.c);
		}

	protected:

		Container c;

	public:

		explicit stack(const Container& cont = Container() ) : c(cont)
		{
		}

		stack(const stack& other) : c(other.c)
		{
		}

		~stack(void)
		{
		}

		stack&	operator=(const stack& other)
		{
			c = other.c;
		}

		T&			top(void) // change T by reference
		{
			return (c.back());
		}

		const T&	top(void) const	// change T by const reference
		{
			return (c.back());
		}

		bool		empty(void) const
		{
			return (c.empty());
		}

		size_type	size(void) const
		{
			return (c.size());
		}

		void		push(const value_type& value)
		{
			c.push_back(value);
		}

		void		pop(void)
		{
			c.pop_back();
		}

	};
	

}

#endif