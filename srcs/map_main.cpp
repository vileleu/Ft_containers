/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_main.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vico <vico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 18:05:27 by vico              #+#    #+#             */
/*   Updated: 2022/02/26 19:19:20 by vico             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.hpp"
#include <map>
#include <iostream>

#define TYPE1 int
#define TYPE2 char
#define NAMESPACE ft

void	print_map(NAMESPACE::map<TYPE1, TYPE2> mp)
{
	std::cout << "size = " << mp.size() << std::endl;
	std::cout << "map content :\n";
	for (NAMESPACE::map<TYPE1, TYPE2>::const_iterator cit(mp.begin()); cit != mp.end(); cit++)
		std::cout << "first = " << cit->first << ", second = " << cit->second << std::endl;
	std::cout << std::endl;
}

int		main()
{
	NAMESPACE::map<TYPE1, TYPE2>	me;

	me.insert(NAMESPACE::make_pair(8, 'l'));
	me.insert(NAMESPACE::make_pair(7, 'f'));
	me.insert(NAMESPACE::make_pair(100, 'M'));
	me.insert(NAMESPACE::make_pair(3, 'R'));
	me.insert(NAMESPACE::make_pair(10, 'u'));

// Iterator
	std::cout << "Iterator" << std::endl;

	{
		NAMESPACE::map<TYPE1, TYPE2>::iterator ite(me.begin());

		std::cout << "\n----iterator----\n" << std::endl;
		while (ite != me.end())
		{
			std::cout << "first = " << ite->first << ", second = " << ite->second << std::endl;
			ite++;
		}
	}
	{
		NAMESPACE::map<TYPE1, TYPE2>::const_iterator ite(me.begin());

		std::cout << "\n----const_iterator----\n" << std::endl;
		while (ite != me.end())
		{
			std::cout << "first = " << ite->first << ", second = " << ite->second << std::endl;
			ite++;
		}
	}
	{
		NAMESPACE::map<TYPE1, TYPE2>::reverse_iterator ite(me.rbegin());

		std::cout << "\n----reverse_iterator----\n" << std::endl;
		while (ite != me.rend())
		{
			std::cout << "first = " << ite->first << ", second = " << ite->second << std::endl;
			ite++;
		}
	}
	{
		NAMESPACE::map<TYPE1, TYPE2>::const_reverse_iterator ite(me.rbegin());

		std::cout << "\n----const_reverse_iterator----\n" << std::endl;
		while (ite != me.rend())
		{
			std::cout << "first = " << ite->first << ", second = " << ite->second << std::endl;
			ite++;
		}
	}

	std::cout << "\n-------------------------------\n" << std::endl;

//	Insert
	std::cout << "Insert" << std::endl;
	NAMESPACE::map<TYPE1, TYPE2>	oth;
	
	{
		print_map(oth);
		std::cout << "insert this :" << std::endl;
		print_map(me);
		oth.insert(me.begin(), me.end());
		oth.insert(NAMESPACE::make_pair(76, 'O'));
		oth.insert(NAMESPACE::make_pair(30, 'O'));
		oth.insert(NAMESPACE::make_pair(1, 'O'));
		print_map(oth);
	}

	std::cout << "\n-------------------------------\n" << std::endl;

//	Find
	std::cout << "Find" << std::endl;

	{
		for (NAMESPACE::map<TYPE1, TYPE2>::iterator it(me.begin()); it != me.end(); it++)
		{
			if (oth.find(it->first) != oth.end())
				std::cout << oth[it->first] << "|";
		}
		std::cout << std::endl;
	}

	std::cout << "\n-------------------------------\n" << std::endl;

// Erase
	std::cout << "Erase" << std::endl;

	{
		for (NAMESPACE::map<TYPE1, TYPE2>::iterator it(me.begin()); it != me.end(); it++)
			std::cout << "first = " << it->first << ", second = " << it->second << std::endl;
		std::cout << "AFTER ERASE" << std::endl;
		me.erase(10);
		me.erase(7);
		for (NAMESPACE::map<TYPE1, TYPE2>::iterator it(me.begin()); it != me.end(); it++)
			std::cout << "first = " << it->first << ", second = " << it->second << std::endl;
	}

	std::cout << "\n-------------------------------\n" << std::endl;

// Swap
	std::cout << "Swap" << std::endl;

	{
		for (NAMESPACE::map<TYPE1, TYPE2>::iterator it(me.begin()); it != me.end(); it++)
			std::cout << "first = " << it->first << ", second = " << it->second << std::endl;
		std::cout << std::endl;
		for (NAMESPACE::map<TYPE1, TYPE2>::iterator it(oth.begin()); it != oth.end(); it++)
			std::cout << "first = " << it->first << ", second = " << it->second << std::endl;
		me.swap(oth);
		std::cout << "AFTER SWAP" << std::endl;
		for (NAMESPACE::map<TYPE1, TYPE2>::iterator it(me.begin()); it != me.end(); it++)
			std::cout << "first = " << it->first << ", second = " << it->second << std::endl;
		std::cout << std::endl;
		for (NAMESPACE::map<TYPE1, TYPE2>::iterator it(oth.begin()); it != oth.end(); it++)
			std::cout << "first = " << it->first << ", second = " << it->second << std::endl;
	}

	std::cout << "\n-------------------------------\n" << std::endl;

// Clear
	std::cout << "Clear" << std::endl;

	{
		std::cout << "size = " << me.size() << std::endl;
		for (NAMESPACE::map<TYPE1, TYPE2>::iterator it(me.begin()); it != me.end(); it++)
			std::cout << "first = " << it->first << ", second = " << it->second << std::endl;
		std::cout << "AFTER CLEAR" << std::endl;
		me.clear();
		std::cout << "size = " << me.size() << std::endl;
		for (NAMESPACE::map<TYPE1, TYPE2>::iterator it(me.begin()); it != me.end(); it++)
			std::cout << "first = " << it->first << ", second = " << it->second << std::endl;
	}

	std::cout << "\n-------------------------------\n" << std::endl;

// Bound
	std::cout << "Bound" << std::endl;
	
	{
		NAMESPACE::map<TYPE1, TYPE2> mp;
		NAMESPACE::map<TYPE1, TYPE2>::iterator itlow,itup;

		mp[20] = 'a';
		mp[40] = 'b';
		mp[60] = 'c';
		mp[80] = 'd';
		mp[100] = 'e';
		for (NAMESPACE::map<TYPE1, TYPE2>::iterator it(mp.begin()); it != mp.end(); it++)
			std::cout << "first = " << it->first << ", second = " << it->second << std::endl;
		std::cout << "\nlower = " << (itlow = mp.lower_bound(20))->first << std::endl;
		std::cout << "upper = " << (itup = mp.upper_bound(79))->first << "\n" << std::endl;
		mp.erase(itlow,itup);
		for (NAMESPACE::map<TYPE1, TYPE2>::iterator it = mp.begin(); it != mp.end(); ++it)
    		std::cout << it->first << " => " << it->second << '\n';
	}

		std::cout << "\n-------------------------------\n" << std::endl;
	return 0;
}
