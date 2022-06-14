# Annihilation List for ft_containers
## General
### Tester Class
Use this dummy class with informative output to test for lifetime of objects of the containers. Create one standard container and one ft::container parameterized over this class:
``` c++
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
```
### Constness
*	Non-`const` member functions with their `const` counterparts should be implemented via the `const` version by applying `const_cast<>`.
## Vector
### Allocator
*	Should be used to allocate memory and construct.
*	Should be kept as an instance private member variable.
### Allocation
*	Should be _exception-safe_. Construction of objects by using `construct()` may throw exceptions. In such case, if they're caught in `main()`, the `allocate()`d pointer must be freed, otherwise a memory leak occurs. This can be achieved by using try-catch blocks.
*	Insertion, reserving and assigning may cause reallocation. In that case, both old and new objects are directly constructed back-to-back (this means one can't call `reserve()` and then inserting utility).
### Exceptions
*	All versions of `at()` throw `std::out_of_range` if out of bounds
*	`reserve()` _and any internal allocation_ throw `std::length_error` if n > max_size
### Max Size
Should be implemented by returning allocator's `max_size()`.
*	If chosen capacity for reallocation is bigger than max_size, it should get truncated to max_size (i.e. there has to be a checking bounds function for this purpose whenever a reallocation is requested).
### Insert
*	A copy of inserted element has to be created in case inserted element is to the right of the position, in the same container, because shifting elements will invalidate the reference.
*	There should be tag dispatching in range modificators in case iterator is of type `InputIterator` -- one should take individual approach for this case (try `std::istream_iterator` to check for that; if the iterator is exhausted, the behavior will be undefined).
### Reallocation
*	All copying/constructing/filling functions (namely insert and assign) must be exception-safe! Any construction can throw, and in that case, the memory should be freed properly, if the exception is handled later by the program; not doing so will yield memory leaks. This implies that any allocations with the allocator must be guarded by a try-catch block which will destroy and deallocate the memory if at least one object construction fails.
*	The latter implies that modifications to vector members have to be done in the right order in case if an error occurs (i.e. incrementing size before construction can result in a foul increment after a failed insert operation).
### Template Ambiguity
*	Insert, assign and constructor functions must use either tag dispatching or SFINAE to differentiate between two numbers (fill function) and two iterators (range function) passed. The first approach is preferrable because it's not polluting the signature of the function.
## List
### Allocator
*	Should be rebound to the node type.
## Associative Containers
### Allocator
*	Should be rebound to the node type.
### Complexity
*	`begin()` and `end()` must be O(1) constant-time, as the standard requires. Otherwise the container fails for being 20 times slower than the standard.