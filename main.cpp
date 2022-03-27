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
#include "rbtree.hpp"

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

#define TESTED_NAMESPACE std

int	main()
{
	TESTED_NAMESPACE::map<int, A>	map1;

	map1[1] = A("1");
	std::cout << "1 inserted to map1" << std::endl;
	map1[2] = A("2");
	std::cout << "2 insterted to map1" << std::endl;

	TESTED_NAMESPACE::map<int, A>	map2;

	map2[1] = A("3");
	map2[2] = A("3");
	map2[3] = A("3");
	map2[4] = A("3");
	std::cout << "3 insterted to map2" << std::endl;
	// map2[2] = A("1 again");
	// std::cout << "1 insterted to map2, again" << std::endl;
	map2 = map1;
	std::cout << "maps assigned" << std::endl;
}
/*
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
*/