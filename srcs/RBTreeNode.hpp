/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBTreeNode.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 15:58:37 by tmoragli          #+#    #+#             */
/*   Updated: 2023/01/03 18:06:04 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBTREENODE_HPP
# define RBTREENODE_HPP
# include <memory>
# include <cstdlib>
# include <fstream>
# include "iterators.hpp"
# include "map.hpp"
# include "RBTree.hpp"

namespace	ft
{
	enum RBTreeColor
	{
		BLACK,
		RED
	};

	template <typename T>
	struct RBTreeNode
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
		bool		is_sentinel;

		RBTreeNode(): data(), parent(NULL), left(NULL), right(NULL), is_sentinel(false)
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

		static Node const* min(Node const* n, Node const* sentinel)
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

		static Node const* max(Node const *n, Node const *sentinel)
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

			node->right = right_node->left;
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
				left_node->right->parent = node;

			left_node->parent = node->parent;
			if (node->parent && node == node->parent->left)
				node->parent->left = left_node;
			else if (node->parent && node == node->parent->right)
				node->parent->right = left_node;

			left_node->right = node;
			node->parent = left_node;
		}

		static Node	*successor(Node *n, Node *start)
		{
			if (n->right)
			{
				if (min(n->right, start)->is_sentinel)
					return NULL;
				return (min(n->right, start));
			}

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
}

#endif