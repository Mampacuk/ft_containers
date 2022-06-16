/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aisraely <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 13:57:06 by aisraely          #+#    #+#             */
/*   Updated: 2022/01/21 13:57:06 by aisraely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUEUE_HPP
# define QUEUE_HPP

# include "deque.hpp"

namespace ft
{
	template <class T, class Container = deque<T> >
	class	queue
	{
		public:
			typedef T									value_type;
			typedef Container							container_type;
			typedef typename container_type::size_type	size_type;
		protected:
			container_type	c;
		public:
			explicit queue(const container_type &ctnr = container_type()) : c(ctnr) { }

			bool	empty() const
			{
				return (c.empty());
			}

			size_type	size() const
			{
				return (c.size());
			}

			value_type	&front()
			{
				return (c.front());
			}

			const value_type	&front() const
			{
				return (c.front());
			}

			value_type	&back()
			{
				return (c.back());
			}

			const value_type	&back() const
			{
				return (c.back());
			}

			void	push(const value_type &val)
			{
				c.push_back(val);
			}

			void	pop()
			{
				c.pop_front();
			}
		private:
			template <class T1, class Container1>
			friend bool	operator==(const queue<T1, Container1>&, const queue<T1, Container1>&);
			template <class T1, class Container1>
			friend bool	operator<(const queue<T1, Container1>&, const queue<T1, Container1>&);
	};

	template <class T, class Container>
	bool	operator==(const queue<T, Container> &lhs, const queue<T, Container> &rhs)
	{
		return (lhs.c == rhs.c);
	}

	template <class T, class Container>
	bool	operator<(const queue<T, Container> &lhs, const queue<T, Container> &rhs)
	{
		return (lhs.c < rhs.c);
	}

	template <class T, class Container>
	bool	operator!=(const queue<T, Container> &lhs, const queue<T, Container> &rhs)
	{
		return (!(lhs == rhs));
	}

	template <class T, class Container>
	bool	operator<=(const queue<T, Container> &lhs, const queue<T, Container> &rhs)
	{
		return (!(rhs < lhs));
	}

	template <class T, class Container>
	bool	operator>(const queue<T, Container> &lhs, const queue<T, Container> &rhs)
	{
		return (rhs < lhs);
	}

	template <class T, class Container>
	bool	operator>=(const queue<T, Container> &lhs, const queue<T, Container> &rhs)
	{
		return (!(lhs < rhs));
	}
}

#endif
