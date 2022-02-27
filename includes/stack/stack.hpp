/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vico <vico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 18:03:26 by vico              #+#    #+#             */
/*   Updated: 2022/02/26 19:07:07 by vico             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
#define STACK_HPP

#include "vector.hpp"

namespace ft
{
	template <class T, class Container = ft::vector<T> >
	class stack
	{
		public:

		typedef Container container_type;
		typedef typename Container::value_type value_type;
		typedef typename Container::size_type size_type;
		typedef typename Container::reference reference;
		typedef typename Container::const_reference const_reference;

		protected:

		container_type c;

		public:

		// Constructor
		explicit stack(const Container& cont = Container())
		{
			c = cont;
		}
		// Destructor
		~stack()
		{
		}
		// Operator Copy
		stack& operator=(const stack& other)
		{
			c = other.c;
			return *this;
		}
		reference	top()
		{
			return c.back();
		}
		const_reference	top() const
		{
			return c.back();
		}
		bool	empty() const
		{
			return c.empty();
		}
		size_type	size() const
		{
			return c.size();
		}
		void	push(const value_type& value)
		{
			c.push_back(value);
		}
		void	pop()
		{
			c.pop_back();
		}
		template <class V, class Cont>
		friend bool	operator==(const ft::stack<V, Cont>& lhs, const ft::stack<V, Cont>& rhs);

		template <class V, class Cont>
		friend bool	operator<(const ft::stack<V, Cont>& lhs, const ft::stack<V, Cont>& rhs);
	};
	template <class T, class Container>
	bool	operator==(const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs)
	{
		if (lhs.c == rhs.c)
			return true;
		return false;
	}
	template <class T, class Container>
	bool	operator!=(const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs)
	{
		if (lhs == rhs)
			return false;
		return true;
	}
	template <class T, class Container>
	bool	operator<(const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs)
	{
		if (lhs.c < rhs.c)
			return true;
		return false;
	}
	template <class T, class Container>
	bool	operator<=(const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs)
	{
		if (lhs < rhs || lhs == rhs)
			return true;
		return false;
	}
	template <class T, class Container>
	bool	operator>(const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs)
	{
		if (lhs <= rhs)
			return false;
		return true;
	}
	template <class T, class Container>
	bool	operator>=(const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs)
	{
		if (lhs < rhs)
			return false;
		return true;
	}
}

#endif
