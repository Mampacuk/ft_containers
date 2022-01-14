# include <cstddef>
# include <memory>
# include "../algorithm.hpp"
# include "../memory.hpp"
# include <iterator>

namespace ft
{
		// iterator_traits
	template <class Iter>
	struct	iterator_traits
	{
		typedef typename Iter::difference_type		difference_type;
		typedef typename Iter::value_type			value_type;
		typedef typename Iter::pointer				pointer;
		typedef typename Iter::reference			reference;
		typedef typename Iter::iterator_category	iterator_category;
	};

	template <class T>
	struct	iterator_traits<T*>
	{
		typedef std::ptrdiff_t					difference_type;
		typedef T								value_type;
		typedef T*								pointer;
		typedef T&								reference;
		typedef std::random_access_iterator_tag	iterator_category;
	};

	template <class T>
	struct	iterator_traits<const T*>
	{
		typedef std::ptrdiff_t					difference_type;
		typedef T								value_type;
		typedef const T*						pointer;
		typedef const T&						reference;
		typedef std::random_access_iterator_tag	iterator_category;
	};

	template <class Iterator, class Container> class normal_iterator;
	template <class T, class Alloc = std::allocator<T> > class vector;
}

template <class Iterator, class Container>
class	ft::normal_iterator
{
	protected:
		Iterator	_base;
		typedef ft::iterator_traits<Iterator>			traits_type;
	public:
		typedef Iterator								iterator_type;
		typedef typename traits_type::iterator_category	iterator_category;
		typedef typename traits_type::value_type		value_type;
		typedef typename traits_type::difference_type	difference_type;
		typedef typename traits_type::reference			reference;
		typedef typename traits_type::pointer			pointer;

		explicit normal_iterator(const Iterator &_base) : _base(_base) { }
		const Iterator	&base() const { return (this->_base); }
		normal_iterator &operator++() { this->_base++; return (*this); }
		normal_iterator operator++(int) { normal_iterator temp = *this; this->_base++; return (temp);}
		reference operator*() const { return (*this->_base); }
};

template <class Iterator, class Container>
bool	operator!=(const ft::normal_iterator<Iterator, Container> &lhs,
					const ft::normal_iterator<Iterator, Container> &rhs)
{
	return (lhs.base() != rhs.base());
}

template <class Iterator, class Container>
typename ft::normal_iterator<Iterator, Container>::difference_type operator-(
	const ft::normal_iterator<Iterator, Container> &lhs,
	const ft::normal_iterator<Iterator, Container> &rhs)
{
	return (lhs.base() - rhs.base());
}

template <class T, class Alloc>
class	ft::vector
{
	public:
		typedef T											value_type;
		typedef Alloc										allocator_type;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;
		typedef ptrdiff_t									difference_type;
		typedef size_t										size_type;
		typedef ft::normal_iterator<pointer, vector>		iterator;
		typedef ft::normal_iterator<const_pointer, vector>	const_iterator;

		~vector();

		iterator				begin();
		iterator				end();

		iterator	erase(iterator position);
		iterator	erase(iterator first, iterator last);
		void		clear();
	protected:
		void			deallocate_a(pointer p, size_type n);
	private:
		allocator_type	_alloc;
		pointer			_data;
		size_type		_capacity;
		size_type		_size;
};

template <class T, class Alloc>
ft::vector<T, Alloc>::~vector()
{
	clear();
	deallocate_a(this->_data, this->_capacity);
}

template <class T, class Alloc>
typename ft::vector<T, Alloc>::iterator ft::vector<T, Alloc>::begin()
{
	return (iterator(this->_data));
}

template <class T, class Alloc>
typename ft::vector<T, Alloc>::iterator ft::vector<T, Alloc>::end()
{
	return (iterator(this->_data + this->_size));
}

template <class T, class Alloc>
typename ft::vector<T, Alloc>::iterator	ft::vector<T, Alloc>::erase(iterator position)
{
	if (position + 1 != end())
		ft::copy(position + 1, end(), position);
	this->_size--;
	this->_alloc.destroy(this->_data + this->_size);
	return (position);
}

template <class T, class Alloc>
typename ft::vector<T, Alloc>::iterator	ft::vector<T, Alloc>::erase(iterator first, iterator last)
{
	if (last != end())
		ft::copy(last, end(), first);
	ft::destroy_a(first.base() + (end() - last), this->_data + this->_size, this->_alloc);
	this->_size -= last - first;
	return (first);
}

template <class T, class Alloc>
void	ft::vector<T, Alloc>::clear()
{
	erase(begin(), end());
}

template <class T, class Alloc>
void	ft::vector<T, Alloc>::deallocate_a(pointer p, size_type n)
{
	if (p)
		this->_alloc.deallocate(p, n);
}

int	main()
{
	ft::vector<float>	hi;
}
