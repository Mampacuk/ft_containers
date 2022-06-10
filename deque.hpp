/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deque.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aisraely <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 12:14:02 by aisraely          #+#    #+#             */
/*   Updated: 2022/01/20 12:14:02 by aisraely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEQUE_HPP
# define DEQUE_HPP

# ifndef DEQUE_BUF_SIZE
#  define DEQUE_BUF_SIZE 512
# endif

# include "vector.hpp"	// will include all the needed headers

namespace ft
{
	size_t	deque_chunk_size(size_t size)
	{
		return (size < DEQUE_BUF_SIZE ? size_t(DEQUE_BUF_SIZE / size) : size_t(1));
	}

	template <typename T, typename Reference, typename Pointer>
	struct	deque_iterator
	{
		typedef deque_iterator<T, T&, T*>				iterator;
		typedef deque_iterator<T, const T&, const T*>	const_iterator;
		typedef T*										element_pointer;
		typedef T**										map_pointer;

		typedef std::random_access_iterator_tag			iterator_category;
		typedef T										value_type;
		typedef Pointer									pointer;
		typedef Reference								reference;
		typedef size_t									size_type;
		typedef ptrdiff_t								difference_type;

		static size_type	chunk_size() const
		{
			return (deque_chunk_size(sizeof(value_type)));
		}

		element_pointer	curr;
		element_pointer	first;
		element_pointer	last;
		map_pointer		node;

		deque_iterator() : curr(), first(), last(), node() { }

		deque_iterator(element_pointer element, map_pointer node) : curr(element), first(*node),
			last(*node + chunk_size()), node(node) { }
		
		deque_iterator(const iterator &copy) : curr(copy.curr), first(copy.first), last(copy.last), node(copy.node) { }

		deque_iterator	&operator=(const deque_iterator &rhs)
		{
			this->curr = rhs.curr;
			this->first = rhs.first;
			this->last = rhs.last;
			this->node = rhs.node;
		}

		reference	operator*() const
		{
			return (*this->curr);
		}

		deque_iterator	operator+(difference_type n) const
		{
			deque_iterator	it(*this);

			if (n < it.last - it.curr)
				it.curr += n;
			else
			{
				if (it.curr + n >= it.last)	// align the offset
				{
					it.node++;
					n -= it.last - it.curr;
				}
				it.node += n / chunk_size();
				it.curr = *it.node + (n % chunk_size());
				it.first = *it.node;
				it.last = it.first + chunk_size();
			}
			return (it);
		}

		deque_iterator	operator-(difference_type n) const
		{
			deque_iterator	it(*this);

			if (n <= it.curr - it.first)
				it.curr -= n;
			else
			{
				if (it.curr - n < it.first)
				{
					it.node--;
					n -= curr
				}
			}
		}
	};

	template <class T, class Alloc = std::allocator<T> >
	class	deque
	{
		public:
			// member types
			typedef T											value_type;
			typedef Alloc										allocator_type;
			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;
			typedef ptrdiff_t									difference_type;
			typedef size_t										size_type;
			// typedef normal_iterator<pointer, vector>			iterator;
			// typedef normal_iterator<const_pointer, vector>		const_iterator;
			// typedef ft::reverse_iterator<iterator>				reverse_iterator;
			// typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;
		protected:
	};
}

#endif