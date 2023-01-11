/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBTreeNode.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 15:58:37 by tmoragli          #+#    #+#             */
/*   Updated: 2023/01/11 18:14:57 by tmoragli         ###   ########.fr       */
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

			Node	*tmp = node->right;

			node->right = tmp->left;
			if (tmp->left)
				tmp->left->parent = node;

			tmp->parent = node->parent;
			if (node->parent && node == node->parent->left)
				node->parent->left = tmp;
			else if (node->parent && node == node->parent->right)
				node->parent->right = tmp;

			tmp->left = node;
			node->parent = tmp;
		}

		static void right_rotate(Node *node)
		{
			if (!node || !node->left)
				return ;
			
			Node	*tmp = node->left;

			node->left = tmp->right;
			if (tmp->right)
				tmp->right->parent = node;

			tmp->parent = node->parent;
			if (node->parent && node == node->parent->left)
				node->parent->left = tmp;
			else if (node->parent && node == node->parent->right)
				node->parent->right = tmp;

			tmp->right = node;
			node->parent = tmp;
		}

		static Node	*successor(Node *n, Node *start)
		{
			if (n && n->right)
			{
				// if (min(n->right, start)->is_sentinel)
				// 	return NULL;
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