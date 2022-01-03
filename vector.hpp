/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aisraely <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 14:31:58 by aisraely          #+#    #+#             */
/*   Updated: 2021/12/29 14:31:58 by aisraely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <cstddef>
# include <memory>
# include <iostream>
# include "memory.hpp"
# include "iterator.hpp"
# include "algorithm.hpp"
# include "type_traits.hpp"

namespace ft
{
	template <class Iterator, class Container> class normal_iterator;
	template <class T, class Alloc = std::allocator<T> > class vector; 
}

template <class Iterator, class Container>
class	ft::normal_iterator
{
	protected:
		Iterator	_base;
		typedef ft::iterator_traits<Iterator>			traits_type;
	public:
		// member types
		typedef Iterator								iterator_type;
		typedef typename traits_type::iterator_category	iterator_category;
		typedef typename traits_type::value_type		value_type;
		typedef typename traits_type::difference_type	difference_type;
		typedef typename traits_type::reference			reference;
		typedef typename traits_type::pointer			pointer;

		normal_iterator() {}

		// copy ctor allowing conversion to const_iterator
		template<typename Iter>
		normal_iterator(const normal_iterator<Iter,
		typename ft::enable_if<(ft::is_same<Iter, typename Container::pointer>::value), Container>::type> &copy) : _base(copy.base()) { }

		explicit normal_iterator(const Iterator &_base) : _base(_base) {}
		~normal_iterator() { }
		normal_iterator	&operator=(const normal_iterator &rhs);
		reference		operator*() const;
		normal_iterator	operator+(difference_type n) const;
		normal_iterator	&operator++();
		normal_iterator	operator++(int);
		normal_iterator	&operator+=(difference_type n);
		normal_iterator	operator-(difference_type n) const;
		normal_iterator	&operator--();
		normal_iterator	operator--(int);
		normal_iterator	&operator-=(difference_type n);
		pointer			operator->() const;
		reference		operator[](difference_type n) const;
		const Iterator	&base() const;
};

// vector::iterator

template <class Iterator, class Container>
const typename ft::normal_iterator<Iterator, Container>::iterator_type	&ft::normal_iterator<Iterator, Container>::base() const
{
	return (this->_base);
}

template <class Iterator, class Container>
ft::normal_iterator<Iterator, Container> &ft::normal_iterator<Iterator, Container>::operator=(const normal_iterator &rhs)
{
	this->_base = rhs._base;
	return (*this);
}

template <class Iterator, class Container>
typename ft::normal_iterator<Iterator, Container>::reference ft::normal_iterator<Iterator, Container>::operator*() const
{
	return (*this->_base);
}

template <class Iterator, class Container>
ft::normal_iterator<Iterator, Container> ft::normal_iterator<Iterator, Container>::operator+(difference_type n) const
{
	return (normal_iterator(this->_base + n));
}

template <class Iterator, class Container>
ft::normal_iterator<Iterator, Container> ft::normal_iterator<Iterator, Container>::operator-(difference_type n) const
{
	return (normal_iterator(this->_base - n));
}

template <class Iterator, class Container>
ft::normal_iterator<Iterator, Container> &ft::normal_iterator<Iterator, Container>::operator++()
{
	this->_base++;
	return (*this);
}

template <class Iterator, class Container>
ft::normal_iterator<Iterator, Container> &ft::normal_iterator<Iterator, Container>::operator--()
{
	this->_base--;
	return (*this);
}

template <class Iterator, class Container>
ft::normal_iterator<Iterator, Container> ft::normal_iterator<Iterator, Container>::operator++(int)
{
	normal_iterator temp = *this;
	this->_base++;
	return (temp);
}

template <class Iterator, class Container>
ft::normal_iterator<Iterator, Container> ft::normal_iterator<Iterator, Container>::operator--(int)
{
	normal_iterator temp = *this;
	this->_base--;
	return (temp);
}

template <class Iterator, class Container>
ft::normal_iterator<Iterator, Container> &ft::normal_iterator<Iterator, Container>::operator+=(difference_type n)
{
	this->_base += n;
	return (*this);
}

template <class Iterator, class Container>
ft::normal_iterator<Iterator, Container> &ft::normal_iterator<Iterator, Container>::operator-=(difference_type n)
{
	this->_base -= n;
	return (*this);
}

template <class Iterator, class Container>
typename ft::normal_iterator<Iterator, Container>::pointer ft::normal_iterator<Iterator, Container>::operator->() const
{
	return (&this->operator*());
}

template <class Iterator, class Container>
typename ft::normal_iterator<Iterator, Container>::reference ft::normal_iterator<Iterator, Container>::operator[](difference_type n) const
{
	return (this->_base[n]);
}

template <class Iterator, class Container>
bool operator==(const typename ft::normal_iterator<Iterator, Container> &lhs,
                   const typename ft::normal_iterator<Iterator, Container> &rhs)
{
	return (lhs.base() == rhs.base());
}

template <class Iterator, class Container>
bool	operator!=(const typename ft::normal_iterator<Iterator, Container> &lhs,
					const typename ft::normal_iterator<Iterator, Container> &rhs)
{
	return (lhs.base() != rhs.base());
}

template <class Iterator, class Container>
bool	operator<(const typename ft::normal_iterator<Iterator, Container> &lhs,
					const typename ft::normal_iterator<Iterator, Container> &rhs)
{
	return (lhs.base() < rhs.base());
}

template <class Iterator, class Container>
bool	operator<=(const typename ft::normal_iterator<Iterator, Container> &lhs,
					const typename ft::normal_iterator<Iterator, Container> &rhs)
{
	return (lhs.base() <= rhs.base());
}

template <class Iterator, class Container>
bool	operator>(const typename ft::normal_iterator<Iterator, Container> &lhs,
					const typename ft::normal_iterator<Iterator, Container> &rhs)
{
	return (lhs.base() > rhs.base());
}

template <class Iterator, class Container>
bool	operator>=(const typename ft::normal_iterator<Iterator, Container> &lhs,
					const typename ft::normal_iterator<Iterator, Container> &rhs)
{
	return (lhs.base() >= rhs.base());
}

template <class Iterator, class Container>
typename ft::normal_iterator<Iterator, Container> operator+(
			typename ft::normal_iterator<Iterator, Container>::difference_type n,
			const typename ft::normal_iterator<Iterator, Container> &it)
{
	return (it + n);
}

template <class Iterator, class Container>
typename ft::normal_iterator<Iterator, Container>::difference_type operator-(
	const typename ft::normal_iterator<Iterator, Container> &lhs,
	const typename ft::normal_iterator<Iterator, Container> &rhs)
{
	return (lhs.base() - rhs.base());
}

template <class T, class Alloc>
class	ft::vector
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
		typedef ft::normal_iterator<pointer, vector>		iterator;
		typedef ft::normal_iterator<const_pointer, vector>	const_iterator;
		typedef typename ft::reverse_iterator<iterator>		reverse_iterator;
		typedef typename ft::reverse_iterator<const_iterator> const_reverse_iterator;

		// (constructor)
		explicit vector(const allocator_type &alloc = allocator_type());
		explicit vector(size_type n, const value_type &val = value_type(), const allocator_type &alloc = allocator_type());
		template <class InputIterator>
			vector(InputIterator first, InputIterator last, const allocator_type &alloc = allocator_type());
		vector(const vector &x);
		vector &operator=(const vector &x);

		// (destructor)
		~vector();

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
		size_type	size() const;
		size_type	max_size() const;
		void		resize(size_type n, value_type val = value_type());
		size_type	capacity() const;
		bool		empty() const;
		void		reserve(size_type n);

		// element access
		reference		operator[](size_type n);
		const_reference	operator[](size_type n) const;
		reference		at(size_type n);
		const_reference	at(size_type n) const;
		reference		front();
		const_reference	front() const;
		reference		back();
		const_reference	back() const;

		// modifiers
		template <class InputIterator>
		void	assign(InputIterator first, InputIterator last);
		void		assign(size_type n, const value_type &val);
		void		push_back(const value_type &val);
		void		pop_back();
		iterator	insert(iterator position, const value_type &val);
		void		insert(iterator position, size_type n, const value_type &val);
		template <class InputIterator>
		void	insert(iterator position, InputIterator first, InputIterator last);
		iterator	erase(iterator position);
		iterator	erase(iterator first, iterator last);
		void		swap(vector &x);
		void		clear();

		// allocator
		allocator_type	get_allocator() const;
	private:
		allocator_type	_alloc;
		pointer			_data;
		size_type		_capacity;
		size_type		_size;
};


// vector

template <class T, class Alloc>
ft::vector<T, Alloc>::vector(const allocator_type &alloc) : _alloc(alloc), _data(NULL), _capacity(0), _size(0) {}

template <class T, class Alloc>
ft::vector<T, Alloc>::~vector()
{
	for (size_type i = this->_size; i > 0; i--)
		this->_alloc.destroy(this->_data + (i - 1));
	this->_alloc.deallocate(this->_data, this->_capacity);
}

template <class T, class Alloc>
typename ft::vector<T, Alloc>::iterator ft::vector<T, Alloc>::begin()
{
	return (iterator(this->_data));
}

template <class T, class Alloc>
typename ft::vector<T, Alloc>::const_iterator ft::vector<T, Alloc>::begin() const
{
	return (const_iterator(this->_data));
}

template <class T, class Alloc>
typename ft::vector<T, Alloc>::iterator ft::vector<T, Alloc>::end()
{
	return (iterator(this->_data + this->_size));
}

template <class T, class Alloc>
typename ft::vector<T, Alloc>::const_iterator ft::vector<T, Alloc>::end() const
{
	return (const_iterator(this->_data + this->_size));
}

template <class T, class Alloc>
typename ft::vector<T, Alloc>::reverse_iterator ft::vector<T, Alloc>::rbegin()
{
	return (reverse_iterator(this->end()));
}

template <class T, class Alloc>
typename ft::vector<T, Alloc>::const_reverse_iterator ft::vector<T, Alloc>::rbegin() const
{
	return (const_reverse_iterator(this->end()));
}

template <class T, class Alloc>
typename ft::vector<T, Alloc>::reverse_iterator ft::vector<T, Alloc>::rend()
{
	return (reverse_iterator(this->begin()));
}

template <class T, class Alloc>
typename ft::vector<T, Alloc>::const_reverse_iterator ft::vector<T, Alloc>::rend() const
{
	return (const_reverse_iterator(this->begin()));
}

template <class T, class Alloc>
typename ft::vector<T, Alloc>::size_type ft::vector<T, Alloc>::size() const
{
	return (this->_size);
}

template <class T, class Alloc>
typename ft::vector<T, Alloc>::size_type ft::vector<T, Alloc>::max_size() const
{
	return (this->_alloc.max_size());
}

template <class T, class Alloc>
void	ft::vector<T, Alloc>::reserve(size_type n)
{
	pointer		new_data;
	if (this->_capacity >= n)
		return ;
	new_data = this->_alloc.allocate(n);
	for (size_type i = 0; i < this->_size; i++)
	{
		this->_alloc.construct(new_data + i, this->_data[i]);
		this->_alloc.destroy(this->_data + i);
	}
	this->_alloc.deallocate(this->_data, this->_capacity);
	this->_data = new_data;
	this->_capacity = n;
}

template <class T, class Alloc>
void	ft::vector<T, Alloc>::push_back(const value_type &val)
{
	this->insert(this->end(), val);
}

template <class T, class Alloc>
typename ft::vector<T, Alloc>::iterator	ft::vector<T, Alloc>::insert(iterator position, const value_type &val)
{
	if (this->_size == this->_capacity)
	{
		difference_type	offset = position.base() - this->_data;
		this->reserve(ft::max(size_type(1), this->_capacity * 2));
		position = this->begin() + offset;
	}
	reverse_iterator it = this->rbegin();
	// std::cout << "before the loop" << std::endl;
	while (it != this->rend() && it.base() - 1 >= position)
	{
		*(it - 1) = *it;
		++it;
	}
	// std::cout << "after the loop" << std::endl;
	this->_alloc.construct(position.base(), val);
	this->_size++;
	return (position);
}

template <class T, class Alloc>
	bool operator==(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs);
template <class T, class Alloc>
	bool operator!=(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs);
template <class T, class Alloc>
	bool operator<(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs);
template <class T, class Alloc>
	bool operator<=(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs);
template <class T, class Alloc>
	bool operator>(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs);
template <class T, class Alloc>
	bool operator>=(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs);

template <class T, class Alloc>
	void swap(ft::vector<T, Alloc> &x, ft::vector<T, Alloc> &y);

#endif
