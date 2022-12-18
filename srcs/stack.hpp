/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 01:39:09 by tmoragli          #+#    #+#             */
/*   Updated: 2022/12/18 02:44:58 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP

#include "algorithm.hpp"
#include "vector.hpp"

namespace ft
{
	template<class T, class Container = vector<T> >
	class stack;

	template <typename T, typename Container>
	class stack
	{
		public:
			typedef T							value_type;
			typedef Container					container_type;
			typedef typename container_type::size_type	size_type;
		protected:
			container_type	_data;
		public:
			explicit	stack(container_type const& c = container_type()): _data(c) {}

			~stack() {}

			bool	empty() const
			{
				return (_data.empty());
			}

			size_type	size() const
			{
				return (_data.size());
			}

			value_type	&top()
			{
				return (_data.back());
			}

			value_type const&	top() const
			{
				return (_data.back());
			}

			void	push(value_type const& val)
			{
				_data.push_back(val);
			}

			void	pop()
			{
				_data.pop_back();
			}

			friend
			bool	operator<(ft::stack<T, Container> const& s1, ft::stack<T, Container> const& s2)
			{
				return (s1._data < s2._data);
			}
	};
}

#endif