/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 20:38:54 by tmoragli          #+#    #+#             */
/*   Updated: 2023/01/13 04:40:19 by tmoragli         ###   ########.fr       */
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
		return (p1.first < p2.first || ((!p2.first < p1.first) && p1.second < p2.second));
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
}

#endif