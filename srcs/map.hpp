/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 17:37:09 by tmoragli          #+#    #+#             */
/*   Updated: 2022/12/26 17:42:25 by tmoragli         ###   ########.fr       */
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
}

#endif