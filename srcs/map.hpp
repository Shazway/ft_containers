/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 17:37:09 by tmoragli          #+#    #+#             */
/*   Updated: 2023/01/13 04:25:46 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

#include "RBTree.hpp"
#include "pair.hpp"

namespace ft
{
	template <typename Key, typename T, typename Compare = std::less<Key>, typename Alloc = std::allocator<pair<Key, T> > >
	class map;

	template <typename Key, typename T, typename Compare, typename Alloc>
	bool	operator>(map<Key, T, Compare, Alloc> const& m1, map<Key, T, Compare, Alloc> const& m2)
	{
		return (m1 < m2);
	}

	template <typename Key, typename T, typename Compare, typename Alloc>
	bool	operator==(map<Key, T, Compare, Alloc> const& m1, map<Key, T, Compare, Alloc> const& m2)
	{
		return (!(m1 < m2) && !(m1 > m2));
	}
	template <typename Key, typename T, typename Compare, typename Alloc>
	bool	operator!=(map<Key, T, Compare, Alloc> const& m1, map<Key, T, Compare, Alloc> const& m2)
	{
		return (!(m1 == m2));
	}

	template <typename Key, typename T, typename Compare, typename Alloc>
	bool	operator<=(map<Key, T, Compare, Alloc> const& m1, map<Key, T, Compare, Alloc> const& m2)
	{
		return (!(m1 > m2));
	}

	template <typename Key, typename T, typename Compare, typename Alloc>
	bool	operator>=(map<Key, T, Compare, Alloc> const& m1, map<Key, T, Compare, Alloc> const& m2)
	{
		return (!(m1 < m2));
	}

	template <typename Key, typename T, typename Compare, typename Alloc>
	void	swap(map<Key, T, Compare, Alloc> &m1, map<Key, T, Compare, Alloc> &m2)
	{
		m1.swap(m2); //to do in class
	}

	template <typename Key, typename T, typename Compare, typename Alloc>
	class map
	{
		public:
			typedef Key													key_type;
			typedef T													data_type;
			typedef pair<key_type, data_type>							value_type;
			typedef Compare												key_compare;
			typedef Alloc												allocator_type;

		private:
			//Comparator class
			class value_compare
			{
				private:
					key_compare	_comparator;
				
				public:
					typedef bool		result_type;
					typedef value_type	first_arg;
					typedef value_type	second_arg;
				
				value_compare(key_compare c): _comparator(c)
				{
				}

				bool operator()(value_type const& x, value_type const& y) const
				{
					return (_comparator(x.first, y.first));
				}
			};

			typedef ft::RBTree<value_type, value_compare, allocator_type>	tree_type;

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
				map(key_compare const& comp = key_compare(), allocator_type const& alloc = allocator_type()): _tree(value_compare(comp), alloc), _comp(comp)
				{
				}
				
				template <class InputIterator>
				map(InputIterator const& first, InputIterator const& last, key_compare const& comp = key_compare(), allocator_type const& alloc = allocator_type()): _tree(first, last, value_compare(comp), alloc), _comp(comp)
				{
				}

				map(map const& copy): _tree(copy._tree), _comp(copy._comp)
				{
				}

				~map()
				{
				}

				//#ifdef __DEBUG
				//	void	print_tree() const
				//	{
				//		_tree.print_tree();
				//	}
				//#endif

				map&	operator=(map const& assign)
				{
					_tree = assign._tree;
					return (*this);
				}

				iterator begin()
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

				reverse_iterator rbegin()
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

				const_reference	at(Key const& key) const
				{
					iterator	it = find(key);

					if (it == NULL)
					{
						std::ostringstream	oss;

						oss << "map key (which is " << key << ") does not exist";
						throw (std::out_of_range(oss.str()));
					}
					return ((*it));
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

				data_type	&operator[](key_type const& key)
				{
					return ((insert(ft::make_pair(key, data_type())).first)->second);
				}

				pair<iterator, bool>	insert(const_reference val)
				{
					return (_tree.insert(val));
				}

				iterator	insert(iterator pos, const_reference val)
				{
					return (_tree.insert(pos, val));
				}

				template <class InputIterator>
				void	insert(InputIterator first, InputIterator last)
				{
					_tree.insert(first, last);
				}

				void	erase(iterator pos)
				{
					_tree.erase(pos);
				}

				size_type	erase(key_type const& key)
				{
					return (_tree.erase(ft::make_pair(key, data_type())));
				}

				void	erase(iterator first, iterator last)
				{
					_tree.erase(first, last);
				}

				void	swap(map& x)
				{
					_tree.swap(x._tree);
				}

				void	clear()
				{
					_tree.clear();
				}

				key_compare key_comp() const
				{
					return (_comp);
				}

				value_compare value_comp() const
				{
					return (value_compare(_comp));
				}

				iterator find(key_type const& key)
				{
					return (_tree.find(ft::make_pair(key, data_type())));
				}

				const_iterator find(key_type const& key) const
				{
					return (_tree.find(ft::make_pair(key, data_type())));
				}

				size_type count(key_type const& key) const
				{
					return (_tree.count(ft::make_pair(key, data_type())));
				}

				iterator lower_bound(key_type const& key)
				{
					return (_tree.lower_bound(ft::make_pair(key, data_type())));
				}

				const_iterator lower_bound(key_type const& key) const
				{
					return (_tree.lower_bound(ft::make_pair(key, data_type())));
				}

				iterator upper_bound(key_type const& key)
				{
					return (_tree.upper_bound(ft::make_pair(key, data_type())));
				}

				const_iterator upper_bound(key_type const& key) const
				{
					return (_tree.upper_bound(ft::make_pair(key, data_type())));
				}

				pair<iterator, iterator> equal_range(key_type const& key)
				{
					return (_tree.equal_range(ft::make_pair(key, data_type())));
				}

				pair<const_iterator, const_iterator> equal_range(key_type const& key) const
				{
					return (_tree.equal_range(ft::make_pair(key, data_type())));
				}

				allocator_type get_allocator() const
				{
					return (_tree.get_allocator());
				}

				friend bool operator<(map const& x, map const& y)
				{
					return (x._tree < y._tree);
				}
	};
}


#endif