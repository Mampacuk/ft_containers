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
		T	key;
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

		reference	operator*() const
		{
			return (static_cast<tree_node<T>*>(this->_node)->key);
		}

		iterator	&operator--()
		{
			if (this->_node->left)
			{
				if (!(this->_node->parent && !this->_node->parent->parent)) // if not super
				{
					this->_node = this->_node->left;
					while (this->_node->right)
						this->_node = this->_node->right;
				}
			}
			else
			{
				if (this->_node == this->_node->parent->right)
					this->_node = this->_node->parent;
				else
				{
					while (this->_node->parent->left == this->_node)
						this->_node = this->_node->parent;
					this->_node = this->_node->parent;
				}
			}
			return (*this);
		}

		iterator	&operator++()
		{
			if (this->_node->right)
			{
				if (!(this->_node->parent && !this->_node->parent->parent)) // if not super
				{
					this->_node = this->_node->right;
					while (this->_node->left)
						this->_node = this->_node->left;
				}
			}
			else
			{
				if (this->_node == this->_node->parent->left)
					this->_node = this->_node->parent;
				else
				{
					while (this->_node->parent->right == this->_node)
						this->_node = this->_node->parent;
					this->_node = this->_node->parent;
				}
			}
			return (*this);
		}
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
		protected:
			bool	is_super(tree_node_base *ptr)
			{
				return (ptr && ptr->parent && !ptr->parent->parent);
			}

			bool	is_external(tree_node_base *ptr)
			{
				return (!ptr || is_super(ptr));
			}

			bool	is_internal(tree_node_base *ptr)
			{
				return (!is_external(ptr));
			}

			bool	is_black(tree_node_base *ptr)
			{
				return (is_external(ptr) || ptr->color == black);
			}

			bool	is_red(tree_node_base *ptr)
			{
				return (!is_black(ptr));
			}

			bool	is_root(tree_node_base *ptr)
			{
				return (!is_external(ptr) && !ptr->parent);
			}

			node	*create_node(const value_type &val)
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
				return (new_node);
			}

			tree_node_base	*minimum(tree_node_base *ptr)
			{
				if (is_external(ptr))
					return (NULL);
				while (is_internal(ptr->left))
					ptr = ptr->left;
				return (ptr);
			}

			tree_node_base	*maximum(tree_node_base *ptr)
			{
				if (is_external(ptr))
					return (NULL);
				while (is_internal(ptr->right))
					ptr = ptr->right;
				return (ptr);
			}

			void	update_super()
			{
				tree_node_base	*min_node = minimum(this->_super.parent);
				tree_node_base	*max_node = maximum(this->_super.parent);

				min_node->left = this->_super;
				max_node->right = this->_super;
				this->_super.right = min_node;
				this->_super.left = max_node;
			}

			void	left_rotate(tree_node_base *x)
			{
				tree_node_base	y = x->right;
				x->right = y->left;
				if (is_internal(y->left))
					y->left->parent = x;
				y->parent = x->parent;
				if (is_root(x))
					this->_super.parent = y;
				else if (x == x->parent->left)
					x->parent->left = y;
				else
					x->parent->right = y;
				y->left = x;
				x->parent = y;
			}

			void	right_rotate(tree_node_base *y)
			{
				tree_node_base	x = y->left;
				y->left = x->right;
				if (is_internal(x->right))
					x->right->parent = y;
				x->parent = y->parent;
				if (is_root(y))
					this->_super.parent = x;
				else if (y == y->parent->right)
					y->parent->right = x;
				else
					y->parent->left = x;
				x->right = y;
				y->parent = x;
			}

			void	insert_fixup(node *z)
			{
				while (is_red(z->parent))
				{
					if (z->parent == z->parent->parent->left)
					{
						node	y = z->parent->parent->right;
						if (is_red(z->parent))
						{
							z->parent->color = black;
							y->color = black;
							z->parent->parent->color = red;
							z = z->parent->parent;
						}
						else
						{
							if (z == z->parent->right)
							{
								z = z->parent;
								left_rotate(z);
							}
							z->parent->color = black;
							z->parent->parent->color = red;
							right_rotate(z->parent->parent);
						}
					}
					else
					{
						node	y = z->parent->parent->left;
						if (is_red(z->parent))
						{
							z->parent->color = black;
							y->color = black;
							z->parent->parent->color = red;
							z = z->parent->parent;
						}
						else
						{
							if (z == z->parent->left)
							{
								z = z->parent;
								right_rotate(z);
							}
							z->parent->color = black;
							z->parent->parent->color = red;
							left_rotate(z->parent->parent);
						}
					}
				}
				this->_super.parent->color = black;
			}

			pair<iterator, bool>	insert(const value_type &val)
			{
				tree_node_base	*y = NULL;			// the node at which the insertion will happen
				node			*x = this->_super.parent;	// begins at the actual root
				while (is_internal(x))
				{
					y = x;
					if (this->_comp(val, x->key))
						x = x->left;
					else if (this->_comp(x->key, val))
						x = x->right;
					else	//equal
						return (make_pair(iterator(x), false));
				}
				node			*z = create_node(val);
				z->parent = y;
				if (is_external(y))
					this->_super.parent = z;
				else if (z->key < y->key)
					y->left = z;
				else
					y->right = z;
				z->left = NULL;
				z->right = NULL;
				z->color = red;
				insert_fixup(z);
				update_super();
				return (make_pair(iterator(z), true));
			}
		public:
			explicit rbtree(const value_compare &comp = value_compare(), const allocator_type &alloc = allocator_type()) : _super(), _size(), _alloc(alloc), _comp(comp)
			{
				this->_super.left = &this->_super;
				this->_super.right = &this->_super;
			}

			// iterators
			iterator	begin()
			{
				return (iterator(this->_super.right));
			}

			iterator	end()
			{
				return (iterator(&this->_super.left));
			}
	};
}

#endif
