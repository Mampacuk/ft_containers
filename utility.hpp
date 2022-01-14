/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aisraely <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 14:59:18 by aisraely          #+#    #+#             */
/*   Updated: 2021/12/30 14:59:18 by aisraely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILITY_HPP
# define UTILITY_HPP

# include <sstream>
# include "pair.hpp"

#define SSTR( x ) static_cast< std::ostringstream & >( \
        ( std::ostringstream() << std::dec << x ) ).str()

namespace ft
{
	template <class T1, class T2>
		pair<T1, T2> make_pair(T1 x, T2 y);
}

template <class T1, class T2>
ft::pair<T1,T2> ft::make_pair(T1 x, T2 y)
{
	return (pair<T1, T2>(x, y));
}

// ft::pair::relational operators

template <class T1, class T2>
	bool operator==(const ft::pair<T1, T2> &lhs, const ft::pair<T1, T2> &rhs)
{
	return (lhs.first == rhs.first && lhs.second == rhs.second);
}

template <class T1, class T2>
	bool operator!=(const ft::pair<T1, T2> &lhs, const ft::pair<T1, T2> &rhs)
{
	return (!(lhs == rhs));
}

template <class T1, class T2>
	bool operator<(const ft::pair<T1, T2> &lhs, const ft::pair<T1, T2> &rhs)
{
	return (lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second));
}

template <class T1, class T2>
	bool operator<=(const ft::pair<T1, T2> &lhs, const ft::pair<T1, T2> &rhs)
{
	return (!(rhs < lhs));
}

template <class T1, class T2>
	bool operator>(const ft::pair<T1, T2> &lhs, const ft::pair<T1, T2> &rhs)
{
	return (rhs < lhs);
}

template <class T1, class T2>
	bool operator>=(const ft::pair<T1, T2> &lhs, const ft::pair<T1, T2> &rhs)
{
	return (!(lhs < rhs));
}

#endif
