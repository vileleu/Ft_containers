/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vico <vico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 14:34:35 by vico              #+#    #+#             */
/*   Updated: 2022/02/25 21:28:23 by vico             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

#include "utils.hpp"

namespace ft
{
	template <class Iter>
	class reverse_iterator
	{
		public:
		
		typedef Iter iterator_type;
		typedef typename ft::iterator_traits<Iter>::iterator_category iterator_category;
		typedef typename ft::iterator_traits<Iter>::value_type value_type;
		typedef typename ft::iterator_traits<Iter>::difference_type difference_type;
		typedef typename ft::iterator_traits<Iter>::pointer pointer;
		typedef typename ft::iterator_traits<Iter>::reference reference;

		private:

		iterator_type	_p;
		
		public:

		reverse_iterator() : _p()
		{
		};
		explicit reverse_iterator(iterator_type x) : _p(x)
		{
		};
		template<class U>
		reverse_iterator(const reverse_iterator<U>& other)
		{
			_p = other.base();
		};
		~reverse_iterator()
		{
		};
		template <class U>
		reverse_iterator& operator=(const reverse_iterator<U>& other)
		{
			_p = other.base();
			return *this;
		}
		iterator_type base() const
		{
			return _p;
		}
		reference operator*() const
		{
			iterator_type tmp(_p);

			tmp--;
			return *tmp;
		}
		pointer operator->() const
		{
			return &operator*();
		}
		reference operator[](difference_type n) const
		{
			return _p[-n - 1];
		}
		reverse_iterator& operator++()
		{
			_p--;
			return *this;
		}
		reverse_iterator& operator--()
		{
			_p++;
			return *this;
		}
		reverse_iterator operator++(int)
		{
			reverse_iterator	ret(*this);

			_p--;
			return ret;
		}
		reverse_iterator operator--(int)
		{
			reverse_iterator	ret(*this);

			_p++;
			return ret;		
		}
		reverse_iterator operator+(difference_type n) const
		{
			reverse_iterator	ret(_p - n);

			return ret;
		}
		reverse_iterator operator-(difference_type n) const
		{
			reverse_iterator	ret(_p + n);

			return ret;
		}
		reverse_iterator& operator+=(difference_type n)
		{
			_p = _p - n;
			return *this;
		}
		reverse_iterator& operator-=(difference_type n)
		{
			_p = _p + n;
			return *this;			
		}
	};
	template <class Iterator1, class Iterator2>
	bool operator==(const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs)
	{
		if (lhs.base() == rhs.base())
			return true;
		return false;
	};
	template <class Iterator1, class Iterator2>
	bool operator!=(const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs)
	{
		if (lhs == rhs)
			return false;
		return true;
	};
	template <class Iterator1, class Iterator2>
	bool operator<(const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs)
	{
		if (lhs.base() > rhs.base())
			return true;
		return false;
	};
	template <class Iterator1, class Iterator2>
	bool operator<=(const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs)
	{
		if (lhs < rhs || lhs == rhs)
			return true;
		return false;
	};
	template <class Iterator1, class Iterator2>
	bool operator>(const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs)
	{
		if (lhs <= rhs)
			return false;
		return true;
	};
	template <class Iterator1, class Iterator2>
	bool operator>=(const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs)
	{
		if (lhs < rhs)
			return false;
		return true;
	};
	template <class Iter>
	ft::reverse_iterator<Iter> operator+(typename ft::reverse_iterator<Iter>::difference_type n, const ft::reverse_iterator<Iter>& it)
	{
		return it + n;
	};
	template <class Iterator>
	typename ft::reverse_iterator<Iterator>::difference_type operator-(const ft::reverse_iterator<Iterator>& lhs, const ft::reverse_iterator<Iterator>& rhs)
	{
		return rhs.base() - lhs.base();
	};
	template <class Iterator1, class Iterator2>
	typename ft::reverse_iterator<Iterator1>::difference_type operator-(const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs)
	{
		return rhs.base() - lhs.base();
	};
}

#endif
