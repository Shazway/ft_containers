/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 17:31:23 by tmoragli          #+#    #+#             */
/*   Updated: 2023/01/03 18:11:54 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <vector.hpp>
#include "vector.hpp"
#include "stack.hpp"
#include "algorithm.hpp"
#include "type_traits.hpp"
#include <istream>
#include "RBTree.hpp"

#define LEFT 

template <typename T>
int get_max_depth(T ref, int depth = 0)
{
	int d1 = depth;
	int d2 = depth;
	if (ref->left)
		d1 = get_max_depth(ref->left, depth + 1);
	if (ref->right)
		d2 = get_max_depth(ref->right, depth + 1);
	return ((d1 > d2) ? d1 : d2);
}

template <typename T, typename B>
void print_tree_visual(T ref, int depth, std::ostream* os, B tree)
{
	T new_stack;
	int space = 1;
	int half;
	int j = 0;

	for (int i = 0; i < depth; i++)
		space = (space * 2) + 1;
	half = (space - 1) / 2;
	for (int i = 0; i < half; i++)
		*os << " ";
	while ((int)ref.size() > j)
	{
		typename T::value_type n = ref[j];
		if (n == NULL || n->is_sentinel)
		{
			*os << "□";
			new_stack.push_back(NULL);
			new_stack.push_back(NULL);
		}
		else
		{
			if (n->color == ft::RED)
				*os << C_RED;
			*os << n->data << END;
			new_stack.push_back(n->left ? n->left : NULL);
			new_stack.push_back(n->right ? n->right : NULL);
		}
		j++;
		if ((int)ref.size() > j)
			for (int i = 0; i < space; i++)
				*os << (j%2 ? "-" : " ");
	}
	*os << std::endl;
	if (depth > 0)
		print_tree_visual(new_stack, depth - 1, os, tree);
}

template <typename T>
void print_tree(T& rbtree, std::ostream* os = &(std::cout))
{
	typedef typename T::Node*	ref;
	{
		ft::vector<ref>	pile;
		pile.push_back(rbtree.root());
		*os << "~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
		print_tree_visual(pile, get_max_depth(rbtree.root()) - 1, os, rbtree);
		*os << "~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
	}
	ref n = rbtree.begin().getCurrent();
	*os << MAGENTA;
	while (n)
	{
		*os << n->data << " ";
		n = n->successor(n, NULL);
	}
	*os << END << std::endl;
	for (int i = 0; i < (int)rbtree.size(); i++)
		*os << (((i / 10) % 2) ? GREEN : YELLOW) << (i % 10) << " ";
	*os << END << std::endl;
}

void main_map()
{
	typedef ft::RBTree<int>		rbtree;
	// typedef ft::Rbtree<int, ft::forbid_double_class_tag>		rbtree;

	{
		rbtree tree;
		try
		{
			tree.insert(4);
			print_tree(tree);
			tree.insert(3);
			print_tree(tree);
			tree.insert(2);
			print_tree(tree);
			tree.insert(1);
			print_tree(tree);
			tree.insert(5);
			print_tree(tree);
			tree.insert(6);
			print_tree(tree);
			std::cout << tree.size() << std::endl;
		}
		catch(const std::exception& e)
		{
			std::cerr << CYAN << e.what() << END << '\n';
		}
		try
		{
			tree.insert(1);
			tree.insert(2);
			tree.insert(3);
			tree.insert(4);
			tree.insert(5);
			tree.insert(6);
			print_tree(tree);
		}
		catch(const std::exception& e)
		{
			std::cerr << CYAN << e.what() << END << '\n';
		}
		// try
		// {
		// 	tree.erase(12);
		// 	print_tree(tree);
		// }
		// catch(const std::exception& e)
		// {
		// 	std::cerr << CYAN << e.what() << END << '\n';
		// }
		// try
		// {
		// 	tree.erase(5);
		// 	print_tree(tree);
		// 	tree.erase(4);
		// 	print_tree(tree);
		// 	tree.erase(4);
		// 	print_tree(tree);
		// 	tree.erase(3);
		// 	tree.erase(3);
		// 	print_tree(tree);
		// }
		// catch(const std::exception& e)
		// {
		// 	std::cerr << CYAN << e.what() << END << '\n';
		// }
	}
	// {
	// 	rbtree tree;
	// 	tree.insert(0);
	// 	tree.insert(4);
	// 	tree.insert(3);
	// 	tree.insert(1);
	// 	tree.insert(8);
	// 	tree.insert(5);
	// 	tree.insert(6);
	// 	tree.insert(5);
	// 	tree.insert(5);
	// 	tree.insert(8);
	// 	print_tree(tree);
	// }
	{
		std::stringstream buff;
		std::ostream err_str(buff.rdbuf());
		int node_nbr = -1;
		try
		{
			srand(6);
			rbtree tree;
			for (int i = 0; i < 50; i++)
			{
				std::cout << "\r insert number " << i << std::flush;
				tree.insert(rand() % 10);
			}
			std::cout << "\r";
			print_tree(tree);
			// for (int i = 0; i < 25; i++)
			// {
			// 	buff.str("");
			// 	print_tree(tree, &err_str);
			// 	std::cout << "\rdelete number " << i << std::flush;
			// 	node_nbr = rand() % tree.size();
			// 	tree.erase(tree[node_nbr]);
			// }
			// std::cout << "\r";
		// 	print_tree(tree);
		}
		catch(const std::exception& e)
		{
			std::cout << std::endl;
			std::cerr << C_RED << "Error while deleting the node " << node_nbr << ":\n" << END << buff.str() << CYAN << e.what() << END << '\n';
		}
	}
}
#include "common.hpp"

int		main(void)
{
	main_map();
	return (0);
}