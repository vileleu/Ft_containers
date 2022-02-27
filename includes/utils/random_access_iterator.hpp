/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_access_iterator.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vico <vico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 20:33:41 by vico              #+#    #+#             */
/*   Updated: 2022/02/25 20:47:32 by vico             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RANDOM_ACCESS_ITERATOR_HPP
#define RANDOM_ACCESS_ITERATOR_HPP

#include "utils.hpp"

namespace ft
{
	template <typename T>
	class random_access_iterator
	{
		public:

		typedef T value_type;
		typedef size_t size_type;
    	typedef std::ptrdiff_t difference_type;
    	typedef T* pointer;
    	typedef T& reference;
    	typedef ft::random_access_iterator_tag iterator_category;
		
		private:

		pointer	_p;

		public:

		//constructor
		random_access_iterator() : _p(NULL)
		{
		}
		random_access_iterator(pointer p) : _p(p)
		{
		}
		random_access_iterator(const random_access_iterator& x) : _p(x.base())
		{
		}
		//destructor
		~random_access_iterator()
		{
		}
		//base
		pointer	base() const
		{
			return _p;
		}
		//overload
		random_access_iterator&	operator=(const random_access_iterator& x)
		{
			_p = x.base();
			return *this;
		}
		reference	operator*()
		{
			return *_p;
		}
		reference	operator*() const
		{
			return *_p;
		}
		pointer		operator->()
		{
			return _p;
		}
		const pointer		operator->() const
		{
			return _p;
		}
		random_access_iterator	operator++(int)
		{
			random_access_iterator ret(*this);

			_p++;
			return ret;
		}
		random_access_iterator&	operator++()
		{
			_p++;
			return *this;
		}
		random_access_iterator	operator--(int)
		{
			random_access_iterator ret(*this);

			_p--;
			return ret;
		}
		random_access_iterator&	operator--()
		{
			_p--;
			return *this;
		}
		random_access_iterator&	operator+=(size_type x)
		{
			_p = _p + x;
			return *this;
		}
		random_access_iterator&	operator-=(size_type x)
		{
			_p = _p - x;
			return *this;
		}
		reference	operator[](size_type x) const
		{
			return *(_p + x);
		}
		operator	random_access_iterator<const value_type>() const
        {
			return _p;
		}
	};
	template <typename T>
	bool	operator==(const random_access_iterator<T>& a, const random_access_iterator<T>& b)
	{
		if (a.base() == b.base())
			return true;
		return false;
	}
	template <typename T, typename V>
	bool	operator==(const random_access_iterator<T>& a, const random_access_iterator<V>& b)
	{
		if (a.base() == b.base())
			return true;
		return false;
	}
	template <typename T>
	bool	operator!=(const random_access_iterator<T>& a, const random_access_iterator<T>& b)
	{
		if (a == b)
			return false;
		return true;
	}
	template <typename T, typename V>
	bool	operator!=(const random_access_iterator<T>& a, const random_access_iterator<V>& b)
	{
		if (a == b)
			return false;
		return true;
	}
	template <typename T>
	bool	operator<(const random_access_iterator<T>& a, const random_access_iterator<T>& b)
	{
		if (a.base() < b.base())
			return true;
		return false;
	}
	template <typename T, typename V>
	bool	operator<(const random_access_iterator<T>& a, const random_access_iterator<V>& b)
	{
		if (a.base() < b.base())
			return true;
		return false;
	}
	template <typename T>
	bool	operator>(const random_access_iterator<T>& a, const random_access_iterator<T>& b)
	{
		if (a < b || a == b)
			return false;
		return true;
	}
	template <typename T, typename V>
	bool	operator>(const random_access_iterator<T>& a, const random_access_iterator<V>& b)
	{
		if (a < b || a == b)
			return false;
		return true;
	}
	template <typename T>
	bool	operator<=(const random_access_iterator<T>& a, const random_access_iterator<T>& b)
	{
		if (a < b || a == b)
			return true;
		return false;
	}
	template <typename T, typename V>
	bool	operator<=(const random_access_iterator<T>& a, const random_access_iterator<V>& b)
	{
		if (a < b || a == b)
			return true;
		return false;
	}
	template <typename T>
	bool	operator>=(const random_access_iterator<T>& a, const random_access_iterator<T>& b)
	{
		if (a < b)
			return false;
		return true;
	}
	template <typename T, typename V>
	bool	operator>=(const random_access_iterator<T>& a, const random_access_iterator<V>& b)
	{
		if (a < b)
			return false;
		return true;
	}
	template <typename T>
	random_access_iterator<T>	operator+(const random_access_iterator<T>& a, typename ft::random_access_iterator<T>::difference_type b)
	{
		return a.base() + b;
	}
	template <typename T>
	random_access_iterator<T>	operator+(typename ft::random_access_iterator<T>::difference_type a, const random_access_iterator<T>& b)
	{
		return b.base() + a;
	}
	template <typename T>
	random_access_iterator<T>	operator-(const random_access_iterator<T>& a, typename ft::random_access_iterator<T>::difference_type b)
	{
		return a.base() - b;
	}
	template <typename T>
	typename ft::random_access_iterator<T>::difference_type	operator-(const random_access_iterator<T>& a, const random_access_iterator<T>& b)
	{
		return a.base() - b.base();
	}
	template <typename T, typename V>
	typename ft::random_access_iterator<T>::difference_type	operator-(const random_access_iterator<T>& a, const random_access_iterator<V>& b)
	{
		return a.base() - b.base();
	}
}

#endif
