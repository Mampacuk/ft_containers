/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aisraely <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 19:58:41 by aisraely          #+#    #+#             */
/*   Updated: 2022/01/20 19:58:41 by aisraely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

# include "functional.hpp"
# include "memory.hpp"
# include "utility.hpp"
# include "iterator.hpp"
# include "rbtree.hpp"

namespace ft
{
	template <class Key,									// map::key_type
		class T,											// map::mapped_type
		class Compare = less<Key>,							// map::key_compare
		class Alloc = std::allocator<pair<const Key, T> >	// map::allocator_type
		>
	class map
	{
		public:
			typedef Key									key_type;
			typedef T									mapped_type;
			typedef pair<const key_type, mapped_type>	value_type;
			typedef Compare								key_compare;

			class	value_compare
			{
					friend class map;
				protected:
					key_compare	_comp;
					value_compare(key_compare c) : _comp(c) { }
				public:
					typedef bool		result_type;
					typedef value_type	first_argument_type;
					typedef value_type	second_argument_type;
					result_type	operator()(const first_argument_type &x, const second_argument_type &y) const
					{
						return (this->_comp(x.first, y.first));
					}
			};

			typedef Alloc												allocator_type;
			typedef typename allocator_type::reference					reference;
			typedef typename allocator_type::const_reference			const_reference;
			typedef typename allocator_type::pointer					pointer;
			typedef typename allocator_type::const_pointer				const_pointer;
			typedef ptrdiff_t											difference_type;
			typedef size_t												size_type;
		protected:
			typedef rbtree<value_type, false, value_compare, allocator_type>	tree;
		public:
			typedef typename tree::iterator								iterator;
			typedef typename tree::const_iterator						const_iterator;
			typedef typename tree::reverse_iterator						reverse_iterator;
			typedef typename tree::const_reverse_iterator				const_reverse_iterator;

		public:
			// (constructor)
			explicit map(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type()) : _tree(comp, alloc) { }

			template <class InputIterator>
			map(InputIterator first, InputIterator last,
				const key_compare &comp = key_compare(),
				const allocator_type &alloc = allocator_type()) : _tree(first, last, comp, alloc) { }

			map(const map &x) : _tree(x._tree) { }

			// (destructor)
			~map() { }

			map	&operator=(const map &x)
			{
				this->_tree = x._tree;
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

			void	swap(map &x)
			{
				this->_tree.swap(x._tree);
			}

			void	clear()
			{
				this->_tree.clear();
			}

			key_compare	key_comp() const
			{
				return (this->_tree.value_comp()._comp);
			}

			value_compare	value_comp() const
			{
				return (this->_tree.value_comp());
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
	};
}

#endif
