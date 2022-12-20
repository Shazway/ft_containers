/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Red_Black_Tree.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 18:14:38 by tmoragli          #+#    #+#             */
/*   Updated: 2022/12/20 21:34:34 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RED_BLACK_TREE_HPP
# define RED_BLACK_TREE_HPP

# include <memory>
# include <cstdlib>
# include <fstream>

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

			RBTreeIterator	&operator=(RBTreeConstIterator const& assign)
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
}

#endif