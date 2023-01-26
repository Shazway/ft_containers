/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MapTreeIterators.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 16:00:20 by tmoragli          #+#    #+#             */
/*   Updated: 2023/01/26 03:40:38 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAPTREEITERATORS_HPP
# define MAPTREEITERATORS_HPP

# include <memory>
# include <cstdlib>
# include <fstream>
# include "iterators.hpp"
# include "RBTreeNode.hpp"

namespace ft
{
	template <typename T>
	class MapTreeIterator
	{
		public:
			typedef std::bidirectional_iterator_tag	iterator_category;

			typedef T 								value_type;
			typedef value_type&						reference;
			typedef value_type*						pointer;
			typedef	std::ptrdiff_t					difference_type;

		private:
			typedef RBTreeNode<T>					Node;

			Node	*_current;
			Node	*_start;
			Node	*_end;
		public:
			MapTreeIterator(Node *n = NULL, Node *start = NULL, Node *end = NULL): _current(n), _start(start), _end(end)
			{
			}

			MapTreeIterator(MapTreeIterator const& copy)
			{
				*this = copy;
			}

			MapTreeIterator	&operator=(MapTreeIterator const& assign)
			{
				_current = assign._current;
				_start = assign._start;
				_end = assign._end;
				return (*this);
			}

			~MapTreeIterator()
			{
			}

			bool	operator==(MapTreeIterator const& comp) const
			{
				return (_current == comp._current);
			}

			bool	operator!=(MapTreeIterator const& comp) const
			{
				return (!(*this == comp));
			}

			reference	operator*() const
			{
				return (*(_current->data));
			}

			pointer	operator->() const
			{
				return (_current->data_addr());
			}

			MapTreeIterator	&operator++()
			{
				_current = Node::successor(_current, _start);
				return (*this);
			}

			MapTreeIterator	operator++(int)
			{
				MapTreeIterator	it(*this);

				_current = Node::successor(_current, _start);
				return (it);
			}

			MapTreeIterator	&operator--()
			{
				_current = Node::predecessor(_current, _end);
				return (*this);
			}

			MapTreeIterator	operator--(int)
			{
				MapTreeIterator	it(*this);

				_current = Node::predecessor(_current, _end);
				return (it);
			}

			Node	*getCurrent() const
			{
				return (_current);
			}

			Node	*getStart() const
			{
				return (_start);
			}

			Node	*getEnd() const
			{
				return (_end);
			}
	};

	template<typename T>
	class MapTreeConstIterator
	{
		public:
			typedef std::bidirectional_iterator_tag		iterator_category;
			typedef T									value_type;
			typedef value_type	const&					reference;
			typedef	value_type	const					*pointer;
			typedef	std::ptrdiff_t						difference_type;
		
		private:
			typedef RBTreeNode<T>	Node;

			Node	*_current;
			Node	*_start;
			Node	*_end;
		public:
			MapTreeConstIterator(Node *n = NULL, Node *start = NULL, Node *end = NULL): _current(n), _start(start), _end(end)
			{
			}
		
			MapTreeConstIterator(MapTreeConstIterator const& copy)
			{
				*this = copy;
			}

			MapTreeConstIterator(MapTreeIterator<value_type> const& copy)
			{
				*this = copy;
			}

			MapTreeConstIterator &operator=(MapTreeConstIterator const& assign)
			{
				_current = assign._current;
				_start = assign._start;
				_end = assign._end;

				return (*this);
			}

			MapTreeConstIterator	&operator=(MapTreeIterator<value_type> const& assign)
			{
				_current = assign.getCurrent();
				_start = assign.getStart();
				_end = assign.getEnd();

				return (*this);
			}

			~MapTreeConstIterator()
			{
			}

			bool	operator==(MapTreeConstIterator const& comp) const
			{
				return (_current == comp._current);
			}

			bool	operator!=(MapTreeConstIterator const& comp) const
			{
				return (!(*this == comp));
			}

			reference	operator*() const
			{
				return (*(_current->data));
			}

			pointer	operator->() const
			{
				return (_current->data_addr());
			}

			MapTreeConstIterator &operator++()
			{
				_current = Node::successor(_current, _start);
				return (*this);
			}

			MapTreeConstIterator	operator++(int)
			{
				MapTreeConstIterator	it(*this);

				_current = Node::successor(_current, _start);
				return (it);
			}

			MapTreeConstIterator &operator--()
			{
				_current = Node::predecessor(_current, _end);
				return (*this);
			}

			MapTreeConstIterator	operator--(int)
			{
				MapTreeConstIterator	it(*this);

				_current = Node::predecessor(_current, _end);
				return (it);
			}
	};
}

#endif