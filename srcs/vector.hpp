/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 00:07:02 by tmoragli          #+#    #+#             */
/*   Updated: 2022/11/26 21:07:57 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>
# include <exception>
# include "algorithm.hpp"
# include "type_traits.hpp"

namespace ft
{
	template < typename T, typename Alloc = std::allocator<T> >
	class vector;

	template <typename T>
	void	swap(vector<T> &a, vector<T> &b){
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
	bool	operator!=(vector<T> const& v1, vector<T> const&& v2)
	{
		if (v1 == v2)
			return (false);
		return (true);
	}

	template <typename T>
	bool	operator>(vector<T> const& v1, vector<T> const& v2)
	{
		return (lexicographical_compare(v1.begin(), v1.end(), v2.begin(), v2.end()));
	}

	template <typename T>
	bool	operator<(vector<T> const& v1, vector<T> const& v2)
	{
		if (v1 > v2 && v1 != v2)
			return (false);
		return (true);
	}

	template <typename T>
	bool	operator<=(vector<T> const& v1, vector<T> const& v2)
	{
		if (v1 < v2 || v1 == v2)
			return (true);
		return (false);
	}
	template <typename T>
	bool	operator>=(vector<T> const& v1, vector<T> const& v2)
	{
		if (v1 > v2 || v1 == v2)
			return (true);
		return (false);
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
	typedef typename std::vector::iterator						iterator;
	typedef typename std::vector::const_iterator				const_iterator;
	typedef typename std::vector::reverse_iterator				reverse_iterator;
	typedef typename std::vector::const_reverse_iterator		const_reverse_iterator;

	typedef typename allocator_type::size_type			size_type;
	typedef typename allocator_type::difference_type	difference_type;
private:
	pointer			_data;
	size_type		_capacity;
	size_type		_size;
	allocator_type	_allocator;
public:
	//CONSTRUCT/DESTRUCT
	explicit vector(const allocator_type &alloc = allocator_type()): _data(NULL), _capacity(0), _size(0), allocator(alloc){}
	explicit vector(size_type count, const value_type &val = value_type(), const allocator_type &alloc = allocator_type()): _data(NULL), _capacity(0), _size(0){
		assign(count, val); // a coder
	}
	template <class InputIterator>
	vector(InputIterator first, InputIterator last, allocator_type const& alloc = allocator_type()): _data(NULL), _capacity(0), _size(0), _allocator(alloc)
	{
		typedef typename ft::is_integral_base<InputIterator>::state	Integral;

		_init_vec(first, last, Integral());
	}
	vector(const vector &copy, allocator_type const& alloc = allocator_type() = allocator_type()): _data(NULL), _capacity(0), _size(0), allocator(alloc)
	{
		*this = copy;
	}
	//operator=
	vector	&operator=(vector<value_type>)
	{
		
	}
	~vector(){
		clear();
		_allocator.deallocate(_data, _capacity);
	}
	size_type	size() const
	{
		return (_size);
	}
	size_type	max_size() const
	{
		return (_allocator.max_size());
	}
	//resize
	size_type	capacity() const
	{
		return (_capacity);
	}
	bool	empty() const
	{
		return (_size == 0);
	}
	//reserve
	//ACCESS
	reference		operator[](size_type index){
		return (_data[index]);
	}
	const_reference	operator[](size_type index) const{
		return (_data[index]);
	}
	reference		at(size_type index)
	{
		check_index(index); // a faire
		return (_data[n]);
	}
	const_reference	at(size_type index) const
	{
		check_index(index); // a faire
		return (_data[n]);
	}
	reference		front()
	{
		return (_data[0])
	}
	const_reference	front() const
	{
		return (_data[0])
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
		typedef typename ft::is_integral_base<InputIterator>::state Integral;
	
		clear();
		dispatch_assignation(first, last, Integral());
	}
	//assign inputiterator first, iterator last
	//assign size n, value val
	//push_back(const value_type &val)
	void	pop_back()
	{
		_data[--_size].~value_type();
	}
	//insert pos val
	//insert pos size val
	//insert pos iterator first iterator last
	//erase pos
	//erase from first to last
	void	swap(vector& elem)
	{
		vector	tmp = *this;
	
		*this = elem;
		elem = tmp;
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
private:
	void	check_index(size_type	index) const
	{
		if (index < _size)
			return ;
		std::ostringstream	oss;
	
		oss << "vector::check_index index (which is " << index << ") >= this->size() (which is " << _size << ")";
		throw (std::out_of_range(oss.str()));
	}
	size_type	next_capacity(size_type nb)
	{
		size_type	i;
		for (i = _capacity; i < n; i *= 2)
			;
		return (i * 2);
	}
	template <typename Integral>
	void	_init_vec(Integral n, Integral val, true_type)
	{
		assign(n, val);
	}

	template <typename InputIterator>
	void	_init_vec(InputIterator first, InputIterator last, false_type)
	{
		assign(first, last);
	}

	template <typename Integral>
	void	dispatch_assignation(Integral n, Integral val, _truth_type)
	{
		insert(begin(), n, val);
	}

	template <typename InputIterator>
	iterator dispatch_assignation(InputIterator first, InputIterator last, false_type)
	{
		insert(begin(), first, last);
	}

	template<typename Integral>
	iterator dispatch_insert(iterator pos, Integral n, Integral val, true_type)
	{
		return (fill_insert(pos, n val));
	}

	template<typename InputIterator>
	iterator range_insert(iterator pos, InputIterator first, InputIterator last)
	{
		difference_type		dt = pos - begin();
		typename InputIterator::difference_type n = 0;
	}
};


#endif