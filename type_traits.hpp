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
	
	// is_integral
	template <class T> struct is_integral : false_type {};
	template <> struct is_integral<bool> : true_type {};
	template <> struct is_integral<char> : true_type {};
	template <> struct is_integral<wchar_t> : true_type {};
	template <> struct is_integral<signed char> : true_type {};
	template <> struct is_integral<short int> : true_type {};
	template <> struct is_integral<int> : true_type {};
	template <> struct is_integral<long int> : true_type {};
	template <> struct is_integral<long long int> : true_type {};
	template <> struct is_integral<unsigned char> : true_type {};
	template <> struct is_integral<unsigned short int> : true_type {};
	template <> struct is_integral<unsigned int> : true_type {};
	template <> struct is_integral<unsigned long int> : true_type {};
	template <> struct is_integral<unsigned long long int> : true_type {};
}

#endif
