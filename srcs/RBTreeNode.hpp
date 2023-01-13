/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBTreeNode.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 15:58:37 by tmoragli          #+#    #+#             */
/*   Updated: 2023/01/13 03:11:02 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBTREENODE_HPP
# define RBTREENODE_HPP
# include <memory>
# include <cstdlib>
# include <fstream>
# include "iterators.hpp"
# include "RBTree.hpp"
# include <fstream>
# include <sstream>
# define __DEBUG


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

		#ifdef __DEBUG
			std::string	dump(bool	link)
			{
				std::ostringstream	oss;

				if (!link)
				{
					oss << "\"" << this << "\" [shape=point]\n";
					return (oss.str());
				}

				std::string	color = (this->color == BLACK ? "black" : "red"); //if black it'll assign black screen
				std::string	style = (color == "black" ? ", color=white" : "");


				oss << "\"" << this << "\" [label=<";
				oss << "<table border='0' cellborder='1' cellspacing='0'>";
				oss << "<tr>";
				oss << "<td port='left' width='21px'></td>";
				oss << "<td port='middle' bgcolor='" << color
					<< "'><font color='white'>" << data << "</font></td>";
				oss << "<td port='right' width='21px'></td>";
				oss << "</tr>";
				oss << "</table>";
				oss << ">]\n";
				if (left)
					oss << "\t\"" << this << "\":left -- \"" << left << "\":middle\n";
				if (right)
					oss << "\t\"" << this << "\":right -- \"" << left << "\":middle\n";

				return (oss.str());
			}
		#endif

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
}

#endif