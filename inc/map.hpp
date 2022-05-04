/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesoeuv <mdesoeuv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 14:45:27 by mdesoeuv          #+#    #+#             */
/*   Updated: 2022/05/04 17:40:02 by mdesoeuv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

namespace ft
{
	template<
    class Key,
    class T,
    class Compare = std::less<Key>,
    class Allocator = std::allocator<std::pair<const Key, T> >
	>
	class map
	{
		public:

			/* ----- forward declarations ----- */
			
			class Iterator;
			class Const_Iterator;
			class TreeNode;
			
			/* ----- member types ----- */

			typedef Key 											key_type;
			typedef T												mapped_type;
			typedef typename ft::pair<const Key, T> 				value_type;		
			typedef std::size_t										size_type;
			typedef std::ptrdiff_t									difference_type;
			typedef Compare											key_compare;
			typedef Allocator										allocator_type;
			typedef value_type&										reference;
			typedef const value_type&								const_reference;
			typedef typename Allocator::pointer						pointer;
			typedef typename Allocator::const_pointer				const_pointer;
			typedef Iterator										iterator;
			typedef Const_Iterator									const_iterator;
			typedef typename ft::Reverse_Iterator<Iterator>			reverse_iterator;
			typedef typename ft::Reverse_Iterator<Const_Iterator>	const_reverse_iterator;
			
		private:

			key_compare		comp;
			allocator_type	alloc;
			TreeNode*		root;

			struct TreeNode
			{
				value_type	pr;
				TreeNode*	left;
				TreeNode*	right;

				TreeNode(value_type pair) : pr(pair), left(NULL), right(NULL)
				{}
				
				TreeNode(const TreeNode& other)
				{
					pr = other.pr;
					left = other.left;
					right = other.right;
				}
				
				~TreeNode(void)
				{}

				TreeNode&	operator=(const TreeNode& rhs)
				{
					pr = rhs.pr;
					left = rhs.left;
					right = rhs.right;

					return (*this);
				}

			};
		
		public:
		
			/* ----- member classes ----- */

			class value_compare
			{

				protected:
				
					Compare	comp;
					value_compare(Compare c) : comp(c)
					{}
								
				public:
				
					typedef bool		result_type;
					typedef	value_type	first_argument_type;
					typedef value_type	second_argument_type;

					bool	operator() (const value_type& lhs, const value_type& rhs) const
					{
						return (comp(lhs.first, rhs.first));
					}

					// ~value_compare(void) is there a destructor for this class ?
					// {}
			
			};

			/* ----- member functions ----- */

			explicit map(const Compare& comp, const Allocator& alloc = Allocator()) : comp(comp), alloc(alloc)
			{
				root = NULL;
			}

			template< class InputIt >
			map(InputIt first, InputIt last, const Compare& comp = Compare(), const Allocator& alloc = Allocator()) : comp(comp), alloc(alloc)
			{
				insert(first, last);
			}
			
			map(const map& other) : comp(other.comp), alloc(other.alloc)
			{
				*this = other;
			}
			
			// unclear if destructor must clear the tree itself
			~map(void)
			{
				clear();
			}
			
			// map&	operator=(const map& other)
			// {
				
				
			// 	return (*this);
			// }

			allocator_type	get_allocator(void) const
			{
				return (alloc);
			}

			/* ----- element access ----- */

			T& at(const Key& key)
			{
				Iterator	it = find(key);
				if (it == end())
					throw (std::out_of_range("key not found"));
				return (it->second);
			}

			T& operator[](const Key& key)
			{
				Iterator	it = find(key);
				if (it != end())
					return ((*it).second);
				else
					return (insert(value_type(key, T())).first->second);
			}
	};
}