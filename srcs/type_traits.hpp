/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_traits.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 17:30:29 by tmoragli          #+#    #+#             */
/*   Updated: 2022/11/26 19:13:36 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPE_TRAITS_HPP
#define TYPE_TRAITS_HPP

namespace ft
{
	//Remove either const or volatile types (or both)
	template <class T> struct remove_cv						{typdef T type};
	template <class T> struct remove_cv<const T>			{typdef T type};
	template <class T> struct remove_cv<volatile T>			{typdef T type};
	template <class T> struct remove_cv<const volatile T>	{typdef T type};

	template <class T> struct remove_const					{typdef T type};
	template <class T> struct remove_const<const T>			{typdef T type};
	
	template <class T> struct remove_volatile				{typdef T type};
	template <class T> struct remove_volatile<volatile T>	{typdef T type};

	//Enable if
	template <bool Cond, typename Result=void>
	struct enable_if {};

	template <typename Result>
	struct enable_if<true, Result> {
		typedef Result type;
	};

	//Integral type check
	//Type states
	struct false_type {static const bool state = false;};
	struct true_type {static const bool state = true;};
	//
	template<typename> struct is_integral_base: false_type {};

	template<> struct is_integral_base<bool>: true_type {};
	template<> struct is_integral_base<char>: true_type {};
	template<> struct is_integral_base<char16_t>: true_type {};
	template<> struct is_integral_base<char32_t>: true_type {};
	template<> struct is_integral_base<wchar_t>: true_type {};
	template<> struct is_integral_base<short>: true_type {};
	template<> struct is_integral_base<int>: true_type {};
	template<> struct is_integral_base<long>: true_type {};
	template<> struct is_integral_base<long long>: true_type {};
	template<> struct is_integral_base<unsigned char>: true_type {};
	template<> struct is_integral_base<unsigned short>: true_type {};
	template<> struct is_integral_base<unsigned int>: true_type {};
	template<> struct is_integral_base<unsigned long>: true_type {};
	template<> struct is_integral_base<unsigned long long>: true_type {};

	template<typename T> struct is_integral: is_integral_base<typename ft::remove_cv<T>::type> {
		typedef bool												value_type;
		typedef is_integral_base<typename ft::remove_cv<T>::type>	type;
	
		operator value_type() {return (this->value);}
	};
}

#endif