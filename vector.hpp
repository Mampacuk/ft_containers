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
# include "memory.hpp"
# include "iterator.hpp"
# include "algorithm.hpp"

namespace ft { template <class T, class Alloc = std::allocator<T> > class vector; }

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
	private:
		template <class value_type>
		class	ptr_iterator : public ft::iterator<ft::random_access_iterator_tag, value_type>
		{
			public:
				friend ft::vector<value_type, allocator_type>;
				ptr_iterator();
				ptr_iterator(const ptr_iterator &copy);
				~ptr_iterator() { }
				ptr_iterator	&operator=(const ptr_iterator &rhs);
				reference		operator*() const;
				ptr_iterator	operator+(difference_type n) const;
				ptr_iterator	&operator++();
				ptr_iterator	operator++(int);
				ptr_iterator	&operator+=(difference_type n);
				ptr_iterator	operator-(difference_type n) const;
				ptr_iterator	&operator--();
				ptr_iterator	operator--(int);
				ptr_iterator	&operator-=(difference_type n);
				pointer			operator->() const;
				reference		operator[](difference_type n) const;
			private:
				ptr_iterator(pointer _ptr);
				pointer			_ptr;
		};
	public:
		typedef ptr_iterator<value_type>					iterator;
		typedef ptr_iterator<const value_type>				const_iterator;
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

// vector::iterator

template <class T, class Alloc>
template <class value_type>
ft::vector<T, Alloc>::ptr_iterator<value_type>::ptr_iterator() {}

template <class T, class Alloc>
template <class value_type>
ft::vector<T, Alloc>::ptr_iterator<value_type>::ptr_iterator(pointer _ptr) : _ptr(_ptr) {}

template <class T, class Alloc>
template <class value_type>
ft::vector<T, Alloc>::ptr_iterator<value_type>::ptr_iterator(const ptr_iterator &copy) : _ptr(copy._ptr) {}

template <class T, class Alloc>
template <class value_type>
ft::vector<T, Alloc>::ptr_iterator<value_type> &ft::vector<T, Alloc>::ptr_iterator<value_type>::operator=(const ptr_iterator &rhs)
{
	this->_ptr = rhs._ptr;
	return (*this);
}

template <class T, class Alloc>
template <class value_type>
typename ft::vector<T, Alloc>::reference ft::vector<T, Alloc>::ptr_iterator<value_type>::operator*() const
{
	return (*this->_ptr);
}

template <class T, class Alloc>
template <class value_type>
ft::vector<T, Alloc>::ptr_iterator<value_type> ft::vector<T, Alloc>::ptr_iterator<value_type>::operator+(difference_type n) const
{
	return (ptr_iterator(this->_ptr + n));
}

template <class T, class Alloc>
template <class value_type>
ft::vector<T, Alloc>::ptr_iterator<value_type> ft::vector<T, Alloc>::ptr_iterator<value_type>::operator-(difference_type n) const
{
	return (ptr_iterator(this->_ptr - n));
}

template <class T, class Alloc>
template <class value_type>
ft::vector<T, Alloc>::ptr_iterator<value_type> &ft::vector<T, Alloc>::ptr_iterator<value_type>::operator++()
{
	this->_ptr++;
	return (*this);
}

template <class T, class Alloc>
template <class value_type>
ft::vector<T, Alloc>::ptr_iterator<value_type> &ft::vector<T, Alloc>::ptr_iterator<value_type>::operator--()
{
	this->_ptr--;
	return (*this);
}

template <class T, class Alloc>
template <class value_type>
ft::vector<T, Alloc>::ptr_iterator<value_type> ft::vector<T, Alloc>::ptr_iterator<value_type>::operator++(int)
{
	ptr_iterator temp = *this;
	this->_ptr++;
	return (temp);
}

template <class T, class Alloc>
template <class value_type>
ft::vector<T, Alloc>::ptr_iterator<value_type> ft::vector<T, Alloc>::ptr_iterator<value_type>::operator--(int)
{
	ptr_iterator temp = *this;
	this->_ptr--;
	return (temp);
}

template <class T, class Alloc>
template <class value_type>
ft::vector<T, Alloc>::ptr_iterator<value_type> &ft::vector<T, Alloc>::ptr_iterator<value_type>::operator+=(difference_type n)
{
	this->_ptr += n;
	return (*this);
}

template <class T, class Alloc>
template <class value_type>
ft::vector<T, Alloc>::ptr_iterator<value_type> &ft::vector<T, Alloc>::ptr_iterator<value_type>::operator-=(difference_type n)
{
	this->_ptr -= n;
	return (*this);
}

template <class T, class Alloc>
template <class value_type>
typename ft::vector<T, Alloc>::pointer ft::vector<T, Alloc>::ptr_iterator<value_type>::operator->() const
{
	return (&this->operator*());
}

template <class T, class Alloc>
template <class value_type>
typename ft::vector<T, Alloc>::reference ft::vector<T, Alloc>::ptr_iterator<value_type>::operator[](difference_type n) const
{
	return (this->_ptr[n]);
}

template <class T, class Alloc>
bool	operator==(const typename ft::vector<T, Alloc>::ptr_iterator &lhs,
                   const typename ft::vector<T, Alloc>::ptr_iterator &rhs)
{
	return (ft::addressof(*lhs) == ft::addressof(*rhs));
}

template <class T, class Alloc>
bool	operator!=(const typename ft::vector<T, Alloc>::ptr_iterator &lhs,
					const typename ft::vector<T, Alloc>::ptr_iterator &rhs)
{
	return (ft::addressof(*lhs) != ft::addressof(*rhs));
}

template <class T, class Alloc>
bool	operator<(const typename ft::vector<T, Alloc>::ptr_iterator &lhs,
					const typename ft::vector<T, Alloc>::ptr_iterator &rhs)
{
	return (ft::addressof(*lhs) < ft::addressof(*rhs));
}

template <class T, class Alloc>
bool	operator<=(const typename ft::vector<T, Alloc>::ptr_iterator &lhs,
					const typename ft::vector<T, Alloc>::ptr_iterator &rhs)
{
	return (ft::addressof(*lhs) <= ft::addressof(*rhs));
}

template <class T, class Alloc>
bool	operator>(const typename ft::vector<T, Alloc>::ptr_iterator &lhs,
					const typename ft::vector<T, Alloc>::ptr_iterator &rhs)
{
	return (ft::addressof(*lhs) > ft::addressof(*rhs));
}

namespace ft {
template <class T, class Alloc>
bool	operator>=(const typename vector<T, Alloc>::ptr_iterator &lhs,
					const typename vector<T, Alloc>::ptr_iterator &rhs)
{
	return (addressof(*lhs) >= addressof(*rhs));
}
}

template <class T, class Alloc>
typename ft::vector<T, Alloc>::ptr_iterator operator+(
			typename ft::vector<T, Alloc>::ptr_iterator::difference_type n,
			const typename ft::vector<T, Alloc>::ptr_iterator &it)
{
	return (it + n);
}

template <class T, class Alloc>
typename ft::vector<T, Alloc>::ptr_iterator::difference_type operator-(
	const typename ft::vector<T, Alloc>::ptr_iterator &lhs,
	const typename ft::vector<T, Alloc>::ptr_iterator &rhs)
{
	return (ft::addressof(*lhs) - ft::addressof(*rhs));
}

// vector

template <class T, class Alloc>
ft::vector<T, Alloc>::vector(const allocator_type &alloc) : _alloc(alloc), _data(NULL), _capacity(0), _size(0) {}

template <class T, class Alloc>
ft::vector<T, Alloc>::~vector()
{
	for (size_type i = this->_size - 1; i >= 0; i--)
		this->_alloc.destroy(this->_data + i);
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
	size_type	i = 0;
	pointer		new_data;
	if (this->_capacity >= n)
		return ;
	new_data = this->_alloc.allocate(n);
	while (i < this->_size)
	{
		this->_alloc.construct(new_data + i, this->_data[i]);
		this->_alloc.destroy(this->_data + i);
		i++;
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
		this->reserve(ft::max(size_type(1), this->_capacity * 2));
	reverse_iterator it = this->rbegin();
	while (it != this->rend() && it.base() - 1 >= position)
	{
		*(it + 1) = *it;
		--it;
	}
	*position = val;
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
