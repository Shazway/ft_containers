/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterators.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 23:44:11 by tmoragli          #+#    #+#             */
/*   Updated: 2022/12/18 01:18:05 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATORS_HPP
#define ITERATORS_HPP
#include <iterator>

namespace ft
{
	//-ITERATOR TRAITS-//
	template<class Iterator>
	struct iterator_traits
	{
		typedef typename Iterator::difference_type			difference_type;
		typedef typename Iterator::value_type				value_type;
		typedef typename Iterator::pointer					pointer;
		typedef typename Iterator::reference				reference;
		typedef typename Iterator::iterator_category		iterator_category;
	};

	template<typename T>
	struct iterator_traits<T*>
	{
		typedef std::ptrdiff_t						difference_type;
		typedef T									value_type;
		typedef T*									pointer;
		typedef T&									reference;
		typedef std::random_access_iterator_tag		iterator_category;
	};

	template<typename T>
	struct iterator_traits<const T*>
	{
		typedef std::ptrdiff_t								difference_type;
		typedef T											value_type;
		typedef T const*									pointer;
		typedef T const&									reference;
		typedef std::random_access_iterator_tag				iterator_category;
	};
	//--------------------------------------------------------------------------//

	//-RANDOM ACCESS ITERATOR CLASS-//
	template <typename T>
	class RandomAccessIterator
	{
		public:
			typedef T													iterator_type;
			typedef typename ft::iterator_traits<T*>::difference_type	difference_type;
			typedef typename ft::iterator_traits<T*>::value_type		value_type;
			typedef typename ft::iterator_traits<T*>::pointer			pointer;
			typedef typename ft::iterator_traits<T*>::reference			reference;
			typedef typename ft::iterator_traits<T*>::iterator_category	iterator_category;
		private:
			T*	_data;
		public:
			RandomAccessIterator(): _data() {}
			RandomAccessIterator(pointer _assign): _data(_assign) {}
			RandomAccessIterator(RandomAccessIterator const& _copy): _data(_copy.base()) {}
			virtual ~RandomAccessIterator() {}

			pointer	base() const
			{
				return (_data);
			}

			operator RandomAccessIterator<T const>() const
			{
				return (RandomAccessIterator<T const>(this->_data));
			}

			RandomAccessIterator&	operator=(RandomAccessIterator const& _assign)
			{
				_data = _assign._data;
				return (*this);
			}

			RandomAccessIterator&	operator++()
			{
				++this->_data;
				return (*this);
			}

			RandomAccessIterator	operator++(int)
			{
				return (RandomAccessIterator(_data++));
			}

			RandomAccessIterator&	operator--()
			{
				--this->_data;
				return (*this);
			}

			RandomAccessIterator	operator--(int)
			{
				return (_data--);
			}

			RandomAccessIterator	operator+(difference_type const& nb) const
			{
				return (RandomAccessIterator(_data + nb));
			}

			RandomAccessIterator&	operator+=(difference_type const& nb)
			{
				_data += nb;
				return (*this);
			}

			RandomAccessIterator	operator-(difference_type const& nb) const
			{
				return (RandomAccessIterator(_data - nb));
			}

			RandomAccessIterator&	operator-=(difference_type const& nb)
			{
				_data -= nb;
				return (*this);
			}

			reference	operator[](difference_type	const& nb)
			{
				return (_data[nb]);
			}

			reference	operator*() const
			{
				return (*(this->_data));
			}

			pointer		operator->() const
			{
				return (_data);
			}
	};
	//---------------------------------------------------------------------------------//

	//-COMPARATORS FOR ITERATORS-//
	template<typename Iterator1, typename Iterator2>
	bool	operator==(RandomAccessIterator<Iterator1> const& it1, RandomAccessIterator<Iterator2> const& it2)
	{
		return (it1.base() == it2.base());
	}

	template<typename Iterator1, typename Iterator2>
	bool	operator!=(RandomAccessIterator<Iterator1> const& it1, RandomAccessIterator<Iterator2> const& it2)
	{
		return (it1.base() != it2.base());
	}

	template<typename Iterator1, typename Iterator2>
	bool	operator<(RandomAccessIterator<Iterator1> const& it1, RandomAccessIterator<Iterator2> const& it2)
	{
		return (it1.base() < it2.base());
	}

	template<typename Iterator1, typename Iterator2>
	bool	operator>(RandomAccessIterator<Iterator1> const& it1, RandomAccessIterator<Iterator2> const& it2)
	{
		return (it2 < it1);
	}

	template<typename Iterator1, typename Iterator2>
	bool	operator>=(RandomAccessIterator<Iterator1> const& it1, RandomAccessIterator<Iterator2> const& it2)
	{
		return (!(it1 < it2));
	}

	template<typename Iterator1, typename Iterator2>
	bool	operator<=(RandomAccessIterator<Iterator1> const& it1, RandomAccessIterator<Iterator2> const& it2)
	{
		return (!(it2 < it1));
	}
	//----------------------------------------------------------------//

	//-INCREMENT AND DECREMENT OPERATORS FOR ITERATORS-//
	template<typename Iterator1, typename Iterator2>
		typename RandomAccessIterator<Iterator1>::difference_type
		operator-(RandomAccessIterator<Iterator1> const& it1, RandomAccessIterator<Iterator2> const& it2)
		{
			return (it1.base() - it2.base());
		}
	template<typename Iterator>
		RandomAccessIterator<Iterator>
		operator+(typename RandomAccessIterator<Iterator>::difference_type nb,
				RandomAccessIterator<Iterator> const& it)
		{
			return (RandomAccessIterator<Iterator>(it.base() + nb));
		}
	//----------------------------------------------------------------//

	//-REVERSE ITERATORS CLASS-//
	template <typename Iterator>
	class reverse_iterator
	{
		public:
			typedef Iterator								iterator;
			typedef typename Iterator::difference_type		difference_type;
			typedef typename Iterator::value_type			value_type;
			typedef typename Iterator::pointer				pointer;
			typedef typename Iterator::reference			reference;
			typedef typename Iterator::iterator_category	iterator_category;
		private:
			Iterator	_data;
		public:
			reverse_iterator(): _data() {}
			reverse_iterator(iterator assign): _data(assign) {}
			reverse_iterator(reverse_iterator const& copy): _data(copy._data) {}

			template<typename It>
				reverse_iterator(reverse_iterator<It> const& it): _data(it.base()) {}

			virtual ~reverse_iterator() {}

			iterator	base() const
			{
				return (_data);
			}

			operator	reverse_iterator<Iterator const>() const
			{
				return (reverse_iterator<Iterator const>(_data));
			}

			reverse_iterator&	operator=(reverse_iterator const& assign)
			{
				_data = assign._data;
				return (*this);
			}

			reverse_iterator&	operator++()
			{
				_data--;
				return (*this);
			}

			reverse_iterator	operator++(int)
			{
				reverse_iterator	tmp(_data);

				_data--;
				return (tmp);
			}

			reverse_iterator&	operator--()
			{
				_data++;
				return (*this);
			}

			reverse_iterator	operator--(int)
			{
				reverse_iterator	tmp(_data);

				_data++;
				return (tmp);
			}

			reverse_iterator	operator+(difference_type const& nb) const
			{
				return (reverse_iterator(_data - nb));
			}

			reverse_iterator&	operator+=(difference_type const& nb)
			{
				_data = _data - nb;
				return (*this);
			}

			reverse_iterator	operator-(difference_type const& nb) const
			{
				return (reverse_iterator(_data + nb));
			}

			reverse_iterator&	operator-=(difference_type const& nb)
			{
				_data = _data + nb;
				return (*this);
			}

			reference	operator[](difference_type const& nb) const
			{
				return (*(*this + nb));
			}

			reference	operator*() const
			{
				iterator	tmp(_data);
				return (*--tmp);
			}

			pointer	operator->() const
			{
				return (&(operator*()));
			}
	};
	//-----------------------------------------------------------------//

	//-OPERATORS FOR REVERSE ITERATORS-//
	template<typename Iterator1, typename Iterator2>
	bool	operator==(reverse_iterator<Iterator1> const& it1, reverse_iterator<Iterator2> const& it2)
	{
		return (it1.base() == it2.base());
	}

	template<typename Iterator1, typename Iterator2>
	bool	operator!=(reverse_iterator<Iterator1> const& it1, reverse_iterator<Iterator2> const& it2)
	{
		return (it1.base() != it2.base());
	}

	template<typename Iterator1, typename Iterator2>
	bool	operator<(reverse_iterator<Iterator1> const& it1, reverse_iterator<Iterator2> const& it2)
	{
		return (it1.base() < it2.base());
	}

	template<typename Iterator1, typename Iterator2>
	bool	operator<=(reverse_iterator<Iterator1> const& it1, reverse_iterator<Iterator2> const& it2)
	{
		return (!(it2 < it1));
	}

	template<typename Iterator1, typename Iterator2>
	bool	operator>(reverse_iterator<Iterator1> const& it1, reverse_iterator<Iterator2> const& it2)
	{
		return (it2 < it1);
	}

	template<typename Iterator1, typename Iterator2>
	bool	operator>=(reverse_iterator<Iterator1> const& it1, reverse_iterator<Iterator2> const& it2)
	{
		return (!(it1 < it2));
	}

	template<typename Iterator1, typename Iterator2>
		typename reverse_iterator<Iterator1>::difference_type
		operator-(reverse_iterator<Iterator1> const& it1, reverse_iterator<Iterator2> const& it2)
		{
			return (it1.base() - it2.base());
		}

	template<typename Iterator>
	reverse_iterator<Iterator> operator+(typename reverse_iterator<Iterator>::difference_type nb,
										reverse_iterator<Iterator> const& it)
	{
		return (it.base() - nb);
	}
	//----------------------------------------------//
}

#endif