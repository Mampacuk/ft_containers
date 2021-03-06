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

	template <class Arg, class Result>
	struct	unary_function
	{
		typedef Arg		argument_type;   
		typedef Result	result_type;  
	};
	
	template <class Arg1, class Arg2, class Result>
	struct	binary_function
	{
		typedef Arg1	first_argument_type;
		typedef Arg2	second_argument_type;

		typedef Result	result_type;
	};

	template <class T>
	struct	equal_to : binary_function<T, T, bool>
	{
		bool	operator() (const T &x, const T &y) const
		{
			return (x == y);
		}
	};

	template <class T>
	struct	less : binary_function<T, T, bool>
	{
		bool operator() (const T &x, const T &y) const
		{
			return (x < y);
		}
	};

	template <class Pair>
	struct select_1st : public unary_function<Pair, typename Pair::first_type>
	{
		typename Pair::first_type	&operator()(Pair &x) const
		{
			return (x.first);
		}

		const typename Pair::first_type	&operator()(const Pair &x) const
		{
			return (x.first);
		}
	};

	template <class T>
	struct	identity : public unary_function<T, T>
	{
		T	&operator()(T &x) const
		{
			return (x);
		}

		const T	&operator()(const T &x) const
		{
			return (x);
		}
	};
}

#endif
