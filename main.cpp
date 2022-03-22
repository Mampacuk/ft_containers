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
#include "rbtree.hpp"

struct A
{
	static int	num;
	int			my_num;
	A() { num++; my_num = num; std::cout << "default-constructed number " << my_num << std::endl; }
	A(const A &a) { num++; my_num = num; std::cout << "copy-constructed number " << my_num << " from number " << a.my_num << std::endl; }
	~A() { std::cout << "destroyed number " << my_num << std::endl; }
	A	&operator=(const A &a) { std::cout << my_num << " assigned to " << a.my_num << std::endl; my_num = a.my_num; return (*this); }
};

std::ostream	&operator<<(std::ostream &o, const A &a)
{
	o << a.my_num;
	return (o);
}

int A::num = 0;

#define TESTED_NAMESPACE ft


int		main(void)
{
	ft::rbtree<int>	tree;
	tree.insert(5);

	tree.insert(10);
	// std::cout << "begin == end? " << (tree.begin() == tree.end() ? "yes" : "no") << std::endl;
	tree.insert(13);
	tree.insert(79);
	tree.insert(0);
	tree.insert(15);
	tree.insert(18);
	tree.print();
	std::cout << "deleting " << *(++tree.begin()) << std::endl;
	tree.erase(++tree.begin());
	tree.print();

	std::cout << "deleting " << *(++(++tree.begin())) << std::endl;
	tree.erase(++(++tree.begin()));
	tree.print();

	std::cout << "deleting " << *(++(++(++tree.begin()))) << std::endl;
	tree.erase(++(++(++tree.begin())));
	tree.print();
}
