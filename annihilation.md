# Annihilation List
## General
### Tester Class
Use this dummy class with informative output to test for lifetime of objects of the containers. Create one standard container and one ft::container parameterized over this class:
```
struct A
{
	static int	num;
	int			my_num;
	A() { num++; my_num = num; std::cout << "default-constructed number " << my_num << std::endl; }
	A(const A &a) { num++; my_num = num; std::cout << "copy-constructed number " << my_num << " from number " << a.my_num << std::endl; }
	~A() { std::cout << "destroyed number " << my_num << std::endl; }
	A	&operator=(const A &a) { std::cout << my_num << " assigned to " << a.my_num << std::endl; my_num = a.my_num; return (*this); }
};
```
## Vector
### Allocator
*	Should be used to allocate memory and construct.
*	Should be kept as an instance private member variable.
### Allocation
*	Should be _exception-safe_. Construction of objects by using `construct()` may throw exceptions. In such case, if they're caught in `main()`, the `allocate()`d pointer must be freed, otherwise a memory leak occurs. This can be achieved by using try-catch block.
*	Insertion, reserving and assigning may cause reallocation. In that case, both old and new objects are directly constructed back-to-back (this means one can't call `reserve()` and then inserting utility).
### Exceptions
*	All versions of `at()` throw `std::out_of_range` if out of bounds
*	`reserve()` throws `std::length_error` if n > max_size
### Max Size
Should be implemented by returning allocator's `max_size()`.