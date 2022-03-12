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

# include "vector.hpp"	// will include all the needed headers

namespace ft
{
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
	};
}

#endif