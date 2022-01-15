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

# include <memory>

namespace ft
{
	// addressof
	// avoids calling object's operator&(); takes care of qualifiers
	template <class T>
	T	*addressof(T &ref)
	{
		return (reinterpret_cast<T*>(&const_cast<char&>(reinterpret_cast<const volatile char&>(ref))));
	}

	// destroy_a
	// destroys elements in range with given allocator
	template <typename ForwardIterator, typename Alloc>
	void	destroy_a(ForwardIterator first, ForwardIterator last, Alloc &alloc)
	{
		for (; first != last; ++first)
			alloc.destroy(addressof(*first));
	}

	// uninitialized_copy_a
	// memory should be only allocated; objects shouldn't be constructed.
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

	// uninitialized_fill_a
	// constructs objects in the given range with the given alloc
	template <typename ForwardIterator, typename T, typename Alloc>
	void	uninitialized_fill_a(ForwardIterator first, ForwardIterator last, const T &x, Alloc &alloc)
	{
		ForwardIterator	curr = first;
		try
		{
			for (; curr != last; ++curr)
				alloc.construct(addressof(*curr), x);
		}
		catch (...)
		{
			destroy_a(first, curr, alloc);
			throw ;
		}
	}

	// uninitialized_fill_n_a
	// differs from its counterpart in that receives `first` and `n` instead of a full range
	template <typename ForwardIterator, typename Size, typename T, typename Alloc>
	void	uninitialized_fill_n_a(ForwardIterator first, Size n, const T &x, Alloc &alloc)
	{
		ForwardIterator	curr = first;
		try
		{
			for (; n > 0; --n, ++curr)
				alloc.construct(addressof(*curr), x);
		}
		catch (...)
		{
			destroy_a(first, curr, alloc);
			throw ;
		}
	}
}

#endif
