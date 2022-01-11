/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aisraely <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/01 20:51:47 by aisraely          #+#    #+#             */
/*   Updated: 2022/01/01 20:51:47 by aisraely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEMORY_HPP
# define MEMORY_HPP

namespace ft
{
	// addressof
	template <class T>
	T	*addressof(T &ref)
	{
		return (reinterpret_cast<T*>(&const_cast<char&>(reinterpret_cast<const volatile char&>(ref))));
	}
	// destroy_a
	template <typename ForwardIterator, typename Alloc>
	void	destroy_a(ForwardIterator first, ForwardIterator last, Alloc &alloc)
	{
		for (; first != last; ++first)
			alloc.destroy(addressof(*first));
	}
	// uninitialized_copy_a
	template <typename InputIterator, typename ForwardIterator, typename Alloc>
	ForwardIterator	uninitialized_copy_a(InputIterator first, InputIterator last, ForwardIterator result, Alloc &alloc)
	{
		ForwardIterator	curr = result;
		try
		{
			for (; first != last; ++first, ++curr)
				alloc.construct(addressof(*curr), *first);
			return (curr);
		}
		catch (...)
		{
			destroy_a(result, curr, alloc);
			throw ;
		}
	}
}

#endif
