/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vico <vico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 19:08:07 by vico              #+#    #+#             */
/*   Updated: 2022/03/01 02:42:43 by vico             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "random_access_iterator.hpp"
#include "reverse_iterator.hpp"

namespace ft
{
	template <typename T>
	class random_access_iterator;

	template <typename T, class Alloc = std::allocator<T> >
	class vector
	{
		public:
		
		typedef T value_type;
		typedef size_t size_type;
		typedef Alloc allocator_type;
		typedef std::ptrdiff_t difference_type;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
		typedef ft::random_access_iterator<value_type> iterator;
		typedef ft::random_access_iterator<const value_type> const_iterator;
		typedef ft::reverse_iterator<iterator> reverse_iterator;
		typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

		private:

		pointer			_array;
		size_type		_capacity;
		size_type		_size;
		allocator_type	_alloc;

		public:

		// Constructor
		explicit vector(const allocator_type& alloc = allocator_type()) : _array(NULL), _capacity(0), _size(0), _alloc(alloc)
		{
		}
		explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) : _array(NULL), _capacity(0), _size(0), _alloc(alloc)
		{
			if (n > max_size())
				throw std::length_error("cannot create ft::vector larger than max_size()");
			insert(begin(), n, val);
		}
		template <class InputIterator>
        vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type()) : _array(NULL), _capacity(0), _size(0), _alloc(alloc)
		{
			insert(begin(), first, last);
		}
		vector (const vector& x) : _array(NULL), _capacity(0), _size(0), _alloc(x.get_allocator())
		{
			insert(begin(), x.begin(), x.end());
		}
		// Destructor
		~vector()
		{
			clear();
			_alloc.deallocate(_array, _capacity);
			_array = NULL;
			_capacity = 0;
		}
		// Operator copy
		vector	operator=(const vector& x)
		{
			clear();
			_alloc.deallocate(_array, _capacity);
			if (x.size() > _capacity)
				_capacity = x.size();
			_size = x.size();
			_array = _alloc.allocate(_capacity);
			for (size_type i(0); i < _size; i++)
				_alloc.construct(&_array[i], x[i]);
			return (*this);
		}
		// Iterators
		iterator	begin()
		{
			return _array;
		}
		const_iterator	begin() const
		{
			return _array;
		}
		iterator	end()
		{
			return _array + _size;
		}
		const_iterator	end() const
		{
			return _array + _size;		
		}
		reverse_iterator rbegin()
		{
			return reverse_iterator(end());
		}
		const_reverse_iterator rbegin() const
		{
			return const_reverse_iterator(end());
		}
		reverse_iterator rend()
		{
			return reverse_iterator(begin());
		}
		const_reverse_iterator rend() const
		{
			return const_reverse_iterator(begin());			
		}
		// Capacity
		size_type	size() const
		{
			return _size;
		}
		size_type	max_size() const
		{
			return _alloc.max_size();
		}
		void		resize(size_type n, value_type val = value_type())
		{
			if (n > max_size())
				throw std::length_error("vector::_M_fill_insert");
			if (n <= _size)
			{
				for (size_type i(n); i < _size; i++)
					_alloc.destroy(&_array[i]);
				_size = n;
			}
			else if (n > _size && n <= _capacity)
			{
				for (size_type i(_size); i < n; i++)
					_alloc.construct(&_array[i], val);
				_size = n;
			}
			else
				insert(end(), n - _size, val);
		}
		size_type	capacity() const
		{
			return _capacity;
		}
		bool		empty() const
		{
			if (_size)
				return false;
			return true;
		}
		void		reserve(size_type n)
		{
			if (n > max_size())
				throw std::length_error("vector::reserve");
			if (n > _capacity)
			{
				pointer	new_array;
				size_type	save(_size);

				new_array = _alloc.allocate(n);
				for (size_type i(0); i < _size; i++)
				{
					_alloc.construct(&new_array[i], _array[i]);
				}
				clear();
				_alloc.deallocate(_array, _capacity);
				_array = new_array;
				_capacity = n;
				_size = save;
			}
		}
		// Element access
		reference	operator[](size_type n)
		{
			return _array[n];
		}
		const_reference	operator[](size_type n) const
		{
			return _array[n];	
		}
		reference	at(size_type n)
		{
			if (n > max_size() || n >= _size)
				throw std::out_of_range("vector::_M_range_check");
			return _array[n];
		}
		const_reference	at(size_type n) const
		{
			if (n > max_size() || n >= _size)
				throw std::out_of_range("vector::_M_range_check");
			return _array[n];
		}
		reference	front()
		{
			return _array[0];
		}
		const_reference	front() const
		{
			return _array[0];
		}
		reference	back()
		{
			return _array[_size - 1];
		}
		const_reference	back() const
		{
			return _array[_size - 1];
		}
		// Modifiers
		template <class InputIterator>
		void assign(InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = NULL)
		{
			size_type		n(0);

			while (last != first)
			{
				n++;
				last--;
			}
			
			if (n > max_size())
				throw std::length_error("cannot create ft::vector larger than max_size()");
			if (n > _capacity)
				reserve(n);
			clear();
			_size = n;
			for (size_type i(0); i < _size; i++)
				_alloc.construct(&_array[i], *(first++));
		}
		void	assign(size_type n, const value_type& val)
		{
			if (n > max_size())
				throw std::length_error("cannot create ft::vector larger than max_size()");
			if (n > _capacity)
				reserve(n);
			clear();
			_size = n;
			for (size_type i(0); i < _size; i++)
				_alloc.construct(&_array[i], val);
		}
		void	push_back(const value_type& val)
		{
			if (_size == _capacity && _capacity)
				reserve(_capacity * 2);
			else if (_size == _capacity && !_capacity)
				reserve(1);
			_alloc.construct(&_array[_size], val);
			_size++;
		}
		void	pop_back()
		{
			if (_size)
			{
				_alloc.destroy(&back());
				_size--;
			}
		}
		iterator	insert(iterator position, const value_type& val)
		{
			difference_type	ret(position - begin());

			insert(position, 1, val);
			return iterator(&_array[ret]);
		}
		void	insert(iterator position, size_type n, const value_type& val)
		{
			if (n > max_size())
				throw std::length_error("vector::_M_fill_insert");
			if (!n)
				return ;

			difference_type	start(position - begin());
			size_type		len(_size - start);
			pointer			tmp(NULL);

			tmp = _alloc.allocate(len);
			if (!_capacity)
				reserve(_size + n);
			else if (_size + n > _size * 2)
				reserve(_size + n);
			else if (_size + n > _capacity)
				reserve(_size * 2);
			for (size_type i(start); i < _size; i++)
			{
				_alloc.construct(&tmp[i - start], _array[i]);
				_alloc.destroy(&_array[i]);
			}
			for (size_type i(0); i < n; i++)
			{
				_alloc.construct(&_array[i + start], val);
				_size++;
			}
			for (size_type i(0); i < len; i++)
			{
				_alloc.construct(&_array[i + start + n], tmp[i]);
				_alloc.destroy(&tmp[i]);
			}
			_alloc.deallocate(tmp, len);
		}
		template <class InputIterator>
		void insert (iterator position, InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = NULL)
		{
			size_type		n(0);

			while (last != first)
			{
				n++;
				last--;
			}

			if (n > max_size())
				throw std::length_error("vector::_M_range_insert");
			if (!n)
				return ;

			difference_type	start(position - begin());
			size_type		len(_size - start);
			pointer			tmp(NULL);

			tmp = _alloc.allocate(len);
			if (!_capacity)
				reserve(_size + n);
			else if (_size + n > _size * 2)
				reserve(_size + n);
			else if (_size + n > _capacity)
				reserve(_size * 2);
			for (size_type i(start); i < _size; i++)
			{
				_alloc.construct(&tmp[i - start], _array[i]);
				_alloc.destroy(&_array[i]);
			}
			for (size_type i(0); i < n; i++)
			{
				_alloc.construct(&_array[i + start], *first);
				first++;
				_size++;
			}
			for (size_type i(0); i < len; i++)
			{
				_alloc.construct(&_array[i + start + n], tmp[i]);
				_alloc.destroy(&tmp[i]);
			}
			_alloc.deallocate(tmp, len);		
		}
		iterator	erase(iterator position)
		{
			return erase(position, position + 1);
		}
		iterator	erase(iterator first, iterator last)
		{
			size_type	max(last - begin());

			for (size_type i(first - begin()); i < _size - 1; i++)
			{
				_alloc.destroy(&_array[i]);
				if (max < _size)
				{
					_alloc.construct(&_array[i], _array[max]);
					_alloc.destroy(&_array[max]);
					max++;
				}
			}
			_size -= last - first;
			return iterator(&_array[first - begin()]);
		}
		void	swap(vector& x)
		{
			pointer			cpy_array(x._array);
			size_type		cpy_capacity(x.capacity());
			size_type		cpy_size(x.size());

			x._array = _array;
			x._capacity = _capacity;
			x._size = _size;
			_array = cpy_array;
			_capacity = cpy_capacity;
			_size = cpy_size;
		}
		void	clear()
		{
			for (size_type i(0); i < _size; i++)
				_alloc.destroy(&_array[i]);
			_size = 0;
		}
		allocator_type	get_allocator() const
		{
			return _alloc;
		}
	};
	template <class T, class Alloc>
	void swap(vector<T,Alloc>& x, vector<T,Alloc>& y)
	{
		x.swap(y);
	}
	template <class T, class Alloc>
	bool	operator==(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		if (lhs.size() == rhs.size())
			return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
		return false;
	}
	template <class T, class Alloc>
	bool	operator!=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (!(lhs == rhs));
	}
	template <class T, class Alloc>
	bool	operator<(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}
	template <class T, class Alloc>
	bool	operator<=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (lhs < rhs || lhs == rhs);
	}
	template <class T, class Alloc>
	bool	operator>(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (!(lhs <= rhs));
	}
	template <class T, class Alloc>
	bool	operator>=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (!(lhs < rhs));
	}
}

#endif
