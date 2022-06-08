/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aisraely <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 14:33:26 by aisraely          #+#    #+#             */
/*   Updated: 2021/12/29 14:33:26 by aisraely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SET_HPP
# define SET_HPP

# include "utility.hpp"
# include "rbtree.hpp"

namespace ft
{
	template <class T,					// set::key_type/value_type
		class Compare = less<T>,		// set::key_compare/value_compare
		class Alloc = std::allocator<T>	// set::allocator_type
		>
	class set
	{
		public:
			typedef T			key_type;
			typedef T			value_type;
			typedef Compare		key_compare;
			typedef Compare		value_compare;
			typedef Alloc		allocator_type;
		private:
			typedef typename Alloc::template rebind<key_type>::other	key_allocator_type;
			typedef rbtree<key_type, value_type, identity<value_type>,
				false, key_compare, key_allocator_type>	tree;
		public:
			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;
			typedef typename tree::const_iterator				iterator;
			typedef typename tree::const_iterator				const_iterator;
			typedef typename tree::const_reverse_iterator		reverse_iterator;
			typedef typename tree::const_reverse_iterator		const_reverse_iterator;
			typedef ptrdiff_t									difference_type;
			typedef size_t										size_type;

		public:
			// (constructor)
			explicit set(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type()) : _tree(comp, alloc) { }

			template <class InputIterator>
			set(InputIterator first, InputIterator last,
				const key_compare &comp = key_compare(),
				const allocator_type &alloc = allocator_type()) : _tree(first, last, comp, alloc) { }

			set(const set &x) : _tree(x._tree) { }

			// (destructor)
			~set() { }

			set	&operator=(const set &x)
			{
				this->_tree = x._tree;
				return (*this);
			}

			// iterators
			iterator	begin()
			{
				return (this->_tree.begin());
			}

			const_iterator	begin() const
			{
				return (this->_tree.begin());
			}

			iterator	end()
			{
				return (this->_tree.end());
			}

			const_iterator	end() const
			{
				return (this->_tree.end());
			}

			reverse_iterator	rbegin()
			{
				return (this->_tree.rbegin());
			}

			const_reverse_iterator	rbegin() const
			{
				return (this->_tree.rbegin());
			}

			reverse_iterator	rend()
			{
				return (this->_tree.rend());
			}

			const_reverse_iterator	rend() const
			{
				return (this->_tree.rend());
			}

			// capacity
			bool	empty() const
			{
				return (this->_tree.empty());
			}

			size_type	size() const
			{
				return (this->_tree.size());
			}

			size_type	max_size() const
			{
				return (this->_tree.max_size());
			}

			// modifiers
			pair<iterator, bool>	insert(const value_type &val)
			{
				return (this->_tree.insert(val));
			}

			iterator	insert(iterator position, const value_type &val)
			{
				return (this->_tree.insert(position, val));
			}

			template <class InputIterator>
			void	insert(InputIterator first, InputIterator last)
			{
				this->_tree.insert(first, last);
			}

			void	erase(iterator position)
			{
				this->_tree.erase(position);
			}

			size_type	erase(const key_type &k)
			{
				return (this->_tree.erase(k));
			}

			void	erase(iterator first, iterator last)
			{
				this->_tree.erase(first, last);
			}

			void	swap(set &x)
			{
				this->_tree.swap(x._tree);
			}

			void	clear()
			{
				this->_tree.clear();
			}

			key_compare	key_comp() const
			{
				return (this->_tree.key_comp());
			}

			value_compare	value_comp() const
			{
				return (this->_tree.key_comp());
			}

			iterator	find(const key_type &k)
			{
				return (this->_tree.find(k));
			}

			const_iterator	find(const key_type &k) const
			{
				return (this->_tree.find(k));
			}

			size_type	count(const key_type &k) const
			{
				return (this->_tree.count(k));
			}

			iterator	lower_bound(const key_type &k)
			{
				return (this->_tree.lower_bound(k));
			}

			const_iterator	lower_bound(const key_type &k) const
			{
				return (this->_tree.lower_bound(k));
			}

			iterator	upper_bound(const key_type &k)
			{
				return (this->_tree.upper_bound(k));
			}

			const_iterator	upper_bound(const key_type &k) const
			{
				return (this->_tree.upper_bound(k));
			}

			pair<const_iterator, const_iterator>	equal_range(const key_type &k) const
			{
				return (this->_tree.equal_range(k));
			}

			pair<iterator, iterator>	equal_range(const key_type &k)
			{
				return (this->_tree.equal_range(k));
			}

			allocator_type	get_allocator() const
			{
				return (this->_tree.get_allocator());
			}

			tree	&get_tree()
			{
				return (this->_tree);
			}
		private:
			tree	_tree;
		private:
			template <class T1, class Compare1, class Alloc1>
			friend bool operator<(const set<T1, Compare1, Alloc1>&, const set<T1, Compare1, Alloc1>&);
			template <class T1, class Compare1, class Alloc1>
			friend bool operator==(const set<T1, Compare1, Alloc1>&, const set<T1, Compare1, Alloc1>&);
	};

	template <class T, class Compare, class Alloc>
	void	swap(const set<T, Compare, Alloc> &x, const set<T, Compare, Alloc> &y)
	{
		x.swap(y);
	}

	template <class T, class Compare, class Alloc>
	bool operator==(const set<T, Compare, Alloc> &lhs, const set<T, Compare, Alloc> &rhs)
	{
		return (lhs._tree == rhs._tree);
	}

	template <class T, class Compare, class Alloc>
	bool operator<(const set<T, Compare, Alloc> &lhs, const set<T, Compare, Alloc> &rhs)
	{
		return (lhs._tree < rhs._tree);
	}

	template <class T, class Compare, class Alloc>
	bool operator!=(const set<T, Compare, Alloc> &lhs, const set<T, Compare, Alloc> &rhs)
	{
		return (!(lhs == rhs));
	}
	
	template <class T, class Compare, class Alloc>
	bool operator<=(const set<T, Compare, Alloc> &lhs, const set<T, Compare, Alloc> &rhs)
	{
		return (!(rhs < lhs));
	}

	template <class T, class Compare, class Alloc>
	bool operator>(const set<T, Compare, Alloc> &lhs, const set<T, Compare, Alloc> &rhs)
	{
		return (rhs < lhs);
	}

	template <class T, class Compare, class Alloc>
	bool operator>=(const set<T, Compare, Alloc> &lhs, const set<T, Compare, Alloc> &rhs)
	{
		return (!(lhs < rhs));
	}
}

#endif
