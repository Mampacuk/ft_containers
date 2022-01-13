/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aisraely <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 15:53:45 by aisraely          #+#    #+#             */
/*   Updated: 2021/12/30 15:53:45 by aisraely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALGORITHM_HPP
# define ALGORITHM_HPP

namespace ft
{
	// equal
	template <class InputIterator1, class InputIterator2>
	bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
	{
		while (first1 != last1)
		{
			if (!(*first1 == *first2))
				return (false);
			++first1;
			++first2;
		}
		return (true);
	}

	template <class InputIterator1, class InputIterator2, class BinaryPredicate>
	bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, BinaryPredicate pred)
	{
		while (first1!=last1)
		{
			if (!pred(*first1,*first2))
				return (false);
			++first1;
			++first2;
		}
		return (true);
	}

	// lexicographical_compare
	template <class InputIterator1, class InputIterator2>
	bool	lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
									InputIterator2 first2, InputIterator2 last2)
	{
		while (first1 != last1)
		{
			if (first2 == last2 || *first2 < *first1)
				return (false);
			else if (*first1 < *first2)
				return (true);
			++first1;
			++first2;
		}
		return (first2 != last2);
	}

	template <class InputIterator1, class InputIterator2, class Compare>
	bool	lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
									InputIterator2 first2, InputIterator2 last2,
									Compare comp)
	{
		while (first1 != last1)
		{
			if (first2 == last2 || comp(*first2, *first1))
				return (false);
			else if (comp(*first1, *first2))
				return (true);
			++first1;
			++first2;
		}
		return (first2 != last2);
	}

	// max
	template <class T>
	const T	&max(const T &a, const T &b)
	{
		return ((a < b) ? b : a);
	}

	template <class T, class Compare>
	const T	&max(const T &a, const T &b, Compare comp)
	{
		return (comp(a, b) ? b : a);
	}

	// swap
	template <class T>
	void	swap(T &a, T &b)
	{
		T	temp(a);
		a = b;
		b = temp;
	}

	// copy
	// copies everything from [first, last) to d_first, returns past-end iterator of dest
	template <class InputIt, class OutputIt>
	OutputIt	copy(InputIt first, InputIt last, OutputIt d_first)
	{
		while (first != last)
			*d_first++ = *first++;
		return (d_first);
	}

	// copy_backward
	// copies everything from [first, last) to d_first, backward, returns iterator to the first element of sequence
	template <class BidirIt1, class BidirIt2>
	BidirIt2	copy_backward(BidirIt1 first, BidirIt1 last, BidirIt2 d_last)
	{
		while (last != first)
			*(--d_last) = *(--last);
		return (d_last);
	}

	// fill
	template <class ForwardIt, class T>
	void	fill(ForwardIt first, ForwardIt last, const T &value)
	{
		for (; first != last; ++first)
			*first = value;
	}

	// fill_n
	template <class OutputIt, class Size, class T>
	OutputIt	fill_n(OutputIt first, Size count, const T &value)
	{
		for (Size i = 0; i < count; i++)
			*first++ = value;
		return (first);
	}
}

#endif
