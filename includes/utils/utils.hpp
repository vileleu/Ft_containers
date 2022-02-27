/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vico <vico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 14:48:21 by vico              #+#    #+#             */
/*   Updated: 2022/02/08 15:41:09 by vico             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
#define UTILS_HPP

#include <memory>
#include <iostream>

namespace ft
{
	struct bidirectional_iterator_tag
	{
	};

	struct random_access_iterator_tag
	{
	};

	template <class Category, class T, class Distance = std::ptrdiff_t, class Pointer = T*, class Reference = T&>
	class iterator
	{
		public:

		typedef Category iterator_category;
		typedef T value_type;
		typedef	Distance difference_type;
		typedef Pointer pointer;
		typedef Reference reference;
	};

	template <class Iterator>
	class iterator_traits
	{
		public:
		
		typedef	typename Iterator::difference_type difference_type;
		typedef	typename Iterator::value_type value_type;
		typedef	typename Iterator::pointer pointer;
		typedef	typename Iterator::reference reference;
		typedef	typename Iterator::iterator_category iterator_category;
	};

	template <class T>
	class iterator_traits<T*>
	{
		public:

		typedef	std::ptrdiff_t difference_type;
		typedef T value_type;
		typedef T* pointer;
		typedef T& reference;
		typedef ft::random_access_iterator_tag iterator_category;
	};
	
	template <class T>
	class iterator_traits<const T*>
	{
		public:
		
		typedef	std::ptrdiff_t difference_type;
		typedef T value_type;
		typedef const T* pointer;
		typedef const T& reference;
		typedef ft::random_access_iterator_tag iterator_category;
	};

	template <class InputIterator1, class InputIterator2>
	bool	equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
	{
		while (first1 != last1)
		{
			if (!(*first1 == *first2))
				return (false);
			first1++;
			first2++;
		}
		return (true);
	}

	template <class InputIterator1, class InputIterator2>
	bool	lexicographical_compare(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2)
	{
		while (first1 != last1)
		{
			if (first2 == last2 || *first2 < *first1)
				return false;
			else if (*first1 < *first2)
				return true;
			first1++;
			first2++;
		}
		return (first2 != last2);
	}

	template <class T1, class T2>
	struct pair
	{
		public:

		typedef T1 first_type;
		typedef T2 second_type;

		first_type	first;
		second_type	second;

		pair() : first(first_type()), second(second_type())
		{
		}
		template<class U, class V>
		pair(const pair<U,V>& pr) : first(pr.first), second(pr.second)
		{
		}
		pair(const first_type& a, const second_type& b) : first(a), second(b)
		{
		}
		pair& operator=(const pair& pr)
		{
			first = pr.first;
			second = pr.second;
			return *this;
		}
	};
	template <class T1, class T2>
	bool operator==(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
	{
		if (lhs.first == rhs.first && lhs.second == rhs.second)
			return true;
		return false;
	}
	template <class T1, class T2>
	bool operator!=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
	{
		return (!(lhs == rhs));
	}
	template <class T1, class T2>
	bool operator<(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
	{
		return lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second);
	}
	template <class T1, class T2>
	bool operator<=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
	{
		return !(rhs < lhs);
	}
	template <class T1, class T2>
	bool operator>(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
	{
		return rhs < lhs;
	}
	template <class T1, class T2>
	bool operator>=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
	{
		return !(lhs < rhs);
	}

	template <class T1, class T2>
	pair<T1,T2> make_pair(T1 x, T2 y)
	{
		return pair<T1,T2>(x, y);
	};

	template <bool Cond, class T = void>
	struct enable_if
	{
	};
	template <class T>
	struct enable_if<true, T>
	{
		typedef T type;
	};

	template <typename T>
	struct is_integral
	{
		static const bool value = false;
	};
	template <>
	struct is_integral<bool>
	{
		static const bool value = true;
	};
	template <>
	struct is_integral<char>
	{
		static const bool value = true;
	};
	template <>
	struct is_integral<wchar_t>
	{
		static const bool value = true;
	};
	template <>
	struct is_integral<signed char>
	{
		static const bool value = true;
	};
	template <>
	struct is_integral<short int>
	{
		static const bool value = true;
	};
	template <>
	struct is_integral<int>
	{
		static const bool value = true;
	};
	template <>
	struct is_integral<long int>
	{
		static const bool value = true;
	};
	template <>
	struct is_integral<unsigned char>
	{
		static const bool value = true;
	};
	template <>
	struct is_integral<unsigned short int>
	{
		static const bool value = true;
	};
	template <>
	struct is_integral<unsigned int>
	{
		static const bool value = true;
	};
	template <>
	struct is_integral<unsigned long int>
	{
		static const bool value = true;
	};
}

#endif
