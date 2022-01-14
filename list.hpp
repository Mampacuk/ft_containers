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
# include <iostream>
# include "memory.hpp"
# include "iterator.hpp"
# include <iterator>
# include "algorithm.hpp"
# include "type_traits.hpp"
# include "utility.hpp"

namespace ft
{
	template <class T> class list_iterator;
	template <class T> class list_const_iterator;
	struct list_node_base;
	template <class T> struct list_node;
	template <class T, class Alloc = std::allocator<T> > class list;
	template <class T, class Alloc>
	void	swap(list<T, Alloc> &x, list<T, Alloc> &y);
}

// util structures for list

struct	ft::list_node_base
{
	list_node_base() : next(), prev() { }
	list_node_base(list_node_base *next, list_node_base *prev) : next(next), prev(prev) { }
	list_node_base	*next;
	list_node_base	*prev;
};

template <class T>
struct	ft::list_node : public list_node_base
{
	list_node(list_node_base *next, list_node_base *prev) : list_node_base(next, prev) { }
	list_node(list_node_base *next, list_node_base *prev, const T &data) : list_node_base(next, prev), data(data) { }
	list_node(const T &data) : data(data) { }
	T	data;
};

// list iterators

template <class T>
struct	ft::list_iterator
{
	// member variables
	list_node_base							*_node;
	// member types
	typedef T								value_type;
	typedef ptrdiff_t						difference_type;
	typedef T&								reference;
	typedef T*								pointer;
	typedef std::bidirectional_iterator_tag	iterator_category;
	
	list_iterator() : _node() { }
	list_iterator(list_node_base *_node) : _node(_node) { }
	list_iterator(const list_iterator &copy) : _node(copy._node) { }
	~list_iterator() { }
	list_iterator	&operator=(const list_iterator &rhs);
	reference		operator*() const;
	list_iterator	&operator++();
	list_iterator	operator++(int);
	list_iterator	&operator--();
	list_iterator	operator--(int);
	pointer			operator->() const;
	friend bool		operator==(const list_iterator &lhs, const list_iterator &rhs) { return (lhs._node == rhs._node); }
	friend bool		operator!=(const list_iterator &lhs, const list_iterator &rhs) { return (lhs._node != rhs._node); }
};

template <class T>
ft::list_iterator<T>	&ft::list_iterator<T>::operator=(const list_iterator &rhs)
{
	this->_node = rhs._node;
	return (*this);
}

template <class T>
typename ft::list_iterator<T>::reference	ft::list_iterator<T>::operator*() const
{
	return (static_cast<list_node<T>*>(this->_node)->data);
}

template <class T>
ft::list_iterator<T>	&ft::list_iterator<T>::operator++()
{
	this->_node =  this->_node->next;
	return (*this);
}

template <class T>
ft::list_iterator<T>	&ft::list_iterator<T>::operator--()
{
	this->_node =  this->_node->prev;
	return (*this);
}

template <class T>
ft::list_iterator<T>	ft::list_iterator<T>::operator++(int)
{
	list_iterator	temp(*this);
	this->_node = this->_node->next;
	return (temp);
}

template <class T>
ft::list_iterator<T>	ft::list_iterator<T>::operator--(int)
{
	list_iterator	temp(*this);
	this->_node = this->_node->prev;
	return (temp);
}

template <class T>
typename ft::list_iterator<T>::pointer	ft::list_iterator<T>::operator->() const
{
	return (&this->operator*());
}

template <class T>
class	ft::list_const_iterator
{
	// member variables
	const list_node_base					*_node;
	// member types
	typedef list_iterator<T>				iterator;
	typedef T								value_type;
	typedef ptrdiff_t						difference_type;
	typedef const T&						reference;
	typedef const T*						pointer;
	typedef std::bidirectional_iterator_tag	iterator_category;
	
	list_const_iterator() : _node() { }
	list_const_iterator(list_node_base *_node) : _node(_node) { }
	list_const_iterator(const iterator &copy) : _node(copy._node) { }
	~list_const_iterator() { }
	list_const_iterator	&operator=(const list_const_iterator &rhs);
	list_const_iterator	&operator++();
	list_const_iterator	operator++(int);
	list_const_iterator	&operator--();
	list_const_iterator	operator--(int);
	reference			operator*() const;
	pointer				operator->() const;
	friend bool			operator==(const list_const_iterator &lhs, const list_const_iterator &rhs) { return (lhs._node == rhs._node); }
	friend bool			operator!=(const list_const_iterator &lhs, const list_const_iterator &rhs) { return (lhs._node != rhs._node); }
};

template <class T>
ft::list_const_iterator<T>	&ft::list_const_iterator<T>::operator=(const list_const_iterator &rhs)
{
	this->_node = rhs._node;
	return (*this);
}

template <class T>
typename ft::list_const_iterator<T>::reference	ft::list_const_iterator<T>::operator*() const
{
	return (static_cast<list_node<T>*>(this->_node)->data);
}

template <class T>
ft::list_const_iterator<T>	&ft::list_const_iterator<T>::operator++()
{
	this->_node =  this->_node->next;
	return (*this);
}

template <class T>
ft::list_const_iterator<T>	&ft::list_const_iterator<T>::operator--()
{
	this->_node =  this->_node->prev;
	return (*this);
}

template <class T>
ft::list_const_iterator<T>	ft::list_const_iterator<T>::operator++(int)
{
	list_const_iterator	temp(*this);
	this->_node = this->_node->next;
	return (temp);
}

template <class T>
ft::list_const_iterator<T>	ft::list_const_iterator<T>::operator--(int)
{
	list_const_iterator	temp(*this);
	this->_node = this->_node->prev;
	return (temp);
}

template <class T>
typename ft::list_const_iterator<T>::pointer	ft::list_const_iterator<T>::operator->() const
{
	return (&this->operator*());
}

template <class T, class Alloc>
class	ft::list
{
	protected:
		typedef list_node<T>									node;
		typedef typename Alloc::template rebind<node>::other	node_allocator_type;
	public:
		// member types
		typedef T												value_type;
		typedef Alloc											allocator_type;
		typedef typename allocator_type::reference				reference;
		typedef typename allocator_type::const_reference		const_reference;
		typedef typename allocator_type::pointer				pointer;
		typedef typename allocator_type::const_pointer			const_pointer;
		typedef ft::list_iterator<value_type>					iterator;
		typedef ft::list_const_iterator<value_type>				const_iterator;
		typedef typename ft::iterator_traits<iterator>::difference_type	difference_type;
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
	private:
		void			put_before(iterator position, const value_type &val = value_type());
		void			remove_node(iterator position);
		list_node_base	*destroy_position(iterator position);
		void			link_nodes(list_node_base *a, list_node_base *b);
	private:
		node_allocator_type	_alloc;
		list_node_base		_header;
		list_node_base		_trailer;
		size_type			_size;
};

template <class T, class Alloc>
ft::list<T, Alloc>::list(const allocator_type &alloc) : _alloc(alloc), _header(), _trailer(), _size(0)
{
	this->_header.next = &this->_trailer;
	this->_trailer.prev = &this->_header;
}

template <class T, class Alloc>
typename ft::list<T, Alloc>::list &ft::list<T, Alloc>::operator=(const list &x)
{
	this->assign(x.begin(), x.end());
	return (*this);
}

template <class T, class Alloc>
ft::list<T, Alloc>::~list()
{
	this->clear();
}

template <class T, class Alloc>
typename ft::list<T, Alloc>::iterator ft::list<T, Alloc>::begin()
{
	return (iterator(this->_header.next));
}

template <class T, class Alloc>
typename ft::list<T, Alloc>::const_iterator ft::list<T, Alloc>::begin() const
{
	return (const_iterator(this->_header.next));
}

template <class T, class Alloc>
typename ft::list<T, Alloc>::iterator ft::list<T, Alloc>::end()
{
	return (iterator(&this->_trailer));
}

template <class T, class Alloc>
typename ft::list<T, Alloc>::const_iterator ft::list<T, Alloc>::end() const
{
	return (const_iterator(&this->_trailer));
}

template <class T, class Alloc>
typename ft::list<T, Alloc>::reverse_iterator ft::list<T, Alloc>::rbegin()
{
	return (reverse_iterator(this->end()));
}

template <class T, class Alloc>
typename ft::list<T, Alloc>::const_reverse_iterator ft::list<T, Alloc>::rbegin() const
{
	return (const_reverse_iterator(this->end()));
}

template <class T, class Alloc>
typename ft::list<T, Alloc>::reverse_iterator ft::list<T, Alloc>::rend()
{
	return (reverse_iterator(this->begin()));
}

template <class T, class Alloc>
typename ft::list<T, Alloc>::const_reverse_iterator ft::list<T, Alloc>::rend() const
{
	return (const_reverse_iterator(this->begin()));
}

template <class T, class Alloc>
bool	ft::list<T, Alloc>::empty() const
{
	return (!this->_size);
}

template <class T, class Alloc>
typename ft::list<T, Alloc>::size_type ft::list<T, Alloc>::size() const
{
	return (this->_size);
}

template <class T, class Alloc>
typename ft::list<T, Alloc>::size_type ft::list<T, Alloc>::max_size() const
{
	return (this->_alloc.max_size());
}

template <class T, class Alloc>
typename ft::list<T, Alloc>::reference	ft::list<T, Alloc>::front()
{
	return (*this->begin());
}

template <class T, class Alloc>
typename ft::list<T, Alloc>::const_reference	ft::list<T, Alloc>::front() const
{
	return (*this->begin());
}

template <class T, class Alloc>
typename ft::list<T, Alloc>::reference	ft::list<T, Alloc>::back()
{
	return (*(--this->end()));
}

template <class T, class Alloc>
typename ft::list<T, Alloc>::const_reference	ft::list<T, Alloc>::back() const
{
	return (*(--this->end()));
}

template <class T, class Alloc>
template <class InputIterator>
void	ft::list<T, Alloc>::assign(typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first, InputIterator last)
{
	iterator	begin = this->begin();
	while (first != last && begin != this->end())
	{
		*begin = *first;
		first++;
		begin++;
	}
	// if this < than range, insert the rest at the end,
	if (begin == this->end())
		this->insert(this->end(), first, last);
	// else if range is shorter, erase the rest from end
	else
		this->erase(begin, this->end());
}

template <class T, class Alloc>
void	ft::list<T, Alloc>::assign(size_type n, const value_type &val)
{
	size_type	i = 0;
	iterator	begin = this->begin();
	while (i < n && begin != this->end())
	{
		*begin = val;
		i++;
		begin++;
	}
	// if this < than range, insert the rest at the end,
	if (begin == this->end())
		this->insert(this->end(), n - i, val);
	// else if range is shorter, erase the rest from end
	else
		this->erase(begin, this->end());
}

template <class T, class Alloc>
void	ft::list<T, Alloc>::push_front(const value_type &val)
{
	this->insert(this->begin(), val);
}

template <class T, class Alloc>
void	ft::list<T, Alloc>::pop_front()
{
	this->erase(this->begin());
}

template <class T, class Alloc>
void	ft::list<T, Alloc>::push_back(const value_type &val)
{
	this->insert(this->end(), val);
}

template <class T, class Alloc>
void	ft::list<T, Alloc>::pop_back()
{
	this->erase(--this->end());
}

template <class T, class Alloc>
typename ft::list<T, Alloc>::iterator	ft::list<T, Alloc>::insert(iterator position, const value_type &val)
{
	this->put_before(position, val);
	this->_size++;
	return (--position);
}

template <class T, class Alloc>
void	ft::list<T, Alloc>::insert(iterator position, size_type n, const value_type &val)
{
	for (size_type i = 0; i < n; i++)
		this->insert(position, val);
}

template <class T, class Alloc>
template <class InputIterator>
void	ft::list<T, Alloc>::insert(iterator position,
	typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first,
	InputIterator last)
{
	while (first != last)
	{
		this->insert(position, *first);
		first++;
	}
}

template <class T, class Alloc>
typename ft::list<T, Alloc>::iterator	ft::list<T, Alloc>::erase(iterator position)
{
	return (this->erase(position, position._node->next));
}

template <class T, class Alloc>
typename ft::list<T, Alloc>::iterator	ft::list<T, Alloc>::erase(iterator first, iterator last)
{
	size_type		n = 0;
	list_node_base	*first_prev = first._node->prev;
	list_node_base	*curr = first._node;
	while (curr != last._node)
	{
		curr = this->destroy_position(curr);
		n++;
	}
	this->link_nodes(first_prev, last._node);
	this->_size -= n;
	return (last._node);
}

template <class T, class Alloc>
void	ft::list<T, Alloc>::swap(list &x)
{
	size_type	temp_size = this->_size;
	this->_size = x._size;
	x._size = temp_size;

	if (!this->empty() && !x.empty())
	{
		list_node_base	*this_header_next = this->_header.next;
		this->link_nodes(&this->_header, x._header.next);
		this->link_nodes(&x._header, this_header_next);

		list_node_base	*this_trailer_prev = this->_trailer.prev;
		this->link_nodes(x._trailer.prev, &this->_trailer);
		this->link_nodes(this_trailer_prev, &x._trailer);
	}
	else if (!x->empty())
	{
		this->link_nodes(&this->_header, x._header.next);
		this->link_nodes(x._trailer.prev, &this->_trailer);
		this->link_nodes(&x._header, &x._trailer);
	}
	else if (!this->empty())
	{
		this->link_nodes(&x._header, this->_header.next);
		this->link_nodes(this->_trailer.prev, &x._trailer);
		this->link_nodes(&this->_header, &this->_trailer);
	}
}

template <class T, class Alloc>
void	ft::list<T, Alloc>::resize(size_type n, value_type val)
{
	if (n > this->_size)
		this->insert(this->end(), n - this->_size, val);
	else if (n < this->_size)
	{
		n = this->_size - n;
		for (size_type i = 0; i < n; i++)
			this->pop_back();
	}
}

template <class T, class Alloc>
void	ft::list<T, Alloc>::clear()
{
	while (!this->empty())
		this->pop_front();
}

template <class T, class Alloc>
void	ft::list<T, Alloc>::splice(iterator position, list &x)
{
	this->
}

template <class T, class Alloc>
void	ft::list<T, Alloc>::remove_node(iterator position)
{
	this->link_nodes(position._node->prev, position._node->next);
	this->destroy_position(position);
}

template <class T, class Alloc>
ft::list_node_base	*ft::list<T, Alloc>::destroy_position(iterator position)
{
	allocator_type	alloc(this->_alloc);
	list_node_base	*position_next = position._node->next;
	// downcast, so that `data` can be accessed because base has only prev/next pointers
	alloc.destroy(&static_cast<node*>(position._node)->data);
	this->_alloc.deallocate(static_cast<node*>(position._node), 1);
	return (position_next);
}

template <class T, class Alloc>
void	ft::list<T, Alloc>::put_before(iterator position, const value_type &val)
{
	node			*new_node = this->_alloc.allocate(1);
	try
	{
		allocator_type	alloc(this->_alloc);
		alloc.construct(&new_node->data, val);
	}
	catch (std::exception &e)
	{
		this->_alloc.deallocate(new_node, 1);
		throw ;
	}
	this->link_nodes(position._node->prev, new_node);
	this->link_nodes(new_node, position._node);
}

template <class T, class Alloc>
void	ft::list<T, Alloc>::link_nodes(list_node_base *a, list_node_base *b)
{
	a->next = b;
	b->prev = a;
}

#endif
