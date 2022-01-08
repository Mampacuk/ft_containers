/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aisraely <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 13:15:25 by aisraely          #+#    #+#             */
/*   Updated: 2022/01/08 13:15:25 by aisraely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_HPP
# define LIST_HPP

# include <cstddef>
# include <memory>
# include <exception>
# include "memory.hpp"
# include "iterator.hpp"
# include "algorithm.hpp"
# include "type_traits.hpp"
# include "utility.hpp"

namespace ft
{
	template <class T> class list_iterator;
	template <class T, class Alloc = std::allocator<T> > class list;
	template <class T, class Alloc>
	void	swap(list<T, Alloc> &x, list<T, Alloc> &y);
}

template <class T, class Alloc>
class	ft::list
{
	public:
		// member types
		typedef T												value_type;
		typedef Alloc											allocator_type;
		typedef typename allocator_type::reference				reference;
		typedef typename allocator_type::const_reference		const_reference;
		typedef typename allocator_type::pointer				pointer;
		typedef typename allocator_type::const_pointer			const_pointer;
		typedef ft::list_iterator<value_type>					iterator;
		typedef ft::list_iterator<const value_type>				const_iterator;
		typedef ft::iterator_traits<iterator>::difference_type	difference_type;
		typedef size_t											size_type;
		typedef typename ft::reverse_iterator<iterator>			reverse_iterator;
		typedef typename ft::reverse_iterator<const_iterator> 	const_reverse_iterator;

		// (constructor)
		explicit list(const allocator_type &alloc = allocator_type());	
		explicit list(size_type n, const value_type &val = value_type(),
			const allocator_type &alloc = allocator_type());
		template <class InputIterator>
		list(InputIterator first, InputIterator last, const allocator_type &alloc = allocator_type());
		list(const list &x);
		list &operator=(const list& x);

		// (destructor)
		~list();

		// iterators
		iterator				begin();
		const_iterator			begin() const;
		iterator				end();
		const_iterator			end() const;
		reverse_iterator		rbegin();
		const_reverse_iterator	rbegin() const;
		reverse_iterator		rend();
		const_reverse_iterator	rend() const;

		// capacity
		bool		empty() const;
		size_type	size() const;
		size_type	max_size() const;

		// element access
		reference		front();
		const_reference	front() const;
		reference		back();
		const_reference	back() const;

		// modifiers
		template <class InputIterator>
		void		assign(typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first, InputIterator last);
		void		assign(size_type n, const value_type &val);
		void		push_front(const value_type &val);
		void		pop_front();
		void		push_back(const value_type &val);
		void		pop_back();
		iterator	insert(iterator position, const value_type &val);
		void		insert(iterator position, size_type n, const value_type &val);
		template <class InputIterator>
		void		insert(iterator position,
			typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first,
			InputIterator last);
		iterator	erase(iterator position);
		iterator	erase(iterator first, iterator last);
		void		swap(list &x);
		void		resize(size_type n, value_type val = value_type());
		void		clear();

		// operations
		void	splice(iterator position, list &x);
		void	splice(iterator position, list &x, iterator i);
		void	splice(iterator position, list &x, iterator first, iterator last);
		void	remove(const value_type &val);
		template <class Predicate>
		void	remove_if(Predicate pred);
		void	unique();
		template <class BinaryPredicate>
		void	unique(BinaryPredicate binary_pred);
		void	merge(list &x);
		template <class Compare>
		void	merge(list &x, Compare comp);
		void	sort();
		template <class Compare>
		void	sort(Compare comp);
		void	reverse();

		// observers
		allocator_type	get_allocator() const;
};

#endif
