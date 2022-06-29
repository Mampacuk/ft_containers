/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aisraely <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 20:26:39 by aisraely          #+#    #+#             */
/*   Updated: 2021/12/31 20:26:39 by aisraely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
# define ITERATOR_HPP

# include <cstddef>
# include <iterator>
# include "memory.hpp"

namespace ft
{
	// iterator_traits
	template <class Iter>
	struct	iterator_traits
	{
		typedef typename Iter::difference_type		difference_type;
		typedef typename Iter::value_type			value_type;
		typedef typename Iter::pointer				pointer;
		typedef typename Iter::reference			reference;
		typedef typename Iter::iterator_category	iterator_category;
	};

	template <class T>
	struct	iterator_traits<T*>
	{
		typedef std::ptrdiff_t					difference_type;
		typedef T								value_type;
		typedef T*								pointer;
		typedef T&								reference;
		typedef std::random_access_iterator_tag	iterator_category;
	};

	template <class T>
	struct	iterator_traits<const T*>
	{
		typedef std::ptrdiff_t					difference_type;
		typedef T								value_type;
		typedef const T*						pointer;
		typedef const T&						reference;
		typedef std::random_access_iterator_tag	iterator_category;
	};

	// reverse_iterator
	// rbegin points to the element preceding the one that would be pointed to by member end.
	template <class Iterator>
	class	reverse_iterator
	{
		protected:
			Iterator	_base;
		public:
			// member types
			typedef Iterator 												iterator_type;
			typedef typename iterator_traits<Iterator>::iterator_category	iterator_category;
			typedef typename iterator_traits<Iterator>::value_type			value_type;
			typedef typename iterator_traits<Iterator>::difference_type		difference_type;
			typedef typename iterator_traits<Iterator>::pointer				pointer;
			typedef typename iterator_traits<Iterator>::reference			reference;
			
			reverse_iterator() : _base() { }

			explicit reverse_iterator(iterator_type it) : _base(it) { }

			template <class Iter>
			reverse_iterator(const reverse_iterator<Iter> &rev_it) : _base(rev_it.base()) { }

			reverse_iterator	&operator=(const reverse_iterator &rhs)
			{
				this->_base = rhs._base;
				return (*this);
			}

			~reverse_iterator() { }

			iterator_type	base() const
			{
				return (this->_base);
			}

			reference	operator*() const
			{
				return (*(--iterator_type(this->_base)));
			}

			reverse_iterator	operator+(difference_type n) const
			{
				return (reverse_iterator(this->_base - n));
			}

			reverse_iterator	operator-(difference_type n) const
			{
				return (reverse_iterator(this->_base + n));
			}

			reverse_iterator	&operator++()
			{
				--this->_base;
				return (*this);
			}

			reverse_iterator	&operator--()
			{
				++this->_base;
				return (*this);
			}

			reverse_iterator	operator++(int)
			{
				reverse_iterator temp(*this);
				++(*this);
				return (temp);
			}

			reverse_iterator	operator--(int)
			{
				reverse_iterator temp(*this);
				--(*this);
				return (temp);
			}

			reverse_iterator	&operator+=(difference_type n)
			{
				this->_base -= n;
				return (*this);
			}

			reverse_iterator	&operator-=(difference_type n)
			{
				this->_base += n;
				return (*this);
			}

			pointer	operator->() const
			{
				return (ft::addressof(operator*()));
			}

			reference	operator[](difference_type n) const
			{
				return (this->_base[-n - 1]);
			}
	};
}

template <class Iterator>
bool	operator==(const ft::reverse_iterator<Iterator> &lhs,
					const ft::reverse_iterator<Iterator> &rhs)
{
	return (lhs.base() == rhs.base());
}

template <class IteratorL, class IteratorR>
bool	operator==(const ft::reverse_iterator<IteratorL> &lhs,
					const ft::reverse_iterator<IteratorR> &rhs)
{
	return (lhs.base() == rhs.base());
}

template <class Iterator>
bool	operator!=(const ft::reverse_iterator<Iterator> &lhs,
					const ft::reverse_iterator<Iterator> &rhs)
{
	return (lhs.base() != rhs.base());
}

template <class IteratorL, class IteratorR>
bool	operator!=(const ft::reverse_iterator<IteratorL> &lhs,
					const ft::reverse_iterator<IteratorR> &rhs)
{
	return (lhs.base() != rhs.base());
}

template <class Iterator>
bool	operator<(const	ft::reverse_iterator<Iterator> &lhs,
				const ft::reverse_iterator<Iterator> &rhs)
{
	return (lhs.base() > rhs.base());
}

template <class IteratorL, class IteratorR>
bool	operator<(const	ft::reverse_iterator<IteratorL> &lhs,
				const ft::reverse_iterator<IteratorR> &rhs)
{
	return (lhs.base() > rhs.base());
}

template <class Iterator>
bool	operator<=(const ft::reverse_iterator<Iterator> &lhs,
					const ft::reverse_iterator<Iterator> &rhs)
{
	return (lhs.base() >= rhs.base());
}

template <class IteratorL, class IteratorR>
bool	operator<=(const ft::reverse_iterator<IteratorL> &lhs,
					const ft::reverse_iterator<IteratorR> &rhs)
{
	return (lhs.base() >= rhs.base());
}

template <class Iterator>
bool	operator>(const	ft::reverse_iterator<Iterator> &lhs,
				const ft::reverse_iterator<Iterator> &rhs)
{
	return (lhs.base() < rhs.base());
}

template <class IteratorL, class IteratorR>
bool	operator>(const ft::reverse_iterator<IteratorL> &lhs,
				const ft::reverse_iterator<IteratorR> &rhs)
{
	return (lhs.base() < rhs.base());
}

template <class Iterator>
bool	operator>=(const	ft::reverse_iterator<Iterator> &lhs,
					const	ft::reverse_iterator<Iterator> &rhs)
{
	return (lhs.base() <= rhs.base());
}

template <class IteratorL, class IteratorR>
bool	operator>=(const ft::reverse_iterator<IteratorL> &lhs,
					const ft::reverse_iterator<IteratorR> &rhs)
{
	return (lhs.base() <= rhs.base());
}

template <class Iterator>
ft::reverse_iterator<Iterator>
	operator+(typename ft::reverse_iterator<Iterator>::difference_type n,
	const ft::reverse_iterator<Iterator> &rev_it)
{
	return (rev_it + n);
}

template <class IteratorL, class IteratorR>
typename ft::reverse_iterator<IteratorL>::difference_type operator-(
	const ft::reverse_iterator<IteratorL> &lhs,
	const ft::reverse_iterator<IteratorR> &rhs)
{
	return (rhs.base() - lhs.base());
}

namespace ft
{
	// distance
	template <class It>
	typename iterator_traits<It>::difference_type do_distance(It first, It last, std::input_iterator_tag)
	{
		typename iterator_traits<It>::difference_type	result = 0;
		while (first != last)
		{
			++first;
			++result;
		}
		return (result);
	}

	template <class It>
	typename iterator_traits<It>::difference_type do_distance(It first, It last, std::random_access_iterator_tag)
	{
		return (last - first);
	}

	template <class It>
	typename iterator_traits<It>::difference_type distance(It first, It last)
	{
		return (do_distance(first, last, typename iterator_traits<It>::iterator_category()));
	}

	// advance
	template <class It>
	void	do_advance(It &it, typename iterator_traits<It>::difference_type n, std::input_iterator_tag)
	{
		while (n > 0)
		{
			--n;
			++it;
		}
	}

	template <class It>
	void	do_advance(It &it, typename iterator_traits<It>::difference_type n, std::bidirectional_iterator_tag)
	{
		while (n > 0)
		{
			--n;
			++it;
		}
		while (n < 0)
		{
			++n;
			--it;
		}
	}

	template <class It>
	void	do_advance(It &it, typename iterator_traits<It>::difference_type n, std::random_access_iterator_tag)
	{
		it += n;
	}

	template <class It, class Distance>
	void	advance(It &it, Distance n)
	{
		do_advance(it, typename iterator_traits<It>::difference_type(n), typename iterator_traits<It>::iterator_category());
	}
}

#endif
