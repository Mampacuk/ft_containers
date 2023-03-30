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

namespace ft
{
	template <class T1, class T2>
	struct pair
	{
		typedef T1 first_type;
		typedef T2 second_type;
		first_type	first;
		second_type	second;

		// (constructor)
		pair() : first(), second() {};
		template<class U, typename V>
		pair(const pair<U, V> &pr) : first(pr.first), second(pr.second) {}
		pair(const first_type &a, const second_type &b) : first(a), second(b) {}
		pair &operator=(const pair &pr)
		{
			this->first = pr.first;
			this->second = pr.second;
			return (*this);
		}
	};
}

#endif
