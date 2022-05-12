/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_map.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesoeuv <mdesoeuv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 16:35:49 by mdesoeuv          #+#    #+#             */
/*   Updated: 2022/05/12 10:16:47 by mdesoeuv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "../inc/map.hpp" 

#include <map>

int	main(void)
{
	typedef ft::map<int, std::string> Map;
	Map	myMap;
	myMap.insert(ft::make_pair<int, std::string>(10, "first"));
	myMap.insert(ft::make_pair<int, std::string>(15, "second"));
	myMap.insert(ft::make_pair<int, std::string>(5, "third"));
	myMap.insert(ft::make_pair<int, std::string>(0, "fourth"));
	// myMap.insert(ft::make_pair<int, std::string>(30, "lol"));
	// myMap.insert(ft::make_pair<int, std::string>(42, "lol2"));
	
	myMap.display(myMap.root(), 0);
	std::cout << "size : " << myMap.size() << std::endl;
	
	std::cout << std::endl << "creating a second map :" << std::endl;
	Map secondMap;
	secondMap.insert(ft::make_pair<int, std::string>(-1000, "minus thousand"));
	secondMap.display(secondMap.root(), 0);
	std::cout << "size : " << secondMap.size() << std::endl;

	std::cout << std::endl << "--- swaping maps ---" << std::endl;
	myMap.swap(secondMap);
	std::cout << "displaying first map :" << std::endl;
	myMap.display(myMap.root(), 0);
	std::cout << "size : " << myMap.size() << std::endl;
	std::cout << std::endl << "displaying second map :" << std::endl;
	secondMap.display(secondMap.root(), 0);
	std::cout << "size : " << secondMap.size() << std::endl;

	std::cout << std::endl << "searching for element with key = -1000 in first map : " <<  myMap.count(-1000) << std::endl;
	std::cout << "searching for element with key = 777 in first map : " <<  myMap.count(777) << std::endl;
	std::cout << "is the first map empty ? " << myMap.empty() << std::endl;
	
	// Map::iterator	it = secondMap.begin();
	std::cout << std::endl << "testing iterators with in order display :" << std::endl;
	for (Map::iterator	it = secondMap.begin(); it != secondMap.end(); ++it)
		std::cout << "key=" << (*it).first << ", value=" << it->second << std::endl;
	std::cout << std::endl << "backward display :" << std::endl;
	for (Map::iterator	it = secondMap.end(); it != secondMap.begin();)
		std::cout << "key=" << (*--it).first << ", value=" << it->second << std::endl;
	// Map::iterator	itEnd = secondMap.end();
	
	
	/////// prendre une ref constante sur la map a utiliser
	// Map::const_iterator	const_it = secondMap.begin();
	std::cout << std::endl << "testing const iterators with in order display :" << std::endl;
	for (Map::const_iterator	const_it = secondMap.begin(); const_it != secondMap.end(); ++const_it)
		std::cout << "key=" << (*const_it).first << ", value=" << const_it->second << std::endl;
	std::cout << std::endl << "backward display :" << std::endl;
	for (Map::const_iterator	const_it = secondMap.end(); const_it != secondMap.begin();)
		std::cout << "key=" << (*--const_it).first << ", value=" << const_it->second << std::endl;
	// Map::const_iterator	const_itEnd = secondMap.end();
	
	std::cout << std::endl << "testing reverse iterator incrementation :" << std::endl;
	for (Map::reverse_iterator it = secondMap.rbegin(); it != secondMap.rend(); ++it)
		std::cout << "key=" << (*it).first << ", value=" << it->second << std::endl;
	
	std::cout << std::endl << "testing reverse iterator decrementation :" << std::endl;
	for (Map::reverse_iterator it = secondMap.rend(); it != secondMap.rbegin();)
	{ 
		it--;
		std::cout << "key=" << (*it).first << ", value=" << it->second << std::endl;
	}

	std::cout << std::endl << "< testing find() function >" << std::endl;
	std::cout << "is key 7 found ? "; 
	if (secondMap.find(7) != secondMap.end())
		std::cout << "true" << std::endl;
	else
		std::cout << "false" << std::endl;
	std::cout << "is key 10 found ? "; 
	if (secondMap.find(10) != secondMap.end())
		std::cout << "true" << std::endl;
	else
		std::cout << "false" << std::endl;

	std::cout << std::endl << "< testing equal_range and lower_bound upper_bound function >" << std::endl;
	ft::pair<Map::iterator, Map::iterator> pair_range = secondMap.equal_range(3);
	std::cout << "displaying key of equal_range(3) : " << pair_range.first->first << ", " << pair_range.second->first << std::endl;
	pair_range = secondMap.equal_range(5);
	std::cout << "displaying key of equal_range(5) : " << pair_range.first->first << ", " << pair_range.second->first << std::endl;
	std::cout << "displaying key of upper_bound(0) : " << secondMap.upper_bound(0)->first << std::endl;
	std::cout << "displaying key of upper_bound(3) : " << secondMap.upper_bound(3)->first << std::endl;
	std::cout << "displaying key of upper_bound(15) : ";
	if (secondMap.upper_bound(15) == secondMap.end())
		std::cout << "end()" << std::endl;
	std::cout << "displaying key of lower_bound(0) : " << secondMap.lower_bound(0)->first << std::endl;
	std::cout << "displaying key of lower_bound(3) : " << secondMap.lower_bound(3)->first << std::endl;
	std::cout << "displaying key of lower_bound(15) : " << secondMap.lower_bound(15)->first << std::endl;
	std::cout << "displaying key of lower_bound(20) : ";
	if (secondMap.lower_bound(20) == secondMap.end())
		std::cout << "end()" << std::endl;
	std::cout << "testing if references from iterators are valid are writable : look for the ZOB" << std::endl;
	pair_range.first->second = "ZOB";
	secondMap.display(secondMap.root(), 0);

	std::cout << std::endl << "< testing at(key) function >" << std::endl;
	std::cout << "value at key = 5 is : " << secondMap.at(5) << std::endl;
	std::cout << "value at key = 12 is : ";
	try
	{
		std::cout << secondMap.at(12) << std::endl;
	}
	catch (std::out_of_range& e)
	{
		std::cout << e.what() << std::endl;
	}

	std::cout << std::endl << "< testing operator== >" << std::endl;
	std::cout << "map 1 == map 2 : " << (myMap == secondMap) << std::endl;
	std::cout << "map 1 != map 2 : " << (myMap != secondMap) << std::endl;
	std::cout << "map 2 == map 2 : " << (secondMap == secondMap) << std::endl;
	std::cout << "map 2 != map 2 : " << (secondMap != secondMap) << std::endl;
	std::cout << "map 1 < map 2 : " << (myMap < secondMap) << std::endl;
	std::cout << "map 2 < map 1 : " << (secondMap < myMap) << std::endl;
	std::cout << "map 1 <= map 2 : " << (myMap <= secondMap) << std::endl;
	std::cout << "map 1 <= map 1 : " << (myMap <= myMap) << std::endl;
	std::cout << "map 1 >= map 2 : " << (myMap >= secondMap) << std::endl;
	std::cout << "map 1 >= map 1 : " << (myMap <= myMap) << std::endl;
	std::cout << std::endl << "--- clearing maps ---" << std::endl;
	myMap.clear();
	secondMap.clear();
	std::cout << "map 1 < map 2 : " << (myMap < secondMap) << std::endl;
	std::cout << "map 2 < map 1 : " << (secondMap < myMap) << std::endl;
	std::cout << "map 1 == map 2 : " << (myMap == secondMap) << std::endl;
	std::cout << "displaying first map :" << std::endl;
	myMap.display(myMap.root(), 0);
	std::cout << "size : " << myMap.size() << std::endl;
	std::cout << "displaying second map :" << std::endl;
	secondMap.display(secondMap.root(), 0);
	std::cout << "size : " << secondMap.size() << std::endl;
	std::cout << "is the first map empty ? " << myMap.empty() << std::endl;

	std::cout << "max_size : " << secondMap.max_size() << std::endl;
	std::cout << "end of main" << std::endl;

	return (0);
}
