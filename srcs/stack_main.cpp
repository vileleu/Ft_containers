/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_main.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vico <vico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 18:05:59 by vico              #+#    #+#             */
/*   Updated: 2022/02/27 19:47:18 by vico             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.hpp"
#include <stack>
#include <iostream>

#define TYPE int
#define NAMESPACE ft

void	print_stack(NAMESPACE::stack<TYPE> st, std::string name)
{
	NAMESPACE::stack<TYPE>	tmp;

	tmp = st;
	std::cout << "\nsize = " << tmp.size() << std::endl;
	std::cout << name << " content :\n";
	while (!tmp.empty())
	{
		std::cout << tmp.top() << " ";
		tmp.pop();
	}
	std::cout << "\n" << std::endl;
}

int		main()
{
	NAMESPACE::stack<TYPE> st;

	st.push(54);
	st.push(90);
	st.push(34);
	print_stack(st, "st");
	std::cout << "st empty : " << (st.empty() ? "true" : "false") << std::endl;

	NAMESPACE::stack<TYPE> copy;

	std::cout << "copy empty : " << (copy.empty() ? "true" : "false") << std::endl;
	copy = st;
	print_stack(copy, "copy");
	std::cout << "copy == st : " << (st == copy ? "true" : "false") << std::endl;
	copy.pop();
	std::cout << "copy == st : " << (st == copy ? "true" : "false") << std::endl;
	return 0;
}
