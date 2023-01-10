/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 17:37:09 by tmoragli          #+#    #+#             */
/*   Updated: 2023/01/10 23:33:09 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP


namespace ft
{
	template <typename T1, typename T2>
	struct pair;

	template <typename T1, typename T2>
	pair<T1, T2> make_pair(T1 first, T2 second)
	{
		return (pair<T1, T2>(first, second));
	}

	template <typename T1, typename T2>
	struct pair
	{
		T1 first;
		T2 second;

		pair()
		{
		}

		pair(T1 const& _first, T2 const& _second): first(_first), second(_second)
		{
		}

		template <typename U, typename V>
		pair(pair<U, V> const& pair): first(pair.first), second(pair.second)
		{
		}

		template <typename U, typename V>
		pair	&operator=(pair<U, V> const& pair)
		{
			first = pair.first;
			second = pair.second;
			return (*this);
		}
	};

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
			typedef Key							key_type;
			typedef T							data_type;
			typedef pair<key_type, data_type>	value_type;
			typedef Compare						key_compare;
			typedef Alloc						allocator_type;

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
		
	};
}


#endif