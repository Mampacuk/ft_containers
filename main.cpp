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
#include <iostream>
#include <list>
#include "list.hpp"

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

class foo {
	public:
		foo(void) { };
		~foo(void) { };
		void m(void) { std::cout << "foo::m called [" << this->value << "]" << std::endl; };
		void m(void) const { std::cout << "foo::m const called [" << this->value << "]" << std::endl; };
		foo &operator=(int src) { this->value = src; return *this; };
		int getValue(void) const { return this->value; };
	private:
		int	value;
};

std::ostream	&operator<<(std::ostream &o, foo const &bar) {
	o << bar.getValue();
	return o;
}

int A::num = 0;

#define TESTED_NAMESPACE ft

#define T_SIZE_TYPE typename TESTED_NAMESPACE::vector<T>::size_type

template <typename T>
void	printSize(TESTED_NAMESPACE::list<T> const &lst, bool print_content = 1)
{
	std::cout << "size: " << lst.size() << std::endl;
	std::cout << "max_size: " << lst.max_size() << std::endl;
	if (print_content)
	{
		typename TESTED_NAMESPACE::list<T>::const_iterator it = lst.begin(), ite = lst.end();
		std::cout << std::endl << "Content is:" << std::endl;
		for (; it != ite; ++it)
			std::cout << "- " << *it << std::endl;
	}
	std::cout << "###############################################" << std::endl;
}


#define TESTED_TYPE int

int		main(void)
{
	TESTED_NAMESPACE::list<TESTED_TYPE> lst(7);
	// TESTED_NAMESPACE::list<TESTED_TYPE> lst_two(4);
	// TESTED_NAMESPACE::list<TESTED_TYPE> lst_three;
	// TESTED_NAMESPACE::list<TESTED_TYPE> lst_four;

	// TESTED_NAMESPACE::list<TESTED_TYPE>::iterator it;

	for (TESTED_NAMESPACE::list<TESTED_TYPE>::iterator it = lst.begin(); it != lst.end(); ++it)
		std::cout << *it << std::endl;

	// it = lst.begin();
	// for (unsigned long int i = 0; i < lst.size(); ++i)
	// {
	// 	*it++ = (lst.size() - i) * 3;
	// 	std::cout << "hello" << std::endl;
	// }
	// std::cout << "hello" << std::endl;
	// it = lst_two.begin();
	// for (unsigned long int i = 0; i < lst_two.size(); ++i)
	// 	*it++ = (lst_two.size() - i) * 5;

	// printSize(lst);
	// printSize(lst_two);

	// lst_three.assign(lst.begin(), lst.end());
	// lst.assign(lst_two.begin(), lst_two.end());
	// lst_two.assign(2, 42);
	// lst_four.assign(4, 21);

	// std::cout << "\t### After assign(): ###" << std::endl;

	// printSize(lst);
	// printSize(lst_two);
	// printSize(lst_three);
	// printSize(lst_four);

	// lst_four.assign(6, 84);
	// printSize(lst_four);

	// std::cout << "\t### assign() : ###" << std::endl;

	// lst.assign(5, 53);

	// it = lst_three.begin(); ++it; ++it; ++it;
	// lst_two.assign(lst_three.begin(), it);

	// printSize(lst);
	// printSize(lst_two);

	// return (0);
}
