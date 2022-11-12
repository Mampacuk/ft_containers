# Annihilation List for ft_containers
## Tester
### `mli`'s Tester
*	The best [tester](https://github.com/mli42/containers_test) so far. 
## General
### Tester Class
Use this dummy class with informative output to test for lifetime of objects of the containers. Create one std::container and one ft::container parameterized over this class:
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
### Allocators
*	Should be used to allocate memory and construct. `new`ing and `delete`ing is an instant fail.
*	Should be kept as an instance private member variable.
*	Allocation should be _exception-safe_. Construction of objects by using `construct()` may throw exceptions. In such case, if they're caught in `main()`, the `allocate()`d pointers must be freed, otherwise a memory leak occurs. This can be achieved by using try-catch blocks.
*	All copying/constructing/filling functions (namely <ins>insert</ins> and <ins>assign</ins>) must be exception-safe! Any construction can throw, and in that case, the memory should be freed properly, if the exception is handled later by the program; not doing so will yield memory leaks. This implies that any allocations with the allocator must be guarded by a try-catch block which will destroy and deallocate the memory if at least one object construction fails.
*	The latter implies that modifications to container private members have to be done in the right order in case if an error occurs (i.e. incrementing size before construction can result in a foul increment after a failed <ins>insert</ins> operation).
### Max Size
*	Should be implemented by returning allocator's `max_size()`.
*	The number returned by it is platform-dependent and, unfortunately, it doesn't have to coincide with the `std` version.
### Template Ambiguity
*	Insert, assign and constructor functions of vector and deque must use either tag dispatching or SFINAE to differentiate between two numbers (fill function) and two iterators (range function) passed. The latter approach is preferrable because it's not polluting the signature of the function.
### Iterators
*	Must be STL-compliant, i.e. should have all types defined, and tags included. It should be passable to call `std::sort()` with them, for example.
*	Should implement the arrow operator by calling `addressof()`! Otherwise, a class with `&` operator overload will call the operator overload function instead.
### Complexity
*	`begin()` and `end()` must be O(1) constant-time, as the standard requires. Otherwise the container fails for being 20 times slower than the standard. (this is a concerning case for tree-based containers where `begin()` and `end()` are tempting to be O(log<sub>2</sub><sup>n</sup>))
### Assignment Operator
*	Should check if the passed reference is of the object itself; return in that case.
### Error Handling
*	Interactions with invalid iterators are the user's responsibility. No protection is required for that.
## Vector
### Exceptions
*	All versions of `at()` throw `std::out_of_range` if out of bounds.
*	`reserve()` _and any internal allocation_ throw `std::length_error` if n > max_size.
### Construction
*	Note that the constructors are not guarded with a try-catch block; if construction fails, the allocated memory stays with the requested capacity to grant amortization; hence size update should happen after construction.
### Insert
*	A copy of inserted element has to be created in case inserted element is to the right of the position, in the same container, because shifting elements will invalidate the reference.
*	There should be tag dispatching in range modificators in case iterator is of type `InputIterator` -- one should take individual approach for this case (try `std::istream_iterator` to check for that; if the iterator is exhausted, the behavior will be undefined).
## Deque
### Implementation
*	Should NOT adapt a list, because must provide random-access O(1) constant-time iterators!
### Chunk Size
*	To grant amortization, should depend on the size of the template parameter: the smaller the value type, the bigger are chunks.
### Allocator
*	Should be rebound to the map (double pointer) type when pointers are created.
### Insert
*	A copy of inserted element has to be created in case inserted element is to the right of the position, in the same container, because shifting elements will invalidate the reference.
*	There should be tag dispatching in range modificators in case iterator is of type `InputIterator` -- one should take individual approach for this case (try `std::istream_iterator` to check for that; if the iterator is exhausted, the behavior will be undefined).
## Tree-Based Containers and List
### Allocator
*	Should be rebound to the node type. (for map, should be rebound to the value type, i.e. pair, first)
