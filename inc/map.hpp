/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesoeuv <mdesoeuv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 14:45:27 by mdesoeuv          #+#    #+#             */
/*   Updated: 2022/05/05 17:41:43 by mdesoeuv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "pair.hpp"
#include "Reverse_Iterator.hpp"

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
		public: ////////////// change to private

			/* ----- forward declarations ----- */
			
			class Iterator;
			class Const_Iterator;
			class TreeNode;
			
		public:
		
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
			
		public: //////////////// change to private

			key_compare		comp;
			allocator_type	alloc;
			TreeNode*		root;
			size_type		_size;

			class TreeNode
			{
				public:				// a voir
				value_type	pr;
				TreeNode*	left;
				TreeNode*	right;
				TreeNode*	parent;
				// allocator_type	alloc;

				// TreeNode(void) : pr(value_type()), left(NULL), right(NULL), parent(NULL)
				// {}

				TreeNode(value_type pair) : pr(pair), left(NULL), right(NULL), parent(NULL)
				{
					
				}
				
				TreeNode(const TreeNode& other)
				{
					pr = other.pr;
					left = other.left;
					right = other.right;
					parent = other.parent;
				}
				
				~TreeNode(void)
				{}

				TreeNode&	operator=(const TreeNode& rhs)
				{
					pr = rhs.pr;
					left = rhs.left;
					right = rhs.right;
					parent = rhs.parent;

					return (*this);
				}

				TreeNode*	create(value_type pr, TreeNode* parent)
				{
					TreeNode*	new_node;


					try
					{
						// new_node = this->alloc.allocate(1);
						// this->alloc.construct(new_node, TreeNode(pr));
						new_node = new TreeNode(pr);
						new_node->parent = parent;
					}
					catch(...)
					{
						return (NULL);
					}
					return (new_node);					
				}

				TreeNode*	lefmost(TreeNode* node)
				{
					if (node == NULL)
						return (NULL);
					while (node->left)
						node = node->left;
					return (node);
				}

				TreeNode*	first(TreeNode* root)
				{
					return (lefmost(root));
				}
				
				TreeNode*	next(TreeNode* node)
				{
					if (node == NULL)
						return (NULL);
					if (node->right)
						return (lefmost(node->right));

					TreeNode* parent = node->parent;
					if (!parent)
						return (NULL);
					if (node == parent->left)
						return (parent);
					while (parent != NULL && node != parent->left)
					{
						node = parent;
						parent = node->parent;
					}
					return (parent);
				}

				void	clear(TreeNode* node)
				{
					if (node == NULL)
						return ;
					clear(node->left);
					clear(node->right);
					delete node;
					// this->alloc.destroy(node);
					// this->alloc.deallocate(node, 1);
				}

				TreeNode*	insert(TreeNode** node, value_type pr)
				{
					if (*node == NULL)
					{
						std::cout << "here" << std::endl;
						*node = create(pr, node->parent);
						return (*node);
					}
					if (pr.first == node->pr.first)
						return (node);
					if (pr.first < node->pr.first)
						node->left = insert(node->left, pr);
					else
						node->right = insert(node->right, pr);
					return (node);
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

			map(void) : comp(std::less<Key>()), alloc(std::allocator<std::pair<const Key, T> >()), _size(0)
			{
				root = NULL;
			}

			explicit map(const Compare& comp, const Allocator& alloc = Allocator()) : comp(comp), alloc(alloc), _size(0)
			{
				root = NULL;
			}

			template< class InputIt >
			map(InputIt first, InputIt last, const Compare& comp = Compare(), const Allocator& alloc = Allocator()) : comp(comp), alloc(alloc), _size(0)
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
				
				// _size = other.size();
			// 	return (*this);
			// }

			allocator_type	get_allocator(void) const
			{
				return (alloc);
			}

			/* ----- element access ----- */

			// T& at(const Key& key)
			// {
			// 	Iterator	it = find(key);
			// 	if (it == end())
			// 		throw (std::out_of_range("key not found"));
			// 	return (it->second);
			// }

			// T& operator[](const Key& key)
			// {
			// 	Iterator	it = find(key);
			// 	if (it != end())
			// 		return ((*it).second);
			// 	else
			// 		return (insert(value_type(key, T())).first->second);
			// }

			/* ----- Iterators ----- */

			// iterator begin(void)
			// {
				
			// }

			// const_iterator	begin(void) const
			// {
				
			// }

			// iterator	end(void)
			// {

			// }
			
			// const_iterator	end(void) const
			// {
				
			// }

			// reverse_iterator	rbegin(void)
			// {
					
			// }

			// const_reverse_iterator	rbegin(void) const
			// {
				
			// }

			// reverse_iterator	rend(void)
			// {
					
			// }

			// const_reverse_iterator	rend(void) const
			// {
				
			// }

			/* ----- capacity ----- */

			// bool	empty(void) const
			// {
			// 	return (begin() == end());
			// }

			// size_type	size(void) const
			// {
			// 	return (end() - begin());
			// }

			// size_type	max_size(void) const
			// {
			// 	return (alloc.max_size());
			// }

			/* ----- modifiers ----- */

			void	clear(void)
			{
				root->clear(root);
				_size = 0;
			}
			
			// ft::pair<iterator, bool> insert(const value_type& value) // try catch ??
			// {
			// 	TreeNode* node = root;
		
			// 	while (node != NULL)
			// 	{
			// 		if (value.first == node->pr.first)
			// 			return (ft::pair(iterator(node), false));
			// 		if (value.first < node->pr.first)
			// 			node = node->left;
			// 		else
			// 			node = node->right;
			// 	}
			// 	node = node->create(value);
			// 	return (ft::pair(iterator(node), true));
			// }

			// iterator insert( iterator hint, const value_type& value ) // wtf ??
			// {
				
			// }
			
			// template <class InputIt>
			// void insert(InputIt first, InputIt last)
			// {
				
			// }

			// void	erase(iterator pos)
			// {
				
			// }
					
	};
}