/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbtree.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aisraely <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 19:53:23 by aisraely          #+#    #+#             */
/*   Updated: 2022/02/06 19:53:23 by aisraely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBTREE_HPP
# define RBTREE_HPP

# include "functional.hpp"
# include "memory.hpp"
# include "utility.hpp"
# include "iterator.hpp"

namespace ft
{
	// util structures for rbtree
	enum	color_type { black, red };

	struct	tree_node_base
	{
		tree_node_base() : left(), right(), parent(), color(black) { }
		tree_node_base	*left;
		tree_node_base	*right;
		tree_node_base	*parent;
		color_type		color;
	};

	template <class T>
	struct	tree_node : public tree_node_base
	{
		T	data;
	};

	// map iterators
	template <class T>
	struct	tree_iterator
	{
		// member variables
		tree_node_base							*_node;
		// member types
		typedef T								value_type;
		typedef ptrdiff_t						difference_type;
		typedef T&								reference;
		typedef T*								pointer;
		typedef std::bidirectional_iterator_tag	iterator_category;
		
		tree_iterator() : _node() { }
		tree_iterator(tree_node_base *_node) : _node(_node) { }
		tree_iterator(const tree_iterator &copy) : _node(copy._node) { }
		~tree_iterator() { }
	};

	template <class T>
	struct	tree_const_iterator
	{
		// member variables
		const tree_node_base					*_node;
		// member types
		typedef tree_iterator<T>				iterator;
		typedef T								value_type;
		typedef ptrdiff_t						difference_type;
		typedef const T&						reference;
		typedef const T*						pointer;
		typedef std::bidirectional_iterator_tag	iterator_category;
		
		tree_const_iterator() : _node() { }
		tree_const_iterator(const tree_node_base *_node) : _node(_node) { }
		tree_const_iterator(const iterator &copy) : _node(copy._node) { }
		~tree_const_iterator() { }
	};

	template <class T, class Compare = less<T>, class Alloc = std::allocator<T> >
	class	rbtree
	{
		protected:
			typedef tree_node<T>									node;
			typedef typename Alloc::template rebind<node>::other	node_allocator_type;
		public:
			typedef T											value_type;
			typedef Compare										value_compare;
			typedef Alloc										allocator_type;
			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;
			typedef ptrdiff_t									difference_type;
			typedef size_t										size_type;
			typedef tree_iterator<value_type>					iterator;
			typedef tree_iterator<value_type>					const_iterator;
			typedef ft::reverse_iterator<iterator>				reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;
		private:
			tree_node_base		_super;
			size_type			_size;
			node_allocator_type	_alloc;
			value_compare		_comp;
		public:
			explicit rbtree(const value_compare &comp = value_compare(), const allocator_type &alloc = allocator_type()) : _super(), _size(), _alloc(alloc), _comp(comp)
			{
				this->_super.left = &this->_super;
				this->_super.right = &this->_super;
			}
		
	};
}

#endif
