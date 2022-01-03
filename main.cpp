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
#include "memory.hpp"
#include <iostream>
#include <map>
#include <iterator>
#include <vector>
#include <utility>


class A
{
    public:

    static int num;
    int my_num;
  A() { num++; my_num = num; std::cout << "DEF CTORED number " << num << std::endl; }
  A(const A &a) { num++; my_num = num; std::cout << "COPY CTORED number " << num << "FROM NUMBER " << a.my_num << std::endl; }
  ~A() { std::cout << "DCTORED number " << my_num << std::endl; }
  A	&operator=(const A&) { std::cout << my_num << " EQUALIZED" << std::endl; return (*this); }
};

int A::num = 0;

int main()
{
    // ft::vector<A> *hello = new ft::vector<A>;

    // hello->insert(hello->begin(), A());

	// hello->insert(hello->begin(), A());

	// delete hello;

    ft::vector<A> *hello = new ft::vector<A>;

    hello->insert(hello->begin(), A());

	hello->insert(hello->begin(), A());

	// delete hello;

	std::cout << std::endl << "-- STD VERSION --" << std::endl;
    
{
	A::num = 0;

	std::vector<A> *hello = new std::vector<A>;

    hello->insert(hello->begin(), A());
    
    hello->insert(hello->begin(), A());

	// hello->insert(hello->begin(), A());
}
}
