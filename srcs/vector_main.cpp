/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_main.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vico <vico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 03:57:30 by vico              #+#    #+#             */
/*   Updated: 2022/03/01 02:52:46 by vico             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.hpp"
#include <vector>
#include <iostream>

#define TYPE int
#define NAMESPACE ft

void	print_vec(NAMESPACE::vector<TYPE> vec)
{
	std::cout << "size = " << vec.size() << std::endl;
	std::cout << "capacity = " << vec.capacity() << std::endl;
	std::cout << "vector content :\n";
	for (NAMESPACE::vector<TYPE>::const_iterator cit(vec.begin()); cit != vec.end(); cit++)
		std::cout << *cit << " ";
	std::cout << std::endl;
}

int		main()
{
	NAMESPACE::vector<TYPE>	me(2, 3);

// Iterator
	std::cout << "Iterator" << std::endl;

	{
		NAMESPACE::vector<TYPE>::iterator ite(me.begin());

		std::cout << "\n----iterator----\n" << std::endl;
		while (ite != me.end())
		{
			std::cout << *ite << std::endl;
			ite++;
		}
	}
	{
		NAMESPACE::vector<TYPE>::iterator it(me.begin());
		NAMESPACE::vector<TYPE>::const_iterator ite(it);

		std::cout << "\n----const_iterator----\n" << std::endl;
		while (ite != me.end())
		{
			std::cout << *ite << std::endl;
			ite++;
		}
	}
	{
		NAMESPACE::vector<TYPE>::iterator it(me.end());
		NAMESPACE::vector<TYPE>::reverse_iterator ite(it);

		std::cout << "\n----reverse_iterator----\n" << std::endl;
		while (ite != me.rend())
		{
			std::cout << *ite << std::endl;
			ite++;
		}
	}
	{
		NAMESPACE::vector<TYPE>::reverse_iterator it(me.rbegin());
		NAMESPACE::vector<TYPE>::const_reverse_iterator ite(it);

		std::cout << "\n----const_reverse_iterator----\n" << std::endl;
		while (ite != me.rend())
		{
			std::cout << *ite << std::endl;
			ite++;
		}
	}

	std::cout << "\n-------------------------------\n" << std::endl;

//	Resize
	std::cout << "Resize" << std::endl;

	{
		for (size_t i(0); i < me.size(); i++)
			std::cout << me[i] << "|";
		std::cout << "\nsize = " << me.size() << ", capacity = " << me.capacity() << std::endl;	
		me.resize(3);
		for (size_t i(0); i < me.size(); i++)
			std::cout << me[i] << "|";
		std::cout << "\nsize = " << me.size() << ", capacity = " << me.capacity() << std::endl;
	}

	std::cout << "\n-------------------------------\n" << std::endl;

//	Reserve
	std::cout << "Reserve" << std::endl;

	{
		me.push_back(111);
		me.push_back(112);
		me.push_back(-28);
		for (size_t i(0); i < me.size(); i++)
			std::cout << me[i] << "|";
		std::cout << "\nsize = " << me.size() << ", capacity = " << me.capacity() << std::endl;

		me.reserve(10);
		std::cout << "\nreserve(10)" << std::endl;
		std::cout << "size = " << me.size() << ", capacity = " << me.capacity() << std::endl;
	}

	std::cout << "\n-------------------------------\n" << std::endl;

//	Assign
	std::cout << "Assign" << std::endl;

	{	
		NAMESPACE::vector<TYPE>::iterator	ite(me.begin() + 2);
	
		print_vec(me);
		me.insert(ite, 3, 101);
		print_vec(me);
	}

	std::cout << "\n-------------------------------\n" << std::endl;

//	Push_back
	std::cout << "Push_back" << std::endl;

	{
		print_vec(me);
		me.push_back(-65);
		me.push_back(-524);
		me.push_back(-87);
		print_vec(me);
		me.pop_back();
		me.pop_back();
		me.pop_back();
		print_vec(me);
	}

	std::cout << "\n-------------------------------\n" << std::endl;

//	Insert
	std::cout << "Insert" << std::endl;

	{
		NAMESPACE::vector<TYPE>	oth(4, 99);

		print_vec(me);
		print_vec(oth);
		me.insert(me.begin(), oth.begin(), oth.end());
		print_vec(me);
		print_vec(oth);
	}

	std::cout << "\n-------------------------------\n" << std::endl;

// Erase
	std::cout << "Erase" << std::endl;

	{
		NAMESPACE::vector<TYPE>::const_iterator	it;

		for (size_t i(0); i < me.size(); i++)
			std::cout << me[i] << "|";
		std::cout << std::endl;
		std::cout << "size = " << me.size() << ", capacity = " << me.capacity() << std::endl;
		it = me.erase(me.begin() + 1, me.end() - 1);
		for (size_t i(0); i < me.size(); i++)
			std::cout << me[i] << "|";
		std::cout << std::endl;
		std::cout << "size = " << me.size() << ", capacity = " << me.capacity() << ", it = " << *it << std::endl;
	}

	std::cout << "\n-------------------------------\n" << std::endl;

// Swap
	std::cout << "Swap" << std::endl;

	{
		NAMESPACE::vector<TYPE>	oth(3, 20);

		for (size_t i(0); i < me.size(); i++)
			std::cout << me[i] << "|";
		std::cout << std::endl;
		std::cout << "size = " << me.size() << ", capacity = " << me.capacity() << std::endl;
		for (size_t i(0); i < oth.size(); i++)
			std::cout << oth[i] << "|";
		std::cout << std::endl;
		std::cout << "size = " << oth.size() << ", capacity = " << oth.capacity() << std::endl;
		oth.swap(me);
		for (size_t i(0); i < me.size(); i++)
			std::cout << me[i] << "|";
		std::cout << std::endl;
		std::cout << "size = " << me.size() << ", capacity = " << me.capacity() << std::endl;
		for (size_t i(0); i < oth.size(); i++)
			std::cout << oth[i] << "|";
		std::cout << std::endl;
		std::cout << "size = " << oth.size() << ", capacity = " << oth.capacity() << std::endl;
	}

	std::cout << "\n-------------------------------\n" << std::endl;

// Clear
	std::cout << "Clear" << std::endl;

	{
		for (size_t i(0); i < me.size(); i++)
			std::cout << me[i] << "|";
		std::cout << std::endl;
		me.clear();
		for (size_t i(0); i < me.size(); i++)
			std::cout << me[i] << "|";
		std::cout << std::endl;		
	}

	std::cout << "\n-------------------------------\n" << std::endl;
	return (0);
}
