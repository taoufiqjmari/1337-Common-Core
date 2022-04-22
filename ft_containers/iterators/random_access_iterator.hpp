#if !defined(RANDOM_ACCESS_ITERATOR_HPP)
#define RANDOM_ACCESS_ITERATOR_HPP

#include "../utils/utils.hpp"

namespace ft
{
	template <class T>
	class random_access_iterator : public ft::iterator<std::random_access_iterator_tag, T>
	{
	public:
		//////////////////////////////////////////////////////////////////////////////
		// TYPES
		//////////////////////////////////////////////////////////////////////////////
		typedef typename ft::iterator<std::random_access_iterator_tag, T>::iterator_category iterator_category;
		typedef typename ft::iterator<std::random_access_iterator_tag, T>::value_type value_type;
		typedef typename ft::iterator<std::random_access_iterator_tag, T>::difference_type difference_type;
		typedef typename ft::iterator<std::random_access_iterator_tag, T>::pointer pointer;
		typedef typename ft::iterator<std::random_access_iterator_tag, T>::reference reference;

		//////////////////////////////////////////////////////////////////////////////
		// CONSTRUCTORS / DESTRUCTORS
		//////////////////////////////////////////////////////////////////////////////
		random_access_iterator() { _it = NULL; }
		random_access_iterator(pointer ptr) : _it(ptr) {}
		random_access_iterator(const random_access_iterator &src) { *this = src; }
		~random_access_iterator() {}

		//////////////////////////////////////////////////////////////////////////////
		// ASSIGNEMENT OPERATOR
		//////////////////////////////////////////////////////////////////////////////
		random_access_iterator &operator=(const random_access_iterator &src)
		{
			_it = src._it;
			return (*this);
		}

		//////////////////////////////////////////////////////////////////////////////
		// INCREMENT / DECREMENT
		//////////////////////////////////////////////////////////////////////////////
		random_access_iterator &operator++()
		{
			_it++;
			return (*this);
		}
		random_access_iterator operator++(int)
		{
			random_access_iterator tmp = *this;
			_it++;
			return (tmp);
		}
		random_access_iterator &operator--()
		{
			_it--;
			return (*this);
		}
		random_access_iterator operator--(int)
		{
			random_access_iterator tmp = *this;
			_it--;
			return (tmp);
		}

		//////////////////////////////////////////////////////////////////////////////
		// DEREFERENCE
		//////////////////////////////////////////////////////////////////////////////
		reference operator*() const { return (*_it); }
		pointer operator->() const { return _it; }
		reference operator[](difference_type n)
		{
			return (*(_it + n));
		}

		//////////////////////////////////////////////////////////////////////////////
		// ARITHMETIC
		//////////////////////////////////////////////////////////////////////////////
		random_access_iterator operator+(difference_type n) const
		{
			return (_it + n);
		}
		random_access_iterator operator-(difference_type n) const
		{
			return (_it - n);
		}
		difference_type operator-(const random_access_iterator &rhs)
		{
			return _it - rhs._it;
		}
		random_access_iterator &operator+=(difference_type n)
		{
			_it += n;
			return (*this);
		}
		random_access_iterator &operator-=(difference_type n)
		{
			_it -= n;
			return (*this);
		}

		//////////////////////////////////////////////////////////////////////////////
		// UTILS
		//////////////////////////////////////////////////////////////////////////////
		pointer base() const { return (_it); }
		operator random_access_iterator<const T>()
		{
			return random_access_iterator<const T>(this->base());
		}

	private:
		//////////////////////////////////////////////////////////////////////////////
		// ATTRIBUTES
		//////////////////////////////////////////////////////////////////////////////
		pointer _it;
	};

	//////////////////////////////////////////////////////////////////////////////
	// EQUALITY
	//////////////////////////////////////////////////////////////////////////////
	template <class T>
	bool operator==(const random_access_iterator<T> &lhs, const random_access_iterator<T> &rhs)
	{
		return (lhs.base() == rhs.base());
	}
	template <class T>
	bool operator!=(const random_access_iterator<T> &lhs, const random_access_iterator<T> &rhs)
	{
		return (lhs.base() != rhs.base());
	}

	//////////////////////////////////////////////////////////////////////////////
	// ARITHMETIC
	//////////////////////////////////////////////////////////////////////////////
	template <class T>
	random_access_iterator<T> operator+(int n, const random_access_iterator<T> &rhs)
	{
		return random_access_iterator<T>(rhs + n);
	}

	//////////////////////////////////////////////////////////////////////////////
	// RELATIONAL OPERATORS
	//////////////////////////////////////////////////////////////////////////////
	template <class T>
	bool operator<(const random_access_iterator<T> &lhs, const random_access_iterator<T> &rhs)
	{
		return (lhs.base() < rhs.base());
	}
	template <class T>
	bool operator>(const random_access_iterator<T> &lhs, const random_access_iterator<T> &rhs)
	{
		return rhs.base() < lhs.base();
	}
	template <class T>
	bool operator<=(const random_access_iterator<T> &lhs, const random_access_iterator<T> &rhs)
	{
		return (lhs.base() <= rhs.base());
	}
	template <class T>
	bool operator>=(const random_access_iterator<T> &lhs, const random_access_iterator<T> &rhs)
	{
		return !ft::operator<(lhs, rhs);
	}

} // namespace ft

#endif // RANDOM_ACCESS_ITERATOR_HPP
