/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesoeuv <mdesoeuv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 14:45:27 by mdesoeuv          #+#    #+#             */
/*   Updated: 2022/05/09 17:11:50 by mdesoeuv         ###   ########lyon.fr   */
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
    class Allocator = std::allocator<ft::pair<const Key, T> >
	>
	class map
	{
		public: ////////////// change to private

			/* ----- forward declarations ----- */
			
			class Iterator;
			class Const_Iterator;
			class BaseNode;
			class Node;
			
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
			typedef typename allocator_type::template rebind<Node>::other node_allocator_type;
			
		public: //////////////// change to private

			key_compare			comp;
			node_allocator_type	alloc; // only TreeNodes are allocated
			
			BaseNode		meta; // end node for end()
			size_type		_size;

			Node* root() {
				return (static_cast<Node*>(meta.left));
			}

			BaseNode* end() {
				return &meta;
			}


			Node*	create(const value_type& pair, BaseNode* parent)
			{
				Node*	new_node;

				try
				{
					new_node = alloc.allocate(1);
					alloc.construct(new_node, Node(pair, parent));
				}
				catch(...)
				{
					return (NULL);
				}
				return (new_node);					
			}


			Node*	insert(value_type pair)
			{
				if (root() == NULL)
				{
					Node* cursor = root();
					cursor = create(pair, &meta);
					meta.left = cursor;
					return (cursor);
				}
				Node* cursor = root();
				while (true)
				{
					if (pair.first < cursor->pair.first)
					{
						if (cursor->left == NULL)
						{
							cursor->left = create(pair, static_cast<BaseNode*>(cursor));
							break ;
						}
						else
						{
							cursor = static_cast<Node*>(cursor->left);
						}
						
					}
					else if (pair.first > cursor->pair.first)
					{
						if (cursor->right == NULL)
						{
							cursor->right = create(pair, static_cast<BaseNode*>(cursor));
							break ;
						}
						else
						{
							cursor = static_cast<Node*>(cursor->right);
						}
						
					}
					else
						break;
				}
				return (cursor);
			}
		
			void	clear(Node* node)
			{
				std::cout << "call to clear" << std::endl;
				if (node == NULL)
					return ;
				if (node->left != NULL)
				{
					std::cout << "go to left" << std::endl;
					clear(static_cast<Node*>(node->left));
				}
				if (node->right != NULL)
				{
					std::cout << "go to right" << std::endl;
					clear(static_cast<Node*>(node->right));
				}
				alloc.destroy(node);
				alloc.deallocate(node, 1);
				node = NULL;
			}


			void	ft_print_tab(int level)
			{
				while (level > 0)
				{
					std::cout << "\t";
					level--;
				}
			}

			void	display(Node* node, int level)
			{
				if (node == NULL)
				{
					ft_print_tab(level);
					std::cout << "<empty>\n";
					return ;
				}
				ft_print_tab(level);
				std::cout << "node : " << node->pair.first << ", " << node->pair.second << std::endl;
				ft_print_tab(level);
				std::cout << "left \n";
				display(static_cast<Node*>(node->left), level + 1);
				ft_print_tab(level);
				std::cout << "right \n";
				display(static_cast<Node*>(node->right), level + 1);
			}


			class BaseNode
			{
				public:				// a voir
				
				// value_type  pr;   // pas de paire  value_type dans le BaseNode => uniquement dans le Node
				BaseNode*	left;
				BaseNode*	right;
				BaseNode*	parent;

				public:

				BaseNode(void) : left(NULL), right(NULL), parent(NULL)
				{
				}
				
				BaseNode(BaseNode* parent) : left(NULL), right(NULL), parent(parent)
				{
				}
				
				BaseNode(const BaseNode& other) : left(other.left), right(other.right), parent(other.parent)
				{
				}
				
				~BaseNode(void)
				{}

				BaseNode*	leftmost() // ne pas prendre de parametre // travailler avec this
				{
					if (*this == NULL)
						return (NULL);
					while (this->left)
						this = this->left;
					return (this);
				}

				BaseNode*	first(BaseNode* root)
				{
					return (leftmost(root));
				}
				
				BaseNode*	next()
				{
					if (*this == NULL)
						return (NULL);
					if (this->right)
						return (this->right->leftmost());

					BaseNode* parent = this->parent;
					if (!parent)
						return (NULL);
					if (this == parent->left)
						return (parent);
					while (parent != NULL && this != parent->left)
					{
						this = parent;
						parent = this->parent;
					}
					return (parent);
				}



			};

			class Node : public BaseNode
			{
				public: // a voir
				
					value_type  pair;
					
				public:

					Node(value_type pair, BaseNode* parent) : BaseNode(parent), pair(pair)
					{
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

			map(void) : comp(std::less<Key>()), alloc(std::allocator<ft::pair<const Key, T> >()), _size(0)
			{
			}

			explicit map(const Compare& comp, const Allocator& alloc = Allocator()) : comp(comp), alloc(alloc), _size(0)
			{
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
			
			~map(void)
			{
				clear(root());
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
				clear(root());
				meta.left = NULL;
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

			void	swap(map& other)
			{
				BaseNode* root_temp = this->meta.left;

				this->meta.left = other.meta.left;
				other.meta.left = root_temp;
			}
					
	};
}