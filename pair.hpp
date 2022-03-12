/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aisraely <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 15:19:08 by aisraely          #+#    #+#             */
/*   Updated: 2021/12/30 15:19:08 by aisraely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAIR_HPP
# define PAIR_HPP

namespace ft { template <class T1, class T2> struct pair; }

template <class T1, class T2>
struct	ft::pair
{
	typedef T1 first_type;
	typedef T2 second_type;
	first_type	first;
	second_type	second;

	// (constructor)
	pair();
	template<class U, class V>
		pair(const pair<U, V> &pr);
	pair(const first_type &a, const second_type &b);
	pair &operator=(const pair &pr);
};

template <class T1, class T2>
ft::pair<T1, T2>::pair() {}

template <class T1, class T2>
template<class U, class V>
ft::pair<T1, T2>::pair(const pair<U, V> &pr) : first(pr.first), second(pr.second) {}

template <class T1, class T2>
ft::pair<T1, T2>::pair(const first_type &a, const second_type &b) : first(a), second(b) {}

template <class T1, class T2>
ft::pair<T1, T2> &ft::pair<T1, T2>::operator=(const pair &pr)
{
	this->first = pr.first;
	this->second = pr.second;
	return (*this);
}

#endif
