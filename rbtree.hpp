/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbtree.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aisraely <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 19:53:23 by aisraely          #+#    #+#             */
/*   Updated: 2022/06/28 22:05:57 by aisraely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBTREE_HPP
# define RBTREE_HPP

# include "functional.hpp"
# include "algorithm.hpp"
# include "memory.hpp"
# include "iterator.hpp"
# include <iostream>

namespace ft
{
	// util structures for rbtree
	enum	color_type { black, red };

	struct	tree_node_base
	{
		tree_node_base() : left(), right(), parent(), color(black) { }
		tree_node_base(const tree_node_base &copy) : left(copy.left), right(copy.right), parent(copy.parent), color(copy.color) { }
		tree_node_base	*left;
		tree_node_base	*right;
		tree_node_base	*parent;
		color_type		color;

		tree_node_base	&operator=(const tree_node_base &rhs)
		{
			this->left = rhs.left;
			this->right = rhs.right;
			this->parent = rhs.parent;
			this->color = rhs.color;
			return (*this);
		}
	};

	template <class T>
	struct	tree_node : public tree_node_base
	{
		T	data;
	};

	// map iterators
	template <class T>
	class	tree_const_iterator;
	
	template <class T>
	class	tree_iterator
	{
		private:
			template <class K1, class T1, class KOV1, bool M1, class C1, class A1>
			friend class rbtree;
			template <class T1>
			friend bool operator==(const tree_iterator<T1> &lhs, const tree_iterator<T1> &rhs);
			template <class T1>
			friend class tree_const_iterator;
			template <class T1>
			friend bool operator==(const tree_iterator<T1> &lhs, const tree_const_iterator<T1> &rhs);
			template <class T1>
			friend bool operator==(const tree_const_iterator<T1> &lhs, const tree_iterator<T1> &rhs);
			// member variables
			tree_node_base							*_node;
		public:
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
				return (ptr and ptr->right and ptr->right->left == ptr and ptr->left and ptr->left->right == ptr);
			}
		public:
			tree_iterator	&operator=(const tree_iterator &rhs)
			{
				this->_node = rhs._node;
				return (*this);
			}

			reference	operator*() const
			{
				return (static_cast<tree_node<T>*>(this->_node)->data);
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
				return (ft::addressof(operator*()));
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
		return (!(lhs == rhs));
	}

	template <class T>
	class	tree_const_iterator
	{
		private:
			template <class K1, class T1, class KOV1, bool M1, class C1, class A1>
			friend class rbtree;
			template <class T1>
			friend bool operator==(const tree_const_iterator<T1> &lhs, const tree_const_iterator<T1> &rhs);
			template <class T1>
			friend bool operator==(const tree_iterator<T1> &lhs, const tree_const_iterator<T1> &rhs);
			template <class T1>
			friend bool operator==(const tree_const_iterator<T1> &lhs, const tree_iterator<T1> &rhs);
			// member variables
			const tree_node_base					*_node;
		public:
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
				return (ptr and ptr->right and ptr->right->left == ptr and ptr->left and ptr->left->right == ptr);
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
				return (static_cast<const tree_node<T>*>(this->_node)->data);
			}

			pointer	operator->() const
			{
				return (ft::addressof(operator*()));
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
		return (!(lhs == rhs));
	}

	template <class T>
	bool	operator!=(const tree_iterator<T> &lhs, const tree_const_iterator<T> &rhs)
	{
		return (!(lhs == rhs));
	}

	template <class T>
	bool	operator!=(const tree_const_iterator<T> &lhs, const tree_iterator<T> &rhs)
	{
		return (!(lhs == rhs));
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

	// Multi == true => multiset/multimap is implemented, Multi == false => set/map
	template <class Key, class T, class KeyOfValue, bool Multi, class Compare = less<T>, class Alloc = std::allocator<T> >
	class	rbtree
	{
		private:
			typedef tree_node<T>									node;
			typedef typename Alloc::template rebind<node>::other	node_allocator_type;
		public:
			typedef Key										key_type;
			typedef T										value_type;
			typedef Compare									key_compare;
			typedef Alloc									allocator_type;
			typedef value_type&								reference;
			typedef const value_type&						const_reference;
			typedef	value_type*								pointer;
			typedef const value_type*						const_pointer;
			typedef ptrdiff_t								difference_type;
			typedef size_t									size_type;
			typedef tree_iterator<value_type>				iterator;
			typedef tree_const_iterator<value_type>			const_iterator;
			typedef ft::reverse_iterator<iterator>			reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;
		private:
			tree_node_base		_super;
			size_type			_size;
			node_allocator_type	_alloc;
			key_compare			_comp;

		public:
			explicit rbtree(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type()) : _super(), _size(), _alloc(alloc), _comp(comp)
			{
				update_super();
			}

			template <class InputIterator>
			rbtree(InputIterator first, InputIterator last, const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type()) : _super(), _size(), _alloc(alloc), _comp(comp)
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
				if (&x != this)
				{
					clear();
					insert(x.begin(), x.end());
				}
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

			iterator	insert(const_iterator position, const value_type &val)
			{
				return (insert(iterator(const_cast<tree_node_base*>(position._node)), val));
			}

			iterator	insert(iterator position, const value_type &val)
			{
				if (position == end())					// hint is end()
				{
					if (!empty() and this->_comp(extract_key(--end()), extract_key(val)))	// hint accepted, i.e. val becomes maximum
						return (hinted_insert((--position)._node, val).first);
					else											// hint rejected
						return (hinted_insert(NULL, val).first);
				}
				else if (this->_comp(extract_key(val), extract_key(position)))	// if inserted node is smaller than hint
				{
					// compare with predecessor
					iterator	pred = position;
					if (position == begin())				// hint is begin() and is a valid hint, new min destined
						return (hinted_insert(position._node, val).first);
					else if (this->_comp(extract_key(--pred), extract_key(val)))	// ensure dest. is in the same subtree
						return (hinted_insert(position._node, val).first);
					else
						return (hinted_insert(NULL, val).first);
				}
				else if (this->_comp(extract_key(position), extract_key(val)))	// if inserted node is greater than hint
				{
					// compare with successor
					iterator	succ = position;
					if (position == --end())				// hint accepted, new maximum destined
						return (hinted_insert(position._node, val).first);
					else if (this->_comp(extract_key(val), extract_key(++position)))	// ensure dest. is in the same subtree
						return (hinted_insert(position._node, val).first);
					else
						return (hinted_insert(NULL, val).first);
				}
				else
					return (hinted_insert(position._node, val).first);	// else is equal to hint
			}

			pair<iterator, bool>	insert(const value_type &val)
			{
				return (hinted_insert(NULL, val));
			}

			template <class InputIterator>
			void	insert(InputIterator first, InputIterator last)
			{
				for (iterator hint = end(); first != last; ++first)	// speeds up the process if
					hint = insert(hint, *first);			// elements are already sorted
			}
		private:
			pair<iterator, bool>	hinted_insert(tree_node_base *hint, const value_type &val)
			{
				tree_node_base	*y = NULL;						// the node at which the insertion will happen
				tree_node_base	*x = (is_internal(hint) ? hint : root());	// take or not take the hint?
				while (is_internal(x))
				{
					y = x;
					if (this->_comp(extract_key(val), extract_key(static_cast<node*>(x))))
						x = x->left;
				    else if (this->_comp(extract_key(static_cast<node*>(x)), extract_key(val)))
						x = x->right;
					else	//equal
					{
						if (!Multi)	// if map/set, deny insertion, else continue
							return (ft::make_pair(iterator(x), false));
						x = x->right;
					}
				}
				node	*z = create_node(val);
				z->parent = y;
				if (is_external(y))
					this->_super.parent = z;
				else if (this->_comp(extract_key(z), extract_key(static_cast<node*>(y))))
					y->left = z;
				else
					y->right = z;
				z->left = NULL;
				z->right = NULL;
				z->color = red;
				this->_size++;
				insert_fixup(z);
				update_super();
				return (ft::make_pair(iterator(z), true));
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
			size_type	erase(const key_type &k)
			{
				iterator	low = lower_bound(k);
				iterator	high = upper_bound(k);
				size_type	deletions = 0;
				while (low != high)
				{
					erase(low++);
					deletions++;
				}
				return (deletions);
			}

			// for set, multiset
			void	erase(const_iterator first, const_iterator last)
			{
				erase(iterator(const_cast<tree_node_base*>(first._node)), iterator(const_cast<tree_node_base*>(last._node)));
			}

			void	erase(iterator first, iterator last)
			{
				while (first != last)
					erase(first++);
			}

			// for set, multiset
			void	erase(const_iterator position)
			{
				erase(iterator(const_cast<tree_node_base*>(position._node)));
			}

			void	erase(iterator position)
			{
				tree_node_base	*x;
				tree_node_base	x_null;	// to replace a NULL leaf with actual node with valid pointers
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
				nullify_leaf(&x_null);
				if (!(--this->_size))
					this->_super.parent = NULL;
				update_super();
			}
		private:
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
			/**
			 * Uncomment for debugging purposes.
			 */
			// void	print_node(const tree_node_base *root, int offset) const
			// {
			// 	if (is_external(root))
			// 		return ;
			// 	for (int i = 0; i < offset; i++)
			// 		std::cout << "  ";
			// 	std::cout << (root->color ? "r" : "b") << static_cast<const node*>(root)->data;
			// 	if (root->parent)
			// 		std::cout << (root == root->parent->left ? "L" : "R");
			// 	if (is_internal(root))
			// 		std::cout << " ( " ;
			// 	std::cout << std::endl;
			// 	this->print_node(root->left, offset + 2);
			// 	this->print_node(root->right, offset + 2);
			// 	if (is_internal(root))
			// 	{
			// 		for (int i = 0; i < offset + 1; i++)
			// 			std::cout << "  ";
			// 		std::cout << ")" << std::endl;
			// 	}
			// }
		protected:
			/**
			 * Uncomment for debugging purposes.
			 */
			// void	print() const
			// {
			// 	if (empty())
			// 	{
			// 		std::cout << "(null)" << std::endl;
			// 		return ;
			// 	}
			// 	std::cout << "size: " << this->_size << std::endl;
			// 	print_node(root(), 0);
			// }
		public:
			void	clear()
			{
				destroy_subtree(root());
				this->_size = 0;
				this->_super.parent = NULL;
				update_super();
			}

			const_iterator	lower_bound(const key_type &k) const
			{
				tree_node_base	x_null;	// to replace a NULL leaf with actual node with valid pointers
				tree_node_base	*x = root();
				if (empty()) return (end());
				while (is_internal(x)) // walk down the tree to find a match
				{
					x_null.parent = x;
					if (this->_comp(k, extract_key(static_cast<node*>(x))))
						x = x->left;
					else if (this->_comp(extract_key(static_cast<node*>(x)), k))
						x = x->right;
					else	// exact match
					{		// get the leftmost one
						iterator	pred = --iterator(x);
						while (pred != end() and !this->_comp(extract_key(pred), extract_key(iterator(x)))
							and !this->_comp(extract_key(iterator(x)), extract_key(pred)))
						{
							x = pred._node;
							--pred;
						}
						return (const_iterator(x)); 
					}
				}
				// if hit a null leaf, set up parent-child r-ships to climb up back later
				x = &x_null;
				if (this->_comp(k, extract_key(static_cast<node*>(x->parent))))
				{
					if (is_super(x->parent->left))
						x->color = red;	// red signifies that a superleaf was replaced
					x->parent->left = x;
				}
				else
				{
					if (is_super(x->parent->right))
						x->color = red;	// red signifies that a superleaf was replaced
					x->parent->right = x;
				}
				while (!is_root(x))
				{
					if (x == x->parent->left)
					{
						nullify_leaf(&x_null);
						return (const_iterator(x->parent));
					}
					else
						x = x->parent;
				}
				nullify_leaf(&x_null); // undo the parent-child r-ships

				return (end());
			}

			const_iterator	upper_bound(const key_type &k) const
			{
				tree_node_base	x_null;	// to replace a NULL leaf with actual node with valid pointers
				tree_node_base	*x = root();
				if (empty()) return (end());
				while (is_internal(x)) // walk down the tree to find a match
				{
					x_null.parent = x;
					if (this->_comp(k, extract_key(static_cast<node*>(x))))
						x = x->left;
					else if (this->_comp(extract_key(static_cast<node*>(x)), k))
						x = x->right;
					else	// exact match
					{		// get_next_value
						const_iterator	succ = ++const_iterator(x);
						while (succ != end() and !this->_comp(extract_key(succ), extract_key(iterator(x)))
							and !this->_comp(extract_key(iterator(x)), extract_key(succ)))
							++succ;
						return (const_iterator(succ._node));
					}
				}
				// if hit a null leaf, set up parent-child r-ships to climb up back later
				x = &x_null;
				if (this->_comp(k, extract_key(static_cast<node*>(x->parent))))
				{
					if (is_super(x->parent->left))
						x->color = red;	// red signifies that a superleaf was replaced
					x->parent->left = x;
				}
				else
				{
					if (is_super(x->parent->right))
						x->color = red;	// red signifies that a superleaf was replaced
					x->parent->right = x;
				}
				while (!is_root(x))
				{
					if (x == x->parent->left)
					{
						nullify_leaf(&x_null);
						return (const_iterator(x->parent));
					}
					else
						x = x->parent;
				}
				nullify_leaf(&x_null); // undo the parent-child r-ships
				return (end());
			}

			iterator	lower_bound(const key_type &k)
			{
				const_iterator	const_it = static_cast<const rbtree&>(*this).lower_bound(k);
				return (iterator(const_cast<tree_node_base*>(const_it._node)));
			}

			iterator	upper_bound(const key_type &k)
			{
				const_iterator	const_it = static_cast<const rbtree&>(*this).upper_bound(k);
				return (iterator(const_cast<tree_node_base*>(const_it._node)));
			}

			void	swap(rbtree &x)
			{
				// update superroot and min and max nodes' pointers
				ft::swap(this->_super.parent, x._super.parent);
				
				// don't let the trees point to other tree's superroots when one of them is empty or underfilled
				this->_super.left = is_super(this->_super.left) ? &x._super : this->_super.left;
				x._super.left = x.is_super(x._super.left) ? &this->_super : x._super.left;
				ft::swap(this->_super.left, x._super.left);
				
				this->_super.right = is_super(this->_super.right) ? &x._super : this->_super.right;
				x._super.right = x.is_super(x._super.right) ? &this->_super : x._super.right;
				ft::swap(this->_super.right, x._super.right);

				// restore circularity for superroots
				this->_super.left->right = &this->_super;
				this->_super.right->left = &this->_super;
				x._super.left->right = &x._super;
				x._super.right->left = &x._super;
				// update sizes
				ft::swap(this->_size, x._size);
			}

			key_compare	key_comp() const
			{
				return (this->_comp);
			}

			iterator	find(const key_type &k)
			{
				const_iterator	const_it = static_cast<const rbtree&>(*this).find(k);
				return (iterator(const_cast<tree_node_base*>(const_it._node)));
			}

			size_type	count(const key_type &k) const
			{
				return (ft::distance(lower_bound(k), upper_bound(k)));
			}

			const_iterator	find(const key_type &k) const
			{
				tree_node_base	*x = root();
				while (is_internal(x))
				{
					if (this->_comp(k, extract_key(static_cast<node*>(x))))
						x = x->left;
					else if (this->_comp(extract_key(static_cast<node*>(x)), k))
						x = x->right;
					else	// exact match
					{		// get the leftmost one
						iterator	pred = --iterator(x);
						while (pred != end() and !this->_comp(extract_key(pred), extract_key(iterator(x)))
							and !this->_comp(extract_key(iterator(x)), extract_key(pred)))
						{
							x = pred._node;
							--pred;
						}
						return (const_iterator(x)); 
					}
				}
				return (end());
			}

			pair<const_iterator, const_iterator>	equal_range(const key_type &k) const
			{
				return (ft::make_pair(lower_bound(k), upper_bound(k)));
			}

			pair<iterator, iterator>	equal_range(const key_type &k)
			{
				pair<const_iterator, const_iterator> const_range = static_cast<const rbtree&>(*this).equal_range(k);
				return (ft::make_pair(iterator(const_cast<tree_node_base*>(const_range.first._node)),
					iterator(const_cast<tree_node_base*>(const_range.second._node))));
			}

			allocator_type	get_allocator() const
			{
				return (this->_alloc);
			}
		private:
			const key_type	&extract_key(const value_type &val) const
			{
				return (KeyOfValue()(val));
			}

			const key_type	&extract_key(const node *ptr) const
			{
				return (extract_key(ptr->data));
			}

			const key_type	&extract_key(const_iterator it) const
			{
				return (extract_key(static_cast<const node*>(it._node)));
			}

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
					alloc.construct(&new_node->data, val);
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

			// when a stacked x_null node is used to emulate a NULL leaf, this function
			// nullifies the leaf at x, if it was replaced by a stacked x_null
			void	nullify_leaf(tree_node_base *x_null) const
			{
				if (x_null->parent)
				{
					if (x_null->parent->left == x_null)
					{
						if (is_red(x_null))	// x_null replaced a super pointer
							x_null->parent->left = const_cast<tree_node_base*>(&this->_super);
						else
							x_null->parent->left = NULL;
					}
					else if (x_null->parent->right == x_null)
					{
						if (is_red(x_null))	// x_null replaced a super pointer
							x_null->parent->right = const_cast<tree_node_base*>(&this->_super);
						else
							x_null->parent->right = NULL;
					}
				}
			}

			void	destroy_node(tree_node_base *x)
			{
				allocator_type	alloc(this->_alloc);
				alloc.destroy(&static_cast<node*>(x)->data);
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

	template <class Key, class T, class KeyOfValue, bool Multi, class Compare, class Alloc>
	void	swap(const rbtree<Key, T, KeyOfValue, Multi, Compare, Alloc> &x, const rbtree<Key, T, KeyOfValue, Multi, Compare, Alloc> &y)
	{
		x.swap(y);
	}

	template <class Key, class T, class KeyOfValue, bool Multi, class Compare, class Alloc>
	bool operator==(const rbtree<Key, T, KeyOfValue, Multi, Compare, Alloc> &lhs, const rbtree<Key, T, KeyOfValue, Multi, Compare, Alloc> &rhs)
	{
		return (lhs.size() == rhs.size() and ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template <class Key, class T, class KeyOfValue, bool Multi, class Compare, class Alloc>
	bool operator!=(const rbtree<Key, T, KeyOfValue, Multi, Compare, Alloc> &lhs, const rbtree<Key, T, KeyOfValue, Multi, Compare, Alloc> &rhs)
	{
		return (!(lhs == rhs));
	}

	template <class Key, class T, class KeyOfValue, bool Multi, class Compare, class Alloc>
	bool operator<(const rbtree<Key, T, KeyOfValue, Multi, Compare, Alloc> &lhs, const rbtree<Key, T, KeyOfValue, Multi, Compare, Alloc> &rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}
	
	template <class Key, class T, class KeyOfValue, bool Multi, class Compare, class Alloc>
	bool operator<=(const rbtree<Key, T, KeyOfValue, Multi, Compare, Alloc> &lhs, const rbtree<Key, T, KeyOfValue, Multi, Compare, Alloc> &rhs)
	{
		return (!(rhs < lhs));
	}

	template <class Key, class T, class KeyOfValue, bool Multi, class Compare, class Alloc>
	bool operator>(const rbtree<Key, T, KeyOfValue, Multi, Compare, Alloc> &lhs, const rbtree<Key, T, KeyOfValue, Multi, Compare, Alloc> &rhs)
	{
		return (rhs < lhs);
	}

	template <class Key, class T, class KeyOfValue, bool Multi, class Compare, class Alloc>
	bool operator>=(const rbtree<Key, T, KeyOfValue, Multi, Compare, Alloc> &lhs, const rbtree<Key, T, KeyOfValue, Multi, Compare, Alloc> &rhs)
	{
		return (!(lhs < rhs));
	}
}

#endif
