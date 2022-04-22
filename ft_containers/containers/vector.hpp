#if !defined(VECTOR_HPP)
#define VECTOR_HPP

#include "../utils/utils.hpp"
#include "../iterators/random_access_iterator.hpp"
#include "../iterators/reverse_iterator.hpp"

namespace ft
{
	template <class T, class Alloc = std::allocator<T> >
	class vector
	{
	public:
		//////////////////////////////////////////////////////////////////////////////
		// TYPES
		//////////////////////////////////////////////////////////////////////////////
		typedef T value_type;
		typedef Alloc allocator_type;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
		typedef ft::random_access_iterator<value_type> iterator;
		typedef ft::random_access_iterator<const value_type> const_iterator;
		typedef ft::reverse_iterator<iterator> reverse_iterator;
		typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
		typedef ptrdiff_t difference_type;
		typedef size_t size_type;

		//////////////////////////////////////////////////////////////////////////////
		// CONSTRUCTORS / DESTRUCTORS
		//////////////////////////////////////////////////////////////////////////////
		explicit vector(const allocator_type &alloc = allocator_type()) : _array(NULL), _alloc(alloc), _size(0), _capacity(0) {}
		explicit vector(size_type n, const value_type &val = value_type(),
						const allocator_type &alloc = allocator_type()) : _alloc(alloc), _size(n), _capacity(n)
		{
			try
			{
				_array = _alloc.allocate(_size);
			}
			catch (std::bad_alloc &e)
			{
				throw e;
			}
			for (size_type i(0); i < _size; i++)
				_alloc.construct(_array + i, val);
		}
		template <class InputIterator>
		vector(InputIterator first, InputIterator last,
			   const allocator_type &alloc = allocator_type(),
			   typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type = InputIterator())
		{
			difference_type n = std::distance(first, last);
			_alloc = alloc;
			_size = n;
			_capacity = n;
			try
			{
				_array = _alloc.allocate(_size);
			}
			catch (std::bad_alloc &e)
			{
				throw e;
			}
			for (size_type i(0); first != last; first++, i++)
				_alloc.construct(_array + i, *first);
		}
		vector(const vector &x)
		{
			_alloc = x.get_allocator();
			_size = x.size();
			_capacity = _size;
			try
			{
				if (_capacity)
					_array = _alloc.allocate(_capacity);
			}
			catch (std::bad_alloc &e)
			{
				throw e;
			}
			for (size_type i(0); i < _size; i++)
				_alloc.construct(_array + i, x[i]);
		}
		~vector()
		{
			this->clear();
			if (_capacity)
				_alloc.deallocate(_array, _capacity);
		}

		//////////////////////////////////////////////////////////////////////////////
		// ASSIGNEMENT OPERATOR
		//////////////////////////////////////////////////////////////////////////////
		vector &operator=(const vector &x)
		{
			clear();
			if (_capacity)
				_alloc.deallocate(_array, _capacity);
			_alloc = x.get_allocator();
			_size = x.size();
			_capacity = x.size();
			try
			{
				if (_capacity)
					_array = _alloc.allocate(_capacity);
			}
			catch (std::bad_alloc &e)
			{
				throw e;
			}
			for (size_type i(0); i < _size; i++)
				_alloc.construct(_array + i, x[i]);
			return *this;
		}

		//////////////////////////////////////////////////////////////////////////////
		// ITERATORS
		//////////////////////////////////////////////////////////////////////////////
		iterator begin() { return (iterator(_array)); };
		const_iterator begin() const { return (const_iterator(_array)); }
		iterator end() { return (iterator(_array + _size)); }
		const_iterator end() const { return (const_iterator(_array + _size)); }
		reverse_iterator rbegin() { return reverse_iterator(end()); }
		const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }
		reverse_iterator rend() { return reverse_iterator(begin()); }
		const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }

		//////////////////////////////////////////////////////////////////////////////
		// CAPACITY
		//////////////////////////////////////////////////////////////////////////////
		size_type size() const { return _size; }
		size_type max_size() const { return (_alloc.max_size()); }
		void resize(size_type n, value_type val = value_type())
		{
			if (n < _size)
			{
				for (size_type i(n); i < _size; i++)
					_alloc.destroy(_array + i);
			}
			try
			{
				if (n > _size)
				{
					this->reserve(n);
					for (size_type i(_size); i < n; i++)
						_alloc.construct(_array + i, val);
				}
			}
			catch (std::length_error &e)
			{
				throw std::length_error("vector");
			}
			_size = n;
		}
		size_type capacity() const { return (_capacity); }
		bool empty() const { return (!_size); }
		void reserve(size_type n)
		{
			if (n > this->max_size())
				throw std::length_error("allocator<T>::allocate(size_t n) 'n' exceeds maximum supported size");
			else if (n > _capacity)
			{
				pointer temp;
				try
				{
					temp = _alloc.allocate(n);
				}
				catch (std::bad_alloc &e)
				{
					throw e;
				}
				for (size_type i(0); i < _size; i++)
				{
					_alloc.construct(temp + i, *(_array + i));
					_alloc.destroy(_array + i);
				}
				if (_capacity)
					_alloc.deallocate(_array, _capacity);
				_array = temp;
				_capacity = n;
			}
		}

		//////////////////////////////////////////////////////////////////////////////
		// ELEMENT ACCESS
		//////////////////////////////////////////////////////////////////////////////
		reference operator[](size_type n) { return (*(_array + n)); }
		const_reference operator[](size_type n) const { return (*(_array + n)); }
		reference at(size_type n)
		{
			if (n < 0 || n >= _size)
				throw std::out_of_range("vector");
			return (_array[n]);
		}
		const_reference at(size_type n) const
		{
			if (n < 0 || n >= _size)
				throw std::out_of_range("vector");
			return (_array[n]);
		}
		reference front() { return (_array[0]); }
		const_reference front() const { return (_array[0]); }
		reference back() { return (*(_array + (_size - 1))); }
		const_reference back() const { return (*(_array + (_size - 1))); }

		//////////////////////////////////////////////////////////////////////////////
		// MODIFIERS
		//////////////////////////////////////////////////////////////////////////////
		template <class InputIterator>
		void assign(InputIterator first, InputIterator last,
					typename std::enable_if<!std::is_integral<InputIterator>::value, InputIterator>::type = InputIterator())
		{
			difference_type n = std::distance(first, last);

			clear();
			reserve(n);
			for (size_type i(0); first != last; first++)
			{
				_alloc.construct(_array + i, *first);
				i++;
			}
			_size = n;
		}
		void assign(size_type n, const value_type &val)
		{
			clear();
			resize(n, val);
		}
		void push_back(const value_type &val)
		{
			if (!_capacity)
				reserve(1);
			else if (_capacity < _size + 1)
				reserve(_capacity * 2);
			_alloc.construct(_array + _size, val);
			_size++;
		}
		void pop_back()
		{
			if (_size)
			{
				_size--;
				_alloc.destroy(_array + _size);
			}
		}
		iterator insert(iterator position, const value_type &val)
		{
			difference_type dist = std::distance(this->begin(), position);

			if (!_capacity)
				this->reserve(1);
			else if (_size + 1 > _capacity)
				this->reserve(_capacity * 2);
			difference_type i(_size);
			for (; i > dist; i--)
				_array[i] = _array[i - 1];
			_array[i] = val;
			_size++;
			return iterator(_array + dist);
		}
		void insert(iterator position, size_type n, const value_type &val)
		{
			difference_type dist = std::distance(this->begin(), position);

			if (n == 0)
				return;
			if (_size + n > _capacity)
			{
				if (_size + n <= _capacity * 2)
					reserve(_capacity * 2);
				else
					reserve(_size + n);
			}
			if (_size)
			{
				for (int i = _size - 1; i >= dist; i--)
					_alloc.construct(_array + i + n, _array[i]);
			}
			for (size_type i = dist; i < dist + n; i++)
				_alloc.construct(_array + i, val);
			_size += n;
		}
		template <class InputIterator>
		void insert(iterator position, InputIterator first, InputIterator last,
					typename std::enable_if<!std::is_integral<InputIterator>::value, InputIterator>::type = InputIterator())
		{
			difference_type dist = std::distance(begin(), position);
			difference_type n = std::distance(first, last);

			if (n == 0)
				return;
			if (_size + n > _capacity)
			{
				if (_size + n <= _capacity * 2)
					reserve(_capacity * 2);
				else
					reserve(_size + n);
			}
			if (_size)
			{
				for (int i = _size - 1; i >= dist; i--)
					_alloc.construct(_array + i + n, _array[i]);
			}
			for (size_type i = dist; first != last; first++, i++)
				_alloc.construct(_array + i, *first);
			_size += n;
		}
		iterator erase(iterator position)
		{
			difference_type n = std::distance(this->begin(), position);

			for (size_type i(n); i < _size - 1; i++)
				_array[i] = _array[i + 1];
			_size--;
			_alloc.destroy(_array + _size);
			return (iterator(_array + n));
		}
		iterator erase(iterator first, iterator last)
		{
			difference_type f_dist = std::distance(this->begin(), first);
			difference_type s_dist = std::distance(first, last);

			size_type i(f_dist);
			for (size_type j(f_dist + s_dist); j < _size; i++, j++)
				_array[i] = _array[j];
			for (; i < _size; i++)
				_alloc.destroy(_array + i);
			_size -= s_dist;
			return (iterator(_array + f_dist));
		}
		void swap(vector &x)
		{
			allocator_type _alloc_temp = x._alloc;
			pointer _array_temp = x._array;
			size_type _size_temp = x._size;
			size_type _capacity_temp = x._capacity;

			x._alloc = _alloc;
			x._array = _array;
			x._size = _size;
			x._capacity = _capacity;

			_alloc = _alloc_temp;
			_array = _array_temp;
			_size = _size_temp;
			_capacity = _capacity_temp;
		}
		void clear()
		{
			for (size_type i(0); i < _size; i++)
				_alloc.destroy(_array + i);
			_size = 0;
		}

		//////////////////////////////////////////////////////////////////////////////
		// ALLOCATOR
		//////////////////////////////////////////////////////////////////////////////
		allocator_type get_allocator() const { return (_alloc); }

	private:
		//////////////////////////////////////////////////////////////////////////////
		// UNDERLYING DATA STRUCTURE
		//////////////////////////////////////////////////////////////////////////////
		pointer _array;

		//////////////////////////////////////////////////////////////////////////////
		// ATTRIBUTES
		//////////////////////////////////////////////////////////////////////////////
		allocator_type _alloc;
		size_type _size;
		size_type _capacity;
	};

	//////////////////////////////////////////////////////////////////////////////
	// NON-MEMBER FUNCTIONS
	//////////////////////////////////////////////////////////////////////////////
	template <class T, class Alloc>
	bool operator==(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin());
	}
	template <class T, class Alloc>
	bool operator!=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return !(lhs == rhs);
	}
	template <class T, class Alloc>
	bool operator<(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}
	template <class T, class Alloc>
	bool operator<=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return !(rhs < lhs);
	}
	template <class T, class Alloc>
	bool operator>(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return rhs < lhs;
	}
	template <class T, class Alloc>
	bool operator>=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return !(lhs < rhs);
	}

	template <class T, class Alloc>
	void swap(vector<T, Alloc> &lhs, vector<T, Alloc> &rhs)
	{
		lhs.swap(rhs);
	}

} // namespace ft

#endif // VECTOR_HPP
