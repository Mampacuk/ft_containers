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

// #include "type_traits.hpp"
// #include <type_traits>
// int	main()
// {
// 	std::cout << ft::is_integral<bool>::value << "     " << std::is_integral<float>::value << std::endl;
// }

# define VERSION ft


int main ()
{
  VERSION::vector<int> foo (3,100);   // three ints with a value of 100
  VERSION::vector<int> bar (2,200);   // two ints with a value of 200

	bar.assign(1, 25);
}
// int main()
// {
// 	VERSION::vector<A> a;
// 	// VERSION::vector<A> b;

// 	// a.insert(a.begin(), arr, arr + 1); 
// 	// std::cout << "inserted array" << std::endl;
// 	// VERSION::vector<int> b;
// 	// VERSION::vector<A> *b = new VERSION::vector<A>;
// 	// for (int i = 0; i < 33; i++)
// 	// 	b.push_back(i);
// 	// std::cout << "b's capacity: " << b.capacity() << std::endl;
//     // a.reserve(15);
// 	for (int i = 0; i < 5; i++)
//         a.push_back(A());
// 	std::cout << "created A" << std::endl;

// 	// for (int i = 0; i < 3; i++)
//     //     b.push_back(A());
// 	    std::cout << "vector a (cap=" << a.capacity() << ", size=" << a.size() << ") is: ";
//     for (VERSION::vector<A>::iterator it = a.begin(); it != a.end(); it++)
//         std::cout << ' ' << *it;
//     std::cout << std::endl;

// 	//     std::cout << "vector b (cap=" << b.capacity() << ", size=" << b.size() << ") is: ";
//     // for (VERSION::vector<A>::iterator it = b.begin(); it != b.end(); it++)
//     //     std::cout << ' ' << *it;
//     // std::cout << std::endl;
// 	// std::cout << std::endl << "created B, calling a.swap(b)" << std::endl << std::endl;

// 	// a.swap(b);
// 	a.clear();
//     std::cout << "vector a (cap=" << a.capacity() << ", size=" << a.size() << ") is: ";
//     for (VERSION::vector<A>::iterator it = a.begin(); it != a.end(); it++)
//         std::cout << ' ' << *it;
//     std::cout << std::endl;

// 	//     std::cout << "vector b (cap=" << b.capacity() << ", size=" << b.size() << ") is: ";
//     // for (VERSION::vector<A>::iterator it = b.begin(); it != b.end(); it++)
//     //     std::cout << ' ' << *it;
//     // std::cout << std::endl;

// 	// std::cout << "capacity after equalizing: " << a.capacity() << std::endl;
//     // // for (int i = 0; i < 5; i++)
//     // //     b->push_back(A());
//     // std::cout << "vector (cap=" << a.capacity() << ", size=" << a.size() << ") is: ";
//     // for (VERSION::vector<A>::iterator it = a.begin(); it != a.end(); it++)
//     //     std::cout << ' ' << *it;
//     // std::cout << std::endl;
//     // std::cout << std::endl << "NOW RESERVING " << std::endl << std::endl;

// 	// a->reserve(10);
//     // //  a->insert(a->begin()+5, arr, arr + 3);
//     // //     std::cout << "CAPCACITY " << a->capacity() << std::endl;
        
//     // std::cout << "vector (cap=" << a->capacity() << ") is: ";
//     // for (VERSION::vector<A>::iterator it = a->begin(); it != a->end(); it++)
//     //     std::cout << ' ' << *it;
// 	// 	std::cout << std::endl;

//     // ft::vector<int> *a = new ft::vector<int>;
// 	// // a->reserve(20);
// 	// for (int i = 0; i < 10; i++)
// 	// 	a->insert(a->end(), i);
//     // //a->reserve(10);
//     // for (int i = 0; i < 16; i++)
//     //     a->push_back(A());
        
    

// //     std::cout << "vector is:";
// //     for (ft::vector<int>::iterator it = a->begin(); it != a->end(); it++)
// //         std::cout << ' ' << *it;
    
// // std::cout << std::endl << "INSERTING 3 TIMES " << std::endl << std::endl;

// // 	a->insert(a->begin() + 5, 3, 999);
//     // std::cout << std::endl << "NOW INSERTING AT BEGIN+8, CAP IS " << a->capacity() << std::endl << std::endl;
    
    
//     //     a->insert(a->begin()+8, A());
//     //     std::cout << "CAPCACITY " << a->capacity() << std::endl;
        
//     //         std::cout << "vector is: ";
//     // for (ft::vector<A>::iterator it = a->begin(); it != a->end(); it++)
//     //     std::cout << ' ' << (*it).my_num;

// 	// delete a;

//     // ft::vector<A> *a = new ft::vector<A>;

//     // a->insert(a->begin(), A());

// 	// a->insert(a->begin(), A());

// 	// delete a;

// // 	std::cout << std::endl << std::endl << "-- STD VERSION --" << std::endl << std::endl;
    
// {
// 	// A::num = 0;
//     // std::vector<A> *a = new std::vector<A>;
//     // // a->reserve(50);
//     // for (int i = 0; i < 10; i++)
//     //     a->push_back(A());
        
    
//     // std::cout << "vector is: ";
//     // for (std::vector<A>::iterator it = a->begin(); it != a->end(); it++)
//     //     std::cout << ' ' << *it;
    
//     // std::cout << std::endl << "NOW INSERTING 3 As AT BEGIN+5, CAP IS " << a->capacity() << std::endl << std::endl;
    
    
//     //  a->insert(a->begin()+5, 3, A());
//     //     std::cout << "CAPCACITY " << a->capacity() << std::endl;
        
//     //         std::cout << "vector is: ";
//     // for (std::vector<A>::iterator it = a->begin(); it != a->end(); it++)
//     //     std::cout << ' ' << *it;


// 	// A::num = 0;

// 	// std::vector<A> *a = new std::vector<A>;

//     // a->insert(a->begin(), A());
    
//     // a->insert(a->begin(), A());

// 	// a->insert(a->begin(), A());
// }
// }
