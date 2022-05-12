/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesoeuv <mdesoeuv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 14:45:27 by mdesoeuv          #+#    #+#             */
/*   Updated: 2022/05/12 12:32:30 by mdesoeuv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "pair.hpp"
#include "equal.hpp"
#include "lexicographical_compare.hpp"
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
		private:

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
			
		private:

			key_compare			comp;
			node_allocator_type	alloc; // only Nodes are allocated
			
			BaseNode		meta; // end node for end()
			size_type		_size;

		public: // change to protected !!!
		
			BaseNode*& root()
			{
				return (meta.left);
			}

			const BaseNode* root() const
			{
				return (meta.left);
			}
			

			BaseNode* end_node()
			{
				return &meta;
			}

			const BaseNode* end_node() const
			{
				return &meta;
			}


			BaseNode*	create(const value_type& pair, BaseNode* parent)
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
				return (static_cast<BaseNode*>(new_node));			
			}

			BaseNode*	deleteBaseNode(BaseNode* node)
			{
				BaseNode*	temp = NULL;

				if (node == NULL)
					return (NULL);
				if (node->left == NULL || node->right == NULL)
				{
					if (node->left == NULL && node->right == NULL)
					{
						temp = node;
						if (node == node->parent->left)
							node->parent->left = NULL;
						else if (node == node->parent->right)
							node->parent->right = NULL;
						
						node = NULL;
					}
					else if (node->left == NULL)
					{
						temp = node->right;
						BaseNode* saveParent = node->parent;
						this->alloc.destroy(static_cast<Node*>(node));
						this->alloc.construct(static_cast<Node*>(node), Node(static_cast<Node*>(temp)->pair, saveParent));
					}
					else if (node->right == NULL)
					{
						temp = node->left;
						BaseNode* saveParent = node->parent;
						this->alloc.destroy(static_cast<Node*>(node));
						this->alloc.construct(static_cast<Node*>(node), Node(static_cast<Node*>(temp)->pair, saveParent));
					}
					this->alloc.destroy(static_cast<Node*>(temp));
					this->alloc.deallocate(static_cast<Node*>(temp), 1);
				}
				else
				{
					temp = node->right->leftmost();
					BaseNode* saveParent = node->parent;
					this->alloc.destroy(static_cast<Node*>(node));
					this->alloc.construct(static_cast<Node*>(node), Node(static_cast<Node*>(temp)->pair, saveParent));
					node->right = deleteBaseNode(node->right);
				}
				if (node == NULL)
					return (node);
				// equilibrage a faire
				
				return (node);
			}


			BaseNode*	insert(value_type pair)
			{
				if (root() == NULL)
				{
					root() = create(pair, &meta);
					_size++;
					return (root());
				}
				BaseNode* cursor = root();
				while (true)
				{
					if (comp(pair.first, static_cast<Node*>(cursor)->pair.first))
					{
						cursor->balance_factor += 1;
						if (cursor->left == NULL)
						{
							cursor->left = create(pair, cursor);
							_size++;
							break ;
						}
						else
						{
							cursor = cursor->left;
						}
						
					}
					else if (comp(static_cast<Node*>(cursor)->pair.first, pair.first))
					{
						cursor->balance_factor -= 1;
						if (cursor->right == NULL)
						{
							cursor->right = create(pair, cursor);
							_size++;
							break ;
						}
						else
						{
							cursor = cursor->right;
						}
					}
					else
						break;
				}
				return (cursor);
			}
		
			void	clear(BaseNode* node)
			{
				std::cout << "call to clear" << std::endl;
				if (node == NULL)
					return ;
				if (node->left != NULL)
				{
					std::cout << "go to left" << std::endl;
					clear(node->left);
				}
				if (node->right != NULL)
				{
					std::cout << "go to right" << std::endl;
					clear(node->right);
				}
				alloc.destroy(static_cast<Node*>(node));
				alloc.deallocate(static_cast<Node*>(node), 1);
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

			void	display(BaseNode* base_node, int level)
			{
				if (base_node == NULL)
				{
					ft_print_tab(level);
					std::cout << "<empty>\n";
					return ;
				}
				Node*	node = static_cast<Node*>(base_node);
				ft_print_tab(level);
				std::cout << "node : " << "BF : " << node->balance_factor << " key : " << node->pair.first << ", value : " << node->pair.second << std::endl;
				ft_print_tab(level);
				std::cout << "left \n";
				display(node->left, level + 1);
				ft_print_tab(level);
				std::cout << "right \n";
				display(node->right, level + 1);
			}

		private:

			class BaseNode
			{
				public:				// a voir
				
				// value_type  pr;   // pas de paire  value_type dans le BaseNode => uniquement dans le Node
				BaseNode*	left;
				BaseNode*	right;
				BaseNode*	parent;
				int			balance_factor;

				public:

				BaseNode(void) : left(NULL), right(NULL), parent(NULL), balance_factor(0)
				{
				}
				
				BaseNode(BaseNode* parent) : left(NULL), right(NULL), parent(parent), balance_factor(0)
				{
				}
				
				BaseNode(const BaseNode& other) : left(other.left), right(other.right), parent(other.parent), balance_factor(other.balance_factor)
				{
				}
				
				~BaseNode(void)
				{}

				BaseNode*	leftmost()
				{
					BaseNode* node = this;

					while (node->left)
						node = node->left;
					return (node);
				}

				const BaseNode*	leftmost() const
				{
					const BaseNode* node = this;

					while (node->left)
						node = node->left;
					return (node);
				}

				BaseNode*	rightmost()
				{
					BaseNode* node = this;

					while (node->right)
						node = node->right;
					return (node);
				}

				const BaseNode*	rightmost() const
				{
					const BaseNode* node = this;

					while (node->right)
						node = node->right;
					return (node);
				}

				BaseNode*	first()
				{
					return (this->leftmost());
				}

				const BaseNode*	first() const
				{
					return (this->leftmost());
				}
				
				BaseNode*	previous()
				{
					BaseNode* node = this;

					if (node->left)
						return (node->left->rightmost());

					BaseNode* parent_node = node->parent;
					while (node != parent_node->right)
					{
						node = parent_node;
						parent_node = node->parent;
					}
					return (node->parent);
				}
				
				const BaseNode*	previous() const
				{
					const BaseNode* node = this;

					if (node->left)
						return (node->left->rightmost());

					const BaseNode* parent_node = node->parent;
					while (node != parent_node->right)
					{
						node = parent_node;
						parent_node = node->parent;
					}
					return (node->parent);
				}
				
				BaseNode*	next()
				{
					BaseNode* node = this;

					if (node->right)
						return (node->right->leftmost());

					BaseNode* parent_node = node->parent;
					while (node != parent_node->left)
					{
						node = parent_node;
						parent_node = node->parent;
					}
					return (node->parent);
				}
				
				const BaseNode*	next() const
				{
					const BaseNode* node = this;

					if (node->right)
						return (node->right->leftmost());

					const BaseNode* parent_node = node->parent;
					while (node != parent_node->left)
					{
						node = parent_node;
						parent_node = node->parent;
					}
					return (node->parent);
				}
				
				Iterator	iter()
				{
					Iterator iter(this);
					
					return (iter);
				}

								
				Const_Iterator	iter() const
				{
					Const_Iterator iter(this);
					
					return (iter);
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

			class Iterator
			{
				protected:

					Node*	ptr;

					friend class Const_Iterator; // in order to construct Const_Iterator from Iterator in Const_Iterator class

				public:

					typedef ft::pair<const Key, T>			value_type;
					typedef std::ptrdiff_t					difference_type;
					typedef value_type&						reference_type;
					typedef	value_type*						pointer;
					typedef std::bidirectional_iterator_tag iterator_category;

					Iterator()
					{
						ptr = NULL;
					} 

					Iterator(BaseNode* base_node)
					{
						ptr = static_cast<Node*>(base_node);
					}

					Iterator(Node* node)
					{
						ptr = node;
					}

					Iterator(const Iterator& other) : ptr(other.ptr)
					{
					}

					~Iterator()
					{
					}

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
						ptr = static_cast<Node*>(ptr->next());
						
						return (*this);
					}


					Iterator	operator++(int)
					{
						Iterator	it_temp = *this;
						
						ptr = static_cast<Node*>(ptr->next());
						return (it_temp);
					}
					
					Iterator&	operator--(void)
					{
						ptr = static_cast<Node*>(ptr->previous());
						
						return (*this);
					}


					Iterator	operator--(int)
					{
						Iterator	it_temp = *this;
						
						ptr = static_cast<Node*>(ptr->previous());
						return (it_temp);
					}


					value_type&	operator*(void)
					{
						return (ptr->pair);
					}

					
					value_type*	operator->(void)
					{
						return (&(ptr->pair));
					}

					Node*	getNode(void)
					{
						return (ptr);
					}
					
			};

			class Const_Iterator
			{
				protected:

					const Node*	ptr;

				public:

					typedef std::bidirectional_iterator_tag iterator_category;

					Const_Iterator()
					{
						ptr = NULL;
					} 

					Const_Iterator(const BaseNode* base_node)
					{
						ptr = static_cast<const Node*>(base_node);
					}

					Const_Iterator(const Node* node)
					{
						ptr = node;
					}

					Const_Iterator(const Const_Iterator& other) : ptr(other.ptr)
					{
					}

					Const_Iterator(const Iterator& other) : ptr(other.ptr)
					{
					}

					~Const_Iterator()
					{
					}

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
						ptr = static_cast<const Node*>(ptr->next());
						
						return (*this);
					}


					Const_Iterator	operator++(int)
					{
						Const_Iterator	it_temp = *this;
						
						ptr = static_cast<const Node*>(ptr->next());
						return (it_temp);
					}
					
					Const_Iterator&	operator--(void)
					{
						ptr = static_cast<const Node*>(ptr->previous());
						
						return (*this);
					}


					Const_Iterator	operator--(int)
					{
						Const_Iterator	it_temp = *this;
						
						ptr = static_cast<const Node*>(ptr->previous());
						return (it_temp);
					}


					const value_type&	operator*(void)
					{
						return (ptr->pair);
					}

					
					const value_type*	operator->(void)
					{
						return (&(ptr->pair));
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
			
			map(const map& other) : comp(other.comp), alloc(other.alloc) // very buggy constructor allocate memory ? insert all range of elements ?
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

			T& at(const Key& key)
			{
				Iterator	it = find(key);
				if (it == end())
					throw (std::out_of_range("key not found"));
				return (it->second);
			}

			// T& operator[](const Key& key)
			// {
			// 	Iterator	it = find(key);
			// 	if (it != end())
			// 		return ((*it).second);
			// 	else
			// 		return (insert(value_type(key, T())).first->second);
			// }

			/* ----- Iterators ----- */

			Iterator begin(void)
			{
				Iterator	it;

				if (root() == NULL)
					it = Iterator(&meta);
				else
					it = Iterator(root()->first());
				return (it);
			}

			Const_Iterator begin(void) const
			{
				Const_Iterator	it;

				if (root() == NULL)
					it = Const_Iterator(&meta);
				else
					it = Const_Iterator(const_cast<const BaseNode*>(root()->first()));

				return (it);
			}

			Iterator end(void)
			{
				Iterator	it(this->end_node());

				return (it);
			}

			Const_Iterator end(void) const
			{
				Const_Iterator	it(const_cast<const BaseNode*>(this->end_node()));

				return (it);
			}

			reverse_iterator	rbegin(void)
			{
				reverse_iterator	it(this->end());
				return (it);	
			}

			const_reverse_iterator	rbegin(void) const
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

			/* ----- capacity ----- */

			bool	empty(void) const
			{
				return (_size == 0);
				// return (begin() == end());
			}

			size_type	size(void) const
			{
				return (_size);
				// return (end() - begin()); really usefull ?
			}

			size_type	max_size(void) const
			{
				return (alloc.max_size());
			}

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

			void	erase(iterator pos)
			{
				BaseNode*	node = static_cast<BaseNode*>(pos.getNode());

				deleteBaseNode(node);
			}
			
			// void erase( iterator first, iterator last )
			// {

			// }

			size_type erase( const Key& key )
			{
				Iterator	item = find(key);
				if (item == this->end())
					return (0);
				erase(item);
				return (1);
			}

			void	swap(map& other)
			{
				BaseNode*	root_temp = this->meta.left;
				size_type	size_temp = this->_size;

				this->meta.left = other.meta.left;
				other.meta.left = root_temp;

				this->_size = other._size;
				other._size = size_temp;

				if (this->root())
					this->root()->parent = &this->meta;
				if (other.root())
					other.root()->parent = &other.meta;
			}

			/* ----- lookup ----- */

			size_type count(const Key& key) const
			{
				const BaseNode *cursor; 

				cursor = root();
				while (cursor)
				{
					if (comp(key, static_cast<const Node*>(cursor)->pair.first))
						cursor = cursor->left;
					else if (comp(static_cast<const Node*>(cursor)->pair.first, key))
						cursor = cursor->right;
					else
						return (1);
				}
				return (0);
			}

			Iterator	find(const Key& key)
			{
				if (root() == NULL)
					return (end());
				
				BaseNode* cursor = root();
				while (cursor != NULL)
				{
					if (comp(key, static_cast<Node*>(cursor)->pair.first))
						cursor = cursor->left;
					else if (comp(static_cast<Node*>(cursor)->pair.first, key))
						cursor = cursor->right;
					else
						return (cursor->iter());
				}
				return (end());
			}

			Const_Iterator	find(const Key& key) const
			{
				if (root() == NULL)
					return (end());
				
				BaseNode* cursor = root();
				while (cursor != NULL)
				{
					if (comp(key, static_cast<Node*>(cursor)->pair.first))
						cursor = cursor->left;
					else if (comp(static_cast<Node*>(cursor)->pair.first, key))
						cursor = cursor->right;
					else
						return (cursor->iter());
				}
				return (end());
			}

			ft::pair<iterator, iterator> equal_range(const Key& key)
			{
				Iterator	first_iter = this->end();
				Iterator	second_iter = this->end();

				Iterator cursor = this->begin();

				while (cursor != this->end())
				{
					if (!comp(cursor->first, key))
					{
						first_iter = cursor;
						break ;
					}
					++cursor;
				}
				cursor = this->begin();
				while (cursor != this->end())
				{
					if (comp(key, cursor->first))
					{
						second_iter = cursor;
						break ;
					}
					++cursor;
				}
				return (ft::make_pair(first_iter, second_iter));
			}

			ft::pair<const_iterator, const_iterator> equal_range(const Key& key) const
			{
				Const_Iterator	first_iter = this->end();
				Const_Iterator	second_iter = this->end();

				Const_Iterator cursor = this->begin();

				while (cursor != this->end())
				{
					if (!comp(cursor->first, key))
					{
						first_iter = cursor;
						break ;
					}
					++cursor;
				}
				cursor = this->begin();
				while (cursor != this->end())
				{
					if (comp(key, cursor->first))
					{
						second_iter = cursor;
						break ;
					}
					++cursor;
				}
				return (ft::make_pair(first_iter, second_iter));
			}

			Iterator	lower_bound(const Key& key)
			{
				Iterator cursor = this->begin();

				while (cursor != this->end())
				{
					if (!comp(cursor->first, key))
					{
						return (cursor);
					}
					++cursor;
				}
				return (cursor);
			}

			Const_Iterator	lower_bound(const Key& key) const
			{
				Const_Iterator cursor = this->begin();

				while (cursor != this->end())
				{
					if (!comp(cursor->first, key))
					{
						return (cursor);
					}
					++cursor;
				}
				return (cursor);
			}

			Iterator	upper_bound(const Key& key)
			{
				Iterator cursor = this->begin();

				while (cursor != this->end())
				{
					if (comp(key, cursor->first))
					{
						return (cursor);
					}
					++cursor;
				}
				return (cursor);
			}

			Const_Iterator	upper_bound(const Key& key) const
			{
				Const_Iterator cursor = this->begin();

				while (cursor != this->end())
				{
					if (comp(key, cursor->first))
					{
						return (cursor);
					}
					++cursor;
				}
				return (cursor);
			}

			/* ----- observers ----- */

			key_compare	key_comp() const 
			{
				return (key_compare()); // ou return (comp)
			}
			
			value_compare	value_comp() const
			{
				return (value_compare(key_comp()));
			}
			
			
	};

	template <class Key, class T, class Compare, class Alloc>
	bool operator==(const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs)
	{
		typename ft::map<Key,T,Compare,Alloc>::const_iterator	lhs_first = lhs.begin();
		typename ft::map<Key,T,Compare,Alloc>::const_iterator	lhs_last = lhs.end();
		typename ft::map<Key,T,Compare,Alloc>::const_iterator	rhs_first = rhs.begin();
		
		if (lhs.size() != rhs.size())
			return (false);
		if (lhs.size() == 0 && rhs.size() == 0)
		{
			return (true);
		}
		return (ft::equal(lhs_first, lhs_last, rhs_first));	
	}

	template< class Key, class T, class Compare, class Alloc >
	bool operator!=( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs )
	{
		return (!(lhs == rhs));
	}

	template< class Key, class T, class Compare, class Alloc >
	bool operator<( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs )
	{
		if (lhs.size() == 0 && rhs.size() == 0)
			return (false);
		if (lhs.size() == 0 && rhs.size() != 0)
			return (true);
		else if (lhs.size() != 0 && rhs.size() == 0)
			return (false);
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template< class Key, class T, class Compare, class Alloc >
	bool operator<=( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs )
	{
		return (!(rhs < lhs));
	}

	template< class Key, class T, class Compare, class Alloc >
	bool operator>( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs )
	{
		return (rhs < lhs);
	}

	template< class Key, class T, class Compare, class Alloc >
	bool operator>=( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs )
	{
		return (!(lhs < rhs));
	}
}