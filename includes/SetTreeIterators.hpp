/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SetTreeIterators.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 18:37:13 by tmoragli          #+#    #+#             */
/*   Updated: 2023/01/26 03:46:52 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SETTREEITERATORS_HPP
#define SETTREEITERATORS_HPP


# include <memory>
# include <cstdlib>
# include <fstream>
# include "iterators.hpp"
# include "RBTreeNode.hpp"

namespace ft
{
	template <typename T>
	class SetTreeIterator
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
			SetTreeIterator(Node *n = NULL, Node *start = NULL, Node *end = NULL): _current(n), _start(start), _end(end)
			{
			}

			SetTreeIterator(SetTreeIterator const& copy)
			{
				*this = copy;
			}

			SetTreeIterator	&operator=(SetTreeIterator const& assign)
			{
				_current = assign._current;
				_start = assign._start;
				_end = assign._end;
				return (*this);
			}

			~SetTreeIterator()
			{
			}

			bool	operator==(SetTreeIterator const& comp) const
			{
				return (_current == comp._current);
			}

			bool	operator!=(SetTreeIterator const& comp) const
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

			SetTreeIterator	&operator++()
			{
				_current = Node::successor(_current, _start);
				return (*this);
			}

			SetTreeIterator	operator++(int)
			{
				SetTreeIterator	it(*this);

				_current = Node::successor(_current, _start);
				return (it);
			}

			SetTreeIterator	&operator--()
			{
				_current = Node::predecessor(_current, _end);
				return (*this);
			}

			SetTreeIterator	operator--(int)
			{
				SetTreeIterator	it(*this);

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
	class SetTreeConstIterator
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
			SetTreeConstIterator(Node *n = NULL, Node *start = NULL, Node *end = NULL): _current(n), _start(start), _end(end)
			{
			}
		
			SetTreeConstIterator(SetTreeConstIterator const& copy)
			{
				*this = copy;
			}

			SetTreeConstIterator(SetTreeIterator<value_type> const& copy)
			{
				*this = copy;
			}

			SetTreeConstIterator &operator=(SetTreeConstIterator const& assign)
			{
				_current = assign._current;
				_start = assign._start;
				_end = assign._end;

				return (*this);
			}

			SetTreeConstIterator	&operator=(SetTreeIterator<value_type> const& assign)
			{
				_current = assign.getCurrent();
				_start = assign.getStart();
				_end = assign.getEnd();

				return (*this);
			}

			~SetTreeConstIterator()
			{
			}

			operator SetTreeIterator<value_type>() const
			{
				return (SetTreeIterator<value_type>(_current, _start, _end));
			}

			bool	operator==(SetTreeConstIterator const& comp) const
			{
				return (_current == comp._current);
			}

			bool	operator!=(SetTreeConstIterator const& comp) const
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

			SetTreeConstIterator &operator++()
			{
				_current = Node::successor(_current, _start);
				return (*this);
			}

			SetTreeConstIterator	operator++(int)
			{
				SetTreeConstIterator	it(*this);

				_current = Node::successor(_current, _start);
				return (it);
			}

			SetTreeConstIterator &operator--()
			{
				_current = Node::predecessor(_current, _end);
				return (*this);
			}

			SetTreeConstIterator	operator--(int)
			{
				SetTreeConstIterator	it(*this);

				_current = Node::predecessor(_current, _end);
				return (it);
			}
	};
}

#endif
