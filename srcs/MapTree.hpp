/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MapTree.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 18:14:38 by tmoragli          #+#    #+#             */
/*   Updated: 2023/01/31 17:24:21 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAPTREE_HPP
# define MAPTREE_HPP
# include <memory>
# include <cstdlib>
# include <fstream>
# include "iterators.hpp"
# include "MapTreeIterators.hpp"
# include "pair.hpp"
# include <fstream>
# include <sstream>
# include "algorithm.hpp"

namespace ft
{
	template <typename T>
	struct RBTreeNode;

	template <typename T, typename Compare, typename Alloc>
	class MapTree;

	template <typename T>
	class MapTreeIterator;

	template <typename T>
	class MapTreeConstIterator;

	template<typename T, typename Compare, typename Alloc>
	bool	operator==(MapTree<T, Compare, Alloc> const& t1, MapTree<T, Compare, Alloc> const& t2)
	{
		typedef typename MapTree<T, Compare, Alloc>::iterator iterator;

		iterator	it1;
		iterator	it2;
		for (it1 = t1.begin(), it2 = t2.begin(); it1 != t1.end() && it2 != t2.end(); it1++, it2++)
			if (*it1 != *it2)
				return (false);
		return (it1 == t1.end() && it2 == t2.end());
	}

	template<typename T, typename Compare, typename Alloc>
	bool	operator!=(MapTree<T, Compare, Alloc> const& t1, MapTree<T, Compare, Alloc> const& t2)
	{
		return (!(t1 == t2));
	}

	template<typename T, typename Compare, typename Alloc>
	bool	operator<(MapTree<T, Compare, Alloc> const& t1, MapTree<T, Compare, Alloc> const& t2)
	{
		return (ft::lexicographical_compare(t1.begin(), t1.end(), t2.begin(), t2.end()));
	}

	template<typename T, typename Compare, typename Alloc>
	bool	operator>(MapTree<T, Compare, Alloc> const& t1, MapTree<T, Compare, Alloc> const& t2)
	{
		return (t2 < t1);
	}

	template<typename T, typename Compare, typename Alloc>
	bool	operator<=(MapTree<T, Compare, Alloc> const& t1, MapTree<T, Compare, Alloc> const& t2)
	{
		return (!(t1 > t2));
	}
	template<typename T, typename Compare, typename Alloc>
	bool	operator>=(MapTree<T, Compare, Alloc> const& t1, MapTree<T, Compare, Alloc> const& t2)
	{
		return (!(t1 < t2));
	}


	template <typename T, typename Compare, typename Alloc>
	class MapTree
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
			typedef ft::RBTreeNode <value_type> Node;
			typename allocator_type::template rebind<Node>::other allocator_node;

		public:
			typedef MapTreeIterator<value_type>				iterator;
			typedef MapTreeConstIterator<value_type>			const_iterator;
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
			MapTree(compare_type const& comp = compare_type(), allocator_type const& alloc = allocator_type()): _root(NULL),
			_size(0), _sentinelStart(NULL), _sentinelEnd(NULL), _comparator(comp), _allocator(alloc), _clear(true)
			{
				_init_tree();
			}

			template <typename InputIterator>
			MapTree(InputIterator first, InputIterator last, compare_type const& comp = compare_type(), allocator_type const& alloc = allocator_type()): _root(NULL), _size(0),
			_sentinelStart(NULL), _sentinelEnd(NULL), _comparator(comp), _allocator(alloc), _clear(true)
			{
				_init_tree();
				insert(first, last);
			}

			MapTree(MapTree const& copy): _root(NULL), _size(0), _sentinelStart(NULL), _sentinelEnd(NULL),
					_comparator(copy._comparator), _allocator(copy._allocator), _clear(true)
			{
				*this = copy;
			}


			~MapTree()
			{
				if (_clear)
				{
					__clear();
					destroy_node(_sentinelEnd);
					destroy_node(_sentinelStart);
				}
			}

			#ifdef __DEBUG


				void	dump(std::string const& filename)
				{
					std::ofstream	ofs(filename.c_str());

					if (!ofs.is_open())
						return ;

					ofs << "graph g {\n";
					ofs << "\tnode [shape=plaintext, fontcolor=white, height=.1];\n\n";
					ofs << "\t" << _sentinelStart->dump(false);
					ofs << "\t" << _sentinelEnd->dump(false);
					dumpTree(ofs, _root);
					ofs << "}";

					ofs.close();
				}

				void	dumpTree(std::ofstream &ofs, Node *node)
				{
					ofs << "\t" << node->dump(true);

					if (node->left && node->left != _sentinelStart)
						dumpTree(ofs, node->left);
					if (node->right && node->right != _sentinelStart)
						dumpTree(ofs, node->right);
				}

				void	print_tree_advanced() const
				{
					const_iterator	it = begin();

					std::cout << "Tree :";
					if (it != end())
					{
						for (; it != end(); it++)
						{
							std::cout << " " << *it << ": " << it.getCurrent() << std::endl
							<< "parent: " << it.getCurrent()->parent << std::endl
							<< "left: " << it.getCurrent()->left << std::endl
							<< "right: " << it.getCurrent()->right << std::endl;
						}
					}
					else
						std::cout << "Tree is empty";
					std::cout << std::endl;

					const_reverse_iterator	c_rit = rbegin();
					std::cout << "Tree :";
					if (c_rit != rend())
						for (; c_rit != rend(); c_rit++)
							std::cout << " " << *c_rit;
					else
						std::cout << "Tree is empty";
					std::cout << std::endl;
				}

				void	print_tree() const
				{
					const_iterator	it = begin();

					std::cout << "Tree :";
					if (it != end())
						for (; it != end(); it++)
							std::cout << " " << *it << ": " << it.getCurrent();
					else
						std::cout << "Tree is empty";
					std::cout << std::endl;

					const_reverse_iterator	c_rit = rbegin();
					std::cout << "Tree :";
					if (c_rit != rend())
						for (; c_rit != rend(); c_rit++)
							std::cout << " " << *c_rit;
					else
						std::cout << "Tree is empty";
					std::cout << std::endl;
				}
			#endif

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

			void	swap(MapTree	&tree)
			{
				ft::__swap(_root, tree._root);
				ft::__swap(_sentinelStart, tree._sentinelStart);
				ft::__swap(_sentinelEnd, tree._sentinelEnd);
				ft::__swap(_size, tree._size);
				ft::__swap(_clear, tree._clear);
			}

			MapTree &operator=(MapTree const& assign)
			{
				__clear();
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
				if ((it = _insert_worker(node)) != end())
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

			template <typename InputIterator>
			void insert(InputIterator first, InputIterator last)
			{
				MapTree::iterator	trash = begin();

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
					Node	*to_delete = first.getCurrent();
					value_type	last_node_data = *last;

					while (to_delete->data != last_node_data)
						to_delete = _delete_node_worker(to_delete);
				}
				else
					_regen_tree(first, last);
			}

			void	clear()
			{
				__clear();
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

			size_type	count(const_reference val) const
			{
				return (_find(val) ? 1 : 0);
			}

			iterator	lower_bound(const_reference val)
			{
				iterator	it;

				for (it = begin(); it != end() && _comparator(*it, val); it++)
					;
				return (it);
			}

			const_iterator	lower_bound(const_reference val) const
			{
				const_iterator	it;

				for (it = begin(); it != end() && _comparator(*it, val); it++)
					;
				return (it);
			}

			iterator	upper_bound(const_reference val)
			{
				iterator	it;

				for (it = begin(); it != end() && !_comparator(val, *it); it++)
					;
				return (it);
			}

			const_iterator	upper_bound(const_reference val) const
			{
				const_iterator	it;

				for (it = begin(); it != end() && !_comparator(val, *it); it++)
					;
				return (it);
			}

			pair<iterator, iterator> equal_range(const_reference val)
			{
				return (ft::make_pair(lower_bound(val), upper_bound(val)));
			}

			pair<const_iterator, const_iterator>	equal_range(const_reference val) const
			{
				return (ft::make_pair(lower_bound(val), upper_bound(val)));
			}

			allocator_type	get_allocator() const
			{
				return (_allocator);
			}

		private:

			void	__clear()
			{
				_clear_worker(_root);
				_size = 0;
				_root = _sentinelEnd;
			}

			void	_regen_tree(iterator first, iterator last)
			{
				MapTree	new_tree(_comparator, _allocator);

				for (iterator it = begin(); it != end(); it++)
				{
					if (first == last || _comparator(*it, *first) || _comparator(*first, *it))
						new_tree.insert(*it);
					else
						first++;
				}
				new_tree._clear = false;

				__clear();
				destroy_node(_sentinelEnd);
				destroy_node(_sentinelStart);
				_root = new_tree._root;
				_sentinelStart = new_tree._sentinelStart;
				_sentinelEnd = new_tree._sentinelEnd;
				_size = new_tree._size;
			}

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
				if (!node->parent)
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

				Node	*sibling = _node_sibling(node), *parent = node->parent;

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
				else
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

			void _delete_child(Node *n, Node *o, bool both_black)
			{
				Node	*parent = o->parent;

				if (o == _root) // 2 nodes are in tree
				{
					pair<Node *, Node *>	on = swap_nodes_data(o, n);
					o = on.first;
					n = on.second;
					o->left = _sentinelStart;
					o->right = _sentinelEnd;
					_sentinelEnd->parent = o;
					_sentinelStart->parent = o;
					destroy_node(n); // Swapped data to erase
				}
				else
				{
					if (o == parent->left)
						parent->left = n;
					else
						parent->right = n;
					if (_sentinelEnd == o)
						_sentinelEnd = n;
					if (_sentinelStart == o)
						_sentinelStart = n;
					if (_sentinelStart == o->left)
					{
						Node	*sentinel_parent = n->min(n, _sentinelStart);
						sentinel_parent->left = _sentinelStart;
						_sentinelStart->parent = sentinel_parent;
					}
					if (_sentinelEnd == o->right)
					{
						Node	*sentinel_parent = n->max(n, _sentinelEnd);
						sentinel_parent->right = _sentinelEnd;
						_sentinelEnd->parent = sentinel_parent;
					}
					n->parent = o->parent;
					destroy_node(o);
					if (both_black)
						_delete_rebalance_tree(n);
					else
						n->color = BLACK;
				}
			}

			// Here i swap everything except for the data of the node, relinking it all together (because of pair<CONST key, T data> i can't just swap the data)//
			//Case where only two nodes are in the tree, so i have little to change and don't want to change sentinels.
			Node	*change_data_node(Node *node, value_type data)
			{
				Node	*sponge = create_node(data);

				sponge->left = node->left;
				sponge->right = node->right;
				sponge->parent = node->parent;

				sponge->color = node->color;
				if (_root == node)
				{
					_root = sponge;
					_root->left = sponge->left;
					_root->right = sponge->right;
				}
				if (_sentinelEnd == node)
					_sentinelEnd = sponge;
				if (_sentinelStart == node)
					_sentinelStart = sponge;
				if (node->left)
						sponge->left->parent = sponge;
				if (node->right)
						sponge->right->parent = sponge;
				if (node->parent)
				{
					if (node->parent->left == node)
						sponge->parent->left = sponge;
					else if (node->parent->right == node)
						sponge->parent->right = sponge;
				}
				destroy_node(node);
				return (sponge);
			}

			pair<Node *, Node *>	swap_nodes_data(Node *a, Node *b)
			{
				value_type	a_data = a->data;
				value_type	b_data = b->data;

				a = change_data_node(a, b_data);
				b = change_data_node(b, a_data);
				return(ft::make_pair(a, b));
			}

			Node	*_delete_node_worker(Node *n)
			{
				Node	*o = _replace_node(n);
				Node	*successor = Node::successor(n, _sentinelStart);
				bool	both_black = _is_black(o) && _is_black(n);

				if (!o)
				{
					_size--;
					_delete_leaf(n, both_black);
					return (successor);
				}
				else if(_is_null(n->left) || _is_null(n->right))
				{
					_size--;
					_delete_child(o, n, both_black);
					return (successor);
				}
				pair<Node *, Node *>	no;

				no = swap_nodes_data(n, o);
				n = no.first;
				o = no.second;
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
				_allocator.construct(node->data_addr(), val);
				node->color = RED;
				return (node);
			}

			void	destroy_node(Node *node)
			{
				allocator_node.destroy(node);
				allocator_node.deallocate(node, 1);
			}

			Node	*_copy_tree(Node *node, Node *parent = NULL) // Copies tree from n to end();
			{
				if (!node)
					return (NULL);
				value_type	tmp(node->data.first, node->data.second);

				Node *node_copy = create_node(tmp);
				node_copy->parent = parent;
				node_copy->color = node->color;
				node_copy->left = _copy_tree(node->left, node_copy);
				node_copy->right = _copy_tree(node->right, node_copy);

				return (node_copy);
			}
	};
}

#endif