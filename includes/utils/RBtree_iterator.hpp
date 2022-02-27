/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBtree_iterator.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vico <vico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 15:30:26 by vico              #+#    #+#             */
/*   Updated: 2022/02/18 00:14:53 by vico             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBtree_iterator_HPP
#define RBtree_iterator_HPP

#include "RBtree.hpp"

namespace ft
{
	template <class T, class N, class Key, class Compare>
	class RBtree_iterator
	{
		public:

		typedef T value_type;
		typedef Key key_type;
		typedef N node_type;
		typedef Compare key_compare;
		typedef size_t size_type;
    	typedef std::ptrdiff_t difference_type;
    	typedef value_type* pointer;
    	typedef value_type& reference;
    	typedef ft::bidirectional_iterator_tag iterator_category;

		private:

		node_type	*_p;
		node_type	*_sentinel;
		node_type	*_save;
		key_compare	_comp;

		void	next()
		{
			key_type	key(_p->data.first);

			if (_p == _sentinel)
			{
				_p = _save;
				while (_p->left != _sentinel && _p->left)
					_p = _p->left;
			}
			else if (_p->right != _sentinel)
			{
				_p = _p->right;
				while (_p->left != _sentinel)
					_p = _p->left;
			}
			else if (_p->parent == NULL)
			{
				_p = _sentinel;
			}
			else if (_p == _p->parent->left)
				_p = _p->parent;
			else if (_p == _p->parent->right)
			{
				while (_p != _sentinel && (_comp(_p->data.first, key) || _p->data.first == key))
				{
					if (_p->parent == NULL)
					{
						_p = _sentinel;
						return ;
					}
					_p = _p->parent;
				}
			}
		}
		void	prev()
		{
			key_type	key(_p->data.first);

			if (_p == _sentinel)
			{
				_p = _save;
				while (_p->right != _sentinel && _p->right)
				{
					_p = _p->right;
				}
			}
			else if (_p->left != _sentinel)
			{
				_p = _p->left;
				while (_p->right != _sentinel)
					_p = _p->right;
			}
			else if (_p->parent == NULL)
			{
				_p = _sentinel;
			}
			else if (_p == _p->parent->right)
				_p = _p->parent;
			else if (_p == _p->parent->left)
			{
				while (_p != _sentinel && (!_comp(_p->data.first, key) || _p->data.first == key))
				{
					if (_p->parent == NULL)
					{
						_p = _sentinel;
						return ;
					}
					_p = _p->parent;
				}
			}			
		}

		public:

		// Constructor
		RBtree_iterator(const Compare& comp = Compare()) : _p(NULL), _sentinel(NULL), _save(NULL), _comp(comp)
		{
		}
		RBtree_iterator(node_type *p, node_type *r, const Compare& comp = Compare()) : _p(p), _sentinel(p), _save(r), _comp(comp)
		{
			while (_sentinel && _sentinel->left)
			{
				_sentinel = _sentinel->left;
			}
		}
		RBtree_iterator(const RBtree_iterator& x) : _p(x._p), _sentinel(x._sentinel), _save(x._save), _comp(x._comp)
		{
		}
		// Destructor
		~RBtree_iterator()
		{
		}
		// Overload
		RBtree_iterator&	operator=(const RBtree_iterator& x)
		{
			_p = x._p;
			_sentinel = x._sentinel;
			_save = x._save;
			_comp = x._comp;
			return *this;
		}
		node_type		*base() const
		{
			return _p;
		}
		node_type		*save() const
		{
			return _save;
		}
		reference	operator*()
		{
			return _p->data;
		}
		reference	operator*() const
		{
			return _p->data;
		}
		pointer		operator->()
		{
			return (&operator*());
		}
		const pointer	operator->() const
		{
			return (&operator*());
		}
		RBtree_iterator	operator++(int)
		{
			RBtree_iterator ret(*this);

			next();
			return ret;
		}
		RBtree_iterator&	operator++()
		{
			next();
			return *this;
		}
		RBtree_iterator	operator--(int)
		{
			RBtree_iterator ret(*this);

			prev();
			return ret;
		}
		RBtree_iterator&	operator--()
		{
			prev();
			return *this;
		}
		operator	RBtree_iterator<const value_type, const node_type, Key, Compare>() const
        {
			RBtree_iterator<const value_type, const node_type, Key, Compare>	x(_p, _save);
			return x;
		}
	};
	template <class T, class N, class Key, class Compare>
	bool	operator==(const RBtree_iterator<T, N, Key, Compare>& a, const RBtree_iterator<T, N, Key, Compare>& b)
	{
		if (a.base() == b.base())
			return true;
		return false;
	}
	template <class T, class NT, class V, class NV, class Key, class Compare>
	bool	operator==(const RBtree_iterator<T, NT, Key, Compare>& a, const RBtree_iterator<V, NV, Key, Compare>& b)
	{
		if (a.base() == b.base())
			return true;
		return false;
	}
	template <class T, class N, class Key, class Compare>
	bool	operator!=(const RBtree_iterator<T, N, Key, Compare>& a, const RBtree_iterator<T, N, Key, Compare>& b)
	{
		if (a.base() != b.base())
			return true;
		return false;
	}
	template <class T, class NT, class V, class NV, class Key, class Compare>
	bool	operator!=(const RBtree_iterator<T, NT, Key, Compare>& a, const RBtree_iterator<V, NV, Key, Compare>& b)
	{
		if (a.base() != b.base())
			return true;
		return false;
	}
}

#endif
