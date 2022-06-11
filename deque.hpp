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

# include "utility.hpp"
# include "iterator.hpp"

namespace ft
{
	size_t	deque_chunk_size(size_t size)
	{
		return (size < DEQUE_BUF_SIZE ? size_t(DEQUE_BUF_SIZE / size) : size_t(1));
	}

	template <typename T, typename Reference, typename Pointer>
	// template <typename T>
	class	deque_iterator
	{
		// private:
		// 	template <class T1, class Reference1, class Pointer1>
		// 	friend bool operator==(const deque_iterator<T1, Reference1, Pointer1> &lhs,
		// 			const deque_iterator<T1, Reference1, Pointer1> &rhs);
		protected:
			typedef deque_iterator<T, T&, T*>				iterator;
			typedef deque_iterator<T, const T&, const T*>	const_iterator;
			typedef T*										element_pointer;
			typedef T**										map_pointer;
			typedef deque_iterator							self;
		public:
			typedef std::random_access_iterator_tag			iterator_category;
			typedef T										value_type;
			typedef Pointer									pointer;
			typedef Reference								reference;
			typedef size_t									size_type;
			typedef ptrdiff_t								difference_type;

		private:
			element_pointer	_curr;
			element_pointer	_first;
			element_pointer	_last;
			map_pointer		_node;

		public:
			static size_type	chunk_size()
			{
				return (deque_chunk_size(sizeof(value_type)));
			}

			deque_iterator() : _curr(), _first(), _last(), _node() { }

			deque_iterator(element_pointer element, map_pointer node) : _curr(element), _first(*node),
				_last(*node + chunk_size()), _node(node) { }
			
			deque_iterator(const iterator &copy) : _curr(copy._curr), _first(copy._first), _last(copy._last), _node(copy._node) { }

			self	&operator=(const deque_iterator &rhs)
			{
				this->_curr = rhs._curr;
				this->_first = rhs._first;
				this->_last = rhs._last;
				this->_node = rhs._node;
			}

			reference	operator*() const
			{
				return (*this->_curr);
			}

			deque_iterator	operator+(difference_type n) const
			{
				deque_iterator	it(*this);

				if (n < it._last - it._curr)
					it._curr += n;
				else
				{
					if (it._curr + n >= it._last)	// align the offset
					{
						it._node++;
						n -= it._last - it._curr;
					}
					it._node += n / chunk_size();
					it._curr = *it._node + (n % chunk_size());
					it._first = *it._node;
					it._last = it._first + chunk_size();
				}
				return (it);
			}

			deque_iterator	operator-(difference_type n) const
			{
				deque_iterator	it(*this);

				if (n <= it._curr - it._first)
					it._curr -= n;
				else
				{
					if (it._curr - n < it._first)	// align the offset
					{
						it._node--;
						n -= it._curr - it._first;
					}
					it._node -= n / chunk_size();
					it._curr = *it._node + chunk_size() - (n % chunk_size());
					it._first = *it._node;
					it._last = it._first + chunk_size();
				}
				return (it);
			}

			self	&operator+=(difference_type n)
			{
				return (*this = operator+(n));
			}

			self	&operator-=(difference_type n)
			{
				return (*this = operator-(n));
			}

			self	&operator++()
			{
				return (*this += 1);
			}

			self	&operator--()
			{
				return (*this -= 1);
			}

			deque_iterator	operator++(int)
			{
				deque_iterator	temp = *this;
				operator++();
				return (temp);
			}

			deque_iterator	operator--(int)
			{
				deque_iterator	temp = *this;
				operator--();
				return (temp);
			}

			pointer	operator->() const
			{
				return (addressof(operator*()));
			}

			reference	operator[](difference_type n) const
			{
				return (*operator+(n));
			}
			
			// relational operators
			friend bool operator==(const self &lhs, const self &rhs)
			{
				return (lhs._curr == rhs._curr);
			}

			template <class ReferenceR, class PointerR>
			friend bool operator==(const self &lhs, const deque_iterator<T, ReferenceR, PointerR> &rhs)
			{
				return (lhs._curr == rhs._curr);
			}

			friend bool	operator<(const self &lhs, const self &rhs)
			{
				if (lhs._node == rhs._node)
					return (lhs._curr < rhs._curr);
				return (lhs._node < rhs._node);
			}

			template <class ReferenceR, class PointerR>
			friend bool operator<(const self &lhs, const deque_iterator<T, ReferenceR, PointerR> &rhs)
			{
				if (lhs._node == rhs._node)
					return (lhs._curr < rhs._curr);
				return (lhs._node < rhs._node);
			}
	};

	// template <class T, class Reference, class Pointer>
	// bool	operator!=(const deque_iterator<T, Reference, Pointer> &lhs,
	// 					const deque_iterator<T, Reference, Pointer> &rhs)
	// {
	// 	return (!(lhs == rhs));
	// }

	// template <class T, class ReferenceL, class ReferenceR, class PointerL, class PointerR>
	// bool	operator!=(const deque_iterator<T, ReferenceL, PointerL> &lhs,
	// 					const deque_iterator<T, ReferenceR, PointerR> &rhs)
	// {
	// 	return (!(lhs == rhs));
	// }

	// template <class T, class Reference, class Pointer>
	// bool	operator<=(const deque_iterator<T, Reference, Pointer> &lhs,
	// 					const deque_iterator<T, Reference, Pointer> &rhs)
	// {
	// 	return (!(rhs < lhs));
	// }

	// template <class T, class ReferenceL, class ReferenceR, class PointerL, class PointerR>
	// bool	operator<=(const deque_iterator<T, ReferenceL, PointerL> &lhs,
	// 					const deque_iterator<T, ReferenceR, PointerR> &rhs)
	// {
	// 	return (!(rhs < lhs));
	// }

	// template <class T, class Reference, class Pointer>
	// bool	operator>(const deque_iterator<T, Reference, Pointer> &lhs,
	// 					const deque_iterator<T, Reference, Pointer> &rhs)
	// {
	// 	return (rhs < lhs);
	// }

	// template <class T, class ReferenceL, class ReferenceR, class PointerL, class PointerR>
	// bool	operator>(const deque_iterator<T, ReferenceL, PointerL> &lhs,
	// 					const deque_iterator<T, ReferenceR, PointerR> &rhs)
	// {
	// 	return (rhs < lhs);
	// }

	// template <class T, class Reference, class Pointer>
	// bool	operator>=(const deque_iterator<T, Reference, Pointer> &lhs,
	// 					const deque_iterator<T, Reference, Pointer> &rhs)
	// {
	// 	return (!(lhs < rhs));
	// }

	// template <class T, class ReferenceL, class ReferenceR, class PointerL, class PointerR>
	// bool	operator>=(const deque_iterator<T, ReferenceL, PointerL> &lhs,
	// 					const deque_iterator<T, ReferenceR, PointerR> &rhs)
	// {
	// 	return (!(lhs < rhs));
	// }

	template <class T, class Alloc = std::allocator<T> >
	class	deque
	{
		public:
			// member types
			typedef T															value_type;
			typedef Alloc														allocator_type;
			typedef typename allocator_type::reference							reference;
			typedef typename allocator_type::const_reference					const_reference;
			typedef typename allocator_type::pointer							pointer;
			typedef typename allocator_type::const_pointer						const_pointer;
			typedef ptrdiff_t													difference_type;
			typedef size_t														size_type;
			typedef deque_iterator<value_type, reference, pointer>				iterator;
			typedef deque_iterator<value_type, const_reference, const_pointer>	const_iterator;
			typedef ft::reverse_iterator<iterator>								reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>						const_reverse_iterator;
		protected:
	};
}

#endif