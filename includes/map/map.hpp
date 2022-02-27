/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vico <vico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 17:28:41 by vico              #+#    #+#             */
/*   Updated: 2022/02/24 12:13:32 by vico             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
#define MAP_HPP

#include "RBtree_iterator.hpp"
#include "reverse_iterator.hpp"


namespace ft
{
	template <class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key, T> > >
	class map
	{

		public:

		typedef Key key_type;
		typedef T mapped_type;
		typedef ft::pair<const key_type, mapped_type> value_type;
		typedef Compare key_compare;
		typedef Alloc allocator_type;
		typedef ft::node<value_type> node_type;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
		typedef ft::RBtree_iterator<value_type, node_type, const key_type, key_compare> iterator;
		typedef ft::RBtree_iterator<const value_type, const node_type, const key_type, key_compare> const_iterator;
		typedef ft::reverse_iterator<iterator> reverse_iterator;	
		typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
		typedef std::ptrdiff_t difference_type;
		typedef size_t size_type;

		class value_compare : public std::binary_function<value_type, value_type, bool>
		{
			friend class map<key_type, mapped_type, key_compare, allocator_type>;

			protected:

			Compare comp;
			value_compare(Compare c) : comp(c)
			{
			}

			public:

			bool	operator()(const value_type& x, const value_type& y) const
			{
				return comp(x.first, y.first);
			}
		};

		private:

		allocator_type											_alloc;
		key_compare												_comp;
		ft::RBtree<const key_type, mapped_type, key_compare>	_tree;

		public:

		// Constructor
		explicit map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _alloc(alloc), _comp(comp)
		{
		}
		template <class InputIterator>
		map(InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _alloc(alloc), _comp(comp)
		{
			insert(first, last);
		}
		map(const map& x) : _alloc(x.get_allocator()), _comp(x._comp), _tree(x._tree)
		{
		}
		// Destructor
		~map()
		{
		}
		// Operator_copy
		map&	operator=(const map& x)
		{
			if (&x != this)
			{
				_tree = x._tree;
				_comp = x._comp;
			}
			return *this;
		}
		// Iterator
		iterator	begin()
		{
			return iterator(_tree.minimum(_tree.getRoot()), _tree.getRoot());
		}
		const_iterator	begin() const
		{
			return const_iterator(_tree.minimum(_tree.getRoot()), _tree.getRoot());
		}
		iterator	end()
		{
			iterator	ret(_tree.maximum(_tree.getRoot()), _tree.getRoot());

			++ret;
			return ret;
		}
		const_iterator	end() const
		{
			const_iterator	ret(_tree.maximum(_tree.getRoot()), _tree.getRoot());

			++ret;
			return ret;
		}
		reverse_iterator	rbegin()
		{
			return reverse_iterator(end());
		}
		const_reverse_iterator	rbegin() const
		{
			return const_reverse_iterator(end());
		}
		reverse_iterator	rend()
		{
			return reverse_iterator(begin());
		}
		const_reverse_iterator	rend() const
		{
			return const_reverse_iterator(begin());
		}
		// Capacity
		bool	empty() const
		{
			if (_tree.size())
				return false;
			return true;
		}
		size_type	size() const
		{
			return _tree.size();
		}
		size_type	max_size() const
		{
			return _tree.max_size();
		}
		// Element access
		mapped_type&	operator[](const key_type& k)
		{
			return (*((this->insert(ft::make_pair(k,mapped_type()))).first)).second;
		}
		// Modifiers
		ft::pair<iterator, bool>	insert(const value_type& val)
		{
			ft::pair<iterator, bool>	tmp;
			size_type					len(size());

			_tree.insert(val);
			if (len == size())
				tmp.second = false;
			else
				tmp.second = true;
			tmp.first = find(val.first);
			return tmp;
		}
		iterator	insert(iterator position, const value_type& val)
		{
			_tree.insert(val);
			position = find(val.first);
			return (position);
		}
		template <class InputIterator>
		void	insert(InputIterator first, InputIterator last)
		{
			while (first != last)
			{
				_tree.insert(*first);
				first++;
			}
		}
		void	erase(iterator position)
		{
			_tree.deleteNode(position->first);
		}
		size_type	erase(const key_type& k)
		{
			size_type	len(size());

			_tree.deleteNode(k);
			if (size() != len)
				return 1;
			return 0;
		}
	    void	erase(iterator first, iterator last)
		{
			key_type	key;

			while (first != last)
			{
				key = first->first;
				first++;
				_tree.deleteNode(key);
			}
		}
		void	swap(map& x)
		{
			_tree.swap(x._tree);
		}
		void	clear()
		{
			_tree.clear();
		}
		// Observers
		key_compare	key_comp() const
		{
			return key_compare();
		}
		value_compare	value_comp() const
		{
			return value_compare(key_compare());
		}
		// Operations
		iterator	find(const key_type& k)
		{
			iterator	tmp(begin());

			while (tmp != end())
			{
				if (tmp->first == k)
					break ;
				tmp++;
			}
			return tmp;
		}
		const_iterator	find(const key_type& k) const
		{
			const_iterator	tmp(begin());

			while (tmp != end())
			{
				if (tmp->first == k)
					break ;
				tmp++;
			}
			return tmp;
		}
		size_type	count(const key_type& k) const
		{
			if (find(k) != end())
				return 1;
			return 0;
		}
		iterator	lower_bound(const key_type& k)
		{
			iterator	tmp(begin());

			while (tmp != end())
			{
				if (_comp(tmp->first, k) == false)
					break;
				tmp++;
			}
			return tmp;
		}
		const_iterator	lower_bound(const key_type& k) const
		{
			const_iterator	tmp(begin());

			while (tmp != end())
			{
				if (_comp(tmp->first, k) == false)
					break;
				tmp++;
			}
			return tmp;
		}
		iterator	upper_bound(const key_type& k)
		{
			iterator	tmp(begin());

			while (tmp != end())
			{
				if (_comp(k, tmp->first) == true)
					break;
				tmp++;
			}
			return tmp;
		}
		const_iterator	upper_bound(const key_type& k) const
		{
			const_iterator	tmp(begin());

			while (tmp != end())
			{
				if (_comp(k, tmp->first) == true)
					break;
				tmp++;
			}
			return tmp;
		}
		ft::pair<iterator, iterator>             equal_range(const key_type& k)
		{
			return ft::make_pair(lower_bound(k), upper_bound(k));
		}
		ft::pair<const_iterator, const_iterator> equal_range(const key_type& k) const
		{
			return ft::make_pair(lower_bound(k), upper_bound(k));
		}
		// Allocator
		allocator_type	get_allocator() const
		{
			return _alloc;
		}
	};

	template <class Key, class T, class Compare, class Alloc>
	bool	operator==(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
	{
		if (lhs.size() == rhs.size())
			return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
		return false;
	}
	template <class Key, class T, class Compare, class Alloc>
	bool	operator!=(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
	{
		return (!(lhs == rhs));
	}
	template <class Key, class T, class Compare, class Alloc>
	bool	operator<(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}
	template <class Key, class T, class Compare, class Alloc>
	bool	operator<=(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
	{
		return (lhs < rhs || lhs == rhs);
	}
	template <class Key, class T, class Compare, class Alloc>
	bool	operator>(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
	{
		return (!(lhs <= rhs));
	}
	template <class Key, class T, class Compare, class Alloc>
	bool	operator>=(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
	{
		return (!(lhs < rhs));
	}
}

#endif
