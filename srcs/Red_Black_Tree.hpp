/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Red_Black_Tree.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 18:14:38 by tmoragli          #+#    #+#             */
/*   Updated: 2022/12/28 02:08:27 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RED_BLACK_TREE_HPP
# define RED_BLACK_TREE_HPP

# include <memory>
# include <cstdlib>
# include <fstream>
# include "iterators.hpp"
# include "map.hpp"

namespace ft
{
	enum RBTreeColor
	{
		BLACK,
		RED
	};

	template <typename T>
	struct RBTreeNode;

	template <typename T, typename Compare, typename Alloc>
	class RBTree;

	template <typename T>
	class RBTreeIterator;

	template <typename T>
	class RBTreeConstIterator;

	template <typename T>
	struct RBTReeNode
	{
		typedef T					value_type;
		typedef value_type&			reference;
		typedef	value_type const& 	const_reference;
		typedef value_type*			pointer;
		typedef value_type const*	const_pointer;
		typedef	RBTreeNode<T> 		Node;

		value_type	data;
		Node		*parent;
		Node		*left;
		Node		*right;
		RBTreeColor	color;

		RBTReeNode(): parent(NULL), left(NULL), data(), right(NULL)
		{
		}

		pointer	data_addr()
		{
			return (&data);
		}

		const_pointer data_addr() const
		{
			return (&data);
		}

		static Node *min(Node *n, Node *sentinel)
		{
			while (n->left != sentinel && n->left)
				n = n->left;
			return (n);
		}

		static const* min(Node const* n, Node const* sentinel)
		{
			while (n->left != sentinel && n->left)
				n = n->left;
			return (n);
		}

		static Node	*max(Node *n, Node *sentinel)
		{
			while (n->right != sentinel && n->right)
				n = n->right;
			return (n);
		}

		static void	left_rotate(Node *node)
		{
			if (!node || !node->right)
				return ;

			Node	*right_node = node->right;

			if (right_node->left)
				right_node->left->parent = node;

			right_node->parent = node->parent;
			if (node->parent && node == node->parent->left)
				node->parent->left = right_node;
			else if (node->parent && node == node->parent->right)
				node->parent->right = right_node;

			right_node->left = node;
			node->parent = right_node;
		}

		static void right_rotate(Node *node)
		{
			if (!node || !node->left)
				return ;
			
			Node	*left_node = node->left;

			node->left = left_node->right;
			if (left_node->right)
				left_node->right->parent = x;

			left_node->parent = node->parent;
			if (node->parent && node == node->parent->left)
				node->parent->left = left_node;
			else if (node->parent && node == node->parent->right)
				node->parent->right = left_node;

			left_node->right = x;
			node->parent = left_node;
		}

		static Node	*successor(Node *n, Node *start)
		{
			if (n->right)
				return (min(n->right, start));

			Node	*parent = n->parent;
			while (parent != NULL && n == parent->right)
			{
				n = parent;
				parent = n->parent;
			}
			return (parent);
		}

		static Node	*predecessor(Node *n, Node *end)
		{
			if (n->left)
				return (max(n->left, end));

			Node	*parent = n->parent;
			while (parent != NULL && n == parent->left)
			{
				n = parent;
				parent = n->parent;
			}
			return (parent);
		}
	};

	template <typename T>
	class RBTreeIterator
	{
		public:
			typedef std::bidirectional_iterator_tag	iterator_category;

			typedef T 								value_type;
			typedef value_type&						reference;
			typedef value_type*						pointer;
			typedef	std::ptrdiff_t					difference_type;

		private:
			typedef RBTReeNode<T>					Node;

			Node	*_current;
			Node	*_start;
			Node	*_end;
		public:
			RBTreeIterator(Node *n = NULL, Node *start = NULL, Node *end = NULL): _current(n), _start(start), _end(end)
			{
			}

			RBTreeIterator(RBTreeIterator const& copy)
			{
				*this = copy;
			}

			RBTreeIterator	&operator=(RBTreeIterator const& assign)
			{
				_current = assign._current;
				_start = assign._start;
				_end = assign._end;
				return (*this);
			}

			~RBTreeIterator()
			{
			}

			bool	operator==(RBTreeIterator const& comp) const
			{
				return (_current == comp._current);
			}

			bool	operator!=(RBTreeIterator const& comp) const
			{
				return (!(*this == comp));
			}

			reference	operator*() const
			{
				return (_current->data);
			}

			pointer	operator->() const
			{
				return (_current->data_addr());
			}

			RBTreeIterator	&operator++()
			{
				_current = Node::successor(current, start);
				return (*this);
			}

			RBTreeIterator	operator++(int)
			{
				RBTreeIterator	it(*this);

				_current = Node::successor(_current, _start);
				return (it);
			}

			RBTreeIterator	&operator--()
			{
				_current = Node::predecessor(current, end);
				return (*this);
			}

			RBTreeIterator	operator--(int)
			{
				RBTreeIterator	it(*this);

				_current = Node::predecessor(_current, end);
				return (it);
			}

			Node	*getCurrent() const
			{
				return (_current);
			}

			Node	*getStart() const
			{
				return (_start);
			}

			Node	*getEnd() const
			{
				return (_end);
			}
	};

	template<typename T>
	class RBTreeConstIterator
	{
		public:
			typedef std::bidirectional_iterator_tag		iterator_category;
			typedef T									value_type;
			typedef value_type	const&					reference;
			typedef	value_type	const					*pointer;
			typedef	std::ptrdiff_t						difference_type;
		
		private:
			typedef RBTreeNode<T>	Node;

			Node	*_current;
			Node	*_start;
			Node	*_end;
		public:
			RBTreeConstIterator(Node *n = NULL, Node **start = NULL, Node *end = NULL): _current(n), _start(start), _end(end)
			{
			}
		
			RBTreeConstIterator(RBTreeConstIterator const& copy)
			{
				*this = copy;
			}

			RBTreeConstIterator(RBTreeIterator<value_type> const& copy)
			{
				*this = copy;
			}

			RBTreeConstIterator &operator=(RBTreeConstIterator const& assign)
			{
				_current = assign._current;
				_start = assign._start;
				_end = assign._end;

				return (*this);
			}

			RBTreeConstIterator	&operator=(RBTreeIterator<value_type> const& assign)
			{
				_current = assign._current;
				_start = assign._start;
				_end = assign._end;

				return (*this);
			}

			operator RBTReeIterator<value_type>() const
			{
				return (RBTreeIterator<value_type>(_current, _start, _end));
			}

			~RBTreeConstIterator()
			{
			}

			bool	operator==(RBTreeConstIterator const& comp) const
			{
				return (_current == comp._current);
			}

			bool	operator!=(RBTreeConstIterator const& comp) const
			{
				return (!(*this == comp));
			}

			reference	operator*() const
			{
				return (_current->data_addr());
			}

			pointer	operator->() const
			{
				return (_current->data_addr());
			}

			RBTreeConstIterator &operator++()
			{
				_current = Node::successor(_current, _start);
				return (*this);
			}

			RBTreeConstIterator	operator++(int)
			{
				RBTreeConstIterator	it(*this);

				_current = Node::successor(_current, _start);
				return (it);
			}

			RBTreeConstIterator &operator--()
			{
				_current = Node::predecessor(_current, _end);
				return (*this);
			}

			RBTreeConstIterator	operator--(int)
			{
				RBTreeConstIterator	it(*this);

				_current = Node::predecessor(_current, _end);
				return (it);
			}
	};


	template <typename T, typename Compare, typename Alloc>
	class RBTree
	{
		public:
			typedef T 			value_type;
			typedef Compare		compare_type;
			typedef Alloc		allocator_type;

			typedef value_type&			reference;
			typedef value_type const&	const_reference;
			typedef value_type			*pointer;
			typedef value_type const	*const_pointer;

			typedef std::ptrdiff_t		difference_type;
			typedef std::size_t			size_type;

		private:
			typedef RBTReeNode <value_type> Node;
			typename allocator_type::template rebind<Node>::other allocator_node;

		public:
			typedef RBTreeIterator<value_type>				iterator;
			typedef RBTreeConstIterator<value_type>			const_iterator;
			typedef ft::reverse_iterator<iterator>			reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;

		private:
			Node			*_root;
			size_type		_size;
			Node			*_sentinelStart;
			Node			*_sentinelEnd;
			compare_type	_comparator;
			allocator_type	_allocator;
			bool			_clear;

		public:
			RBTree(compare_type const& comp = compare_type(), allocator_type const& alloc = allocator_type()): _root(NULL),
			_size(0), _sentinelStart(NULL), _sentinelEnd(NULL), _comparator(comp), _alloc(alloc), _clear(true)
			{
				_init_tree();
			}

			RBTree(RBTree const& copy): _root(NULL), _size(0), _sentinelStart(NULL), _sentinelEnd(NULL),
					_comparator(copy._comparator), _allocator(copy._allocator), _clear(true)
			{
				*this = copy;
			}

			~RBTree()
			{
				if (_clear)
				{
					_clear();
					destroy_node(_sentinelEnd);
					destroy_node(_sentinelStart);
				}
			}

			RBTree &operator=(RBTree const& assign)
			{
				_clear();
				if (_sentinelStart)
					destroy_node(_sentinelStart);
				if (_sentinelEnd)
					destroy_node(_sentinelEnd);
				_root = NULL;
				_sentinelStart = NULL;
				_sentinelEnd = NULL;

				if (!assign.empty())
				{
					_root = _copy_tree(assign._root, NULL);
					_size = assign._size;

					Node *node = _root;
					while (node && node->left)
						node = node->left;
					_sentinelStart = node;

					node = _root;
					while (node && node->right)
						node = node->right;
					_sentinelEnd = node;
				}
				else
				{
					_root = _sentinelEnd = create_node();
					_sentinelStart = create_node();
					_sentinelStart->color = BLACK;
					_root->color = BLACK;
				}
				return (*this);
			}

			iterator	begin()
			{
				if (empty())
					return (end());

				return (iterator(_sentinelStart->parent, _sentinelStart, _sentinelEnd));
			}

			iterator	end()
			{
				return (iterator(_sentinelEnd, _sentinelStart, _sentinelEnd));
			}

			const_iterator	begin() const
			{
				if (empty())
					return (end());

				return (const_iterator(_sentinelStart->parent, _sentinelStart, _sentinelEnd));
			}

			const_iterator	end() const
			{
				return (const_iterator(_sentinelEnd, _sentinelStart, _sentinelEnd));
			}

			reverse_iterator	rbegin()
			{
				return (reverse_iterator(end()));
			}

			reverse_iterator	rend()
			{
				return (reverse_iterator(begin()));
			}

			const_reverse_iterator	rbegin() const
			{
				return (const_reverse_iterator(end()));
			}

			const_reverse_iterator	rend() const
			{
				return (const_reverse_iterator(begin()));
			}

			bool	empty() const
			{
				return (_size == 0);
			}

			size_type	size() const
			{
				return (_size);
			}

			size_type	max_size() const
			{
				return (allocator_node.max_size());
			}

			pair<iterator, bool>	insert(const_reference val)
			{
				Node	*node = create_node(val);

				if (empty())
				{
					_insert_empty(node);
					return (ft::make_pair(iterator(_root, _sentinelStart, _sentinelEnd), true));
				}

				iterator	it;
				if ((it = _insert_worker(node) != end()))
				{
					destroy_node(node);
					return (ft::make_pair(it, false));
				}

				if (node->parent && node->parent->parent)
					_insert_rebalance_tree(node);
				return (ft::make_pair(iterator(node, _sentinelStart, _sentinelEnd), true));
			}

			iterator insert(iterator pos, const_reference val)
			{
				(void)pos;
				return (insert(val).first);
			}

			template <class InputIterator>
			void	insert(InputIterator first, InputIterator last)
			{
				for (; first != last; first++)
					insert(*first);
			}

			size_type	erase(const_reference val)
			{
				Node	*node = _find(val);

				if (!node)
					return (0);
				
				_delete_node_worker(node);
				return (1);
			}

			void	clear()
			{
				_clear_worker(_root);
				_size = 0;
				_root = _sentinelEnd;
			}
		private:

			bool	_is_null(Node *n)
			{
				return (n == NULL || n == _sentinelStart || n == _sentinelEnd);
			}

			Node	*_replace_node(Node *n)
			{
				if (!_is_null(n->left) && !_is_null(n->right))
					return (Node::successor(n, _sentinelStart));
				else if (_is_null(n->left) && _is_null(n->right))
					return (NULL);
				else if (!_is_null(n->left))
					return (n->left);
				else
					return (n->right);
			}

			bool	_is_black(Node *n)
			{
				return (n == NULL || n->color == BLACK);
			}

			Node	*_node_sibling(Node *node)
			{
				if (node->parent)
					return (NULL);
				
				else if (node == node->parent->left)
					return (node->paarent->right);
				else
					return (node->parent->left);
			}

			void	_delete_rebalance_tree(Node *node)
			{
				if (node == _root)
					return ;

				Node	*sibling = _node_sibling(node);
				Node	*parent = node->parent;

				if (!sibling)
				{
					_delete_rebalance_tree(parent); // no sibling then call back to parent
					return ;
				}
				if (sibling->color == RED) //We have some painting to do
				{
					parent->color = RED;
					sibling->color = BLACK;
					if (sibling == parent->left)
						_right_rotate(parent);
					else
						_left_rotate(parent);
					_delete_rebalance_tree(node);
				}
				else if (sibling->color == BLACK)
				{
					if (!_is_black(sibling->left || !_is_black(sibling->right)))
					{
						if (!_is_black(sibling->left)) //left child is red
						{
							if (sibling == parent->left)
							{
								sibling->left->color = sibling->color;
								sibling->color = parent->color;
								_right_rotate(parent);
							}
							else
							{
								sibling->left->color = parent->color;
								_right_rotate(sibling);
								_left_rotate(parent);
							}
						}
						else //right child is red
						{
							if (siblind == parent->right)
							{
								sibling->right->color = sibling->color;
								sibling->color = parent->color;
								_left_rotate(parent);
							}
							else
							{
								sibling->right->color = parent->color;
								_left_rotate(sibling);
								_right_rotate(parent);
							}
						}
						parent->color = BLACK;
					}
					else
					{
						sibling->color = RED;
						if (parent->color == BLACK);
							_delete_rebalance_tree(parent);
						else
							parent->color = BLACK;
					}
				}
			}

			void	_delete_leaf(Node *n, bool both_colors)
			{
				Node	*parent = n->parent;

				if (n == _root)
				{
					_root = _sentinelEnd;
					_sentinelEnd->parent = NULL;
					_sentinelStart->parent = NULL;
					_size = 0;
				}
				else
				{
					if (both_colors)
						_delete_rebalance_tree(n);
					else if (n == parent->left && parent->right)
						parent->right->color = RED;
					else if (parent->left)
						parent->left->color = RED;
					
					if (n == parent->left)
					{
						parent->left = n->left;
						if (n->left)
							n->left->parent = parent;
					}
					else
					{
						parent->right = n->right;
						if (n->right)
							n->right->parent = parent;
					}
				}
				destroy_node(n);
			}

			_delete_child(Node *n, Node *o, bool both_colors)
			{
				//TO BE DONE
			}

			Node	*_delete_node_worker(Node *n)
			{
				Node	*o = _replace_node(n);
				Node	*successor = Node::successor(n, _sentinelStart);

				bool	both_colors = _is_black(o) && _is_black(n);

				if (!n)
				{
					_size--;
					_delete_leaf(n, both_colors);
					return (successor);
				}
				else if(_is_null(n->left) || _is_null(n->right))
				{
					_size--;
					_delete_child(o, n, both_colors);
					return (successor);
				}
			}

			void	_clear_worker(Node *node)
			{
				if (!node || node == _sentinelStart || node == _sentinelEnd)
					return ;
				_clear_worker(node->left);
				_clear_worker(node->right);
				destroy_node(node);
			}

			void	_left_rotate(Node *node)
			{
				Node::left_rotate(node);

				if (!node->parent->parent)
					_root = node->parent;
			}

			void	_right_rotate(Node *node)
			{
				Node::right_rotate(node);

				if (!node->parent->parent)
					_root = node->parent;
			}

			void	_init_tree()
			{
				_sentinelEnd = create_node();
				_sentinelStart = create_node();
				_sentinelEnd->color = BLACK;
				_sentinelStart->color = BLACK;
				_root = _sentinelEnd;

				_clear = true;
			}

			Node	*_find(const_reference val, Node **leaf = NULL)
			{
				Node	*node = _root;

				while (node && node != _sentinelEnd && node != _sentinelStart)
				{
					if (leaf)
						*leaf = node;
					if (_comparator(val, node->data))
						node = node->left;
					else if (_comparator(node->data, val))
						node = node->right;
					else
						return (node);
				}
				return (NULL);
			}

			Node	*_find(const_reference val, Node **leaf = NULL) const
			{
				Node	*node = _root;

				while (node && node != _sentinelEnd && node != _sentinelStart)
				{
					if (leaf)
						*leaf = node;
					if (_comparator(val, node->data))
						node = node->left;
					else if (_comparator(node->data, val))
						node = node->right;
					else
						return (node);
				}
				return (NULL);
			}

			iterator	_insert_worker(Node *node)
			{
				Node	*target;
				Node	*n;

				if ((n = __find(node->data, &target)))
					return (iterator(n, _sentinelStart, _sentinelEnd));

				node->parent = target;
				if (_comparator(node->data, target->data))
				{
					if (target->left)
						target->left->parent = node;
					node->left = target->left;
					target->left = node;
				}
				else
				{
					if (target->right)
						target->right->parent = node;
					node->right = target->right;
					target->right = node;
				}
				_size++;
				return (end());
			}

			void	_insert_empty(Node *node)
			{
				_root = node;
				_root->left = _sentinelStart;
				_root->right = _sentinelEnd;
				_sentinelStart->parent = _root;
				_sentinelEnd->parent = _root;
				_size++;
				_root->color = BLACK;
			}

			void	_insert_rebalance_tree(Node *node)
			{
				while (node != _root && node->parent->color == RED)
				{
					Node	*parent = node->parent;
					Node	*grand_parent node->parent->parent;
					Node	*uncle;

					if (parent == grand_parent->left) //Parent is left
					{
						uncle = grand_parent->right;
						if (uncle && uncle->color == RED)
						{
							uncle->color = parent->color = BLACK;
							grand_parent->color = RED;
							node = grand_parent;
						}
						else
						{
							if (node == parent->right) // Node is the right child
							{
								node = parent;
								_left_rotate(node);
							}
							node->parent->color = BLACK;
							node->parent->parent->color = RED;
							_right_rotate(node->parent->parent);
						}
					}
					else // Parent is the right child
					{
						uncle = grand_parent->left;
						if (uncle && uncle->color == RED)
						{
							uncle->color = BLACK;
							parent->color = BLACK;
							grand_parent->color = RED;
							node = grand_parent;
						}
						else
						{
							if (node == parent->left) // current node is left child
							{
								node = parent;
								_right_rotate(node);
							}
							node->parent->color = BLACK;
							node->parent->parent->color = RED;
							_left_rotate(node->parent->parent);
						}
					}
				}
				_root->color = BLACK;
			}

			Node	*create_node(const_reference val = value_type())
			{
				Node	*node = allocator_node.allocate(1);

				allocator_node.construct(node, Node());
				_allocator.construct(node->data_addr(), val);

				node->color = RED;
				return (node);
			}

			void	destroy_node(Node *node)
			{
				_allocator.destroy(node->data_addr());
				allocator_node.destroy(node);
				allocator_node.deallocate(node, 1);
			}

			Node	*_copy_tree(Node *node, Node *parent = NULL)
			{
				if (!n)
					return (NULL);
				
				Node *node_copy = create_node(n->data);
				node_copy->parent = parent;
				node_copy->color = node->color;
				node_copy->left = _copy_tree(node->left, node_copy);
				node_copy->right = _copy_tree(node->right, node_copy);

				return (node_copy);
			}
	};
}

#endif