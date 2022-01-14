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
// # include <exception>
// # include "iterator.hpp"
# include "algorithm.hpp"
# include "memory.hpp"
# include <iterator>
// # include "type_traits.hpp"
// # include "utility.hpp"
// # include <iostream>

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

	template <class Iterator, class Container> class normal_iterator;
	template <class T, class Alloc = std::allocator<T> > class vector;
	// template <class T, class Alloc>
	// void	swap(vector<T, Alloc> &x, vector<T, Alloc> &y);
}

// vector iterator

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

		// normal_iterator() : _base() { }

		// copy ctor allowing conversion to const_iterator
		// template<typename Iter>
		// normal_iterator(const normal_iterator<Iter,
		// typename ft::enable_if<(ft::is_same<Iter, typename Container::pointer>::value), Container>::type> &copy) : _base(copy.base()) { }

		explicit normal_iterator(const Iterator &_base) : _base(_base) { }
		// ~normal_iterator() { }
		// normal_iterator	&operator=(const normal_iterator &rhs);
		// reference		operator*() const;
		// normal_iterator	operator+(difference_type n) const;
		// normal_iterator	&operator++();
		// normal_iterator	operator++(int);
		// normal_iterator	&operator+=(difference_type n);
		// normal_iterator	operator-(difference_type n) const;
		// normal_iterator	&operator--();
		// normal_iterator	operator--(int);
		// normal_iterator	&operator-=(difference_type n);
		// pointer			operator->() const;
		// reference		operator[](difference_type n) const;
		const Iterator	&base() const { return (this->_base); }
};

// vector::iterator

// template <class Iterator, class Container>
// const typename ft::normal_iterator<Iterator, Container>::iterator_type	&ft::normal_iterator<Iterator, Container>::base() const
// {
// 	return (this->_base);
// }

// template <class Iterator, class Container>
// ft::normal_iterator<Iterator, Container> &ft::normal_iterator<Iterator, Container>::operator=(const normal_iterator &rhs)
// {
// 	this->_base = rhs._base;
// 	return (*this);
// }

// template <class Iterator, class Container>
// typename ft::normal_iterator<Iterator, Container>::reference ft::normal_iterator<Iterator, Container>::operator*() const
// {
// 	return (*this->_base);
// }

// template <class Iterator, class Container>
// ft::normal_iterator<Iterator, Container> ft::normal_iterator<Iterator, Container>::operator+(difference_type n) const
// {
// 	return (normal_iterator(this->_base + n));
// }

// template <class Iterator, class Container>
// ft::normal_iterator<Iterator, Container> ft::normal_iterator<Iterator, Container>::operator-(difference_type n) const
// {
// 	return (normal_iterator(this->_base - n));
// }

// template <class Iterator, class Container>
// ft::normal_iterator<Iterator, Container> &ft::normal_iterator<Iterator, Container>::operator++()
// {
// 	this->_base++;
// 	return (*this);
// }

// template <class Iterator, class Container>
// ft::normal_iterator<Iterator, Container> &ft::normal_iterator<Iterator, Container>::operator--()
// {
// 	this->_base--;
// 	return (*this);
// }

// template <class Iterator, class Container>
// ft::normal_iterator<Iterator, Container> ft::normal_iterator<Iterator, Container>::operator++(int)
// {
// 	normal_iterator temp = *this;
// 	this->_base++;
// 	return (temp);
// }

// template <class Iterator, class Container>
// ft::normal_iterator<Iterator, Container> ft::normal_iterator<Iterator, Container>::operator--(int)
// {
// 	normal_iterator temp = *this;
// 	this->_base--;
// 	return (temp);
// }

// template <class Iterator, class Container>
// ft::normal_iterator<Iterator, Container> &ft::normal_iterator<Iterator, Container>::operator+=(difference_type n)
// {
// 	this->_base += n;
// 	return (*this);
// }

// template <class Iterator, class Container>
// ft::normal_iterator<Iterator, Container> &ft::normal_iterator<Iterator, Container>::operator-=(difference_type n)
// {
// 	this->_base -= n;
// 	return (*this);
// }

// template <class Iterator, class Container>
// typename ft::normal_iterator<Iterator, Container>::pointer ft::normal_iterator<Iterator, Container>::operator->() const
// {
// 	return (&this->operator*());
// }

// template <class Iterator, class Container>
// typename ft::normal_iterator<Iterator, Container>::reference ft::normal_iterator<Iterator, Container>::operator[](difference_type n) const
// {
// 	return (this->_base[n]);
// }

// template <class Iterator, class Container>
// bool operator==(const ft::normal_iterator<Iterator, Container> &lhs,
//                    const ft::normal_iterator<Iterator, Container> &rhs)
// {
// 	return (lhs.base() == rhs.base());
// }

// template <class Iterator, class Container>
// bool	operator!=(const ft::normal_iterator<Iterator, Container> &lhs,
// 					const ft::normal_iterator<Iterator, Container> &rhs)
// {
// 	return (lhs.base() != rhs.base());
// }

// template <class Iterator, class Container>
// bool	operator<(const ft::normal_iterator<Iterator, Container> &lhs,
// 					const ft::normal_iterator<Iterator, Container> &rhs)
// {
// 	return (lhs.base() < rhs.base());
// }

// template <class Iterator, class Container>
// bool	operator<=(const ft::normal_iterator<Iterator, Container> &lhs,
// 					const ft::normal_iterator<Iterator, Container> &rhs)
// {
// 	return (lhs.base() <= rhs.base());
// }

// template <class Iterator, class Container>
// bool	operator>(const ft::normal_iterator<Iterator, Container> &lhs,
// 					const ft::normal_iterator<Iterator, Container> &rhs)
// {
// 	return (lhs.base() > rhs.base());
// }

// template <class Iterator, class Container>
// bool	operator>=(const ft::normal_iterator<Iterator, Container> &lhs,
// 					const ft::normal_iterator<Iterator, Container> &rhs)
// {
// 	return (lhs.base() >= rhs.base());
// }

// template <class Iterator, class Container>
// typename ft::normal_iterator<Iterator, Container> operator+(
// 			typename ft::normal_iterator<Iterator, Container>::difference_type n,
// 			const ft::normal_iterator<Iterator, Container> &it)
// {
// 	return (it + n);
// }

template <class Iterator, class Container>
bool	operator!=(const ft::normal_iterator<Iterator, Container> &lhs,
					const ft::normal_iterator<Iterator, Container> &rhs)
{
	return (lhs.base() != rhs.base());
}

template <class Iterator, class Container>
typename ft::normal_iterator<Iterator, Container>::difference_type operator-(
	const ft::normal_iterator<Iterator, Container> &lhs,
	const ft::normal_iterator<Iterator, Container> &rhs)
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
		// typedef typename allocator_type::reference			reference;
		// typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;
		typedef ptrdiff_t									difference_type;
		typedef size_t										size_type;
		typedef ft::normal_iterator<pointer, vector>		iterator;
		typedef ft::normal_iterator<const_pointer, vector>	const_iterator;
		// typedef typename ft::reverse_iterator<iterator>		reverse_iterator;
		// typedef typename ft::reverse_iterator<const_iterator> const_reverse_iterator;

		// (constructor)
		// explicit vector(const allocator_type &alloc = allocator_type());
		// explicit vector(size_type n, const value_type &val = value_type(), const allocator_type &alloc = allocator_type());
		// template <class InputIterator>
		// vector(InputIterator first, InputIterator last, const allocator_type &alloc = allocator_type());
		// vector(const vector &x);
		// vector &operator=(const vector &x);

		// (destructor)
		~vector();

		// iterators
		iterator				begin();
		// const_iterator			begin() const;
		iterator				end();
		// const_iterator			end() const;
		// reverse_iterator		rbegin();
		// const_reverse_iterator	rbegin() const;
		// reverse_iterator		rend();
		// const_reverse_iterator	rend() const;

		// // capacity
		// size_type	size() const;
		// size_type	max_size() const;
		// void		resize(size_type n, value_type val = value_type());
		// size_type	capacity() const;
		// bool		empty() const;
		// void		reserve(size_type n);

		// // element access
		// reference		operator[](size_type n);
		// const_reference	operator[](size_type n) const;
		// reference		at(size_type n);
		// const_reference	at(size_type n) const;
		// reference		front();
		// const_reference	front() const;
		// reference		back();
		// const_reference	back() const;

		// modifiers
		// template <class InputIterator>
		// void		assign(InputIterator first, InputIterator last);
		// void		assign(size_type n, const value_type &val);
		// void		push_back(const value_type &val);
		// void		pop_back();
		// iterator	insert(iterator position, const value_type &val);
		// void		insert(iterator position, size_type n, const value_type &val);
		// template <class InputIterator>
		// void		insert(iterator position, InputIterator first, InputIterator last);
		iterator	erase(iterator position);
		iterator	erase(iterator first, iterator last);
		// void		swap(vector &x);
		void		clear();

		// allocator
		// allocator_type	get_allocator() const;
	protected:
		// pointer			allocate_a(size_type n);
		void			deallocate_a(pointer p, size_type n);
		// template <typename ForwardIterator>
		// pointer			allocate_and_copy(size_type n, ForwardIterator first, ForwardIterator last);
		// size_type		check_length(size_type n, const char *s);
		// template <typename InputIterator>
		// void			constructor_dispatch(InputIterator first, InputIterator last, ft::false_type);
		// template <typename Integral>
		// void			constructor_dispatch(Integral n, Integral val, ft::true_type);
		// template <typename InputIterator>
		// void			range_construct(InputIterator first, InputIterator last, std::input_iterator_tag);
		// template <typename ForwardIterator>
		// void			range_construct(ForwardIterator first, ForwardIterator last, std::forward_iterator_tag);
		// void			fill_construct(size_type n, const value_type &val);
		// template <typename InputIterator>
		// void			insert_dispatch(iterator position, InputIterator first, InputIterator last, ft::false_type);
		// template <typename Integral>
		// void			insert_dispatch(iterator position, Integral n, Integral val, ft::true_type);
		// template <typename InputIterator>
		// void			range_insert(iterator position, InputIterator first, InputIterator last, std::input_iterator_tag);
		// template <typename ForwardIterator>
		// void			range_insert(iterator position, ForwardIterator first, ForwardIterator last, std::forward_iterator_tag);
		// void			fill_insert(iterator position, size_type n, const value_type &val);
		// template <typename InputIterator>
		// void			assign_dispatch(InputIterator first, InputIterator last, ft::false_type);
		// template <typename Integral>
		// void			assign_dispatch(Integral n, Integral val, ft::true_type);
		// template <typename InputIterator>
		// void			range_assign(InputIterator first, InputIterator last, std::input_iterator_tag);
		// template <typename ForwardIterator>
		// void			range_assign(ForwardIterator first, ForwardIterator last, std::forward_iterator_tag);
		// void			fill_assign(size_type n, const value_type &val);
	private:
		// private member variables
		allocator_type	_alloc;
		pointer			_data;
		size_type		_capacity;
		size_type		_size;
};

// vector

// template <class T, class Alloc>
// ft::vector<T, Alloc>::vector(const allocator_type &alloc) : _alloc(alloc), _data(NULL), _capacity(0), _size(0) {}

// template <class T, class Alloc>
// ft::vector<T, Alloc>::vector(size_type n, const value_type &val, const allocator_type &alloc) : _alloc(alloc), _data(NULL), _capacity(0), _size(0)
// {
// 	this->_data = allocate_a(check_length(static_cast<size_type>(n), "vector::vector"));
// 	this->_capacity = n;
// 	fill_construct(n, val);
// }

// template <class T, class Alloc>
// template <class InputIterator>
// ft::vector<T, Alloc>::vector(InputIterator first, InputIterator last, const allocator_type &alloc) : _alloc(alloc), _data(NULL), _capacity(0), _size(0)
// {
// 	constructor_dispatch(first, last, typename ft::is_integral<InputIterator>::type());
// }

// template <class T, class Alloc>
// template <typename InputIterator>
// void	ft::vector<T, Alloc>::constructor_dispatch(InputIterator first, InputIterator last, ft::false_type)
// {
// 	// template argument was an iterator, proceed
// 	range_construct(first, last, typename ft::iterator_traits<InputIterator>::iterator_category());
// }

// template <class T, class Alloc>
// template <typename Integral>
// void	ft::vector<T, Alloc>::constructor_dispatch(Integral n, Integral val, ft::true_type)
// {
// 	this->_data = allocate_a(check_length(static_cast<size_type>(n), "vector::constructor_dispatch"));
// 	this->_capacity = n;
// 	// template argument was an integer, do fill_construct() instead
// 	fill_construct(static_cast<size_type>(n), val);
// }

// template <class T, class Alloc>
// void	ft::vector<T, Alloc>::fill_construct(size_type n, const value_type &val)
// {
// 	ft::uninitialized_fill_n_a(this->_data, n, val, this->_alloc);
// 	this->_size = n;
// }

// template <class T, class Alloc>
// template <typename InputIterator>
// void	ft::vector<T, Alloc>::range_construct(InputIterator first, InputIterator last, std::input_iterator_tag)
// {
// 	try
// 	{
// 		for (; first != last; ++first)
// 			push_back(*first);
// 	}
// 	catch (...)
// 	{
// 		clear();
// 		throw ;
// 	}
// }

// template <class T, class Alloc>
// template <typename ForwardIterator>
// void	ft::vector<T, Alloc>::range_construct(ForwardIterator first, ForwardIterator last, std::forward_iterator_tag)
// {
// 	const size_type	n = ft::distance(first, last);
// 	this->_data = allocate_a(check_length(n, "vector::range_construct"));
// 	this->_capacity = n;
// 	ft::uninitialized_copy_a(first, last, this->_data, this->_alloc);
// 	this->_size = n;
// }

// template <class T, class Alloc>
// ft::vector<T, Alloc>::vector(const vector &x) : _alloc(x._alloc), _data(NULL), _capacity(0), _size(0)
// {
// 	range_construct(x.begin(), x.end(), std::random_access_iterator_tag());
// }

// template <class T, class Alloc>
// typename ft::vector<T, Alloc>::vector &ft::vector<T, Alloc>::operator=(const vector &x)
// {
// 	if (&x != this)
// 	{
// 		const size_type	x_size = x.size();
// 		// reallocate, not enough memory
// 		if (x_size > this->_capacity)
// 		{
// 			pointer	new_data = allocate_and_copy(x_size, x.begin(), x.end());
// 			clear();
// 			deallocate_a(this->_data, this->_capacity);
// 			this->_data = new_data;
// 			this->_capacity = x_size;
// 		}
// 		// copy from x to this, and destroy the rest past x's elements
// 		else if (this->_size >= x_size)
// 			ft::destroy_a(ft::copy(x.begin(), x.end(), begin()), end(), this->_alloc);
// 		// memory is enough, assign constructed objects and construct the ones that are beyond size
// 		else
// 		{
// 			ft::copy(x._data, x._data + this->_size, this->_data);
// 			ft::uninitialized_copy_a(x._data + this->_size, x._data + x_size, this->_data + this->_size, this->_alloc);
// 		}
// 		this->_size = x_size;
// 	}
// 	return (*this);
// }

template <class T, class Alloc>
ft::vector<T, Alloc>::~vector()
{
	clear();
	deallocate_a(this->_data, this->_capacity);
}

template <class T, class Alloc>
typename ft::vector<T, Alloc>::iterator ft::vector<T, Alloc>::begin()
{
	return (iterator(this->_data));
}

// template <class T, class Alloc>
// typename ft::vector<T, Alloc>::const_iterator ft::vector<T, Alloc>::begin() const
// {
// 	return (const_iterator(this->_data));
// }

template <class T, class Alloc>
typename ft::vector<T, Alloc>::iterator ft::vector<T, Alloc>::end()
{
	return (iterator(this->_data + this->_size));
}

// template <class T, class Alloc>
// typename ft::vector<T, Alloc>::const_iterator ft::vector<T, Alloc>::end() const
// {
// 	return (const_iterator(this->_data + this->_size));
// }

// template <class T, class Alloc>
// typename ft::vector<T, Alloc>::reverse_iterator ft::vector<T, Alloc>::rbegin()
// {
// 	return (reverse_iterator(end()));
// }

// template <class T, class Alloc>
// typename ft::vector<T, Alloc>::const_reverse_iterator ft::vector<T, Alloc>::rbegin() const
// {
// 	return (const_reverse_iterator(end()));
// }

// template <class T, class Alloc>
// typename ft::vector<T, Alloc>::reverse_iterator ft::vector<T, Alloc>::rend()
// {
// 	return (reverse_iterator(begin()));
// }

// template <class T, class Alloc>
// typename ft::vector<T, Alloc>::const_reverse_iterator ft::vector<T, Alloc>::rend() const
// {
// 	return (const_reverse_iterator(begin()));
// }

// template <class T, class Alloc>
// typename ft::vector<T, Alloc>::size_type ft::vector<T, Alloc>::size() const
// {
// 	return (this->_size);
// }

// template <class T, class Alloc>
// typename ft::vector<T, Alloc>::size_type ft::vector<T, Alloc>::max_size() const
// {
// 	return (this->_alloc.max_size());
// }

// template <class T, class Alloc>
// void	ft::vector<T, Alloc>::resize(size_type n, value_type val)
// {
// 	if (n > this->_size)
// 		insert(end(), n - this->_size, val);
// 	else if (n < this->_size)
// 		erase(end() - (this->_size - n), end());
// }

// template <class T, class Alloc>
// typename ft::vector<T, Alloc>::size_type ft::vector<T, Alloc>::capacity() const
// {
// 	return (this->_capacity);
// }

// template <class T, class Alloc>
// bool	ft::vector<T, Alloc>::empty() const
// {
// 	return (!this->_size);
// }

// template <class T, class Alloc>
// void	ft::vector<T, Alloc>::reserve(size_type n)
// {
// 	if (n > max_size())
// 		throw std::length_error("vector::reserve");
// 	if (this->_capacity < n)
// 	{
// 		// allocate and copy what already was initialized
// 		pointer		new_data = allocate_and_copy(n, this->_data, this->_data + this->_size);
// 		// free old data
// 		clear();
// 		deallocate_a(this->_data, this->_capacity);
// 		this->_data = new_data;
// 		this->_capacity = n;
// 	}
// }

// template <class T, class Alloc>
// typename ft::vector<T, Alloc>::reference ft::vector<T, Alloc>::operator[](size_type n)
// {
// 	return (this->_data[n]);
// }

// template <class T, class Alloc>
// typename ft::vector<T, Alloc>::const_reference ft::vector<T, Alloc>::operator[](size_type n) const
// {
// 	return (this->_data[n]);
// }

// template <class T, class Alloc>
// typename ft::vector<T, Alloc>::reference ft::vector<T, Alloc>::at(size_type n)
// {
// 	if (n >= this->_size)
// 		throw std::out_of_range("vector::at: n (which is " + SSTR(n) + ") >= this->size() (which is " + SSTR(this->_size) + ")");
// 	return (this->_data[n]);
// }

// template <class T, class Alloc>
// typename ft::vector<T, Alloc>::const_reference ft::vector<T, Alloc>::at(size_type n) const
// {
// 	if (n >= this->_size)
// 		throw std::out_of_range("vector::at: n (which is " + SSTR(n) + ") >= this->size() (which is " + SSTR(this->_size) + ")");
// 	return (this->_data[n]);
// }

// template <class T, class Alloc>
// typename ft::vector<T, Alloc>::reference ft::vector<T, Alloc>::front()
// {
// 	return (this->_data[0]);
// }

// template <class T, class Alloc>
// typename ft::vector<T, Alloc>::const_reference ft::vector<T, Alloc>::front() const
// {
// 	return (this->_data[0]);
// }

// template <class T, class Alloc>
// typename ft::vector<T, Alloc>::reference ft::vector<T, Alloc>::back()
// {
// 	return (this->_data[this->_size - 1]);
// }

// template <class T, class Alloc>
// typename ft::vector<T, Alloc>::const_reference ft::vector<T, Alloc>::back() const
// {
// 	return (this->_data[this->_size - 1]);
// }

// template <class T, class Alloc>
// void	ft::vector<T, Alloc>::push_back(const value_type &val)
// {
// 	insert(end(), val);
// }

// template <class T, class Alloc>
// void	ft::vector<T, Alloc>::pop_back()
// {
// 	erase(end() - 1);
// }

// template <class T, class Alloc>
// typename ft::vector<T, Alloc>::iterator	ft::vector<T, Alloc>::insert(iterator position, const value_type &val)
// {
// 	// offset, to return a valid iterator
// 	const size_type	n = position - begin();
// 	// building at past-end with enough capacity treated separately
// 	if (this->_size != this->_capacity && position == end())
// 		this->_alloc.construct(this->_data + this->_size, val);
// 	else
// 	{
// 		// no reallocation needed, thus 1 element will get displaced past-end
// 		if (this->_size != this->_capacity)
// 		{
// 			// displace last element
// 			this->_alloc.construct(this->_data + this->_size, *(this->_data + this->_size - 1));
// 			// in case if an element being inserted is inside the container, after `position`,
// 			// because the reference will be invalidated after elements are shifted to right
// 			value_type	val_copy = val;
// 			// shift elements after position to the right
// 			ft::copy_backward(position.base(), this->_data + this->_size - 1, this->_data + this->_size);
// 			// assign to position from copy
// 			*position = val_copy;
// 		}
// 		// reallocation needed
// 		else
// 		{
// 			const size_type	new_capacity = check_length(1, "vector::insert");
// 			const size_type	elems_before = position - begin();
// 			pointer			new_data = allocate_a(new_capacity);
// 			pointer			new_data_end = new_data;
// 			try
// 			{
// 				// elements itself
// 				this->_alloc.construct(new_data + elems_before, val);
// 				// so that catch block will destroy only the failed object
// 				new_data_end = NULL;
// 				// import everything before position 
// 				new_data_end = ft::uninitialized_copy_a(this->_data, position.base(), new_data, this->_alloc);
// 				new_data_end++;
// 				// import everything after position 
// 				new_data_end = ft::uninitialized_copy_a(position.base(), this->_data + this->_size, new_data_end, this->_alloc);
// 			}
// 			catch (...)
// 			{
// 				if (!new_data_end)
// 					this->_alloc.destroy(new_data + elems_before);
// 				else
// 					ft::destroy_a(new_data, new_data_end, this->_alloc);
// 				deallocate_a(new_data, new_capacity);
// 				throw ;
// 			}
// 			clear();
// 			deallocate_a(this->_data, this->_capacity);
// 			this->_data = new_data;
// 			this->_capacity = new_capacity;
// 		}
// 	}
// 	this->_size++;
// 	return (iterator(this->_data + n));
// }

// template <class T, class Alloc>
// void	ft::vector<T, Alloc>::insert(iterator position, size_type n, const value_type &val)
// {
// 	fill_insert(position, n, val);
// }

// // is separated from insert(fill) so that tag dispatch works correctly
// template <class T, class Alloc>
// void	ft::vector<T, Alloc>::fill_insert(iterator position, size_type n, const value_type &val)
// {
// 	if (!n)
// 		return ;
// 	// no reallocation needed, can work with already allocated memory
// 	if (this->_capacity - this->_size >= n)
// 	{
// 		// in case position points to element inside the container
// 		value_type	val_copy = val;
// 		const size_type	elems_after = end() - position;
// 		// if no filled elements will be constructed beyond size
// 		if (elems_after > n)
// 		{
// 			// displace elements from the end of sequence to the right, beyond size, by constructing objects on uninitialized memory
// 			ft::uninitialized_copy_a(this->_data + size - n, this->_data + this->_size, this->_data + this->_size, this->_alloc);
// 			// copying whatever is not displaced into uninitialized memory -- backwards, because it happens to the right
// 			ft::copy_backward(position.base(), this->_data + this->_size - n, this->_data + this->_size);
// 			// fill in the gaps
// 			ft::fill(position.base(), position.base() + n, val_copy);
// 		}
// 		// filled elements will be constructed beyond size
// 		else
// 		{
// 			// fill in elements past size
// 			ft::uninitialized_fill_n_a(this->_data + this->_size, n - elems_after, val_copy, this->_alloc);
// 			// move whatever's from position till size past newly constructed filled elements
// 			ft::uninitialized_copy_a(position.base(), this->_data + this->_size, this->_data + this->_size + n - elems_after, this->_alloc);
// 			// now fill in the old range from position till size
// 			ft::fill(position.base(), this->_data + this->_size, val_copy);
// 		}
// 	}
// 	// allocation is required
// 	else
// 	{
// 		const size_type	new_capacity = check_length(n, "vector::fill_insert");
// 		const size_type	elems_before = position - begin();
// 		pointer			new_data = allocate_a(new_capacity);
// 		pointer			new_data_end = new_data;
// 		try
// 		{
// 			// construct the filled elements in newly allocated memory
// 			ft::uninitialized_fill_n_a(new_data + elems_before, n, val, this->_alloc);
// 			// so that if in next uninitialized_copy_a() an exception is thrown, the section above gets destroyed only
// 			new_data_end = NULL;
// 			// copy whatever was before the filled elements to new memory
// 			new_data_end = ft::uninitialized_copy_a(this->_data, position.base(), new_data, this->_alloc);
// 			// so that if in next uninitialized_copy_a() an exception is thrown, elements constructed above don't get missed
// 			new_data_end += n;
// 			// copy whatever was after the filled elements to new memory
// 			new_data_end = ft::uninitialized_copy_a(position.base(), this->_data + this->_size, new_data_end, this->_alloc);
// 		}
// 		catch (...)
// 		{
// 			if (!new_data_end)
// 				ft::destroy_a(new_data + elems_before, new_data + elems_before + n, this->_alloc);
// 			else
// 				ft::destroy_a(new_data, new_data_end, this->_alloc);
// 			deallocate_a(new_data, new_capacity);
// 			throw ;
// 		}
// 		// free old memory
// 		clear();
// 		deallocate_a(this->_data, this->_capacity);
// 		// assign new pointers and data
// 		this->capacity = new_capacity;
// 		this->_data = new_data;
// 	}
// 	this->_size += n;
// }

// template <class T, class Alloc>
// template <class InputIterator>
// void	ft::vector<T, Alloc>::range_insert(iterator position, InputIterator first, InputIterator last, std::input_iterator_tag)
// {
// 	for (; first != last; ++first, ++position)
// 		position = insert(position, *first);
// }

// template <class T, class Alloc>
// template <class ForwardIterator>
// void	ft::vector<T, Alloc>::range_insert(iterator position, ForwardIterator first, ForwardIterator last, std::forward_iterator_tag)
// {
// 	if (first == last)
// 		return ;
// 	const size_type	n = ft::distance(first, last);
// 	// no reallocation needed
// 	if (this->_capacity - this->_size >= n)
// 	{
// 		const size_type	elems_after = end() - position;
// 		// if no range elements will be constructed beyond size
// 		if (elems_after > n)
// 		{
// 			// displace elements from the end of sequence to the right, beyond size, by constructing objects on uninitialized memory
// 			ft::uninitialized_copy_a(this->_data + size - n, this->_data + this->_size, this->_data + this->_size, this->_alloc);
// 			// copying whatever is not displaced into uninitialized memory -- backwards, because it happens to the right
// 			ft::copy_backward(position.base(), this->_data + this->_size - n, this->_data + this->_size);
// 			// copy range in the gap
// 			ft::copy(first, last, position);
// 		}
// 		// range elements will be constructed beyond size
// 		else
// 		{
// 			ForwardIterator	mid = first;
// 			// this now points to the first of last elements of range about to be displaced to uninitialized memory
// 			ft::advance(mid, elems_after);
// 			// initialize them (lower part of range)
// 			ft::uninitialized_copy_a(mid, last, this->_data + this->_size, this->_alloc);
// 			// transfer whatever was after position past newly transferred range elements
// 			ft::uninitialized_copy_a(position.base(), this->_data + this->_size, this->_data + this->_size + n - elems_after, this->_alloc);
// 			// transfer the rest from range (higher part of range)		
// 			ft::copy(first, mid, position);
// 		}
// 	}
// 	// reallocation needed
// 	else
// 	{
// 		const size_type	new_capacity = check_length(n, "vector::range_insert");
// 		pointer			new_data = allocate_a(new_capacity);
// 		pointer			new_data_end = new_data;
// 		try
// 		{
// 			// build before position
// 			new_data_end = ft::uninitialized_copy_a(this->_data, position.base(), new_data, this->_alloc);
// 			// build range
// 			new_data_end = ft::uninitialized_copy_a(first, last, new_data_end, this->_alloc);
// 			// build after position
// 			new_data_end = ft::uninitialized_copy_a(position.base(), this->_data + this->_size, new_data_end, this->_alloc);
// 		}
// 		catch (...)
// 		{
// 			ft::destroy_a(new_data, new_data_end, this->_alloc);
// 			deallocate_a(new_data, new_capacity);
// 			throw ;
// 		}
// 		// free old memory
// 		clear();
// 		deallocate_a(this->_data, this->_capacity);
// 		// assign new pointers and data
// 		this->capacity = new_capacity;
// 		this->_data = new_data;
// 	}
// 	this->_size += n;
// }

// template <class T, class Alloc>
// template <class InputIterator>
// void	ft::vector<T, Alloc>::insert(iterator position, InputIterator first, InputIterator last)
// {
// 	// disambiguate between a possible fill call
// 	insert_dispatch(position, first, last, typename ft::is_integral<InputIterator>::type());
// }

// template <class T, class Alloc>
// template <typename InputIterator>
// void	ft::vector<T, Alloc>::insert_dispatch(iterator position, InputIterator first, InputIterator last, ft::false_type)
// {
// 	// template argument was an iterator, proceed
// 	range_insert(position, first, last, typename ft::iterator_traits<InputIterator>::iterator_category());
// }

// template <class T, class Alloc>
// template <typename Integral>
// void	ft::vector<T, Alloc>::insert_dispatch(iterator position, Integral n, Integral val, ft::true_type)
// {
// 	// template argument was an integer, do fill_insert() instead
// 	fill_insert(position, n, val);
// }

// template <class T, class Alloc>
// template <class InputIterator>
// void	ft::vector<T, Alloc>::assign(InputIterator first, InputIterator last)
// {
// 	assign_dispatch(first, last, typename ft::is_integral<InputIterator>::type());
// }

// template <class T, class Alloc>
// template <typename InputIterator>
// void	ft::vector<T, Alloc>::assign_dispatch(InputIterator first, InputIterator last, ft::false_type)
// {
// 	// template argument was an iterator, proceed
// 	range_assign(first, last, typename ft::iterator_traits<InputIterator>::iterator_category());
// }

// template <class T, class Alloc>
// template <typename Integral>
// void	ft::vector<T, Alloc>::assign_dispatch(Integral n, Integral val, ft::true_type)
// {
// 	// template argument was an integer, do fill_assign() instead
// 	fill_assign(n, val);
// }

// template <class T, class Alloc>
// void	ft::vector<T, Alloc>::assign(size_type n, const value_type &val)
// {
// 	fill_assign(n, val);
// }

// template <class T, class Alloc>
// void	ft::vector<T, Alloc>::fill_assign(size_type n, const value_type &val)
// {
// 	// reallocation required
// 	if (n > this->_capacity)
// 	{
// 		vector	temp(n, val, this->_alloc);
// 		temp.swap(*this);
// 	}
// 	else if (n > this->_size)
// 	{
// 		ft::fill(begin(), end(), val);
// 		ft::uninitialized_fill_n_a(this->_data + this->_size, n - this->_size, val, this->_alloc);
// 	}
// 	else
// 		ft::destroy_a(ft::fill_n(this->_data, n, val), this->_data + this->_size, this->_alloc);
// 	this->_size = n;
// }

// template <class T, class Alloc>
// template <typename InputIterator>
// void	ft::vector<T, Alloc>::range_assign(InputIterator first, InputIterator last, std::input_iterator_tag)
// {
// 	pointer		curr = this->_data;
// 	// copy starting from the beginning
// 	for (; first != last && curr != this->_data + this->_size; ++curr, ++first)
// 		*curr = *first;
// 	// if range is shorter than the vector
// 	if (first == last)
// 	{
// 		// destroy the end
// 		ft::destroy_a(curr, this->_data + this->_size);
// 		// update the size
// 		this->_size = curr - this->_data;
// 	}
// 	else
// 		insert(end(), first, last);
// }

// template <class T, class Alloc>
// template <typename ForwardIterator>
// void	ft::vector<T, Alloc>::range_assign(ForwardIterator first, ForwardIterator last, std::forward_iterator_tag)
// {
// 	const size_type	len = ft::distance(first, last);
// 	if (len > this->_capacity)
// 	{
// 		pointer	temp = allocate_and_copy(len, first, last);
// 		clear();
// 		deallocate_a(this->_data, this->_capacity);
// 		this->_data = temp;
// 		this->_capacity = len;
// 	}
// 	// copy and discard the rest
// 	else if (this->_size >= len)
// 		ft::destroy_a(ft::copy(first, last, this->_data), this->_data + this->_size, this->_alloc);
// 	else
// 	{
// 		ForwardIterator	mid = first;
// 		ft::advance(mid, this->_size);
// 		// copy upper part
// 		ft::copy(first, mid, this->_data);
// 		// construct lower part
// 		ft::uninitialized_copy_a(mid, last, this->_data + this->_size, this->_alloc);
// 	}
// 	this->_size = len;
// }

template <class T, class Alloc>
typename ft::vector<T, Alloc>::iterator	ft::vector<T, Alloc>::erase(iterator position)
{
	// if it's not the last element, then do shifting to left
	if (position + 1 != end())
		ft::copy(position + 1, end(), position);
	this->_size--;
	// destroy the extra element at the end
	this->_alloc.destroy(this->_data + this->_size);
	return (position);
}

template <class T, class Alloc>
typename ft::vector<T, Alloc>::iterator	ft::vector<T, Alloc>::erase(iterator first, iterator last)
{
	// if last is the end then no point to shift
	if (last != end())
		ft::copy(last, end(), first);
	// destroy the rest
	ft::destroy_a(first.base() + (end() - last), this->_data + this->_size, this->_alloc);
	this->_size -= last - first;
	return (first);
}

// template <class T, class Alloc>
// void	ft::vector<T, Alloc>::swap(vector &x)
// {
// 	ft::swap(this->_data, x._data);
// 	ft::swap(this->_capacity, x._capacity);
// 	ft::swap(this->_size, x._size);
// }

template <class T, class Alloc>
void	ft::vector<T, Alloc>::clear()
{
	erase(begin(), end());
}

// template <class T, class Alloc>
// typename ft::vector<T, Alloc>::allocator_type	ft::vector<T, Alloc>::get_allocator() const
// {
// 	return (this->_alloc);
// }

// template <class T, class Alloc>
// typename ft::vector<T, Alloc>::pointer	ft::vector<T, Alloc>::allocate_a(size_type n)
// {
// 	return (n ? this->_alloc.allocate(n) : pointer());
// }

template <class T, class Alloc>
void	ft::vector<T, Alloc>::deallocate_a(pointer p, size_type n)
{
	if (p)
		this->_alloc.deallocate(p, n);
}

// template <class T, class Alloc>
// template <typename ForwardIterator>
// typename ft::vector<T, Alloc>::pointer	ft::vector<T, Alloc>::allocate_and_copy(size_type n, ForwardIterator first, ForwardIterator last)
// {
// 	pointer	result = allocate_a(n);
// 	try
// 	{
// 		ft::uninitialized_copy_a(first, last, result, this->_alloc);
// 		return (result);
// 	}
// 	catch (...)
// 	{
// 		deallocate_a(result, n);
// 		throw ;
// 	}
// }

// template <class T, class Alloc>
// typename ft::vector<T, Alloc>::size_type	ft::vector<T, Alloc>::check_length(size_type n, const char *s)
// {
// 	// the insertion will inevitably lead to running out of memory
// 	if (this->max_size() - this->_size < n)
// 		throw std::length_error(s);
// 	// either expand twice, or fit
// 	const size_type	new_size = this->_size + ft::max(this->_size, n);
// 	// in case if an overflow occured, or the doubling exceeds the max size, shrink to fit
// 	return ((new_size < this->_size || new_size > this->max_size()) ? this->max_size() : new_size);
// }

// template <class T, class Alloc>
// bool operator==(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs)
// {
// 	return (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
// }

// template <class T, class Alloc>
// bool operator!=(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs)
// {
// 	return (!(lhs == rhs));
// }

// template <class T, class Alloc>
// bool operator<(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs)
// {
// 	return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
// }

// template <class T, class Alloc>
// bool operator<=(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs)
// {
// 	return (!(rhs < lhs));
// }

// template <class T, class Alloc>
// bool operator>(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs)
// {
// 	return (rhs < lhs);
// }

// template <class T, class Alloc>
// bool operator>=(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs)
// {
// 	return (!(lhs < rhs));
// }

// template <class T, class Alloc>
// void ft::swap(vector<T, Alloc> &x, vector<T, Alloc> &y)
// {
// 	x.swap(y);
// }

#endif
