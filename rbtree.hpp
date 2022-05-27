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
		protected:
			bool	is_super(tree_node_base *ptr)
			{
				return (ptr and ptr->right and ptr->right->left == ptr);
			}
		public:
			tree_iterator	&operator=(const tree_iterator &rhs)
			{
				this->_node = rhs._node;
				return (*this);
			}

			reference	operator*() const
			{
				return (static_cast<tree_node<T>*>(this->_node)->key);
			}

			tree_iterator	&operator++()
			{
				if (this->_node->right)
				{
					this->_node = this->_node->right;
					while (!is_super(this->_node) and this->_node->left and !is_super(this->_node->left))
						this->_node = this->_node->left;
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

			tree_iterator	operator++(int)
			{
				tree_iterator	temp(*this);
				operator++();
				return (temp);
			}

			tree_iterator	&operator--()
			{
				if (this->_node->left)
				{
					this->_node = this->_node->left;
					while (!is_super(this->_node) and this->_node->right and !is_super(this->_node->right))
						this->_node = this->_node->right;
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

			tree_iterator	operator--(int)
			{
				tree_iterator	temp(*this);
				operator--();
				return (temp);
			}

			pointer	operator->() const
			{
				return (addressof(operator*()));
			}
	};

	template <class T>
	bool	operator==(const tree_iterator<T> &lhs, const tree_iterator<T> &rhs)
	{
		return (lhs._node == rhs._node);
	}

	template <class T>
	bool	operator!=(const tree_iterator<T> &lhs, const tree_iterator<T> &rhs)
	{
		return (lhs._node != rhs._node);
	}

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
		protected:
			bool	is_super(const tree_node_base *ptr)
			{
				return (ptr and ptr->right and ptr->right->left == ptr);
			}
		public:
			tree_const_iterator	&operator=(const iterator &rhs)
			{
				this->_node = rhs._node;
				return (*this);
			}

			tree_const_iterator	&operator++()
			{
				if (this->_node->right)
				{
					this->_node = this->_node->right;
					while (!is_super(this->_node) and this->_node->left and !is_super(this->_node->left))
						this->_node = this->_node->left;
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

			tree_const_iterator	operator++(int)
			{
				tree_const_iterator	temp(*this);
				operator++();
				return (temp);
			}

			tree_const_iterator	&operator--()
			{
				if (this->_node->left)
				{
					this->_node = this->_node->left;
					while (!is_super(this->_node) and this->_node->right and !is_super(this->_node->right))
						this->_node = this->_node->right;
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

			tree_const_iterator	operator--(int)
			{
				tree_const_iterator	temp(*this);
				operator--();
				return (temp);
			}

			reference	operator*() const
			{
				return (static_cast<const tree_node<T>*>(this->_node)->key);
			}

			pointer	operator->() const
			{
				return (addressof(operator*()));
			}
	};

	template <class T>
	bool	operator==(const tree_const_iterator<T> &lhs, const tree_const_iterator<T> &rhs)
	{
		return (lhs._node == rhs._node);
	}

	template <class T>
	bool	operator!=(const tree_const_iterator<T> &lhs, const tree_const_iterator<T> &rhs)
	{
		return (lhs._node != rhs._node);
	}

	template <class T>
	bool	operator!=(const tree_iterator<T> &lhs, const tree_const_iterator<T> &rhs)
	{
		return (lhs._node != rhs._node);
	}

	template <class T>
	bool	operator!=(const tree_const_iterator<T> &lhs, const tree_iterator<T> &rhs)
	{
		return (lhs._node != rhs._node);
	}

	template <class T>
	bool	operator==(const tree_iterator<T> &lhs, const tree_const_iterator<T> &rhs)
	{
		return (lhs._node == rhs._node);
	}

	template <class T>
	bool	operator==(const tree_const_iterator<T> &lhs, const tree_iterator<T> &rhs)
	{
		return (lhs._node == rhs._node);
	}

	// Multi == true => multiset/multimap is implemented, Multi == false => set/multimap
	template <class T, bool Multi, class Compare = less<T>, class Alloc = std::allocator<T> >
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
			typedef tree_const_iterator<value_type>				const_iterator;
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
				update_super();
			}

			template <class InputIterator>
			rbtree(InputIterator first, InputIterator last, const value_compare &comp = value_compare(), const allocator_type &alloc = allocator_type()) : _super(), _size(), _alloc(alloc), _comp(comp)
			{
				update_super();
				insert(first, last);
			}

			rbtree(const rbtree &x) : _super(), _size(), _alloc(x._alloc), _comp(x._comp)
			{
				update_super();
				insert(x.begin(), x.end());
			}

			~rbtree()
			{
				clear();
			}

			rbtree	&operator=(const rbtree &x)
			{
				clear();
				insert(x.begin(), x.end());
				return (*this);
			}

			// iterators
			iterator	begin()
			{
				return (iterator(this->_super.right));
			}

			const_iterator	begin() const
			{
				return (const_iterator(this->_super.right));
			}

			iterator	end()
			{
				return (iterator(&this->_super));
			}

			const_iterator	end() const
			{
				return (const_iterator(&this->_super));
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
			bool		empty() const
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
			// operator[] should be implemented in map ADT
			
		public:
			iterator	insert(iterator position, const value_type &val)
			{
				if (position == end())					// hint is end()
				{
					if (!empty() and this->_comp(*(--end()), val))	// hint accepted, i.e. val becomes maximum
						return (hinted_insert((--position)._node, val)->first);
					else											// hint rejected
						return (hinted_insert(NULL, val)->first);
				}
				else if (this->_comp(val, *position))	// if inserted node is smaller than hint
				{
					// compare with predecessor
					iterator	pred = position;
					if (position == begin())				// hint is begin() and is a valid hint, new min destined
						return (hinted_insert(position._node, val)->first);
					else if (this->_comp(*(--pred), val))	// ensure dest. is in the same subtree
						return (hinted_insert(position._node, val)->first);
					else
						return (hinted_insert(NULL, val)->first);
				}
				else if (this->_comp(*position, val))	// if inserted node is greater than hint
				{
					// compare with successor
					iterator	succ = position;
					if (position == *(--end()))	// hint accepted, new maximum destined
						return (hinted_insert(position._node, val)->first);
					else if (this->_comp(val, *(++position)))	// ensure dest. is in the same subtree
						return (hinted_insert(position._node, val)->first);
					else
						return (hinted_insert(NULL, val)->first);
				}
				else
					return (hinted_insert(position._node, val)->first);	// else is equal to hint
			}

			pair<iterator, bool>	insert(const value_type &val)
			{
				return (hinted_insert(NULL, val));
			}

			template <class InputIterator>
			void	insert(InputIterator first, InputIterator last)
			{
				iterator	hint;
				for (; first != last; ++first)			// speeds up the process if
					hint = insert(hint, *first)->first;	// elements are already sorted
			}
		protected:
			pair<iterator, bool>	hinted_insert(tree_node_base *hint, const value_type &val)
			{
				tree_node_base	*y = NULL;						// the node at which the insertion will happen
				tree_node_base	*x = (is_internal(hint) ? hint : root());	// take or not take the hint?
				while (is_internal(x))
				{
					y = x;
					if (this->_comp(val, static_cast<node*>(x)->key))
						x = x->left;
				                   	else if (this->_comp(static_cast<node*>(x)->key, val))
						x = x->right;
					else	//equal
					{
						if (!Multi)	// if map/set, deny insertion, else continue
							return (make_pair(iterator(x), false));
						x = x->right;
					}
				}
				node	*z = create_node(val);
				z->parent = y;
				if (is_external(y))
					this->_super.parent = z;
				else if (z->key < static_cast<node*>(y)->key)
					y->left = z;
				else
					y->right = z;
				z->left = NULL;
				z->right = NULL;
				z->color = red;
				this->_size++;
				insert_fixup(z);
				update_super();
				return (make_pair(iterator(z), true));
			}
		
			void	insert_fixup(tree_node_base *z)
			{
				while (is_red(z->parent))
				{
					if (z->parent == z->parent->parent->left)
					{
						tree_node_base	*y = z->parent->parent->right;
						if (is_red(y))
						{
							z->parent->color = black;
							if (is_internal(y))
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
						tree_node_base	*y = z->parent->parent->left;
						if (is_red(y))
						{
							z->parent->color = black;
							if (is_internal(y))
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
				root()->color = black;
			}
		public:
			size_type	erase(const value_type &k)
			{
				iterator	low = lower_bound(k);
				iterator	high = upper_bound(k);
				size_type	deletions = ft::distance(low, high);
				erase(low, high);
				return (deletions);
			}

			void	erase(iterator first, iterator last)
			{
				for (; first != last)
					erase(first++);
			}

			void	erase(iterator position)
			{
				tree_node_base	*x;
				tree_node_base	x_null;
				tree_node_base	*z = position._node;
				tree_node_base	*y = z;
				color_type		y_old_color = y->color;
				if (is_external(z->left))
				{
					if (is_external(x = z->right))
						x = &x_null;
					transplant(z, x);
				}
				else if (is_external(z->right))
				{
					if (is_external(x = z->left))
						x = &x_null;
					transplant(z, x);
				}
				else
				{
					y = minimum(z->right);
					y_old_color = y->color;
					if (is_external(x = y->right))
						x = &x_null;
					if (y->parent == z)
					{
						y->right = x;
						x->parent = y;
					}
					else
					{
						transplant(y, x);
						y->right = z->right;
						y->right->parent = y;
					}
					transplant(z, y);
					y->left = z->left;
					y->left->parent = y;
					y->color = z->color;
				}
				destroy_node(z);
				if (y_old_color == black)
					erase_fixup(x);
				if (x == &x_null)
				{
					if (x->parent->left == x)
						x->parent->left = NULL;
					else if (x->parent->right == x)
						x->parent->right = NULL;
				}
				update_super();
				this->_size--;
			}
		protected:
			void	erase_fixup(tree_node_base *x)
			{
				while (x != root() and is_black(x))
				{
					if (x == x->parent->left)
					{
						tree_node_base	*w = x->parent->right;
						if (is_red(w))
						{
							w->color = black;
							x->parent->color = red;
							left_rotate(x->parent);
							w = x->parent->right;
						}
						if (is_black(w->left) and is_black(w->right))
						{
							w->color = red;
							x = x->parent;
						}
						else
						{
							if (is_black(w->right))
							{
								w->left->color = black;
								w->color = red;
								right_rotate(w);
								w = x->parent->right;
							}
							w->color = x->parent->color;
							x->parent->color = black;
							w->right->color = black;
							left_rotate(x->parent);
							x = root();	// to terminate the loop
						}
					}
					else
					{
						tree_node_base	*w = x->parent->left;
						if (is_red(w))
						{
							w->color = black;
							x->parent->color = red;
							right_rotate(x->parent);
							w = x->parent->left;
						}
						if (is_black(w->right) and is_black(w->left))
						{
							w->color = red;
							x = x->parent;
						}
						else
						{
							if (is_black(w->left))
							{
								w->right->color = black;
								w->color = red;
								left_rotate(w);
								w = x->parent->left;
							}
							w->color = x->parent->color;
							x->parent->color = black;
							w->left->color = black;
							right_rotate(x->parent);
							x = root();	// to terminate the loop
						}
					}
				}
				x->color = black;
			}
		public:
			void	print_node(const tree_node_base *root, int offset) const
			{
				if (is_external(root))
					return ;
				for (int i = 0; i < offset; i++)
					std::cout << "  ";
				std::cout << (root->color ? "r" : "b") << static_cast<const node*>(root)->key;
				if (root->parent)
					std::cout << (root == root->parent->left ? "L" : "R");
				if (is_internal(root))
					std::cout << " ( " ;
				std::cout << std::endl;
				this->print_node(root->left, offset + 2);
				this->print_node(root->right, offset + 2);
				if (is_internal(root))
				{
					for (int i = 0; i < offset + 1; i++)
						std::cout << "  ";
					std::cout << ")" << std::endl;
				}
			}

			void	print(void) const
			{
				if (this->empty())
				{
					std::cout << "(null)" << std::endl;
					return ;
				}
				std::cout << "size: " << this->_size << std::endl;
				this->print_node(root(), 0);
			}

			void	clear()
			{
				destroy_subtree(root());
				this->_super.parent = NULL;
				update_super();
			}

			iterator	lower_bound(const value_type &k)
			{
				tree_node_base	*x = root();
				while ()
				if (is_external(x))
					return (NULL);
				if (this->_comp(k, static_cast<node*>(x)->key))
					return (tree_search(x->left, k));
				else if (this->_comp(static_cast<node*>(x)->key, k))
					return (tree_search(x->right, k));
				else	// exact match
					return (x);
				if (is_internal(x))
					return (iterator(x));
				while (!is_root(x))
				{
					if (x == x->parent->right)
						return (iterator(x->parent));
					else
						x = x->parent;
				}
				return (end());
			}

			const_iterator	lower_bound(const value_type &k) const
			{
				iterator	non_const = lower_bound(k);
				return (const_iterator(non_const));
			}
		protected:
			tree_node_base	*root() const
			{
				return (this->_super.parent);
			}

			bool	is_super(const tree_node_base *ptr) const
			{
				return (ptr and ptr == &this->_super);
			}

			bool	is_external(const tree_node_base *ptr) const
			{
				return (!ptr or is_super(ptr));
			}

			bool	is_internal(const tree_node_base *ptr) const
			{
				return (!is_external(ptr));
			}

			bool	is_black(const tree_node_base *ptr) const
			{
				return (is_external(ptr) or ptr->color == black);
			}

			bool	is_red(const tree_node_base *ptr) const
			{
				return (!is_black(ptr));
			}

			bool	is_root(const tree_node_base *ptr) const
			{
				return (is_internal(ptr) and !ptr->parent);
			}

			node	*create_node(const value_type &val)
			{
				node	*new_node = this->_alloc.allocate(1);
				try
				{
					allocator_type	alloc(this->_alloc);
					alloc.construct(&new_node->key, val);
				}
				catch (...)
				{
					this->_alloc.deallocate(new_node, 1);
					throw ;
				}
				return (new_node);
			}

			tree_node_base	*minimum(tree_node_base *ptr) const
			{
				if (is_external(ptr))
					return (NULL);
				while (is_internal(ptr->left))
					ptr = ptr->left;
				return (ptr);
			}

			tree_node_base	*maximum(tree_node_base *ptr) const
			{
				if (is_external(ptr))
					return (NULL);
				while (is_internal(ptr->right))
					ptr = ptr->right;
				return (ptr);
			}

			void	update_super()
			{
				tree_node_base	*min_node = minimum(root());
				tree_node_base	*max_node = maximum(root());

				if (!min_node and !max_node)
				{
					this->_super.left = &this->_super;
					this->_super.right = &this->_super;
					return ;
				}
				min_node->left = &this->_super;
				max_node->right = &this->_super;
				this->_super.right = min_node;
				this->_super.left = max_node;
			}

			void	left_rotate(tree_node_base *x)
			{
				tree_node_base	*y = x->right;
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
				tree_node_base	*x = y->left;
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

			// establishes parent-child relationships between u's parent and v,
			// effectively replacing u with v (does not relink u's children to v)
			void	transplant(tree_node_base *u, tree_node_base *v)
			{
				if (is_root(u))
					this->_super.parent = v;
				else if (u == u->parent->left)
					u->parent->left = v;
				else
					u->parent->right = v;
				if (is_internal(v))
					v->parent = u->parent;
			}

			void	destroy_node(tree_node_base *x)
			{
				allocator_type	alloc(this->_alloc);
				alloc.destroy(&static_cast<node*>(x)->key);
				this->_alloc.deallocate(static_cast<node*>(x), 1);
			}

			void	destroy_subtree(tree_node_base *x)
			{
				if (is_external(x))
					return ;
				destroy_subtree(x->left);
				destroy_subtree(x->right);
				destroy_node(x);
			}
	};
}

#endif
