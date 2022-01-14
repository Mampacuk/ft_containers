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

#include <vector>
#include "vector.hpp"
// #include "memory.hpp"
#include <iostream>
// #include <map>
// #include <iterator>
// #include <utility>
#include <list>
// #include "list.hpp"

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

# define VERSION ft

int	main()
{
	// A	arr[] = {A(), A(), A()};
	// std::cout << "array created" << std::endl;
	// VERSION::vector<A>	v(10, A());

	int	arr[] = {1, 2, 3};

	VERSION::vector<int>    v;

	v.assign(arr, arr+3);

	VERSION::vector<int> a;

	a = v;
	std::cout << "vector (size=" << v.size() << ", cap=" << v.capacity() << ") is:";
	for (VERSION::vector<int>::iterator it = v.begin(); it != v.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << std::endl;
}

// int main()
// {
// 	VERSION::list<A>	a;
// 	VERSION::vector<int>	vec;
// 	vec.reserve(vec.max_size() + 1);
// 	int	arr[] = {1, 2, 3, 4};
// 	VERSION::list<int>	l;
// 	for (int i = 10; i < 15; i++) l.insert(l.begin(), i);
// 	vec.insert(vec.end(), arr, arr+4);
// 	vec.assign(l.begin(), l.end());
// 	// VERSION::list<A>	b;
// 	std::cout << "vector a is:";
// 	for (VERSION::vector<int>::iterator it = vec.begin(); it != vec.end(); it++)
// 	{
// 		std::cout << ' ' << *it;
// 	}
// 	std::cout << std::endl;
// 	a.insert(a.end(), 3, A());
// 	// b.insert(b.begin(), A());
// 	std::cout << "resizing to 1" << std::endl;
// 	a.resize(1);
// 	// std::cout << "list b is:";
// 	// for (VERSION::list<A>::iterator it = b.begin(); it != b.end(); it++)
// 	// {
// 	// 	std::cout << ' ' << *it;
// 	// }
// 	// std::cout << std::endl;
// 	std::cout << "list a is:";
// 	for (VERSION::list<A>::iterator it = a.begin(); it != a.end(); it++)
// 	{
// 		std::cout << ' ' << *it;
// 	}
// 	std::cout << std::endl;
// 	std::cout << std::endl << "dtoring..." << std::endl;
// }
