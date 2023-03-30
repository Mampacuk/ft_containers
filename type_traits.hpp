/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_traits.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aisraely <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 16:09:52 by aisraely          #+#    #+#             */
/*   Updated: 2021/12/30 16:09:52 by aisraely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPE_TRAITS_HPP
# define TYPE_TRAITS_HPP

namespace ft
{
	// enable_if
	template <bool Cond, class T = void> 
		struct enable_if {};
	template <class T>
		struct enable_if<true, T> { typedef T type; };
	
	// integral_constant
	template <class T, T v>
	struct integral_constant
	{
		typedef T value_type;
		static const value_type value = v;
		typedef integral_constant<T, v> type;
		operator value_type() const throw() { return value; }
	};

	// true_type, false_type
	typedef integral_constant<bool, true> true_type;
	typedef integral_constant<bool, false> false_type;

	// is_same
	template<class T, class U>
		struct is_same : false_type {};
	template<class T>
		struct is_same<T, T> : true_type {};
	
	// remove_cv
	template <class T> struct remove_cv { typedef T type; };
	template <class T> struct remove_cv<const T> { typedef T type; };
	template <class T> struct remove_cv<volatile T> { typedef T type; };
	template <class T> struct remove_cv<const volatile T> { typedef T type; };

	// is_integral
	template <class> struct is_integral_base : false_type {};
	template <> struct is_integral_base<bool> : true_type {};
	template <> struct is_integral_base<char> : true_type {};
	template <> struct is_integral_base<wchar_t> : true_type {};
	template <> struct is_integral_base<signed char> : true_type {};
	template <> struct is_integral_base<short int> : true_type {};
	template <> struct is_integral_base<int> : true_type {};
	template <> struct is_integral_base<long int> : true_type {};
	template <> struct is_integral_base<long long int> : true_type {};
	template <> struct is_integral_base<unsigned char> : true_type {};
	template <> struct is_integral_base<unsigned short int> : true_type {};
	template <> struct is_integral_base<unsigned int> : true_type {};
	template <> struct is_integral_base<unsigned long int> : true_type {};
	template <> struct is_integral_base<unsigned long long int> : true_type {};

	template <class T> struct is_integral : is_integral_base<typename remove_cv<T>::type> {};
}

#endif
