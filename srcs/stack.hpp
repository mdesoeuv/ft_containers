#ifndef STACK_HPP
# define STACK_HPP

# include <deque> // to remove for use with ft::vector

namespace ft
{
	template <class T, class Container = std::deque<T> > // change the underlying container by ft::vector
	class stack
	{

		using container_type = Container;
		using value_type = Container::value_type;
		using size_type = Container::size_type;
		using reference = Container::reference;
		using const_reference = Container::const_reference;

	private:
		
	protected:

		Container c;

	public:

		explicit stack( const Container& cont = Container() );
		stack( const stack& other );
		~stack(void);
		stack&	operator=(const stack& other);

		T&			top(void); // change T by reference
		const T&	top(void) const;	// change T by const reference

		bool		empty(void) const;
		size_type	size(void) const;

		void		push(const value_type& value);
		void		pop(void);

	};
	
	template< class T, class Container >
	bool operator==(const ft::stack<T, Container>& lhs, const ft::stack<T,Container>& rhs);

	template< class T, class Container >
	bool operator!=(const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs);

	template< class T, class Container >
	bool operator<(const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs);

	template< class T, class Container >
	bool operator<=(const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs);

	template< class T, class Container >
	bool operator>(const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs);

	template< class T, class Container >
	bool operator>=(const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs);



}

#endif