/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multimultimap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aisraely <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 14:27:18 by aisraely          #+#    #+#             */
/*   Updated: 2022/06/08 14:27:18 by aisraely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MULTIMAP_HPP
# define MULTIMAP_HPP

# include "utility.hpp"
# include "rbtree.hpp"

namespace ft
{
	template <class Key,									// multimap::key_type
		class T,											// multimap::mapped_type
		class Compare = less<Key>,							// multimap::key_compare
		class Alloc = std::allocator<pair<const Key, T> >	// multimap::allocator_type
		>
	class multimap
	{
		public:
			typedef Key									key_type;
			typedef T									mapped_type;
			typedef pair<const key_type, mapped_type>	value_type;
			typedef Compare								key_compare;
			typedef Alloc								allocator_type;

			class	value_compare : public binary_function<value_type, value_type, bool>
			{
					friend class multimap<key_type, value_type, key_compare, allocator_type>;
				protected:
					key_compare	_comp;
				public:
					value_compare(key_compare c) : _comp(c) { }
					bool	operator()(const value_type &x, const value_type &y) const
					{
						return (this->_comp(x.first, y.first));
					}
			};
		private:
			typedef typename Alloc::template rebind<value_type>::other	pair_allocator_type;
			typedef rbtree<key_type, value_type, select_1st<value_type>,
				true, key_compare, pair_allocator_type>	tree;
		public:
			typedef typename pair_allocator_type::reference				reference;
			typedef typename pair_allocator_type::const_reference		const_reference;
			typedef typename pair_allocator_type::pointer				pointer;
			typedef typename pair_allocator_type::const_pointer			const_pointer;
			typedef ptrdiff_t											difference_type;
			typedef size_t												size_type;
			typedef typename tree::iterator								iterator;
			typedef typename tree::const_iterator						const_iterator;
			typedef typename tree::reverse_iterator						reverse_iterator;
			typedef typename tree::const_reverse_iterator				const_reverse_iterator;

		public:
			// (constructor)
			explicit multimap(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type()) : _tree(comp, alloc) { }

			template <class InputIterator>
			multimap(InputIterator first, InputIterator last,
				const key_compare &comp = key_compare(),
				const allocator_type &alloc = allocator_type()) : _tree(first, last, comp, alloc) { }

			multimap(const multimap &x) : _tree(x._tree) { }

			// (destructor)
			~multimap() { }

			multimap	&operator=(const multimap &x)
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

			// element access
			mapped_type	&operator[](const key_type &k)
			{
				return ((*(insert(ft::make_pair(k, mapped_type())).first)).second);
			}

			// modifiers
			iterator	insert(const value_type &val)
			{
				return (this->_tree.insert(val).first);
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

			void	swap(multimap &x)
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
				return (value_compare(key_comp()));
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
		private:
			tree	_tree;
		private:
			template <class Key1, class T1, class Compare1, class Alloc1>
			friend bool operator<(const multimap<Key1, T1, Compare1, Alloc1>&, const multimap<Key1, T1, Compare1, Alloc1>&);
			template <class Key1, class T1, class Compare1, class Alloc1>
			friend bool operator==(const multimap<Key1, T1, Compare1, Alloc1>&, const multimap<Key1, T1, Compare1, Alloc1>&);
	};

	template <class Key, class T, class Compare, class Alloc>
	void	swap(const multimap<Key, T, Compare, Alloc> &x, const multimap<Key, T, Compare, Alloc> &y)
	{
		x.swap(y);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator==(const multimap<Key, T, Compare, Alloc> &lhs, const multimap<Key, T, Compare, Alloc> &rhs)
	{
		return (lhs._tree == rhs._tree);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator<(const multimap<Key, T, Compare, Alloc> &lhs, const multimap<Key, T, Compare, Alloc> &rhs)
	{
		return (lhs._tree < rhs._tree);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator!=(const multimap<Key, T, Compare, Alloc> &lhs, const multimap<Key, T, Compare, Alloc> &rhs)
	{
		return (!(lhs == rhs));
	}
	
	template <class Key, class T, class Compare, class Alloc>
	bool operator<=(const multimap<Key, T, Compare, Alloc> &lhs, const multimap<Key, T, Compare, Alloc> &rhs)
	{
		return (!(rhs < lhs));
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator>(const multimap<Key, T, Compare, Alloc> &lhs, const multimap<Key, T, Compare, Alloc> &rhs)
	{
		return (rhs < lhs);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator>=(const multimap<Key, T, Compare, Alloc> &lhs, const multimap<Key, T, Compare, Alloc> &rhs)
	{
		return (!(lhs < rhs));
	}
}

#endif