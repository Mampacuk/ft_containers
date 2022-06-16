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
#include "deque.hpp"
#include "vector.hpp"

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
	
	ft::deque<std::string> hi;
	// ft::deque<int>::const_iterator	hell2(hell1);
	// hi.push_front("f");
	// hi.push_front("f");
	for (int i = 0; i < 32; i++)
		hi.push_back("hi");
	hi.push_back("b");
	hi.push_back("b");
	hi.push_front("f");
	hi.push_front("f");
	// hi.push_back("b");
	// hi.push_back("b");
	hi.pop_back();
	hi.pop_back();
	hi.pop_back();
	// hi.pop_front();
	// hi.print();
}
