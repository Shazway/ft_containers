/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBTreeIterators.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 16:00:20 by tmoragli          #+#    #+#             */
/*   Updated: 2023/01/11 20:37:12 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBTREEITERATORS_HPP
# define RBTREEITERATORS_HPP

# include <memory>
# include <cstdlib>
# include <fstream>
# include "iterators.hpp"
# include "RBTreeNode.hpp"

namespace ft
{
	template <typename T>
	class RBTreeIterator
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
			RBTreeIterator(Node *n = NULL, Node *start = NULL, Node *end = NULL): _current(n), _start(start), _end(end)
			{
			}

			RBTreeIterator(RBTreeIterator const& copy)
			{
				*this = copy;
			}

			RBTreeIterator	&operator=(RBTreeIterator const& assign)
			{
				_current = assign._current;
				_start = assign._start;
				_end = assign._end;
				return (*this);
			}

			~RBTreeIterator()
			{
			}

			bool	operator==(RBTreeIterator const& comp) const
			{
				return (_current == comp._current);
			}

			bool	operator!=(RBTreeIterator const& comp) const
			{
				return (!(*this == comp));
			}

			reference	operator*() const
			{
				return (_current->data);
			}

			pointer	operator->() const
			{
				return (_current->data_addr());
			}

			RBTreeIterator	&operator++()
			{
				_current = Node::successor(_current, _start);
				return (*this);
			}

			RBTreeIterator	operator++(int)
			{
				RBTreeIterator	it(*this);

				_current = Node::successor(_current, _start);
				return (it);
			}

			RBTreeIterator	&operator--()
			{
				_current = Node::predecessor(_current, _end);
				return (*this);
			}

			RBTreeIterator	operator--(int)
			{
				RBTreeIterator	it(*this);

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
	class RBTreeConstIterator
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
			RBTreeConstIterator(Node *n = NULL, Node **start = NULL, Node *end = NULL): _current(n), _start(start), _end(end)
			{
			}
		
			RBTreeConstIterator(RBTreeConstIterator const& copy)
			{
				*this = copy;
			}

			RBTreeConstIterator(RBTreeIterator<value_type> const& copy)
			{
				*this = copy;
			}

			RBTreeConstIterator &operator=(RBTreeConstIterator const& assign)
			{
				_current = assign._current;
				_start = assign._start;
				_end = assign._end;

				return (*this);
			}

			RBTreeConstIterator	&operator=(RBTreeIterator<value_type> const& assign)
			{
				_current = assign._current;
				_start = assign._start;
				_end = assign._end;

				return (*this);
			}

			operator RBTreeIterator<value_type>() const
			{
				return (RBTreeIterator<value_type>(_current, _start, _end));
			}

			~RBTreeConstIterator()
			{
			}

			bool	operator==(RBTreeConstIterator const& comp) const
			{
				return (_current == comp._current);
			}

			bool	operator!=(RBTreeConstIterator const& comp) const
			{
				return (!(*this == comp));
			}

			reference	operator*() const
			{
				return (_current->data_addr());
			}

			pointer	operator->() const
			{
				return (_current->data_addr());
			}

			RBTreeConstIterator &operator++()
			{
				_current = Node::successor(_current, _start);
				return (*this);
			}

			RBTreeConstIterator	operator++(int)
			{
				RBTreeConstIterator	it(*this);

				_current = Node::successor(_current, _start);
				return (it);
			}

			RBTreeConstIterator &operator--()
			{
				_current = Node::predecessor(_current, _end);
				return (*this);
			}

			RBTreeConstIterator	operator--(int)
			{
				RBTreeConstIterator	it(*this);

				_current = Node::predecessor(_current, _end);
				return (it);
			}
	};
}

#endif