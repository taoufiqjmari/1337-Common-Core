#if !defined(MAP_HPP)
#define MAP_HPP

#include "../containers/vector.hpp"
#include "../utils/utils.hpp"
#include "../utils/avl_tree.hpp"
#include "../iterators/bidirectional_iterator.hpp"
#include "../iterators/reverse_iterator.hpp"

namespace ft
{
	template <class Key, class T, class Compare = std::less<Key>,
			  class Alloc = std::allocator<ft::pair<const Key, T> > >
	class map
	{
	public:
		//////////////////////////////////////////////////////////////////////////////
		// TYPES
		//////////////////////////////////////////////////////////////////////////////
		typedef Key key_type;
		typedef T mapped_type;
		typedef ft::pair<const key_type, mapped_type> value_type;
		typedef Compare key_compare;
		typedef class value_compare : std::binary_function<value_type, value_type, bool>
		{ // in C++98, it is required to inherit binary_function<value_type,value_type,bool>s
			friend class map;

		protected:
			Compare comp;
			value_compare(Compare c) : comp(c) {}

		public:
			typedef bool result_type;
			typedef value_type first_argument_type;
			typedef value_type second_argument_type;
			bool operator()(const value_type &x, const value_type &y) const
			{
				return comp(x.first, y.first);
			}
		} value_compare;
		typedef Alloc allocator_type;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
		typedef ft::bidirectional_iterator<value_type> iterator;
		typedef ft::bidirectional_iterator<const value_type> const_iterator;
		typedef ft::reverse_iterator<iterator> reverse_iterator;
		typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
		typedef typename iterator_traits<iterator>::difference_type difference_type;
		typedef size_t size_type;

		//////////////////////////////////////////////////////////////////////////////
		// CONSTRUCTORS / DESTRUCTORS
		//////////////////////////////////////////////////////////////////////////////
		explicit map(const key_compare &comp = key_compare(),
					 const allocator_type &alloc = allocator_type()) : _alloc(alloc), _comp(comp) {}
		template <class InputIterator>
		map(InputIterator first, InputIterator last, const key_compare &comp = key_compare(),
			const allocator_type &alloc = allocator_type()) : _alloc(alloc), _comp(comp) { insert(first, last); }
		map(const map &x) : _alloc(x._alloc), _comp(x._comp) { insert(x.begin(), x.end()); }
		~map() { clear(); }

		//////////////////////////////////////////////////////////////////////////////
		// OPERATORS
		//////////////////////////////////////////////////////////////////////////////
		map &operator=(const map &x)
		{
			clear();
			_alloc = x._alloc;
			_comp = x._comp;
			try
			{
				Node<value_type> *tmp = _node_alloc.allocate(1);
				if (_tree.get_end())
					_node_alloc.deallocate(_tree.get_end(), 1);
				_tree.set_end(tmp);
			}
			catch (std::bad_alloc &e)
			{
				throw e;
			}
			insert(x.begin(), x.end());
			return *this;
		}

		//////////////////////////////////////////////////////////////////////////////
		// ITERATORS
		//////////////////////////////////////////////////////////////////////////////
		iterator begin() { return _tree.begin(); }
		const_iterator begin() const { return _tree.begin(); }
		iterator end() { return _tree.end(); }
		const_iterator end() const { return _tree.end(); }
		reverse_iterator rbegin() { return _tree.rbegin(); }
		const_reverse_iterator rbegin() const { return _tree.rbegin(); }
		reverse_iterator rend() { return _tree.rend(); }
		const_reverse_iterator rend() const { return _tree.rend(); }

		//////////////////////////////////////////////////////////////////////////////
		// CAPACITY
		//////////////////////////////////////////////////////////////////////////////
		bool empty() const { return _tree.empty(); }
		size_type size() const { return _tree.size(); }
		size_type max_size() const { return _tree.max_size(); }

		//////////////////////////////////////////////////////////////////////////////
		// ELEMENT ACCESS
		//////////////////////////////////////////////////////////////////////////////
		mapped_type &operator[](const key_type &k)
		{
			iterator tmp = find(k);
			if (tmp == end())
				tmp = insert(value_type(k, mapped_type())).first;
			return tmp->second;
		}

		//////////////////////////////////////////////////////////////////////////////
		// MODIFIERS
		//////////////////////////////////////////////////////////////////////////////
		pair<iterator, bool> insert(const value_type &val)
		{
			bool inserted(true);
			Node<value_type> *tmp = _tree.insert_node(_tree.get_root(), val, inserted);
			_tree.set_root(tmp);
			return pair<iterator, bool>(iterator(_tree.get_root(), _tree.get_end(), _tree.find_node(val.first)), inserted);
		}
		iterator insert(iterator position, const value_type &val)
		{
			(void)position;
			return insert(val).first;
		}
		template <class InputIterator>
		void insert(InputIterator first, InputIterator last)
		{
			for (; first != last; first++)
				insert(*first);
		}
		void erase(iterator position)
		{
			Node<value_type> *tmp = _tree.erase_node(_tree.get_root(), position.base()->data.first);
			_tree.set_root(tmp);
		}
		size_type erase(const key_type &k)
		{
			if (_tree.count(k) == 0)
				return 0;
			erase(find(k));
			return 1;
		}
		void erase(iterator first, iterator last)
		{
			ft::vector<key_type> keysToErase;
			for (; first != last; first++)
				keysToErase.push_back(first.base()->data.first);
			for (size_type i(0); i < keysToErase.size(); i++)
				erase(keysToErase[i]);
		}
		void swap(map &x)
		{
			std::swap(_alloc, x._alloc);
			std::swap(_comp, x._comp);
			_tree.swap(x._tree);
		}
		void clear() { erase(begin(), end()); }

		//////////////////////////////////////////////////////////////////////////////
		// OBSERVERS
		//////////////////////////////////////////////////////////////////////////////
		key_compare key_comp() const { return key_compare(); }
		value_compare value_comp() const { return value_compare(key_comp()); }

		//////////////////////////////////////////////////////////////////////////////
		// OPERATIONS
		//////////////////////////////////////////////////////////////////////////////
		iterator find(const key_type &k) { return _tree.find(k); }
		const_iterator find(const key_type &k) const { return _tree.find(k); }
		size_type count(const key_type &k) const { return _tree.count(k); }
		iterator lower_bound(const key_type &k) { return _tree.lower_bound(k); }
		const_iterator lower_bound(const key_type &k) const { return _tree.lower_bound(k); }
		iterator upper_bound(const key_type &k) { return _tree.upper_bound(k); }
		const_iterator upper_bound(const key_type &k) const { return _tree.upper_bound(k); }
		pair<const_iterator, const_iterator> equal_range(const key_type &k) const { return _tree.equal_range(k); }
		pair<iterator, iterator> equal_range(const key_type &k) { return _tree.equal_range(k); }

		//////////////////////////////////////////////////////////////////////////////
		// ALLOCATOR
		//////////////////////////////////////////////////////////////////////////////
		allocator_type get_allocator() const { return _alloc; }

		//////////////////////////////////////////////////////////////////////////////
		// DEBUG
		//////////////////////////////////////////////////////////////////////////////
		// void print() const { _tree.print(_tree.get_root()); }

	private:
		//////////////////////////////////////////////////////////////////////////////
		// UNDERLYING DATA STRUCTURE
		//////////////////////////////////////////////////////////////////////////////
		typedef ft::AVLTree<value_type, allocator_type, key_compare> tree_type;
		typedef typename allocator_type::template rebind<Node<value_type> >::other node_allocator;

		//////////////////////////////////////////////////////////////////////////////
		// ATTRIBUTES
		//////////////////////////////////////////////////////////////////////////////
		allocator_type _alloc;
		node_allocator _node_alloc;
		key_compare _comp;
		tree_type _tree;
	};

	//////////////////////////////////////////////////////////////////////////////
	// NON-MEMBER FUNCTIONS
	//////////////////////////////////////////////////////////////////////////////
	template <class Key, class T, class Compare, class Alloc>
	bool operator==(const ft::map<Key, T, Compare, Alloc> &lhs,
					const ft::map<Key, T, Compare, Alloc> &rhs)
	{
		return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin());
	}
	template <class Key, class T, class Compare, class Alloc>
	bool operator!=(const ft::map<Key, T, Compare, Alloc> &lhs,
					const ft::map<Key, T, Compare, Alloc> &rhs)
	{
		return !(lhs == rhs);
	}
	template <class Key, class T, class Compare, class Alloc>
	bool operator<(const ft::map<Key, T, Compare, Alloc> &lhs,
				   const ft::map<Key, T, Compare, Alloc> &rhs)
	{
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}
	template <class Key, class T, class Compare, class Alloc>
	bool operator<=(const ft::map<Key, T, Compare, Alloc> &lhs,
					const ft::map<Key, T, Compare, Alloc> &rhs)
	{
		return !(rhs < lhs);
	}
	template <class Key, class T, class Compare, class Alloc>
	bool operator>(const ft::map<Key, T, Compare, Alloc> &lhs,
				   const ft::map<Key, T, Compare, Alloc> &rhs)
	{
		return rhs < lhs;
	}
	template <class Key, class T, class Compare, class Alloc>
	bool operator>=(const ft::map<Key, T, Compare, Alloc> &lhs,
					const ft::map<Key, T, Compare, Alloc> &rhs)
	{
		return !(lhs < rhs);
	}

	template <class Key, class T, class Compare, class Alloc>
	void swap(ft::map<Key, T, Compare, Alloc> &lhs,
			  ft::map<Key, T, Compare, Alloc> &rhs)
	{
		lhs.swap(rhs);
	}

} // namespace ft

#endif // MAP_HPP
