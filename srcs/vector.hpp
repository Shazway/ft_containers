/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 00:07:02 by tmoragli          #+#    #+#             */
/*   Updated: 2022/11/21 00:42:18 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define VECTOR_HPP

# include <numeric>
# include <sstream>
# include <cstring>
# include <stdexcept>
# include <exception>
# include <memory>

namespace ft
{
	template < typename T, typename Allocate = std::allocator<T> >
	class vector;

	template <typename T>
	void	swap(vector<T>, &a, vector<T> &b){
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
		return (std::lexicographical_compare(v1.begin(), v1.end(), v2.begin(), v2.end()));
		//Faire la comparaison lexicographicale nous même
	}

	template <typename T>
	bool	operator<(vector<T> const& v1, vector<T> const& v2)
	{
		if (v1 > v2)
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
	typedef T value_type;
	typedef Allocator allocator_type;
}


#endif