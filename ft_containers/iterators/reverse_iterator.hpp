#if !defined(REVERSE_ITERATOR_HPP)
#define REVERSE_ITERATOR_HPP

#include "../utils/utils.hpp"

namespace ft
{
	template <class Iterator>
	class reverse_iterator
	{
	public:
		//////////////////////////////////////////////////////////////////////////////
		// TYPES
		//////////////////////////////////////////////////////////////////////////////
		typedef Iterator iterator_type;
		typedef typename iterator_traits<Iterator>::iterator_category iterator_category;
		typedef typename iterator_traits<Iterator>::value_type value_type;
		typedef typename iterator_traits<Iterator>::difference_type difference_type;
		typedef typename iterator_traits<Iterator>::pointer pointer;
		typedef typename iterator_traits<Iterator>::reference reference;

		//////////////////////////////////////////////////////////////////////////////
		// CONSTRUCTORS / DESTRUCTORS
		//////////////////////////////////////////////////////////////////////////////
		reverse_iterator() : _it(iterator_type()) {}
		explicit reverse_iterator(iterator_type it) : _it(it) {}
		template <class Iter>
		reverse_iterator(const reverse_iterator<Iter> &rev_it) : _it(rev_it.base()) {}

		//////////////////////////////////////////////////////////////////////////////
		// ASSIGNMENT OPERATOR
		//////////////////////////////////////////////////////////////////////////////
		reverse_iterator &operator=(const reverse_iterator &src)
		{
			_it = src.base();
			return *this;
		}

		//////////////////////////////////////////////////////////////////////////////
		// INCREMENT / DECREMENT
		//////////////////////////////////////////////////////////////////////////////
		reverse_iterator &operator++()
		{
			--_it;
			return *this;
		}
		reverse_iterator operator++(int)
		{
			reverse_iterator temp = *this;
			++(*this);
			return temp;
		}
		reverse_iterator &operator--()
		{
			++_it;
			return *this;
		}
		reverse_iterator operator--(int)
		{
			reverse_iterator temp = *this;
			--(*this);
			return temp;
		}

		//////////////////////////////////////////////////////////////////////////////
		// DEREFERENCE
		//////////////////////////////////////////////////////////////////////////////
		reference operator*() const
		{
			iterator_type temp = _it;
			return (*(--temp));
		}
		pointer operator->() const { return &(operator*()); }
		reference operator[](difference_type n) const { return (base()[-n - 1]); }

		//////////////////////////////////////////////////////////////////////////////
		// ARITHMETIC
		//////////////////////////////////////////////////////////////////////////////
		reverse_iterator operator+(difference_type n) const
		{
			return (reverse_iterator(_it - n));
		}
		reverse_iterator operator-(difference_type n) const
		{
			return (reverse_iterator(_it + n));
		}
		reverse_iterator &operator+=(difference_type n)
		{
			_it -= n;
			return (*this);
		}
		reverse_iterator &operator-=(difference_type n)
		{
			_it += n;
			return (*this);
		}

		//////////////////////////////////////////////////////////////////////////////
		// UTILS
		//////////////////////////////////////////////////////////////////////////////
		iterator_type base() const { return (_it); }
		operator reverse_iterator<const Iterator>()
		{
			return reverse_iterator<const Iterator>(this->base());
		}

	private:
		//////////////////////////////////////////////////////////////////////////////
		// ATTRIBUTES
		//////////////////////////////////////////////////////////////////////////////
		iterator_type _it;
	};

	//////////////////////////////////////////////////////////////////////////////
	// RELATIONAL OPERATORS
	//////////////////////////////////////////////////////////////////////////////
	template <class Iterator>
	bool operator==(const reverse_iterator<Iterator> &lhs,
					const reverse_iterator<Iterator> &rhs)
	{
		return (lhs.base() == rhs.base());
	}

	template <class Iterator>
	bool operator!=(const reverse_iterator<Iterator> &lhs,
					const reverse_iterator<Iterator> &rhs)
	{
		return (lhs.base() != rhs.base());
	}

	template <class Iterator>
	bool operator<(const reverse_iterator<Iterator> &lhs,
				   const reverse_iterator<Iterator> &rhs)
	{
		return (lhs.base() > rhs.base());
	}

	template <class Iterator>
	bool operator<=(const reverse_iterator<Iterator> &lhs,
					const reverse_iterator<Iterator> &rhs)
	{
		return (lhs.base() >= rhs.base());
	}

	template <class Iterator>
	bool operator>(const reverse_iterator<Iterator> &lhs,
				   const reverse_iterator<Iterator> &rhs)
	{
		return (lhs.base() < rhs.base());
	}

	template <class Iterator>
	bool operator>=(const reverse_iterator<Iterator> &lhs,
					const reverse_iterator<Iterator> &rhs)
	{
		return (lhs.base() <= rhs.base());
	}

	//////////////////////////////////////////////////////////////////////////////
	// ARITHMETIC
	//////////////////////////////////////////////////////////////////////////////
	template <class Iterator>
	reverse_iterator<Iterator> operator+(
		typename reverse_iterator<Iterator>::difference_type n,
		const reverse_iterator<Iterator> &rev_it)
	{
		return reverse_iterator<Iterator>(rev_it + n);
	}
	template <class Iterator>
	typename reverse_iterator<Iterator>::difference_type operator-(
		const reverse_iterator<Iterator> &lhs,
		const reverse_iterator<Iterator> &rhs)
	{
		return rhs.base() - lhs.base();
	}

} // namespace ft

#endif // REVERSE_ITERATOR_HPP
