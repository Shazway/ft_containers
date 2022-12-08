/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 00:07:02 by tmoragli          #+#    #+#             */
/*   Updated: 2022/12/08 23:23:18 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef VECTOR_HPP
# define VECTOR_HPP

# include "algorithm.hpp"
# include "type_traits.hpp"
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

/*template <typename T, typename T1>
Coder la classe iterator sur vector
*/

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
	//Iterators (les faire soit même)
	typedef typename std::vector<T>::iterator					iterator;
	typedef typename std::vector<T>::const_iterator				const_iterator;
	typedef typename std::vector<T>::reverse_iterator			reverse_iterator;
	typedef typename std::vector<T>::const_reverse_iterator		const_reverse_iterator;

	typedef typename allocator_type::size_type			size_type;
	typedef typename allocator_type::difference_type	difference_type;
private:
	pointer			_data;
	size_type		_capacity;
	size_type		_size;
	allocator_type	_allocator;
public:
	//CONSTRUCT/DESTRUCT
	explicit vector(const allocator_type &alloc = allocator_type()): _data(NULL), _capacity(0), _size(0), _allocator(alloc)
	{
	}
	
	explicit vector(size_type count, value_type const& val = value_type(), allocator_type const& alloc = allocator_type()): _data(NULL), _capacity(0), _size(0), _allocator(alloc)
	{
		_data = _allocator.allocate(count);
		_capacity = count;
		for (;_size < count; _size++)
			_allocator.construct(_data + _size, val);
		//assign(count, val);
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

	void	reserve(size_type n)
	{
		if (n > max_size())
			throw (std::length_error("vector::reserve"));
		if (_capacity == 0)
			n = n ? n : 1;
		if (_capacity < n)
		{
			pointer	tmp_data;
			size_type	tmp_cap;

			tmp_data = _data;
			tmp_cap = _capacity;

			_data = _allocator.allocate(n);
			_capacity = n;
			for (size_type i = 0; i < _size; i++)
			{
				_allocator.construct(_data + i, *(tmp_data + i));
				_allocator.destroy(tmp_data + i);
			}
			_allocator.deallocate(tmp_data, tmp_cap);
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
		return (_data[0]);
	}

	const_reference	front() const
	{
		return (_data[0]);
	}

	reference		back()
	{
		return (_data[_size - 1]);
	}
	
	const_reference	back() const
	{
		return (_data[_size - 1]);
	}

	template <typename InputIterator>
	void assign(InputIterator first, InputIterator last)
	{
		typedef typename ft::is_integral<InputIterator> _Integral;

		clear();
		dispatch_assignation(first, last, _Integral());
	}

	void	assign(size_type n, value_type const& val)
	{
		clear();
		insert(begin(), n, val);
	}

	void	push_back(const value_type &val)
	{
		if (_size == _capacity || _capacity == 0)
			reserve(_capacity * 2);
		_allocator.construct(_data + _size++, val);
	}

	void	pop_back()
	{
		_data[--_size].~value_type();
	}

	iterator	insert(iterator pos, value_type const& val)
	{
		return (fill_insert(pos, 1, val));
	}

	void	insert(iterator pos, size_type n, value_type const& val)
	{
		fill_insert(pos, n, val);
	}

	template <typename InputIterator>
	void	insert(iterator pos, InputIterator first, InputIterator last)
	{
		typedef typename ft::is_integral<InputIterator>	_Integral;

		dispatch_insert(pos, first, last, _Integral());
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
		{
			std::cout << "SIZE == " << _size <<std::endl;
			_allocator.destroy(_data + i);
		}
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
//--CAPACITY NEEDS CALCULATION--//
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

	template <typename Integral>
	void	dispatch_assignation(Integral n, Integral val, true_type)
	{
		insert(begin(), n, val);
	}

	template <typename InputIterator>
	void	dispatch_assignation(InputIterator first, InputIterator last, false_type)
	{
		insert(begin(), first, last);
	}

	template<typename Integral>
	iterator	dispatch_insert(iterator pos, Integral n, Integral val, true_type)
	{
		return (fill_insert(pos, n, val));
	}
	template<typename InputIterator>
	iterator	dispatch_insert(iterator pos, InputIterator first, InputIterator end, false_type)
	{
		return (range_insert(pos, first, end));
	}
//--INSERT NEW ELEMENTS WITH A RANGE BETWEEN TWO ITERATORS--//
	template<typename InputIterator>
	iterator range_insert(iterator pos, InputIterator first, InputIterator last)
	{
		difference_type		diff = pos - begin();
		difference_type		n = 0;

		for (InputIterator it = first; it != last; it++)
			n++;
		if (!_capacity)
			reserve(n);
		else if (_size + n > _capacity)
			reserve(next_capacity(n));

		ft_memmove(_data + diff + n, _data + diff, sizeof(value_type) * (_size - diff));
		size_type i = 0;
		for (InputIterator it = first; it != last; it++, i++)
			_allocator.construct(_data + diff + i, *it);
		_size += n;

		return (iterator(_data + diff));
	}

	iterator fill_insert(iterator pos, size_type n, value_type const& val)
	{
		difference_type diff = pos - begin();
	
		if (!_capacity)
			reserve(n);
		else if(_size + n > _capacity)
			reserve(next_capacity(n));

		ft_memmove(_data + diff + n, _data + diff, sizeof(value_type) * (_size - diff));
		for (size_type i = 0; i < n; i++)
			_allocator.construct(_data + diff + i, val);
		_size += n;
		return (iterator(_data + diff));
	}

	void	*ft_memmove(void *dest, const void *src, size_t n)
	{
		unsigned int	i;

		if (!dest && !src)
			return (NULL);
		if (dest > src)
		{
			while (n > 0)
			{
				((char *)dest)[n - 1] = ((char *)src)[n - 1];
				n--;
			}
		}
		else
		{
			i = 0;
			while (i < n)
			{
				((char *)dest)[i] = ((char *)src)[i];
				i++;
			}
		}
		return (dest);
	}
	void	*ft_memcpy(void *dest, const void *src, size_t n)
	{
		unsigned char	*cast_dst;
		unsigned char	*cast_src;

		cast_dst = (unsigned char *)dest;
		cast_src = (unsigned char *)src;
		if (!n || dest == src)
			return (dest);
		while (n)
		{
			*cast_dst++ = *cast_src++;
			n--;
		}
		return (dest);
	}
};

#endif