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
# include "algorithm.hpp"
# include "memory.hpp"
# include "type_traits.hpp"

namespace ft
{
	template <typename T>
	size_t	deque_chunk_size()
	{
		return (sizeof(T) < DEQUE_BUF_SIZE ? size_t(DEQUE_BUF_SIZE / sizeof(T)) : size_t(1));
	}

	template <typename T, typename Reference, typename Pointer>
	// template <typename T>
	class	deque_iterator
	{
		private:
			template <typename Val, typename Ref, typename Ptr>
			friend class deque_iterator;
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
			deque_iterator() : _curr(), _first(), _last(), _node() { }

			deque_iterator(element_pointer element, map_pointer node) : _curr(element), _first(*node),
				_last(*node + chunk_size()), _node(node) { }
			
			deque_iterator(const iterator &copy) : _curr(copy._curr), _first(copy._first), _last(copy._last), _node(copy._node) { }

			void	set_node(map_pointer p)
			{
				this->_node = p;
				this->_first = *p;
				this->_last = *p + deque_chunk_size<T>();
			}

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
					it.set_node(it.node + n / deque_chunk_size<T>());
					it._curr = *it._node + (n % deque_chunk_size<T>());
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
					it.set_node(it._node - n / deque_chunk_size<T>());
					it._curr = *it._node + deque_chunk_size<T>() - (n % deque_chunk_size<T>());
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

			template <class T1, class ReferenceL, class ReferenceR, class PointerL, class PointerR>
			friend typename deque_iterator<T1, ReferenceL, PointerL>::difference_type operator-(
				const deque_iterator<T1, ReferenceL, PointerL> &lhs,
				const deque_iterator<T1, ReferenceR, PointerR> &rhs);
	};

	template <class T, class Reference, class Pointer>
	bool	operator!=(const deque_iterator<T, Reference, Pointer> &lhs,
						const deque_iterator<T, Reference, Pointer> &rhs)
	{
		return (!(lhs == rhs));
	}

	template <class T, class ReferenceL, class ReferenceR, class PointerL, class PointerR>
	bool	operator!=(const deque_iterator<T, ReferenceL, PointerL> &lhs,
						const deque_iterator<T, ReferenceR, PointerR> &rhs)
	{
		return (!(lhs == rhs));
	}

	template <class T, class Reference, class Pointer>
	bool	operator<=(const deque_iterator<T, Reference, Pointer> &lhs,
						const deque_iterator<T, Reference, Pointer> &rhs)
	{
		return (!(rhs < lhs));
	}

	template <class T, class ReferenceL, class ReferenceR, class PointerL, class PointerR>
	bool	operator<=(const deque_iterator<T, ReferenceL, PointerL> &lhs,
						const deque_iterator<T, ReferenceR, PointerR> &rhs)
	{
		return (!(rhs < lhs));
	}

	template <class T, class Reference, class Pointer>
	bool	operator>(const deque_iterator<T, Reference, Pointer> &lhs,
						const deque_iterator<T, Reference, Pointer> &rhs)
	{
		return (rhs < lhs);
	}

	template <class T, class ReferenceL, class ReferenceR, class PointerL, class PointerR>
	bool	operator>(const deque_iterator<T, ReferenceL, PointerL> &lhs,
						const deque_iterator<T, ReferenceR, PointerR> &rhs)
	{
		return (rhs < lhs);
	}

	template <class T, class Reference, class Pointer>
	bool	operator>=(const deque_iterator<T, Reference, Pointer> &lhs,
						const deque_iterator<T, Reference, Pointer> &rhs)
	{
		return (!(lhs < rhs));
	}

	template <class T, class ReferenceL, class ReferenceR, class PointerL, class PointerR>
	bool	operator>=(const deque_iterator<T, ReferenceL, PointerL> &lhs,
						const deque_iterator<T, ReferenceR, PointerR> &rhs)
	{
		return (!(lhs < rhs));
	}

	template <class T, class Reference, class Pointer>
	deque_iterator<T, Reference, Pointer>
	operator+(typename deque_iterator<T, Reference, Pointer>::difference_type n,
				const deque_iterator<T, Reference, Pointer> &it)
	{
		return (it + n);
	}

	template <class T, class ReferenceL, class ReferenceR, class PointerL, class PointerR>
	typename deque_iterator<T, ReferenceL, PointerL>::difference_type operator-(
		const deque_iterator<T, ReferenceL, PointerL> &lhs,
		const deque_iterator<T, ReferenceR, PointerR> &rhs)
	{
		if (lhs._node == rhs._node)
			return (lhs._curr - rhs._curr);
		return ((lhs._node - rhs._node - 1) * deque_chunk_size<T>()
			+ (lhs._curr - lhs._first) + (rhs._last - rhs._curr));
	}

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
			typedef typename iterator::map_pointer								map_pointer;
			typedef typename Alloc::template rebind<pointer>::other				map_allocator_type;
		private:
			// private member variables
			iterator		_start;
			iterator		_finish;
			map_pointer		_map;
			size_type		_map_size;
			allocator_type	_alloc;
		
		public:
			explicit deque(const allocator_type &alloc = allocator_type()) : _alloc(alloc)
			{
				create_map(0);
			}

			explicit deque(size_type n, const value_type &val = value_type(), const allocator_type &alloc = allocator_type()) : _alloc(alloc)
			{
				create_map(check_length(n));
				fill_construct(val);
			}

			template <class InputIterator>
			deque(InputIterator first, InputIterator last, const allocator_type &alloc = allocator_type()) : _alloc(alloc)
			{
				constructor_dispatch(first, last, typename ft::is_integral<InputIterator>::type());
			}
		private:
			template <class InputIterator>
			void	constructor_dispatch(InputIterator first, InputIterator last, ft::false_type)
			{
				// template argument was an iterator, proceed
				range_construct(first, last, typename ft::iterator_traits<InputIterator>::iterator_category());
			}

			template <typename Integral>
			void	constructor_dispatch(Integral n, Integral val, ft::true_type)
			{
				create_map(check_length(static_cast<size_type>(n)));
				// template argument was an integer, do fill_construct() instead
				fill_construct(val);
			}

			void	fill_construct(const value_type &val)
			{
				map_pointer	curr;
				try
				{
					// build fully filled chunks
					for (curr = this->_start._node; curr != this->_finish._node; ++curr)
						ft::uninitialized_fill_a(*curr, *curr + deque_chunk_size<T>(), val, this->_alloc);
					// build the last bit which may be smaller than chunk size
					ft::uninitialized_fill_a(this->_finish._first, this->_finish._curr, val, this->_alloc);
				}
				catch (...)
				{
					ft::destroy_a(this->_start, iterator(*curr, curr), this->_alloc);
					throw ;
				}
			}

			template <typename InputIterator>
			void	range_construct(InputIterator first, InputIterator last, std::input_iterator_tag)
			{
				create_map(0);
				try
				{
					for (; first != last; ++first)
						push_back(*first);
				}
				catch (...)
				{
					clear();
					throw ;
				}
			}

			template <typename ForwardIterator>
			void	range_construct(ForwardIterator first, ForwardIterator last, std::forward_iterator_tag)
			{
				size_type	n = ft::distance(first, last);
				create_map(n);
				map_pointer	curr;
				try
				{
					// build fully filled chunks
					for (curr = this->_start._node; curr != this->_finish._node; ++curr)
					{
						ForwardIterator	mid = first;
						ft::advance(mid, deque_chunk_size<T>());
						ft::uninitialized_copy_a(first, mid, *curr, this->_alloc);
						first = mid;
					}
					// build the last bit which may be smaller than chunk size
					ft::uninitialized_copy_a(first, last, this->_finish._first, this->_alloc);
				}
				catch (...)
				{
					ft::destroy_a(this->_start, iterator(*curr, curr), this->_alloc);
					throw ;
				}
			}
		public:
			deque(const deque &x) : _alloc(x._alloc)
			{
				range_construct(x.begin(), x.end(), std::random_access_iterator_tag());
			}

			deque	&operator=(const deque &x)
			{
				if (&x != this)
				{
					const size_type	x_size = x.size();
					const size_type	this_size = this->size();
					// enough elts currently, copy from x to this, and destroy the rest past x's elements
					if (this_size >= x_size)
					{
						iterator new_end = ft::copy(x.begin(), x.end(), begin());	// copy down
						destroy_elements(new_end, end());							// erase the rest
						destroy_nodes(new_end._node + 1, this->_finish._node + 1);	// shrink to fit
						this->_finish = new_end;									// update finish
					}
					else	// not enough elts, reallocation may happen
					{
						ft::copy(x.begin(), x.begin() + difference_type(this_size), begin());
						range_insert(end(), x.begin() + difference_type(this_size), x.end(), std::random_access_iterator_tag);
					}
				}
				return (*this);
			}

			~deque()
			{
				destroy_elements(this->_start, this->_finish);
				destroy_nodes(this->_start._node, this->_finish._node + 1);
				deallocate_map(this->_map, this->_map_size);
			}

			// iterators
			iterator	begin()
			{
				return (this->_start);
			}

			const_iterator	begin() const
			{
				return (const_iterator(this->_start));
			}

			iterator	end()
			{
				return (this->_finish);
			}

			const_iterator	end() const
			{
				return (const_iterator(this->_finish));
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
		private:
			template <class InputIterator>
			void	range_insert(iterator position, InputIterator first, InputIterator last, std::input_iterator_tag)
			{
				for (; first != last; ++first, ++position)
					position = insert(position, *first);
			}

			template <class ForwardIterator>
			void	range_insert(iterator position, ForwardIterator first, ForwardIterator last, std::forward_iterator_tag)
			{
				const size_type n = ft::distance(first, last);
				if (position == begin()) // faster insertion at the front
				{
					iterator	new_start = reserve_elements_at_front(n);
					try
					{
						ft::uninitialized_copy_a(first, last, new_start);
						this->_start = new_start;
					}
					catch (...)
					{
						destroy_nodes(new_start._node, this->_start._node);
						throw ;
					}
				}
				else if (position == end()) // faster insertion at the back
				{
					iterator	new_finish = reserve_elements_at_back(n);
					try
					{
						ft::uninitialized_copy_a(first, last, end());
						this->_finish = new_finish;
					}
					catch (...)
					{
						destroy_nodes(this->_finish._node + 1, new_finish._node + 1);
						throw ;
					}
				}
				else // slow insertion in the middle
					insert_aux(position, first, last, n);
			}

			template <typename ForwardIterator>
			void	insert_aux(iterator position, ForwardIterator first, ForwardIterator last, size_type n)
			{
				const difference_type	elems_before = position - this->_start;
				const size_type			length = size();
				// decide whether to displace (push) elements to the front (left) or back (right)
				if (static_cast<size_type>(elems_before) < length / 2)
				{
					iterator	new_start = reserve_elements_at_front(n);
					iterator	old_start = this->_start;
					try
					{
						// 1 uninitialized_copy and 2 copies needed, otherwise if there's more to insert than there
						// was before position, 2 uninitialized_copies and 1 copy needed:
						// first two calls to copying either move existing elements and then the thied one moves from range,
						// or vice versa
						if (elems_before >= difference_type(n))
						{
							iterator	mid = this->_start + n; // from here, second half of existing elements will be copied to the old-start
							ft::uninitialized_copy_a(this->_start, mid, new_start); // first half of existing elements built on raw memory
							this->_start = new_start;
							ft::copy(mid, position, old_start);						// second half of existing elements copied to non-raw memory
							ft::copy(first, last, position - n);					// range is copied to non-raw memory
						}
						else
						{
							iterator		range_begin;
							ForwardIterator	mid = first;
							ft::advance(mid, n - elems_before); // [first, mid) will be built on raw memory
							range_begin = ft::uninitialized_copy_a(this->_start, position, new_start, this->_alloc); // all existing before elements built on raw memory
							ft::uninitialized_copy_a(first, mid, range_begin, this->_alloc);	// first half of range built on raw memory
							this->_start = new_start;
							ft::copy(mid, last, old_start);										// second half of range copied to non-raw memory
						}
					}
					catch (...)
					{
						// free chunks allocated by reserve* functions
						destroy_nodes(new_start._node, this->_start._node);
						throw ;
					}
				}
				else	// symmetric code, but for back
				{
					iterator				new_finish = reserve_elements_at_back(n);
					iterator				old_finish = this->_finish;
					const difference_type	elems_after = difference_type(length) - elems_before;
					try
					{
						if (elems_after > difference_type(n))
						{
							iterator	mid = this->_finish - difference_type(n);
							ft::uninitialized_copy_a(mid, this->_finish, this->_finish, this->_alloc);
							this->_finish = new_finish;
							ft::copy(position, mid, old_finish);
							ft::copy(first, last, position);
						}
						else
						{
							iterator		old_elems_begin;
							ForwardIterator	mid = first;
							ft::advance(mid, elems_after);
							old_elems_begin = ft::uninitialized_copy_a(mid, last, this->_finish, this->_alloc);
							ft::uninitialized_copy_a(position, this->_finish, old_elems_begin, this->_alloc);
							this->_finish = new_finish;
							ft::copy(first, mid, position);
						}
					}
					catch (...)
					{
						destroy_nodes(this->_finish._node + 1, new_finish._node + 1);
						throw ;
					}
				}
			}

			// return correct new start/end. allocates new chunks if there isn't enough available
			iterator	reserve_elements_at_front(size_type n)
			{
				const size_type	free_cells = this->_start._curr - this->_start._first;
				if (n > free_cells)
					new_elements_at_front(n - free_cells);
				return (this->_start - difference_type(n));
			}

			iterator	reserve_elements_at_back(size_type n)
			{
				const size_type	free_cells = this->_finish._last - this->_finish._curr;
				if (n > free_cells)
					new_elements_at_back(n - free_cells);
				return (this->_finish + difference_type(n));
			}

			// allocates new chunks, if needed also allocates new pointers for the map
			void	new_elements_at_front(size_type n)
			{
				check_length(size() + n);
				const size_type	new_nodes = (n + deque_chunk_size<T>() - 1) / deque_chunk_size<T>();
				reserve_map_at_front(new_nodes);
				size_type	i;
				try
				{
					for (i = 1; i <= new_nodes; i++)	// allocate nodes, assign pointers
						*(this->_start._node - i) = allocate_node();
				}
				catch (...)
				{
					for (size_type j = 1; j < i; j++)
						deallocate_node(*(this->_start._node - j));
					throw ;
				}
			}

			void	new_elements_at_back(size_type n)
			{
				check_length(size() + n);
				const size_type	new_nodes = (n + deque_chunk_size<T>() - 1) / deque_chunk_size<T>();
				reserve_map_at_back(new_nodes);
				size_type	i;
				try
				{
					for (i = 1; i <= new_nodes; i++)	// allocate nodes, assign pointers
						*(this->_finish._node + i) = allocate_node();
				}
				catch (...)
				{
					for (size_type j = 1; j < i; j++)
						deallocate_node(*(this->_finish._node + j));
					throw ;
				}
			}

			// check if room has to be made for new chunk pointers
			void	reserve_map_at_front(size_type nodes_to_add = 1)
			{
				if (nodes_to_add > size_type(this->_start._node - this->_map))
					reallocate_map(nodes_to_add, true);
			}

			void	reserve_map_at_back(size_type nodes_to_add = 1)
			{
				if (nodes_to_add > size_type(this->_map_size - (this->_finish._node - this->_map) - 1))
					reallocate_map(nodes_to_add, false);
			}

			// allocates only pointers; doesn't allocate chunks. allocates new, bigger map if necessary
			void	reallocate_map(size_type nodes_to_add, bool add_at_front)
			{
				const size_type old_num_nodes = this->_finish._node - this->_start._node + 1;
				const size_type	new_num_nodes = old_num_nodes + nodes_to_add;
				map_pointer		new_start;
				
				if (this->_map_size > 2 * new_num_nodes) // there should be twice the nodes required to amortize
				{
					// move pointers to the middle of the map (if adding at front, skip over the nodes that will be allocated)
					new_start = this->_map + (this->_map_size - new_num_nodes) / 2 + (add_at_front ? nodes_to_add : 0);
					if (new_start < this->_start._node) // move pointers
						ft::copy(this->_start._node, this->_finish._node + 1, new_start);
					else
						ft::copy_backward(this->_start._node, this->_finish._node + 1, new_start + old_num_nodes);
				}
				else									// otherwise reallocate and relocate
				{
					const size_type	new_map_size = this->_map_size + ft::max(this->_map_size, nodes_to_add) + 2;
					map_pointer		new_map = allocate_map(new_map_size);
					new_start = new_map + (new_map_size - new_num_nodes) / 2 + (add_at_front ? nodes_to_add : 0);
					ft::copy(this->_start._node, this->_finish._node + 1, new_start);
					deallocate_map(this->_map, this->_map_size);
					this->_map = new_map;
					this->_map_size = new_map_size;
				}
				this->_start.set_node(new_start);
				this->_start.set_node(new_start + old_num_nodes - 1);
			}

			void	create_map(size_type num_elts)
			{
				const size_type	num_nodes = num_elts / deque_chunk_size<T>() + 1;

				this->_map_size = ft::max(8, num_nodes + 2);
				this->_map = allocate_map(this->_map_size);

				map_pointer	map_start = this->_map + (this->_map_size - num_nodes) / 2;
				map_pointer	map_finish = map_start + num_nodes;

				try
				{
					create_nodes(map_start, map_finish);
				}
				catch (...)
				{
					deallocate_map(this->_map, this->_map_size);
					this->_map = map_pointer();
					this->_map_size = 0;
					throw ;
				}

				this->_start.set_node(map_start);
				this->_finish.set_node(map_finish - 1);
				this->_start._curr = this->_start._first;
				this->_finish._curr = this->_finish._first + num_elts % deque_chunk_size<T>();
			}

			void	create_nodes(map_pointer map_start, map_pointer map_finish)
			{
				map_pointer	curr;
				try
				{
					for (curr = map_start; curr != map_finish; ++curr)
						*curr = allocate_node();
				}
				catch (...)
				{
					destroy_nodes(map_start, curr);
					throw ;
				}
			}
		public:
			// capacity
			size_type	size() const
			{
				return (this->_finish - this->_start);
			}

			size_type	max_size() const
			{
				return (this->_alloc.max_size());
			}

			void	resize(size_type n, value_type val = value_type())
			{
				if (n > this->_size)
					insert(end(), n - this->_size, val);
				else if (n < this->_size)
					erase(end() - (this->_size - n), end());
			}

			bool	empty() const
			{
				return (this->_finish == this->_start);
			}

			// element access
			reference	operator[](size_type n)
			{
				return (this->_start[n]);
			}

			const_reference	operator[](size_type n) const
			{
				return (this->_start[n]);
			}

			reference	at(size_type n)
			{
				const size_type	this_size = size();
				if (n >= this_size)
					throw std::out_of_range("deque::at: n (which is " + SSTR(n) + ") >= this->size() (which is " + SSTR(this_size) + ")");
				return (this->_start[n]);
			}

			const_reference	at(size_type n) const
			{
				const size_type	this_size = size();
				if (n >= this_size)
					throw std::out_of_range("deque::at: n (which is " + SSTR(n) + ") >= this->size() (which is " + SSTR(this_size) + ")");
				return (this->_start[n]);
			}

			reference	front()
			{
				return (this->_start[0]);
			}

			const_reference	front() const
			{
				return (this->_start[0]);
			}

			reference	back()
			{
				return (this->_start[size() - 1]);
			}

			const_reference	back() const
			{
				return (this->_start[size() - 1]);
			}

			allocator_type	get_allocator() const
			{
				return (this->_alloc);
			}
		private:
			map_pointer	allocate_map(size_type n)
			{
				map_allocator_type	map_alloc(this->_alloc);
				return (map_alloc.allocate(n));
			}

			void	deallocate_map(map_pointer p, size_type n)
			{
				map_allocator_type	map_alloc(this->_alloc);
				if (p)
					map_alloc.deallocate(p, n);
			}

			pointer	allocate_node()
			{
				return (this->_alloc.allocate(deque_chunk_size<T>()));
			}

			void	deallocate_node(pointer p)
			{
				if (p)
					this->_alloc.deallocate(p, deque_chunk_size<T>());
			}

			void	destroy_nodes(map_pointer first, map_pointer last)
			{
				for (map_pointer curr = first; curr != last; ++curr)
					deallocate_node(*curr);
			}

			void	destroy_elements(iterator first, iterator last)
			{
				// clear middle chunks that are completely filled
				for (map_pointer node = first._node + 1; node != last._node; ++node)
					ft::destroy_a(*node, *node + deque_chunk_size<T>(), this->_alloc);
				// clear leftovers from left and right
				if (first._node != last._node)
				{
					ft::destroy_a(first._curr, first._last, this->_alloc);
					ft::destroy_a(last._first, last._curr);
				}
				else
					ft::destroy_a(first._curr, last._curr, this->_alloc);
			}

			size_type	check_length(size_type n)
			{
				if (n > ft::min(LLONG_MAX, max_size()))
					throw std::length_error("cannot allocate requested memory");
				return (n);
			}
	};
}

#endif