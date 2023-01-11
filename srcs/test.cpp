/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 17:31:23 by tmoragli          #+#    #+#             */
/*   Updated: 2023/01/11 19:10:41 by tmoragli         ###   ########.fr       */
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
	ft::map<int, std::string>	map;

	int		a = 5;
	std::string	b = "testing";

	map.insert(ft::make_pair(a, b));
	print_tree(map)
}

int		main(void)
{
	main_map();
	return (0);
}