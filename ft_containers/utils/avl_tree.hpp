#if !defined(AVL_TREE_HPP)
#define AVL_TREE_HPP

#include "utils.hpp"
#include "../iterators/bidirectional_iterator.hpp"
#include "../iterators/reverse_iterator.hpp"

namespace ft
{
	template <class T>
	class bidirectional_iterator;

	//////////////////////////////////////////////////////////////////////////////
	// NODE
	//////////////////////////////////////////////////////////////////////////////
	template <typename T>
	struct Node
	{
		T data;
		Node<T> *left;
		Node<T> *right;
		Node<T> *parent;
		int height;

		Node() : data(T()), left(NULL), right(NULL), parent(NULL), height(1) {}
		Node(T data) : data(data), left(NULL), right(NULL), parent(NULL), height(1) {}
		Node(const Node &src) { *this = src; }
		~Node() {}
		Node &operator=(const Node &src)
		{
			data = src.data;
			left = src.left;
			right = src.right;
			parent = src.parent;
			height = src.height;
			return *this;
		}
	};

	//////////////////////////////////////////////////////////////////////////////
	// AVL_TREE
	//////////////////////////////////////////////////////////////////////////////
	template <typename T, class Alloc = std::allocator<T>, class Compare = std::less<typename T::first_type> >
	class AVLTree
	{
	public:
		//////////////////////////////////////////////////////////////////////////////
		// TYPES
		//////////////////////////////////////////////////////////////////////////////
		typedef typename T::first_type key_type;
		typedef typename T::second_type mapped_type;
		typedef T value_type;
		typedef Compare key_compare;
		typedef Alloc allocator_type;
		typedef ft::bidirectional_iterator<value_type> iterator;
		typedef ft::bidirectional_iterator<const value_type> const_iterator;
		typedef ft::reverse_iterator<iterator> reverse_iterator;
		typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
		typedef size_t size_type;

		typedef Node<value_type> *node_pointer;
		typedef typename allocator_type::template rebind<Node<value_type> >::other node_allocator;

		//////////////////////////////////////////////////////////////////////////////
		// CONSTRUCTORS / DESTRUCTORS
		//////////////////////////////////////////////////////////////////////////////
		AVLTree()
		{
			_root = NULL;
			try
			{
				_end = _alloc.allocate(1);
			}
			catch (std::bad_alloc &e)
			{
				throw e;
			}
			_size = 0;
		}
		AVLTree(const AVLTree &src) { *this = src; }
		AVLTree &operator=(const AVLTree &src)
		{
			(void)src;
			return *this;
		}
		~AVLTree()
		{
			_alloc.deallocate(_end, 1);
		}

		//////////////////////////////////////////////////////////////////////////////
		// GETTERS / SETTERS
		//////////////////////////////////////////////////////////////////////////////
		node_pointer get_root() const { return _root; }
		void set_root(node_pointer root) { _root = root; }
		node_pointer get_end() const { return _end; }
		void set_end(node_pointer end) { _end = end; }
		size_t get_size() const { return _size; }

		//////////////////////////////////////////////////////////////////////////////
		// UTILITIES
		//////////////////////////////////////////////////////////////////////////////
		node_pointer get_min(node_pointer node) const
		{
			node_pointer current = node;

			while (current->left != NULL)
				current = current->left;

			return current;
		}
		int get_height(node_pointer node) const
		{
			if (node == NULL)
				return 0;
			return node->height;
		}
		int get_balance_factor(node_pointer node) const
		{
			if (node == NULL)
				return 0;
			return get_height(node->left) - get_height(node->right);
		}
		bool empty() const { return _size == 0; }
		size_type size() const { return _size; }
		size_type max_size() const { return _alloc.max_size(); }
		void swap(AVLTree &other)
		{
			std::swap(_root, other._root);
			std::swap(_end, other._end);
			std::swap(_size, other._size);
			std::swap(_alloc, other._alloc);
			std::swap(_comp, other._comp);
		}
		int max(int a, int b) const { return a > b ? a : b; }

		//////////////////////////////////////////////////////////////////////////////
		// ROTAIONS
		//////////////////////////////////////////////////////////////////////////////
		node_pointer right_rotate(node_pointer node)
		{
			node_pointer left = node->left;
			node_pointer leftRight = left->right;
			node_pointer parent = node->parent;

			left->right = node;
			node->left = leftRight;
			node->parent = left;
			left->parent = parent;
			if (leftRight)
				leftRight->parent = node;

			node->height = max(get_height(node->left), get_height(node->right)) + 1;
			left->height = max(get_height(left->left), get_height(left->right)) + 1;

			return left;
		}
		node_pointer left_rotate(node_pointer node)
		{
			node_pointer right = node->right;
			node_pointer rightLeft = right->left;
			node_pointer parent = node->parent;

			right->left = node;
			node->right = rightLeft;
			node->parent = right;
			right->parent = parent;
			if (rightLeft)
				rightLeft->parent = node;

			node->height = max(get_height(node->left), get_height(node->right)) + 1;
			right->height = max(get_height(right->left), get_height(right->right)) + 1;

			return right;
		}

		//////////////////////////////////////////////////////////////////////////////
		// BALANCE
		//////////////////////////////////////////////////////////////////////////////
		node_pointer balance_node(node_pointer node)
		{
			node->height = max(get_height(node->left), get_height(node->right)) + 1;
			int balance = get_balance_factor(node);

			// Left Left Case
			if (balance > 1 && get_balance_factor(node->left) >= 0)
				return right_rotate(node);
			// Left Right Case
			else if (balance > 1 && get_balance_factor(node->left) < 0)
			{
				node->left = left_rotate(node->left);
				return right_rotate(node);
			}
			// Right Right Case
			else if (balance < -1 && get_balance_factor(node->right) <= 0)
				return left_rotate(node);
			// Right Left Case
			else if (balance < -1 && get_balance_factor(node->right) > 0)
			{
				node->right = right_rotate(node->right);
				return left_rotate(node);
			}
			return node;
		}

		//////////////////////////////////////////////////////////////////////////////
		// INSERTION
		//////////////////////////////////////////////////////////////////////////////
		node_pointer insert_node(node_pointer node, value_type data, bool &inserted)
		{
			if (node == NULL)
			{
				node_pointer temp;
				try
				{
					temp = _alloc.allocate(1);
				}
				catch (std::bad_alloc &e)
				{
					throw e;
				}
				_alloc.construct(temp, data);
				_size++;
				return temp;
			}
			if (!_comp(data.first, node->data.first) && !_comp(node->data.first, data.first))
			{
				inserted = false;
				return node;
			}
			else if (_comp(data.first, node->data.first))
			{
				node->left = insert_node(node->left, data, inserted);
				if (!node->left->parent)
					node->left->parent = node;
			}
			else
			{
				node->right = insert_node(node->right, data, inserted);
				if (!node->right->parent)
					node->right->parent = node;
			}

			return balance_node(node);
		}

		//////////////////////////////////////////////////////////////////////////////
		// DELETION
		//////////////////////////////////////////////////////////////////////////////
		node_pointer erase_node(node_pointer node, key_type &key)
		{
			if (node == NULL)
				return node;

			if (!_comp(key, node->data.first) && !_comp(node->data.first, key))
			{
				if (node->left == NULL || node->right == NULL)
				{
					node_pointer temp = node->left ? node->left : node->right;

					if (temp == NULL)
					{
						temp = node;
						node = NULL;
					}
					else
					{
						_pair_alloc.destroy(&node->data);
						_pair_alloc.construct(&(node->data), temp->data);
						node->height = temp->height;
						node->left = temp->left;
						node->right = temp->right;
					}

					_alloc.deallocate(temp, 1);
					_size--;
				}
				else
				{
					node_pointer temp = get_min(node->right);
					_pair_alloc.construct(&(node->data), temp->data);
					node->right = erase_node(node->right, temp->data.first);
				}
			}
			else if (_comp(key, node->data.first))
				node->left = erase_node(node->left, key);
			else
				node->right = erase_node(node->right, key);

			if (node == NULL)
				return node;
			return balance_node(node);
		}

		//////////////////////////////////////////////////////////////////////////////
		// FIND
		//////////////////////////////////////////////////////////////////////////////
		size_type count(const key_type &k) const
		{
			node_pointer node = _root;
			while (node != NULL)
			{
				if (!_comp(k, node->data.first) && !_comp(node->data.first, k))
					return 1;
				else if (_comp(k, node->data.first))
					node = node->left;
				else
					node = node->right;
			}
			return 0;
		}
		node_pointer find_node(const key_type &k)
		{
			node_pointer node = _root;
			while (node != NULL)
			{
				if (!_comp(k, node->data.first) && !_comp(node->data.first, k))
					return node;
				else if (_comp(k, node->data.first))
					node = node->left;
				else
					node = node->right;
			}
			return NULL;
		}
		iterator find(const key_type &k)
		{
			if (count(k))
				return iterator(_root, _end, find_node(k));
			else
				return end();
		}

		//////////////////////////////////////////////////////////////////////////////
		// ITERATOR
		//////////////////////////////////////////////////////////////////////////////
		iterator begin()
		{
			if (_size == 0)
				return iterator(_root, _end, _end);
			return iterator(_root, _end, get_min(_root));
		}
		const_iterator begin() const
		{
			if (_size == 0)
				return iterator(_root, _end, _end);
			return iterator(_root, _end, get_min(_root));
		}
		iterator end()
		{
			if (_size == 0)
				return begin();
			return iterator(_root, _end, get_end());
		}
		const_iterator end() const
		{
			if (_size == 0)
				return begin();
			return iterator(_root, _end, get_end());
		}
		reverse_iterator rbegin() { return reverse_iterator(end()); }
		const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }
		reverse_iterator rend() { return reverse_iterator(begin()); }
		const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }

		//////////////////////////////////////////////////////////////////////////////
		// BOUND
		//////////////////////////////////////////////////////////////////////////////
		node_pointer find_bound(const key_type &k) const
		{
			node_pointer node = _root;
			while (node != NULL)
			{
				if (!_comp(k, node->data.first) && !_comp(node->data.first, k))
					return node;
				else if (_comp(k, node->data.first))
				{
					if (node->left)
						node = node->left;
					else
						return node;
				}
				else
				{
					if (node->right)
						node = node->right;
					else
						return node;
				}
			}
			return NULL;
		}
		iterator lower_bound(const key_type &k)
		{
			node_pointer node = find_bound(k);
			iterator it(_root, _end, node);

			if ((!_comp(k, node->data.first) && !_comp(node->data.first, k)) || _comp(k, node->data.first))
				return it;
			else
				return ++it;
		}
		const_iterator lower_bound(const key_type &k) const
		{
			node_pointer node = find_bound(k);
			iterator it(_root, _end, node);

			if ((!_comp(k, node->data.first) && !_comp(node->data.first, k)) || _comp(k, node->data.first))
				return it;
			else
				return ++it;
		}
		iterator upper_bound(const key_type &k)
		{
			node_pointer node = find_bound(k);
			iterator it(_root, _end, node);

			if (_comp(k, node->data.first))
				return it;
			else
				return ++it;
		}
		const_iterator upper_bound(const key_type &k) const
		{
			node_pointer node = find_bound(k);
			iterator it(_root, _end, node);

			if (_comp(k, node->data.first))
				return it;
			else
				return ++it;
		}
		pair<const_iterator, const_iterator> equal_range(const key_type &k) const
		{
			return ft::make_pair(lower_bound(k), upper_bound(k));
		}
		pair<iterator, iterator> equal_range(const key_type &k)
		{
			return ft::make_pair(lower_bound(k), upper_bound(k));
		}

		//////////////////////////////////////////////////////////////////////////////
		// UTILITY
		//////////////////////////////////////////////////////////////////////////////
		void print(node_pointer root, int space = 0) const
		{
			if (root == NULL)
				return;

			space += 10;

			// Process right child first
			print(root->right, space);

			// Print current node after space count
			std::cout << std::endl;
			for (int i(10); i < space; i++)
				std::cout << " ";
			std::cout << root->data.first << ", " << root->data.second << std::endl;

			// Process left child
			print(root->left, space);
		}

	private:
		node_pointer _root;
		node_pointer _end;
		node_allocator _alloc;
		allocator_type _pair_alloc;
		key_compare _comp;
		size_type _size;
	};

} // namespace ft

#endif // AVL_TREE_HPP
