/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesoeuv <mdesoeuv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 14:45:27 by mdesoeuv          #+#    #+#             */
/*   Updated: 2022/05/16 13:32:02 by mdesoeuv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "pair.hpp"
#include "equal.hpp"
#include "lexicographical_compare.hpp"
#include "Reverse_Iterator.hpp"

namespace ft
{
	int	max(int a, int b);

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

			/* ----- display function ----- */
			
			public:

			void	display(void)
			{
				displayBaseNode(root(), 0);
			}
			
		private:

			key_compare			comp;
			node_allocator_type	alloc;
			
			BaseNode		meta;
			size_type		_size;

		private:
		
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

			int	getBalanceFactor(BaseNode* node)
			{
				if (node == NULL)
					return (0);
				return (node->getHeight(node->left) - node->getHeight(node->right));
			}

			BaseNode*	leftRotation(BaseNode* node)
			{
				// std::cout << "left rotation" << std::endl;
				
				if (node == NULL)
					return (node);
				
				BaseNode*	y = node->right;
				BaseNode*	t2 = y->left;

				node->right = t2;
				y->left = node;

				if (node == root())
					root() = y;

				y->parent = node->parent;
				if (t2)
					t2->parent = node;
				node->parent = y;
				
				node->height = 1 + std::max(node->getHeight(node->left), node->getHeight(node->right));
				y->height = 1 + std::max(node->getHeight(y->left), node->getHeight(y->right));

				return (y);
			}

			BaseNode*	rightRotation(BaseNode* node)
			{
				// std::cout << "right rotation" << std::endl;
				
				if (node == NULL)
					return (node);
				
				BaseNode*	y = node->left;
				BaseNode*	t3 = y->right;
				if (node == root())
					root() = y;
				
				y->parent = node->parent;
				node->left = t3;
				if (t3)
					t3->parent = node;
				y->right = node;

				node->parent = y;

				node->height = 1 + std::max(node->getHeight(node->left), node->getHeight(node->right));
				y->height = 1 + std::max(node->getHeight(y->left), node->getHeight(y->right));

				return (y);
			}


			BaseNode*	balanceTree(BaseNode* node)
			{
				int	balance = getBalanceFactor(node);

				if (node == NULL)
					return (node);
				if (balance == 2 && getBalanceFactor(node->left) == 1)
				{
					std::cout << "LL imbalance" << std::endl;
					return (rightRotation(node));
				}

				if (balance == -2 && getBalanceFactor(node->right) == -1)
				{
					std::cout << "RR imbalance" << std::endl;
					return (leftRotation(node));
				}

				if (balance == 2 && getBalanceFactor(node->left) == -1)
				{
					std::cout << "LR imbalance" << std::endl;
					node->left = leftRotation(node->left);
					return (rightRotation(node));
				}

				if (balance == -2 && getBalanceFactor(node->right) == 1)
				{
					std::cout << "RL imbalance" << std::endl;
					node->right = rightRotation(node->right);
					return (leftRotation(node));
				}

				return (node);

			}

			BaseNode*	create(const value_type& pair, BaseNode* parent)
			{
				Node*	new_node;

				new_node = alloc.allocate(1);
				try
				{
					alloc.construct(new_node, Node(pair, parent));
				}
				catch(...)
				{
					alloc.deallocate(new_node, 1);
					throw ;
				}
				_size++;
				return (static_cast<BaseNode*>(new_node));			
			}

			void	subtree_shift(BaseNode* node, BaseNode* new_node)
			{
				if (node == root())
					root() = new_node;
				else if (node == node->parent->left)
					node->parent->left = new_node;
				else if (node == node->parent->right)
					node->parent->right = new_node;
				if (new_node != NULL)
					new_node->parent = node->parent;
			}

			// void	subtree_shift(BaseNode* node, BaseNode* new_node)
			// {
			// 	BaseNode* parent = node->parent;
			// 	(node == parent->left)
			// 		? parent->left
			// 		: parent->right = new_node;
			// 	new_node->parent = parent;
			// }

			void	deleteNode(BaseNode* node)
			{
				if (node->left == NULL)
				{
					subtree_shift(node, node->right);
					rebalance(node->right);
				}
				else if (node->right == NULL)
				{
					subtree_shift(node, node->left);
					rebalance(node->left);
				}
				else
				{
					BaseNode* y = node->next();
					if (y->parent != node)
					{
						subtree_shift(y, y->right);
						y->right = node->right;
						y->right->parent = y;
						
						balanceTree(y->right);
					}
					subtree_shift(node, y);
					y->left = node->left;
					y->left->parent = y;
					rebalance(y);
				}
				removeNode(node);
			}

			void	removeNode(BaseNode* node)
			{
				this->alloc.destroy(static_cast<Node*>(node));
				this->alloc.deallocate(static_cast<Node*>(node), 1);
				_size--;
			}

			void	rebalance(BaseNode* node)
			{
				if (node == NULL)
					return ;
				while (node != &meta)
				{
					node->height = 1 + std::max(node->getHeight(node->left), node->getHeight(node->right));
					balanceTree(node);
					node = node->parent;
				}
			}


			BaseNode*	insertBaseNode(BaseNode* node, BaseNode* parent, value_type pair)
			{
				if (node == NULL)
					return (create(pair, parent));
				if (comp(pair.first, static_cast<Node*>(node)->pair.first))
					node->left = insertBaseNode(node->left, node, pair);
				else if (comp(static_cast<Node*>(node)->pair.first, pair.first))
					node->right = insertBaseNode(node->right, node, pair);
				else
					return (node);

				node->height = 1 + std::max(node->getHeight(node->left), node->getHeight(node->right));
				
				return (balanceTree(node));
			}

			void	clearBaseNode(BaseNode*& node)
			{
				if (node == NULL)
					return ;
				if (node->left != NULL)
					clearBaseNode(node->left);
				if (node->right != NULL)
					clearBaseNode(node->right);
				alloc.destroy(static_cast<Node*>(node));
				alloc.deallocate(static_cast<Node*>(node), 1);
				_size--;
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

			private:

			void	displayBaseNode(BaseNode* base_node, int level)
			{
				if (base_node == NULL)
				{
					ft_print_tab(level);
					std::cout << "<empty>\n";
					return ;
				}
				Node*	node = static_cast<Node*>(base_node);
				ft_print_tab(level);
				std::cout << "node : " << "BF : " << getBalanceFactor(node) << " key : " << node->pair.first << ", value : " << node->pair.second << std::endl;
				ft_print_tab(level);
				std::cout << "left \n";
				displayBaseNode(node->left, level + 1);
				ft_print_tab(level);
				std::cout << "right \n";
				displayBaseNode(node->right, level + 1);
			}

		private:

			class BaseNode
			{
				public:				// a voir pour protected ?
				
				BaseNode*	left;
				BaseNode*	right;
				BaseNode*	parent;
				int			height;

				public:

				BaseNode(void) : left(NULL), right(NULL), parent(NULL), height(1)
				{
				}
				
				BaseNode(BaseNode* parent) : left(NULL), right(NULL), parent(parent), height(1)
				{
				}
				
				// a voir, constructeur normalement inutile, passer en private ?
				BaseNode(const BaseNode& other) : left(other.left), right(other.right), parent(other.parent), height(other.height)
				{
				}
				
				~BaseNode(void)
				{}

				int	getHeight(BaseNode* node)
				{
					if (node == NULL)
						return (0);
					return (node->height);
				}

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

					BaseNode*	getNode(void)
					{
						return (static_cast<BaseNode*>(ptr));
					}
					
			};

			class Const_Iterator
			{
				protected:

					const Node*	ptr;

				public:

					typedef ft::pair<const Key, T>			value_type;
					typedef std::ptrdiff_t					difference_type;
					typedef value_type&						reference_type;
					typedef	value_type*						pointer;
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
			
			map(const map& other) : comp(other.comp), alloc(other.alloc)
			{
				*this = other;
			}
			
			~map(void)
			{
				clear();
			}
			
			map&	operator=(const map& other)
			{
				clear();				

				for (Const_Iterator iter = other.begin(); iter != other.end(); ++iter)
				{
					this->insert(*iter);
				}
				_size = other.size();
				return (*this);
			}

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
				clearBaseNode(root());
				meta.left = NULL;
			}
			
			ft::pair<iterator, bool> insert(const value_type& value) // try catch ??
			{
				size_type	old_size = size();
				Iterator	inserted_node;
				
				if (root() == NULL)
				{
					root() = create(value, &meta);
					return (ft::make_pair(Iterator(root()), true));
				}
				insertBaseNode(root(), &meta, value);
				inserted_node = find(value.first);
				if (old_size == size())
					return (ft::make_pair(inserted_node, false));
				else
					return (ft::make_pair(inserted_node, true));
			}

			// iterator insert( iterator hint, const value_type& value ) // wtf how to update balance factor if insertion from child node  ??
			// {
			// 	(void)hint;

			// 	// verifier que le noeud peut etre inseré a l'endroit demandé, si oui insertion puis rebalance vers le haut
			// 	return (insert(value).first);
			// }
			
			template <class InputIt>
			void insert(InputIt first, InputIt last)
			{
				for (; first != last; ++first)
				{
					insert(*first);
				}
			}

			void	erase(iterator pos)
			{
				deleteNode(pos.getNode());
			}
			
			void erase( iterator first, iterator last )
			{
				iterator temp = first;
				for (; first != last;)
				{
					++temp;
					std::cout << "erasing iter with key : " << (*first).first << std::endl;
					deleteNode(first.getNode());
					first = temp;
				}
				std::cout << "lol" << std::endl;

			}

			size_type erase( const Key& key )
			{
				Iterator	item = find(key);
				if (item == this->end())
					return (0);
				deleteNode(item.getNode());
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
				Const_Iterator cursor; 

				cursor = find(key);
				if (cursor != this->end())
					return (1);
				return (0);
			}

			Iterator	find(const Key& key)
			{
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
				const BaseNode* cursor = root();
				while (cursor != NULL)
				{
					if (comp(key, static_cast<const Node*>(cursor)->pair.first))
						cursor = cursor->left;
					else if (comp(static_cast<const Node*>(cursor)->pair.first, key))
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