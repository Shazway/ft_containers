/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 02:06:24 by tmoragli          #+#    #+#             */
/*   Updated: 2023/01/16 15:22:53 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SET_HPP
# define SET_HPP

#include "RBTree.hpp"
#include "type_traits.hpp"
#include <iostream>

namespace ft
{
	template <typename T, typename Compare = ft::less<T>, typename Alloc = std::allocator<T> >
	class set;

	template <typename T, typename Compare, typename Alloc>
	bool	operator>(set<T, Compare, Alloc> const& s1, set<T, Compare, Alloc> const& s2)
	{
		return (s2 < s1);
	}

	template <typename T, typename Compare, typename Alloc>
	bool	operator==(set<T, Compare, Alloc> const& s1, set<T, Compare, Alloc> const& s2)
	{
		return (!(s2 < s1) && !(s1 < s2));
	}

	template <typename T, typename Compare, typename Alloc>
	bool	operator!=(set<T, Compare, Alloc> const& s1, set<T, Compare, Alloc> const& s2)
	{
		return (!(s1 == s2));
	}

	template <typename T, typename Compare, typename Alloc>
	bool	operator<=(set<T, Compare, Alloc> const& s1, set<T, Compare, Alloc> const& s2)
	{
		return (!(s1 > s2));
	}

	template <typename T, typename Compare, typename Alloc>
	bool	operator>=(set<T, Compare, Alloc> const& s1, set<T, Compare, Alloc> const& s2)
	{
		return (!(s1 < s2));
	}

	
	template <typename T, typename Compare, typename Alloc>
	void	swap(set<T, Compare, Alloc> &s1, set<T, Compare, Alloc> &s2)
	{
		s1.swap(s2);
	}

	
	template <typename T, typename Compare, typename Alloc>
	class set
	{
		public:
			typedef T		key_type;
			typedef T		value_type;
			typedef Compare	key_compare;
			typedef Compare value_compare;
			typedef Alloc	allocator_type;

		private:
			typedef RBTree<value_type, value_compare, allocator_type>	tree_type;

		public:
			typedef typename tree_type::reference			reference;
			typedef typename tree_type::const_reference		const_reference;
			typedef typename tree_type::pointer				pointer;
			typedef typename tree_type::const_pointer		const_pointer;

			typedef typename tree_type::iterator				iterator;
			typedef typename tree_type::const_iterator			const_iterator;
			typedef typename tree_type::reverse_iterator		reverse_iterator;
			typedef typename tree_type::const_reverse_iterator	const_reverse_iterator;

			typedef typename tree_type::difference_type			difference_type;
			typedef typename tree_type::size_type				size_type;

		private:
			tree_type	_tree;
			key_compare	_comp;

		public:
			explicit set(key_compare const& comp = key_compare(), allocator_type const& alloc = allocator_type()): _tree(value_compare(comp), alloc), _comp(comp)
			{
			}

			template <typename InputIterator>
			set(InputIterator first, InputIterator last, key_compare const& comp = key_compare(), allocator_type const& alloc = allocator_type()) : _tree(first, last, value_compare(comp), alloc), _comp(comp)
			{
			}

			set(set const& copy): _tree(copy._tree), _comp(copy._comp)
			{
			}

			~set()
			{
			}

			set	&operator=(set const& assign)
			{
				_tree = assign._tree;
				return (*this);
			}

			iterator	begin()
			{
				return (_tree.begin());
			}

			const_iterator	begin() const
			{
				return (_tree.begin());
			}

			iterator	end()
			{
				return (_tree.end());
			}

			const_iterator	end() const
			{
				return (_tree.end());
			}

			reverse_iterator	rbegin()
			{
				return (_tree.rbegin());
			}

			const_reverse_iterator	rbegin() const
			{
				return (_tree.rbegin());
			}

			reverse_iterator	rend()
			{
				return (_tree.rend());
			}

			const_reverse_iterator	rend() const
			{
				return (_tree.rend());
			}

			bool	empty() const
			{
				return (_tree.empty());
			}

			size_type	size() const
			{
				return (_tree.size());
			}

			size_type	max_size() const
			{
				return (_tree.max_size());
			}

			pair<iterator, bool>	insert(const_reference val)
			{
				return (_tree.insert(val));
			}

			iterator	insert(iterator pos, const_reference val)
			{
				return (_tree.insert(pos, val));
			}

			template <typename InputIterator>
			void	insert(InputIterator first, InputIterator last)
			{
				_tree.insert(first, last);
			}

			void	erase(iterator	pos)
			{
				_tree.erase(pos);
			}

			size_type	erase(value_type const& val)
			{
				return (_tree.erase(val));
			}

			void	erase(iterator first, iterator last)
			{
				_tree.erase(first, last);
			}

			void	swap(set &other)
			{
				_tree.swap(other._tree);
			}

			void	clear()
			{
				_tree.clear();
			}

			key_compare	key_comp() const
			{
				return (_comp);
			}

			value_compare	value_comp() const
			{
				return (_comp);
			}

			iterator	find(key_type const& key)
			{
				return (_tree.find(key));
			}

			const_iterator	find(key_type const& key) const
			{
				return (_tree.find(key));
			}

			size_type	count(key_type const& key) const
			{
				return (_tree.count(key));
			}

			iterator	lower_bound(key_type const& key)
			{
				return (_tree.lower_bound(key));
			}

			const_iterator	lower_bound(key_type const& key) const
			{
				return (_tree.lower_bound(key));
			}

			iterator	upper_bound(key_type const& key)
			{
				return (_tree.upper_bound(key));
			}

			const_iterator	upper_bound(key_type const& key) const
			{
				return (_tree.upper_bound(key));
			}

			pair<iterator, iterator>	equal_range(key_type const& key)
			{
				return (_tree.equal_range(key));
			}

			pair<const_iterator, const_iterator>	equal_range(key_type const& key) const
			{
				return (_tree.equal_range(key));
			}

			allocator_type	get_allocator() const
			{
				return (_tree.get_allocator());
			}

			friend bool	operator<(set const& s1, set const& s2)
			{
				return (s1._tree < s2._tree);
			}
	};
}

#endif