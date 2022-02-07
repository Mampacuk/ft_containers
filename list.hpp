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

# include "memory.hpp"
# include "iterator.hpp"
# include "algorithm.hpp"
# include "type_traits.hpp"
# include "utility.hpp"
# include "functional.hpp"

namespace ft
{
	// util structures for list
	struct	list_node_base
	{
		list_node_base() : next(), prev() { }
		list_node_base	*next;
		list_node_base	*prev;
	};

	template <class T>
	struct	list_node : public list_node_base
	{
		T	data;
	};

	// list iterators
	template <class T>
	struct	list_iterator
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

		list_iterator	&operator=(const list_iterator &rhs)
		{
			this->_node = rhs._node;
			return (*this);
		}

		reference	operator*() const
		{
			return (static_cast<list_node<T>*>(this->_node)->data);
		}

		list_iterator	&operator++()
		{
			this->_node =  this->_node->next;
			return (*this);
		}

		list_iterator	operator++(int)
		{
			list_iterator	temp(*this);
			this->_node = this->_node->next;
			return (temp);
		}

		list_iterator	&operator--()
		{
			this->_node =  this->_node->prev;
			return (*this);
		}

		list_iterator	operator--(int)
		{
			list_iterator	temp(*this);
			this->_node = this->_node->prev;
			return (temp);
		}

		pointer			operator->() const
		{
			return (addressof(operator*()));
		}
	};

	template <class T>
	bool	operator==(const list_iterator<T> &lhs, const list_iterator<T> &rhs)
	{
		return (lhs._node == rhs._node);
	}

	template <class T>
	bool	operator!=(const list_iterator<T> &lhs, const list_iterator<T> &rhs)
	{
		return (lhs._node != rhs._node);
	}

	template <class T>
	struct	list_const_iterator
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
		list_const_iterator(const list_node_base *_node) : _node(_node) { }
		list_const_iterator(const iterator &copy) : _node(copy._node) { }
		~list_const_iterator() { }
		
		list_const_iterator	&operator=(const list_const_iterator &rhs)
		{
			this->_node = rhs._node;
			return (*this);
		}

		list_const_iterator	&operator++()
		{
			this->_node =  this->_node->next;
			return (*this);
		}

		list_const_iterator	operator++(int)
		{
			list_const_iterator	temp(*this);
			this->_node = this->_node->next;
			return (temp);
		}
		
		list_const_iterator	&operator--()
		{
			this->_node =  this->_node->prev;
			return (*this);
		}

		list_const_iterator	operator--(int)
		{
			list_const_iterator	temp(*this);
			this->_node = this->_node->prev;
			return (temp);
		}

		reference			operator*() const
		{
			return (static_cast<const list_node<T>*>(this->_node)->data);
		}

		pointer				operator->() const
		{
			return (addressof(operator*()));
		}
	};

	template <class T>
	bool	operator==(const list_const_iterator<T> &lhs, const list_const_iterator<T> &rhs)
	{
		return (lhs._node == rhs._node);
	}

	template <class T>
	bool	operator!=(const list_const_iterator<T> &lhs, const list_const_iterator<T> &rhs)
	{
		return (lhs._node != rhs._node);
	}

	template <class T>
	bool	operator!=(const list_iterator<T> &lhs, const list_const_iterator<T> &rhs)
	{
		return (lhs._node != rhs._node);
	}

	template <class T>
	bool	operator!=(const list_const_iterator<T> &lhs, const list_iterator<T> &rhs)
	{
		return (lhs._node != rhs._node);
	}

	template <class T>
	bool	operator==(const list_iterator<T> &lhs, const list_const_iterator<T> &rhs)
	{
		return (lhs._node == rhs._node);
	}

	template <class T>
	bool	operator==(const list_const_iterator<T> &lhs, const list_iterator<T> &rhs)
	{
		return (lhs._node == rhs._node);
	}

	template <class T, class Alloc = std::allocator<T> >
	class	list
	{
		protected:
			typedef list_node<T>									node;
			typedef typename Alloc::template rebind<node>::other	node_allocator_type;
		public:
			// member types
			typedef T													value_type;
			typedef Alloc												allocator_type;
			typedef typename allocator_type::reference					reference;
			typedef typename allocator_type::const_reference			const_reference;
			typedef typename allocator_type::pointer					pointer;
			typedef typename allocator_type::const_pointer				const_pointer;
			typedef list_iterator<value_type>							iterator;
			typedef list_const_iterator<value_type>						const_iterator;
			typedef typename iterator_traits<iterator>::difference_type	difference_type;
			typedef size_t												size_type;
			typedef typename ft::reverse_iterator<iterator>				reverse_iterator;
			typedef typename ft::reverse_iterator<const_iterator>		const_reverse_iterator;
		
		protected:
			node_allocator_type	_alloc;
			list_node_base		_header;
			list_node_base		_trailer;
			size_type			_size;
		
		public:
			// (constructor)
			explicit list(const allocator_type &alloc = allocator_type()) : _alloc(alloc), _header(), _trailer(), _size(0)
			{
				this->_header.next = &this->_trailer;
				this->_trailer.prev = &this->_header;
			}

			explicit list(size_type n, const value_type &val = value_type(),
				const allocator_type &alloc = allocator_type()) : _alloc(alloc), _header(), _trailer(), _size(0)
			{
				this->_header.next = &this->_trailer;
				this->_trailer.prev = &this->_header;
				fill_assign(n, val);
			}

			template <class InputIterator>
			list(InputIterator first, InputIterator last, const allocator_type &alloc = allocator_type()) : _alloc(alloc), _header(), _trailer(), _size(0)
			{
				this->_header.next = &this->_trailer;
				this->_trailer.prev = &this->_header;
				constructor_dispatch(first, last, typename ft::is_integral<InputIterator>::type());
			}

		protected:
			template <class InputIterator>
			void	constructor_dispatch(InputIterator first, InputIterator last, false_type)
			{
				// template argument was an iterator, proceed
				range_assign(first, last);
			}

			template <typename Integral>
			void	constructor_dispatch(Integral n, Integral val, true_type)
			{
				fill_assign(n, val);
			}

		public:
			list(const list &x) : _alloc(x._alloc), _header(), _trailer(), _size(0)
			{
				this->_header.next = &this->_trailer;
				this->_trailer.prev = &this->_header;
				range_assign(x.begin(), x.end());
			}

			list	&operator=(const list& x)
			{
				range_assign(x.begin(), x.end());
				return (*this);
			}

			// (destructor)
			~list()
			{
				clear();
			}

			// iterators
			iterator	begin()
			{
				return (iterator(this->_header.next));
			}

			const_iterator	begin() const
			{
				return (const_iterator(this->_header.next));
			}

			iterator	end()
			{
				return (iterator(&this->_trailer));
			}

			const_iterator	end() const
			{
				return (const_iterator(&this->_trailer));
			}

			reverse_iterator	rbegin()
			{
				return (reverse_iterator(end()));
			}

			const_reverse_iterator	rbegin() const
			{
				return (const_reverse_iterator(end()));
			}

			reverse_iterator	rend()
			{
				return (reverse_iterator(begin()));
			}

			const_reverse_iterator	rend() const
			{
				return (const_reverse_iterator(begin()));
			}

			// capacity
			bool	empty() const
			{
				return (!this->_size);
			}

			size_type	size() const
			{
				return (this->_size);
			}

			size_type	max_size() const
			{
				return (this->_alloc.max_size());
			}

			// element access
			reference	front()
			{
				return (*begin());
			}

			const_reference	front() const
			{
				return (*begin());
			}

			reference	back()
			{
				return (*(--end()));
			}

			const_reference	back() const
			{
				return (*(--end()));
			}

			// modifiers
			void		assign(size_type n, const value_type &val)
			{
				fill_assign(n, val);
			}

			template <class InputIterator>
			void		assign(InputIterator first, InputIterator last)
			{
				assign_dispatch(first, last, typename ft::is_integral<InputIterator>::type());
			}

		protected:
			template <class InputIterator>
			void		assign_dispatch(InputIterator first, InputIterator last, false_type)
			{
				range_assign(first, last);
			}

			template <class Integral>
			void		assign_dispatch(Integral n, Integral val, true_type)
			{
				fill_assign(n, val);
			}

			template <class InputIterator>
			void	range_assign(InputIterator first, InputIterator last)
			{
				iterator	begin = this->begin();
				while (first != last && begin != end())
				{
					*begin = *first;
					first++;
					begin++;
				}
				// if this < than range, insert the rest at the end,
				if (begin == end())
					insert(end(), first, last);
				// else if range is shorter, erase the rest till end
				else
					erase(begin, end());
			}

			void	fill_assign(size_type n, const value_type &val)
			{
				size_type	i = 0;
				iterator	begin = this->begin();
				while (i < n && begin != end())
				{
					*begin = val;
					i++;
					begin++;
				}
				// if this < than range, insert the rest at the end,
				if (begin == end())
					insert(end(), n - i, val);
				// else if range is shorter, erase the rest from end
				else
					erase(begin, end());
			}

		public:
			void	push_front(const value_type &val)
			{
				insert(begin(), val);
			}

			void	pop_front()
			{
				erase(begin());
			}

			void	push_back(const value_type &val)
			{
				insert(end(), val);
			}

			void	pop_back()
			{
				erase(--end());
			}

			iterator	insert(iterator position, const value_type &val)
			{
				put_before(position, val);
				this->_size++;
				return (--position);
			}

			void	insert(iterator position, size_type n, const value_type &val)
			{
				fill_insert(position, n, val);
			}

			template <class InputIterator>
			void	insert(iterator position, InputIterator first, InputIterator last)
			{
				insert_dispatch(position, first, last, typename ft::is_integral<InputIterator>::type());
			}

		protected:
			template <class InputIterator>
			void	insert_dispatch(iterator position, InputIterator first, InputIterator last, false_type)
			{
				range_insert(position, first, last);
			}

			template <class Integral>
			void	insert_dispatch(iterator position, Integral n, Integral val, true_type)
			{
				fill_insert(position, n, val);
			}

			void	fill_insert(iterator position, size_type n, const value_type &val)
			{
				for (size_type i = 0; i < n; i++)
					insert(position, val);
			}

			template <class InputIterator>
			void	range_insert(iterator position, InputIterator first, InputIterator last)
			{
				while (first != last)
				{
					insert(position, *first);
					first++;
				}
			}
		
		public:
			iterator	erase(iterator position)
			{
				return (erase(position, position._node->next));
			}

			iterator	erase(iterator first, iterator last)
			{
				size_type		n = 0;
				list_node_base	*first_prev = first._node->prev;
				list_node_base	*curr = first._node;
				while (curr != last._node)
				{
					curr = destroy_position(curr);
					n++;
				}
				link_nodes(first_prev, last._node);
				this->_size -= n;
				return (last._node);
			}

			void	swap(list &x)
			{
				ft::swap(this->_size, x._size);
				if (!empty() && !x.empty())
				{
					list_node_base	*this_header_next = this->_header.next;
					link_nodes(&this->_header, x._header.next);
					link_nodes(&x._header, this_header_next);
					list_node_base	*this_trailer_prev = this->_trailer.prev;
					link_nodes(x._trailer.prev, &this->_trailer);
					link_nodes(this_trailer_prev, &x._trailer);
				}
				else if (!x.empty())
				{
					link_nodes(&this->_header, x._header.next);
					link_nodes(x._trailer.prev, &this->_trailer);
					link_nodes(&x._header, &x._trailer);
				}
				else if (!empty())
				{
					link_nodes(&x._header, this->_header.next);
					link_nodes(this->_trailer.prev, &x._trailer);
					link_nodes(&this->_header, &this->_trailer);
				}
			}

			void	resize(size_type n, value_type val = value_type())
			{
				if (n > this->_size)
					insert(end(), n - this->_size, val);
				else if (n < this->_size)
				{
					n = this->_size - n;
					for (size_type i = 0; i < n; i++)
						pop_back();
				}
			}

			void	clear()
			{
				while (!empty())
					pop_front();
			}

			// operations
			void	splice(iterator position, list &x)
			{
				this->_size += x._size;
				x._size = 0;
				list_node_base	*first = x.begin()._node;
				list_node_base	*last = x.end()._node;
				list_node_base	*last_prev = last->prev;
				link_nodes(first->prev, last);
				link_nodes(position._node->prev, first);
				link_nodes(last_prev, position._node);
			}

			void	splice(iterator position, list &x, iterator i)
			{
				splice(position, x, i, iterator(i._node->next));
			}

			void	splice(iterator position, list &x, iterator first, iterator last)
			{
				size_type	n = ft::distance(first, last);
				this->_size += n;
				x._size -= n;
				list_node_base	*_first = first._node;
				list_node_base	*_last = last._node;
				list_node_base	*_last_prev = _last->prev;
				link_nodes(_first->prev, _last);
				link_nodes(position._node->prev, _first);
				link_nodes(_last_prev, position._node);
			}

			void	remove(const value_type &val)
			{
				for (iterator it = begin(); it != end(); ++it)
					if (*it == val)
						it = --erase(it);
			}

			template <class Predicate>
			void	remove_if(Predicate pred)
			{
				for (iterator it = begin(); it != end(); ++it)
					if (pred(*it))
						it = --erase(it);
			}

			void	unique()
			{
				unique(ft::equal_to<value_type>());
			}

			template <class BinaryPredicate>
			void	unique(BinaryPredicate binary_pred)
			{
				for (iterator it = begin(); it != --end() && it != end();)
					if (binary_pred(*it, *iterator(it._node->next)))
						it = --erase(++it);
					else
						++it;
			}

			void	merge(list &x)
			{
				merge(x, ft::less<value_type>());
			}

			template <class Compare>
			void	merge(list &x, Compare comp)
			{
				if (&x == this)
					return ;
				iterator	this_it = begin();
				for (iterator x_it = x.begin(); x_it != x.end() && this_it != end();)
				{
					if (comp(*x_it, *this_it))
						splice(this_it, x, x_it++);
					else
						++this_it;
				}
				if (this_it == end())
					splice (this_it, x);
			}

			void	sort()
			{
				sort(ft::less<value_type>());
			}

			template <class Compare>
			void	sort(Compare comp)
			{
				mergesort(*this, comp);
			}

		protected:
			template <class Compare>
			void	mergesort(list &x, Compare comp)
			{
				// base case; trivially sorted
				if (x.size() < 2) return ;
				// split list into two equal parts
				list		left, right;
				iterator	mid = x.begin();
				ft::advance(mid, x.size() / 2);
				right.splice(right.end(), x, mid, x.end());
				left.splice(left.end(), x);
				// recur for each part
				mergesort(left, comp);
				mergesort(right, comp);
				// add elements back and merge
				x.splice(x.end(), left);
				x.merge(right, comp);
			}

		public:
			void	reverse()
			{
				if (this->_size > 1)
				{
					size_type	i = 0;
					iterator	curr = --(--end());
					while (i < this->_size - 1)
					{
						iterator	curr_prev(curr._node->prev);
						splice(end(), *this, curr);
						curr = curr_prev;
						i++;
					}
				}
			}

			// observers
			allocator_type	get_allocator() const
			{
				return (allocator_type(this->_alloc));
			}
		protected:
			list_node_base	*destroy_position(iterator position)
			{
				allocator_type	alloc(this->_alloc);
				list_node_base	*position_next = position._node->next;
				// downcast, so that `data` can be accessed because base has only prev/next pointers
				alloc.destroy(&static_cast<node*>(position._node)->data);
				this->_alloc.deallocate(static_cast<node*>(position._node), 1);
				return (position_next);
			}

			void	put_before(iterator position, const value_type &val)
			{
				node	*new_node = this->_alloc.allocate(1);
				try
				{
					allocator_type	alloc(this->_alloc);
					alloc.construct(&new_node->data, val);
				}
				catch (...)
				{
					this->_alloc.deallocate(new_node, 1);
					throw ;
				}
				link_nodes(position._node->prev, new_node);
				link_nodes(new_node, position._node);
			}

			void	link_nodes(list_node_base *a, list_node_base *b)
			{
				a->next = b;
				b->prev = a;
			}
	};

	template <class T, class Alloc>
	void	swap(list<T, Alloc> &x, list<T, Alloc> &y)
	{
		x.swap(y);
	}

	template <class T, class Alloc>
	bool	operator==(const ft::list<T, Alloc> &lhs, const ft::list<T, Alloc> &rhs)
	{
		return (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template <class T, class Alloc>
	bool	operator!=(const ft::list<T, Alloc> &lhs, const ft::list<T, Alloc> &rhs)
	{
		return (!(lhs == rhs));
	}

	template <class T, class Alloc>
	bool	operator<(const ft::list<T, Alloc> &lhs, const ft::list<T, Alloc> &rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template <class T, class Alloc>
	bool	operator<=(const ft::list<T, Alloc> &lhs, const ft::list<T, Alloc> &rhs)
	{
		return (!(rhs < lhs));
	}

	template <class T, class Alloc>
	bool	operator>(const ft::list<T, Alloc> &lhs, const ft::list<T, Alloc> &rhs)
	{
		return (rhs < lhs);
	}

	template <class T, class Alloc>
	bool	operator>=(const ft::list<T, Alloc> &lhs, const ft::list<T, Alloc> &rhs)
	{
		return (!(lhs < rhs));
	}
}

#endif
