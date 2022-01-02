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

	template <bool Cond, class T = void>
		typedef typename enable_if<Cond, T>::type enable_if_t;
}

#endif
