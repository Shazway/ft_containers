/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 00:07:02 by tmoragli          #+#    #+#             */
/*   Updated: 2023/01/26 04:27:55 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef VECTOR_HPP
# define VECTOR_HPP

# include "algorithm.hpp"
# include "type_traits.hpp"
# include "iterators.hpp"
#include <numeric>
#include <cstring>
#include <string>
#include <sstream>
#include <stdexcept>
#include <exception>
#include <memory>
#include <vector>
#include "Colors.hpp"

namespace ft
{
	template < typename T, typename Alloc = std::allocator<T> >
	class vector;

	template <typename T>
	void	swap(vector<T> &a, vector<T> &b)
	{
		a.swap(b);
	}
	//Faire les iterators
	template <typename T>
	bool	operator==(vector<T> const& v1, vector<T> const& v2)
	{
		if (v1.size() != v2.size())
			return (false);
		for (typename vector<T>::size_type i = 0; i < v1.size(); i++)
			if(v1[i] != v2[i])
				return (false);
		return(true);
	}

	template <typename T>
	bool	operator!=(vector<T> const& v1, vector<T> const& v2)
	{
		if (v1 == v2)
			return (false);
		return (true);
	}

	template <typename T>
	bool	operator<(vector<T> const& v1, vector<T> const& v2)
	{
		return (ft::lexicographical_compare(v1.begin(), v1.end(), v2.begin(), v2.end()));
	}

	template <typename T>
	bool	operator>(vector<T> const& v1, vector<T> const& v2)
	{
		return (v2 < v1);
	}

	template <typename T>
	bool	operator<=(vector<T> const& v1, vector<T> const& v2)
	{
		return (!(v2 < v1));
	}
	template <typename T>
	bool	operator>=(vector<T> const& v1, vector<T> const& v2)
	{
		return (!(v1 < v2));
	}
}

template <typename T, typename Alloc>
class ft::vector
{
public:
	typedef T		value_type;
	typedef Alloc	allocator_type;

	typedef typename allocator_type::reference			reference;
	typedef typename allocator_type::const_reference	const_reference;
	typedef typename allocator_type::pointer			pointer;
	typedef typename allocator_type::const_pointer		const_pointer;
	typedef typename ft::RandomAccessIterator<T>				iterator;
	typedef typename ft::RandomAccessIterator<const T>			const_iterator;
	typedef typename ft::reverse_iterator<iterator>				reverse_iterator;
	typedef typename ft::reverse_iterator<const_iterator>		const_reverse_iterator;

	typedef typename allocator_type::size_type			size_type;
	typedef typename allocator_type::difference_type	difference_type;
private:
	pointer			_data;
	size_type		_capacity;
	size_type		_size;
	allocator_type	_allocator;
public:
	//CONSTRUCT/DESTRUCT
	explicit vector(allocator_type const& alloc = allocator_type()): _data(NULL), _capacity(0), _size(0), _allocator(alloc)
	{
	}
	
	explicit vector(size_type count, const_reference val = value_type(), allocator_type const& alloc = allocator_type()): _data(NULL), _capacity(0), _size(0), _allocator(alloc)
	{
		_data = _allocator.allocate(count);
		_capacity = count;
		for (;_size < count; _size++)
			_allocator.construct(_data + _size, val);
	}

	template <class InputIterator>
	vector(InputIterator first, InputIterator last, allocator_type const& alloc = allocator_type()): _data(NULL), _capacity(0), _size(0), _allocator(alloc)
	{
		typedef typename ft::is_integral<InputIterator>	_Integral;

		_init_vec(first, last, _Integral());
	}

	vector(vector const& copy, allocator_type const& alloc = allocator_type() = allocator_type()): _data(NULL), _capacity(0), _size(0), _allocator(alloc)
	{
		*this = copy;
	}

	~vector()
	{
		clear();
		_allocator.deallocate(_data, _capacity);
	}

	vector	&operator=(vector<value_type> const& _assign)
	{
		_allocator = _assign._allocator;
		assign(_assign.begin(), _assign.end());
		return (*this);
	}

	iterator	begin()
	{
		return (iterator(_data));
	}
	
	iterator	end()
	{
		return (iterator(_data + _size));
	}

	const_iterator	begin() const
	{
		return (const_iterator(_data));
	}

	const_iterator	end() const
	{
		return (const_iterator(_data + _size));
	}

	reverse_iterator	rbegin()
	{
		return (reverse_iterator(end()));
	}

	reverse_iterator	rend()
	{
		return (reverse_iterator(begin()));
	}

	const_reverse_iterator	rbegin() const
	{
		return (const_reverse_iterator(end()));
	}

	const_reverse_iterator	rend() const
	{
		return (const_reverse_iterator(begin()));
	}

	size_type	size() const
	{
		return (_size);
	}

	size_type	max_size() const
	{
		return (_allocator.max_size());
	}

	void		resize(size_type nb, value_type val = value_type())
	{
		if (nb < _size)
			erase(begin() + nb, end());
		else if (nb > _size)
		{
			difference_type	diff = nb - _size;
			insert(end(), diff, val);
		}
	}

	size_type	capacity() const
	{
		return (_capacity);
	}

	bool	empty() const
	{
		return (!_size);
	}

	void	push_back(const_reference val)
	{
		const value_type	tmp = val;
		if (_size == _capacity || _capacity == 0)
			reserve(_capacity * 2);
		_allocator.construct(_data + _size, tmp);
		_size++;
	}

	void	reserve(size_type n)
	{
		if (n > max_size())
			throw (std::length_error("vector::reserve"));
		if (_capacity == 0)
			n = n ? n : 1;
		if (_capacity < n)
		{
			size_type	tmp_cap = n;
			pointer	tmp_data = _allocator.allocate(tmp_cap);

			for (size_type i = 0; i < _size; i++)
			{
				value_type	tmp_val = _data[i];
				_allocator.construct(tmp_data + i, tmp_val);
				_allocator.destroy(&(_data[i]));
			}
			_allocator.deallocate(_data, _capacity);
			_data = tmp_data;
			_capacity = tmp_cap;
		}
	}

	//ACCESS
	reference		operator[](size_type index){
		return (_data[index]);
	}

	const_reference	operator[](size_type index) const{
		return (_data[index]);
	}

	reference		at(size_type index)
	{
		check_index(index);
		return (_data[index]);
	}

	const_reference	at(size_type index) const
	{
		check_index(index);
		return (_data[index]);
	}

	reference		front()
	{
		return (*_data);
	}

	const_reference	front() const
	{
		return (*_data);
	}

	reference		back()
	{
		return (_data[_size - 1]);
	}
	
	const_reference	back() const
	{
		return (_data[_size - 1]);
	}

	template <class InputIterator>
		typename ft::enable_if<!ft::is_integral<InputIterator>::state>::type
		assign(InputIterator first, InputIterator last)
		{
			clear();
			insert(begin(), first, last);
		}

	void	assign(size_type n, const_reference val)
	{
		clear();
		insert(begin(), n, val);
	}


	void	pop_back()
	{
		_data[--_size].~value_type();
	}

	iterator	insert(iterator pos, const_reference val)
	{
		std::cout << "insert of val: " << val << std::endl;
		if (_size == 0 || pos == end())
		{
			push_back(val);
			return (end() - 1);
		}
		size_type 	i;
		size_type	index_of_pos = pos - begin();

		if (_capacity < _size + 1)
		{
			reserve(_capacity * 2);
			pos = begin() + index_of_pos;
		}
		i = _size;
		if (i != index_of_pos)
		{
			_allocator.construct(_data + i, _data[i - 1]);
			--i;
			for (; i > index_of_pos; i--)
				_data[i] = _data[i - 1];
			_data[i] = val;
		}
		else
			_allocator.construct(_data + i, val);
		_size++;
		return (pos);
	}

	void	insert(iterator pos, size_type n, const_reference val)
	{
		if (_size + n > _capacity) 
		{
			size_type	to_add = pos- begin();
			if (_size + n > _capacity * 2)
				reserve(_size + n);
			else
				reserve(_size * 2);
			pos = begin() + to_add;
		}
		for (size_type i = 0; i < n; ++i)
			pos = insert(pos, val) + 1;
	}

	template <class InputIterator>
		typename ft::enable_if<!ft::is_integral<InputIterator>::state>::type
		insert(iterator pos, InputIterator first, InputIterator last)
		{
			for (; first != last; first++)
				pos = insert(pos, *first) + 1;
		}

	iterator	erase(iterator pos)
	{
		return (erase(pos, pos + 1));
	}

	iterator	erase(iterator first, iterator last)
	{
		size_type dist = std::distance(first, last);

		if (dist == 0)
			return (last);
		for (size_type i = 0; (last + i) != end(); i++)
			*(first + i) = *(last + i);
		for (size_type i = 0; i < dist; i++)
			pop_back();
		return (first);
	}

	void	swap(vector& elem)
	{
		pointer			data = elem._data;
		size_type		size = elem._size;
		size_type		cap = elem._capacity;
		allocator_type	alloc = elem._allocator;

		elem._data = this->_data;
		elem._size = this->_size;
		elem._allocator = this->_allocator;
		elem._capacity = this->_capacity;

		this->_data = data;
		this->_size = size;
		this->_capacity = cap;
		this->_allocator = alloc;
	}

	void	clear()
	{
		if (!_data)
			return ;
		for (size_type i = 0; i < _size; i++)
			_allocator.destroy(_data + i);
		_size = 0;
	}

	allocator_type	get_allocator() const
	{
		return (_allocator);
	}

//--UTILS FOR PUBLIC FUNCTIONS--//
private:
//--INDEX CHECKER--//
	void	check_index(size_type	index) const
	{
		if (index < _size && index >= 0)
			return ;
		std::ostringstream	oss;
	
		oss << "vector::check_index index (which is " << index << ") >= this->size() (which is " << _size << ")";
		throw (std::out_of_range(oss.str()));
	}
//--CAPACITY NEEDS HIGH INCREMENT--//
	size_type	next_capacity(size_type nb)
	{
		size_type	i;

		for (i = _capacity; i < nb; i *= 2)
			;
		return (i * 2);
	}
//--INITIALIZE VECTOR (Classic/integral type)--//
	template <typename Integral>
	void	_init_vec(Integral n, Integral val, true_type)
	{
		assign(n, val);
	}

//--INITIALIZE VECTOR (from first to last/not integral type)--//
	template <typename InputIterator>
	void	_init_vec(InputIterator first, InputIterator last, false_type)
	{
		assign(first, last);
	}
};

#endif