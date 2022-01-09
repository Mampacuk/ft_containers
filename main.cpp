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

#include "vector.hpp"
// #include "memory.hpp"
#include <iostream>
// #include <map>
// #include <iterator>
// #include <utility>
#include <list>
#include "list.hpp"

class A
{
    public:

    static int num;
    int my_num;
  A() { num++; my_num = num; std::cout << "DEF CTORED number " << num << std::endl; }
  A(const A &a) { num++; my_num = num; std::cout << "COPY CTORED number " << num << " FROM NUMBER " << a.my_num << std::endl; }
  ~A() { std::cout << "DCTORED number " << my_num << std::endl; }
  A	&operator=(const A &a) { std::cout << my_num << " EQUALIZED TO " << a.my_num << std::endl; return (*this); }
};

std::ostream	&operator<<(std::ostream &o, const A &a)
{
	o << a.my_num;
	return (o);
}

int A::num = 0;

# define VERSION ft

int main ()
{
	VERSION::list<A>	heyooo;

	heyooo.insert(heyooo.end(), 3, A());

	std::cout << "list is:";
	for (VERSION::list<A>::iterator it = heyooo.begin(); it != heyooo.end(); it++)
	{
		std::cout << ' ' << *it;
	}
	std::cout << std::endl << "dtoring..." << std::endl;
}
