#include <iterator>
#include <memory>
#include <type_traits>
#include <iostream>

template <class Iterator, class Container>
class	normal_iterator
{
	protected:
		Iterator	_base;
	public:
		// template<typename Iter>
		// normal_iterator(const normal_iterator<Iter,
		// typename std::enable_if<(std::is_same<Iter, typename Container::pointer>::value), Container>::type> &copy) : _base(copy.base()) { }
		
		explicit normal_iterator(const Iterator &_base) : _base(_base) { }
		
		const Iterator	&base() const { return (this->_base); }
};

template <class Iterator, class Container>
bool	operator!=(const normal_iterator<Iterator, Container> &lhs,
					const normal_iterator<Iterator, Container> &rhs)
{
	return (lhs.base() != rhs.base());
}

template <class T, class Alloc = std::allocator<T> >
class	vector
{
	public:
		typedef T										value_type;
		typedef Alloc									allocator_type;
		typedef typename allocator_type::pointer		pointer;
		typedef typename allocator_type::const_pointer	const_pointer;
		typedef normal_iterator<pointer, vector>		iterator;
		typedef normal_iterator<const_pointer, vector>	const_iterator;

		iterator		begin() { return (iterator(this->_data)); }
		const_iterator	begin() const { return (const_iterator(this->_data)); }
		iterator		end() { return (iterator(this->_data)); }
		const_iterator	end() const { return (const_iterator(this->_data)); }
		iterator		erase(iterator first, iterator last)
		{
			if (last != end())
				// std::copy(last, end(), first);
				std::cout << "clear()" << std::endl;
			return (first);
		}
		~vector() { erase(begin(), end()); }
	private:
		pointer			_data;
};

class A {};

int	main()
{
	vector<A>	hi;
}