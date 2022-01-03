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

namespace ft
{
	template <class Iter>
		struct iterator_traits;
	template <class T>
		struct iterator_traits<T*>;
	template <class T>
		struct iterator_traits<const T*>;
	// iterator category tags
	struct input_iterator_tag { };
	struct forward_iterator_tag : public input_iterator_tag { };
	struct bidirectional_iterator_tag : public forward_iterator_tag { };
	struct random_access_iterator_tag : public bidirectional_iterator_tag { };
	// iterator base class
	template <class Category, class T, class Distance = ptrdiff_t,
		class Pointer = T*, class Reference = T&>
		struct iterator;
	// reverse_iterator
	template <class Iterator> class reverse_iterator;
}

// iterator base class
template <class Category, class T, class Distance,
		class Pointer, class Reference>
struct ft::iterator
{
	typedef T			value_type;
	typedef Distance	difference_type;
	typedef Pointer		pointer;
	typedef Reference	reference;
	typedef Category	iterator_category;
};

// iterator_traits
template <class Iter>
struct ft::iterator_traits
{
	typedef typename Iter::difference_type		difference_type;
	typedef typename Iter::value_type			value_type;
	typedef typename Iter::pointer				pointer;
	typedef typename Iter::reference			reference;
	typedef typename Iter::iterator_category	iterator_category;
};

template <class T>
struct ft::iterator_traits<T*>
{
	typedef std::ptrdiff_t					difference_type;
	typedef T								value_type;
	typedef T*								pointer;
	typedef T&								reference;
	typedef ft::random_access_iterator_tag	iterator_category;
};

template <class T>
struct ft::iterator_traits<const T*>
{
	typedef std::ptrdiff_t					difference_type;
	typedef T								value_type;
	typedef const T*						pointer;
	typedef const T&						reference;
	typedef ft::random_access_iterator_tag	iterator_category;
};

// reverse_iterator
// rbegin points to the element preceding the one that would be pointed to by member end.
template <class Iterator>
class ft::reverse_iterator : public ft::iterator<typename Iterator::iterator_category, typename Iterator::value_type,
			typename Iterator::difference_type, typename Iterator::pointer, typename Iterator::reference>
{
	public:
		// member types
		typedef Iterator 													iterator_type;
		typedef typename ft::iterator_traits<Iterator>::iterator_category	iterator_category;
		typedef typename ft::iterator_traits<Iterator>::value_type			value_type;
		typedef typename ft::iterator_traits<Iterator>::difference_type		difference_type;
		typedef typename ft::iterator_traits<Iterator>::pointer				pointer;
		typedef typename ft::iterator_traits<Iterator>::reference			reference;
		reverse_iterator();
		explicit reverse_iterator(iterator_type it);
		template <class Iter>
			reverse_iterator(const reverse_iterator<Iter> &rev_it);
		~reverse_iterator() { }
		iterator_type		base() const;
		reverse_iterator	&operator=(const reverse_iterator &rhs);
		reference			operator*() const;
		reverse_iterator	operator+(difference_type n) const;
		reverse_iterator	&operator++();
		reverse_iterator	operator++(int);
		reverse_iterator	&operator+=(difference_type n);
		reverse_iterator	operator-(difference_type n) const;
		reverse_iterator	&operator--();
		reverse_iterator	operator--(int);
		reverse_iterator	&operator-=(difference_type n);
		pointer				operator->() const;
		reference			operator[](difference_type n) const;
	private:
		Iterator	_base;
};

template <class Iterator>
ft::reverse_iterator<Iterator>::reverse_iterator() {}

template <class Iterator>
ft::reverse_iterator<Iterator>::reverse_iterator(iterator_type it) : _base(it) {}

template <class Iterator>
template <class Iter>
ft::reverse_iterator<Iterator>::reverse_iterator(const reverse_iterator<Iter> &rev_it) : _base(rev_it.base()) {}

template <class Iterator>
typename ft::reverse_iterator<Iterator>::iterator_type ft::reverse_iterator<Iterator>::base() const
{
	return (this->_base);
}

template <class Iterator>
typename ft::reverse_iterator<Iterator>::reference ft::reverse_iterator<Iterator>::operator*() const
{
	return (*(--iterator_type(this->_base)));
}

template <class Iterator>
ft::reverse_iterator<Iterator> ft::reverse_iterator<Iterator>::operator+(difference_type n) const
{
	return (reverse_iterator(this->_base - n));
}

template <class Iterator>
ft::reverse_iterator<Iterator> ft::reverse_iterator<Iterator>::operator-(difference_type n) const
{
	return (reverse_iterator(this->_base + n));
}

template <class Iterator>
ft::reverse_iterator<Iterator> &ft::reverse_iterator<Iterator>::operator++()
{
	--this->_base;
	return (*this);
}

template <class Iterator>
ft::reverse_iterator<Iterator> &ft::reverse_iterator<Iterator>::operator--()
{
	++this->_base;
	return (*this);
}

template <class Iterator>
ft::reverse_iterator<Iterator> ft::reverse_iterator<Iterator>::operator++(int)
{
	reverse_iterator temp(*this);
	--(*this);
	return (temp);
}

template <class Iterator>
ft::reverse_iterator<Iterator> ft::reverse_iterator<Iterator>::operator--(int)
{
	reverse_iterator temp(*this);
	++(*this);
	return (temp);
}

template <class Iterator>
ft::reverse_iterator<Iterator> &ft::reverse_iterator<Iterator>::operator+=(difference_type n)
{
	this->_base -= n;
	return (*this);
}

template <class Iterator>
ft::reverse_iterator<Iterator> &ft::reverse_iterator<Iterator>::operator-=(difference_type n)
{
	this->_base += n;
	return (*this);
}

template <class Iterator>
typename ft::reverse_iterator<Iterator>::pointer ft::reverse_iterator<Iterator>::operator->() const
{
	return (&this->operator*());
}

template <class Iterator>
typename ft::reverse_iterator<Iterator>::reference ft::reverse_iterator<Iterator>::operator[](difference_type n) const
{
	return (this->_base[-n - 1]);
}

template <class Iterator>
bool	operator==(const ft::reverse_iterator<Iterator> &lhs,
					const ft::reverse_iterator<Iterator> &rhs)
{
	return (lhs.base() == rhs.base());
}

template <class Iterator>
bool	operator!=(const ft::reverse_iterator<Iterator> &lhs,
					const ft::reverse_iterator<Iterator> &rhs)
{
	return (lhs.base() != rhs.base());
}

template <class Iterator>
bool	operator<(const ft::reverse_iterator<Iterator> &lhs,
				const ft::reverse_iterator<Iterator> &rhs)
{
	return (lhs.base() > rhs.base());
}

template <class Iterator>
bool	operator<=(const ft::reverse_iterator<Iterator> &lhs,
					const ft::reverse_iterator<Iterator> &rhs)
{
	return (lhs.base() >= rhs.base());
}

template <class Iterator>
bool	operator>(const ft::reverse_iterator<Iterator> &lhs,
					const ft::reverse_iterator<Iterator> &rhs)
{
	return (lhs.base() < rhs.base());
}

template <class Iterator>
bool	operator>=(const ft::reverse_iterator<Iterator> &lhs,
					const ft::reverse_iterator<Iterator> &rhs)
{
	return (lhs.base() <= rhs.base());
}

template <class Iterator>
ft::reverse_iterator<Iterator>	operator+(
	typename ft::reverse_iterator<Iterator>::difference_type n,
	const ft::reverse_iterator<Iterator> &rev_it)
{
	return (rev_it + n);
}

template <class Iterator>
typename ft::reverse_iterator<Iterator>::difference_type operator-(
	const ft::reverse_iterator<Iterator> &lhs,
    const ft::reverse_iterator<Iterator> &rhs)
{
	return (rhs.base() - lhs.base());
}

#endif
