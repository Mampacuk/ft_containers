/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aisraely <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 14:33:19 by aisraely          #+#    #+#             */
/*   Updated: 2021/12/29 14:33:19 by aisraely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP

# include "vector.hpp"

namespace ft
{
	template <class T, class Container = vector<T> >
	class	stack
	{
		public:
			typedef T									value_type;
			typedef Container							container_type;
			typedef typename container_type::size_type	size_type;
		protected:
			container_type	c;
		public:
			explicit stack(const container_type &ctnr = container_type()) : c(ctnr) { }

			bool	empty() const
			{
				return (c.empty());
			}

			size_type	size() const
			{
				return (c.size());
			}

			value_type	&top()
			{
				return (c.back());
			}

			const value_type	&top() const
			{
				return (c.back());
			}

			void	push(const value_type &val)
			{
				c.push_back(val);
			}

			void	pop()
			{
				c.pop_back();
			}
		private:
			template <class T1, class Container1>
			friend bool	operator==(const stack<T1, Container1>&, const stack<T1, Container1>&);
			template <class T1, class Container1>
			friend bool	operator<(const stack<T1, Container1>&, const stack<T1, Container1>&);
			// friend bool	operator==(const stack &lhs, const stack &rhs);
			// friend bool	operator!=(const stack &lhs, const stack &rhs);
			// friend bool	operator<(const stack &lhs, const stack &rhs);
			// friend bool	operator<=(const stack &lhs, const stack &rhs);
			// friend bool	operator>(const stack &lhs, const stack &rhs);
			// friend bool	operator>=(const stack &lhs, const stack &rhs);
	};

	template <class T, class Container>
	bool	operator==(const ft::stack<T, Container> &lhs, const ft::stack<T, Container> &rhs)
	{
		return (lhs.c == rhs.c);
	}

	template <class T, class Container>
	bool	operator<(const ft::stack<T, Container> &lhs, const ft::stack<T, Container> &rhs)
	{
		return (lhs.c < rhs.c);
	}

	template <class T, class Container>
	bool	operator!=(const ft::stack<T, Container> &lhs, const ft::stack<T, Container> &rhs)
	{
		return (!(lhs == rhs));
	}

	template <class T, class Container>
	bool	operator<=(const ft::stack<T, Container> &lhs, const ft::stack<T, Container> &rhs)
	{
		return (!(rhs < lhs));
	}

	template <class T, class Container>
	bool	operator>(const ft::stack<T, Container> &lhs, const ft::stack<T, Container> &rhs)
	{
		return (rhs < lhs);
	}

	template <class T, class Container>
	bool	operator>=(const ft::stack<T, Container> &lhs, const ft::stack<T, Container> &rhs)
	{
		return (!(lhs < rhs));
	}
}

#endif
