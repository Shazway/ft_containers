/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBTree.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 18:14:38 by tmoragli          #+#    #+#             */
/*   Updated: 2023/01/03 21:03:58 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBTREE_HPP
# define RBTREE_HPP

# include <memory>
# include <cstdlib>
# include <fstream>
# include "iterators.hpp"
# include "map.hpp"
#include "RBTreeIterators.hpp"
#include "RBTreeNode.hpp"

namespace ft
{
	template <typename T>
	struct RBTreeNode;

	template <typename T, typename Compare, typename Alloc>
	class RBTree;

	template <typename T>
	class RBTreeIterator;

	template <typename T>
	class RBTreeConstIterator;

	template <typename T, class Alloc = std::allocator<ft::RBTreeNode<T> >, typename Compare = std::less<T> >
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

			typedef ft::RBTreeNode <value_type> Node;
		private:
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
			_size(0), _sentinelStart(NULL), _sentinelEnd(NULL), _comparator(comp), _allocator(alloc), _clear(true)
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
					clear();
					destroy_node(_sentinelEnd);
					destroy_node(_sentinelStart);
				}
			}

			bool	is_sentinel(Node const* node) const
			{
				return (node == _sentinelEnd || node == _sentinelStart);
			}

			Node	*operator[](int nb)
			{
				Node	*node = begin().getCurrent();

				for (int i = 0; i < nb; i++)
					node = node->successor(node, _root);
				return (node);
			}

			RBTree &operator=(RBTree const& assign)
			{
				clear();
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

			Node	*getSentinelEnd() const
			{
				return (_sentinelEnd);
			}

			Node	*getSentinelStart() const
			{
				return (_sentinelStart);
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

			Node	*root() const
			{
				return (_root);
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
				it = _insert_worker(node);
				if ((it != end()))
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

			void	erase(iterator pos)
			{
				iterator last = pos;
				last++;
				erase(pos, last);
			}

			void	erase(iterator first, iterator last)
			{
				if (first == end())
					return ;

				if (first == begin() && last == end())
				{
					clear();
					return ;
				}

				size_type	n = 0;
				iterator	i = first;
				
				for (; i != last; i++)
					n++;
				
				if (n < _size / 2)
				{
					Node	*to_delete = first._current;
					value_type	last_node_data = *last;

					while (to_delete->data != last_node_data)
						to_delete = _delete_node_worker(to_delete);
				}
				// else
				// 	_regen_tree(first, last); //TO BE FINISHED
			}

			size_type	erase(Node *node)
			{
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

			iterator find(const_reference val)
			{
				Node	*seeker = _find(val);

				if (!seeker)
					return (end());
				return (iterator(seeker, _sentinelStart, _sentinelEnd));
			}

			const_iterator find(const_reference val) const
			{
				Node	*seeker = _find(val);

				if (!seeker)
					return (end());
				return (const_iterator(seeker, _sentinelStart, _sentinelEnd));
			}
			Node	*find(value_type	val)
			{
				return (_find(val, NULL));
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
					return (node->parent->right);
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
					if (!_is_black(sibling->left) || !_is_black(sibling->right))
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
							if (sibling == parent->right)
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
						if (parent->color == BLACK)
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

			void _delete_child(Node *n, Node *o, bool both_colors)
			{
				Node	*parent = o->parent;

				if (o == _root) // 2 nodes are in tree
				{
					ft::__swap(n->data, o->data);
					o->left = _sentinelStart;
					o->right = _sentinelEnd;
					destroy_node(n); // Swapped data to erase
				}
				else
				{
					if (o == parent->left)
						parent->left = n;
					else
						parent->right = n;
					destroy_node(o);
					n->parent = parent;
					if (both_colors)
						_delete_rebalance_tree(n);
					else
						n->color = BLACK;
				}
				return ;
			}

			Node	*_delete_node_worker(Node *n)
			{
				Node	*o = _replace_node(n);
				Node	*successor = Node::successor(n, _sentinelStart);

				bool	both_colors = _is_black(o) && _is_black(n);

				if (!o)
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

				ft::__swap(o->data, n->data);
				_delete_node_worker(o);
				return (n);
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
				_sentinelEnd->is_sentinel = true;
				_sentinelStart->is_sentinel = true;
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

				if ((n = _find(node->data, &target)))
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
					Node	*grand_parent = node->parent->parent;
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
				_allocator.construct(node, Node());

				node->data = val;
				node->color = RED;
				return (node);
			}

			void	destroy_node(Node *node)
			{
				_allocator.destroy(node);
				allocator_node.destroy(node);
				allocator_node.deallocate(node, 1);
			}

			Node	*_copy_tree(Node *node, Node *parent = NULL)
			{
				if (!node)
					return (NULL);
				
				Node *node_copy = create_node(node->data);
				node_copy->parent = parent;
				node_copy->color = node->color;
				node_copy->left = _copy_tree(node->left, node_copy);
				node_copy->right = _copy_tree(node->right, node_copy);

				return (node_copy);
			}
	};
}

#endif