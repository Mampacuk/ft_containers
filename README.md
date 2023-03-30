# ft_containers
School 42's project "ft_containers" implementation.
## Content
- [x] vector
- [x] list
- [x] map
- [x] stack
- [x] queue
- [x] deque
- [x] set
- [x] multiset
- [x] multimap
## Notes
*	Passes `mli`'s [tester](https://github.com/mli42/containers_test) with flying colors. (except for a relational_ope test that complains about my own `ft::swap()`)
*   Passes `mleblanc`'s [tester](https://github.com/Mikastiv/ft_containers-terminator) with flying colors, including the benchmarks.
*	Check the Annihilation List at the root repository for some tricky cases and remarks so you can fail as many people as possible during the evaluation process!
## Credits
*	"Introduction to Algorithms," aka CLRS, or the Bible of Algorithms, 3rd edition, for the red-black tree implementation, Chapter 13.
*	"Data Structures & Algorithms in Java," 6th edition, for `rbtree::lower_bound()` and `rbtree::upper_bound()`, Chapter 11.1.
*	[libstdc++-v3](https://github.com/gcc-mirror/gcc/tree/master/libstdc%2B%2B-v3/include/bits) official STL implementation, for deque, and other containers' memory allocation and template resolution processes.
