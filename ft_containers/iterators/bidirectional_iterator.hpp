#if !defined(BIDIRECTIONAL_ITERATOR_HPP)
#define BIDIRECTIONAL_ITERATOR_HPP

#include "../utils/utils.hpp"
#include "../utils/avl_tree.hpp"

namespace ft
{
	template <class T>
	struct Node;

	template <class T>
	class bidirectional_iterator : public ft::iterator<std::bidirectional_iterator_tag, T>
	{
	public:
		//////////////////////////////////////////////////////////////////////////////
		// TYPES
		//////////////////////////////////////////////////////////////////////////////
		typedef typename ft::iterator<std::bidirectional_iterator_tag, T>::iterator_category iterator_category;
		typedef typename ft::iterator<std::bidirectional_iterator_tag, T>::value_type value_type;
		typedef typename ft::iterator<std::bidirectional_iterator_tag, T>::difference_type difference_type;
		typedef typename ft::iterator<std::bidirectional_iterator_tag, T>::pointer pointer;
		typedef typename ft::iterator<std::bidirectional_iterator_tag, T>::reference reference;

		typedef ft::Node<value_type> &node_reference;
		typedef ft::Node<value_type> *node_pointer;
		typedef ft::Node<const value_type> *const_node_pointer;

		//////////////////////////////////////////////////////////////////////////////
		// CONSTRUCTORS / DESTRUCTORS
		//////////////////////////////////////////////////////////////////////////////
		bidirectional_iterator() { _it = NULL; }
		bidirectional_iterator(node_pointer root, node_pointer end, node_pointer ptr) : _root(root), _end(end), _it(ptr) {}
		bidirectional_iterator(const bidirectional_iterator &src) { *this = src; }
		~bidirectional_iterator() {}

		//////////////////////////////////////////////////////////////////////////////
		// OPERATORS
		//////////////////////////////////////////////////////////////////////////////
		bidirectional_iterator &operator=(const bidirectional_iterator &src)
		{
			_root = src._root;
			_end = src._end;
			_it = src._it;
			return *this;
		}

		//////////////////////////////////////////////////////////////////////////////
		// INCREMENT / DECREMENT
		//////////////////////////////////////////////////////////////////////////////
		bidirectional_iterator &operator++()
		{
			_it = in_order_successor(_it);
			return (*this);
		}
		bidirectional_iterator operator++(int)
		{
			bidirectional_iterator tmp = *this;
			_it = in_order_successor(_it);
			return tmp;
		}
		bidirectional_iterator &operator--()
		{
			_it = in_order_predecessor(_it);
			return (*this);
		}
		bidirectional_iterator operator--(int)
		{
			bidirectional_iterator tmp = *this;
			_it = in_order_predecessor(_it);
			return tmp;
		}

		//////////////////////////////////////////////////////////////////////////////
		// DEREFERENCE
		//////////////////////////////////////////////////////////////////////////////
		reference operator*() const { return _it->data; }
		pointer operator->() const { return &_it->data; }

		//////////////////////////////////////////////////////////////////////////////
		// UTILS
		//////////////////////////////////////////////////////////////////////////////
		node_pointer base() const { return (_it); }
		operator bidirectional_iterator<const T>()
		{
			return bidirectional_iterator<const T>((const_node_pointer)_root, (const_node_pointer)_end, (const_node_pointer)this->base());
		}

		//////////////////////////////////////////////////////////////////////////////
		// TRAVERSE
		//////////////////////////////////////////////////////////////////////////////
		node_pointer get_max(node_pointer node)
		{
			node_pointer current = node;

			while (current->right != NULL)
				current = current->right;

			return current;
		}
		node_pointer get_min(node_pointer node)
		{
			node_pointer current = node;

			while (current->left != NULL)
				current = current->left;

			return current;
		}
		node_pointer in_order_predecessor(node_pointer n)
		{
			if (n == _end)
				return (get_max(_root));

			if (n->left != NULL)
				return get_max(n->left);

			node_pointer parent = n->parent;
			while (parent != NULL && n == parent->left)
			{
				n = parent;
				parent = parent->parent;
			}

			if (!parent)
				return _end;
			return parent;
		}
		node_pointer in_order_successor(node_pointer n)
		{
			if (n == _end)
				return (get_min(_root));

			if (n->right != NULL)
				return get_min(n->right);

			node_pointer parent = n->parent;
			while (parent != NULL && n == parent->right)
			{
				n = parent;
				parent = parent->parent;
			}

			if (!parent)
				return _end;
			return parent;
		}

	private:
		//////////////////////////////////////////////////////////////////////////////
		// ATTRIBUTES
		//////////////////////////////////////////////////////////////////////////////
		node_pointer _root;
		node_pointer _end;
		node_pointer _it;
	};

	//////////////////////////////////////////////////////////////////////////////
	// EQUALITY
	//////////////////////////////////////////////////////////////////////////////
	template <class T>
	bool operator==(const bidirectional_iterator<T> &lhs, const bidirectional_iterator<T> &rhs)
	{
		return (lhs.base() == rhs.base());
	}
	template <class T>
	bool operator!=(const bidirectional_iterator<T> &lhs, const bidirectional_iterator<T> &rhs)
	{
		return (lhs.base() != rhs.base());
	}

} // namespace ft

#endif // BIDIRECTIONAL_ITERATOR_HPP
