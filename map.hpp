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
	template <class Key,										// map::key_type
		class T,												// map::mapped_type
		class Compare = less<Key>,							// map::key_compare
		class Alloc = std::allocator<pair<const Key, T> >	// map::allocator_type>
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
			typedef rbtree<value_type, value_compare, allocator_type>	tree;
		public:
			typedef tree::iterator										iterator;
			typedef tree::const_iterator								const_iterator;
			typedef tree::reverse_iterator								reverse_iterator;
			typedef tree::const_reverse_iterator						const_reverse_iterator;

		public:
			// (constructor)
			explicit map(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type()) : _tree()
			{

			}

			template <class InputIterator>
			map(InputIterator first, InputIterator last,
				const key_compare &comp = key_compare(),
				const allocator_type &alloc = allocator_type());

			map(const map &x);

			map	&operator=(const map &x);

			// (destructor)
			~map() { }
		private:
			tree	_tree;
	};
}

#endif
