/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functional.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aisraely <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 21:08:00 by aisraely          #+#    #+#             */
/*   Updated: 2022/01/15 21:08:00 by aisraely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONAL_HPP
# define FUNCTIONAL_HPP

namespace ft
{
	template <class T>
	struct	equal_to
	{
		bool	operator() (const T &x, const T &y) const
		{
			return (x == y);
		}
	};

	template <class T>
	struct	less
	{
		bool operator() (const T &x, const T &y) const
		{
			return (x < y);
		}
	};
}

#endif
