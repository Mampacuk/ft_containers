/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aisraely <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 15:13:28 by aisraely          #+#    #+#             */
/*   Updated: 2021/12/29 15:13:28 by aisraely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <deque>
#include <vector>
#include <map>
#include <algorithm>
#include "rbtree.hpp"
#include "vector.hpp"
#include "map.hpp"
#include "functional.hpp"

struct A
{
	static int	num;
	int			my_num;
	A() { num++; my_num = num; std::cout << "default-constructed number " << my_num << std::endl; }
	A(std::string msg) { num++; my_num = num; std::cout << "default-constructed number " << my_num << " (msg: " << msg << ")" << std::endl; }
	A(const A &a) { num++; my_num = num; std::cout << "copy-constructed number " << my_num << " from number " << a.my_num << std::endl; }
	~A() { std::cout << "destroyed number " << my_num << std::endl; }
	A	&operator=(const A &a) { std::cout << my_num << " assigned to " << a.my_num << std::endl; my_num = a.my_num; return (*this); }
};

bool	operator<(const A &a, const A &b)
{
	return (a.my_num < b.my_num);
}

std::ostream	&operator<<(std::ostream &o, const A &a)
{
	o << a.my_num;
	return (o);
}

int A::num = 0;

#define TESTED_NAMESPACE ft


int		main(void)
{
	ft::map<int, int>	tree;

	// TESTED_NAMESPACE::vector<A>	a(10);
	// TESTED_NAMESPACE::vector<A>	b(10, A());
	// ft::rbtree<int, int, ft::identity<int>, true>	tree;

	// tree.insert(ft::make_pair(1, 5));
	// tree.insert(ft::make_pair(1, 5));
	tree.insert(ft::make_pair(1, 5));
	// tree.insert(5);
	tree.insert(ft::make_pair(2, 5));
	// tree.insert(5);
	// tree.insert(5);
	// tree.insert(10);
	// tree.insert(13);
	// tree.insert(79);
	// tree.insert(0);
	// tree.insert(15);
	// tree.insert(18);
	tree.get_tree().print();

	// ft::rbtree<int, true>::iterator itlow = tree.lower_bound(5);

	// ft::pair<ft::rbtree<int, true>::iterator, ft::rbtree<int, true>::iterator> range = tree.equal_range(5);

	// for (; range.first != range.second; ++range.first)
	// 	std::cout << *range.first << std::endl;
	// std::cout << "deleting " << *(++tree.begin()) << std::endl;
	// tree.erase(++tree.begin());
	// tree.print();

	// std::cout << "deleting " << *(++(++tree.begin())) << std::endl;
	// tree.erase(++(++tree.begin()));
	// tree.print();

	// std::cout << "deleting " << *(++(++(++tree.begin()))) << std::endl;
	// tree.erase(++(++(++tree.begin())));
	// tree.print();
}
