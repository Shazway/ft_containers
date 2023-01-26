/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 20:38:54 by tmoragli          #+#    #+#             */
/*   Updated: 2023/01/25 23:59:14 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAIR_HPP
# define PAIR_HPP

namespace ft
{
	template <typename T1, typename T2>
	struct pair;

	template <typename T1, typename T2>
	pair<T1, T2> make_pair(T1 first, T2 second)
	{
		return (pair<T1, T2>(first, second));
	}

	template <class T1, class T2>
	bool	operator==(pair<T1, T2> const&	p1, pair<T1, T2> const&	p2)
	{
		return (p1.first == p2.first && p1.second == p2.second);
	}

	template <class T1, class T2>
	bool	operator!=(pair<T1, T2> const&	p1, pair<T1, T2> const&	p2)
	{
		return (!(p1 == p2));
	}

	template <class T1, class T2>
	bool	operator<(pair<T1, T2> const&	p1, pair<T1, T2> const&	p2)
	{
		return (p1.first < p2.first || (!(p2.first < p1.first) && p1.second < p2.second));
	}
	
	template <class T1, class T2>
	bool	operator<=(pair<T1, T2> const&	p1, pair<T1, T2> const&	p2)
	{
		return (!(p2 < p1));
	}
	
	template <class T1, class T2>
	bool	operator>(pair<T1, T2> const&	p1, pair<T1, T2> const&	p2)
	{
		return (p2 < p1);
	}
	
	template <class T1, class T2>
	bool	operator>=(pair<T1, T2> const&	p1, pair<T1, T2> const&	p2)
	{
		return (!(p1 < p2));
	}
	
	template <typename T1, typename T2>
	struct pair
	{
		typedef T1	first_type;
		typedef T2	second_type;

		first_type first;
		second_type	second;

		pair(): first(T1()), second(T2())
		{
		}

		pair(first_type const& _first, second_type const& _second): first(_first), second(_second)
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
}

#endif