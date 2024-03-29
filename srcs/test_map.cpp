/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_map.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesoeuv <mdesoeuv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 16:35:49 by mdesoeuv          #+#    #+#             */
/*   Updated: 2022/05/20 16:38:15 by mdesoeuv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/tests.hpp" 

int	test_map(void)
{
	Map	myMap;
	CHECK_STATUS(myMap);
	myMap.insert(lib::make_pair(10, "first"));
	myMap.insert(lib::make_pair(15, "second"));
	myMap.insert(lib::make_pair(5, "third"));
	lib::pair<Map::iterator, bool> insertion_result;
	insertion_result = myMap.insert(lib::make_pair(0, "fourth"));
	std::cout << "insertion success of non double element : " << insertion_result.second << std::endl;
	std::cout << "iterator on the inserted element : " << insertion_result.first->first << std::endl;
	insertion_result = myMap.insert(lib::make_pair(0, "fourth"));
	std::cout << "insertion success of non double element : " << insertion_result.second << std::endl;
	std::cout << "iterator on the inserted element : " << insertion_result.first->first << std::endl;
	// myMap.insert(lib::make_pair(30, "lol"));
	// myMap.insert(lib::make_pair(42, "lol2"));
	std::cout << "insertion with operator[], inserting key 3, value HERE" << std::endl;
	myMap[3] = "HERE";
	std::cout << myMap[3] << std::endl;
	CHECK_STATUS(myMap);
	insertion_result = myMap.insert(lib::make_pair(-12, "lol"));
	std::cout << "insertion success : " << insertion_result.second << std::endl;
	insertion_result = myMap.insert(lib::make_pair(-15, "third"));
	std::cout << "insertion success : " << insertion_result.second << std::endl;
	insertion_result = myMap.insert(lib::make_pair(-25, "third"));
	std::cout << "insertion success : " << insertion_result.second << std::endl;
	insertion_result = myMap.insert(lib::make_pair(-35, "third"));
	std::cout << "insertion success : " << insertion_result.second << std::endl;
	CHECK_STATUS(myMap);
	std::cout << "inserting value with predecessor as hint : " << myMap.insert(insertion_result.first, lib::make_pair(-30, "INSERTED HINT"))->second << std::endl;
	// std::cout << "inserting value with predecessor as hint : " << myMap.insert(insertion_result.first, lib::make_pair(-30, "INSERTED HINT"))->second << std::endl;
	CHECK_STATUS(myMap);
	
	std::cout << std::endl << "creating a second map :" << std::endl;
	Map secondMap;
	secondMap.insert(lib::make_pair(-1000, "minus thousand"));
	CHECK_STATUS(secondMap);

	std::cout << std::endl << "--- swaping maps ---" << std::endl;
	myMap.swap(secondMap);
	std::cout << "displaying first map :" << std::endl;
	CHECK_STATUS(myMap);
	std::cout << std::endl << "displaying second map :" << std::endl;
	CHECK_STATUS(secondMap);

	std::cout << std::endl << "searching for element with key = -1000 in first map with count() : " <<  myMap.count(-1000) << std::endl;
	std::cout << "searching for element with key = 777 in first map with count () : " <<  myMap.count(777) << std::endl;
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
	lib::pair<Map::iterator, Map::iterator> pair_range = secondMap.equal_range(3);
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
	secondMap.begin()->second = "ZOB";
	CHECK_STATUS(secondMap);

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

	std::cout << std::endl << "< testing erase functions >" << std::endl;
	std::cout << "erasing the node key=5, value=ZOB" << std::endl;
	secondMap.erase(5);
	CHECK_STATUS(secondMap);

	std::cout << std::endl << "erasing the iter=begin()" << std::endl;
	secondMap.erase(secondMap.begin());
	CHECK_STATUS(secondMap);
	std::cout << std::endl << "removing root node :" << std::endl;
	secondMap.erase(3);
	CHECK_STATUS(secondMap);

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
	
	std::cout << std::endl << "< testing operator= >" << std::endl;
	Map	thirdMap;
	thirdMap.insert(lib::make_pair(42, "forty-two"));
	std::cout << "before assignation :" << std::endl;
	CHECK_STATUS(thirdMap);
	std::cout << "after assignation :" << std::endl;
	thirdMap = secondMap;
	std::cout << "is assigned map really equal to other map : " << (thirdMap == secondMap) << std::endl;
	CHECK_STATUS(thirdMap);
	CHECK_STATUS(secondMap);

	std::cout << std::endl << "construction by copy :" << std::endl;
	Map fourthMap(thirdMap);
	CHECK_STATUS(fourthMap);

	std::cout << std::endl << "changing element in previous map to prove deep copy :" << std::endl;
	thirdMap.insert(lib::make_pair(42, "forty-two"));
	CHECK_STATUS(thirdMap);
	std::cout << std::endl;
	CHECK_STATUS(fourthMap); 
	std::cout << std::endl << "removing root key: " << std::endl;
	fourthMap.erase(0);
	CHECK_STATUS(fourthMap);

	std::cout << std::endl << "erasing with iterators" << std::endl;
	std::cout << "begin : " << fourthMap.begin()->first << ", end : " << fourthMap.rbegin()->first << std::endl;
	fourthMap.erase(fourthMap.begin(), fourthMap.end());
	std::cout << "display :" << std::endl;
	CHECK_STATUS(fourthMap);
	
	CHECK_STATUS(myMap);
	std::cout << "second map status" << std::endl;
	CHECK_STATUS(secondMap);
	CHECK_STATUS(thirdMap);
	CHECK_STATUS(fourthMap);
	
	std::cout << std::endl << "--- clearing maps ---" << std::endl;
	myMap.clear();
	secondMap.clear();
	std::cout << "map 1 < map 2 : " << (myMap < secondMap) << std::endl;
	std::cout << "map 2 < map 1 : " << (secondMap < myMap) << std::endl;
	std::cout << "map 1 == map 2 : " << (myMap == secondMap) << std::endl;
	std::cout << "displaying first map :" << std::endl;
	CHECK_STATUS(myMap);
	std::cout << "displaying second map :" << std::endl;
	CHECK_STATUS(secondMap);
	std::cout << "is the first map empty ? " << myMap.empty() << std::endl;

	std::cout << "max_size : " << secondMap.max_size() << std::endl;

	Map	fifthMap;
	std::cout << "last test with 1000 elements inserted one by one to check perfs" << std::endl;
	for (int i = 0; i < 1000; ++i)
	{
		fifthMap.insert(lib::make_pair(i, "string"));
	}
	CHECK_STATUS(fifthMap);
	fifthMap.erase(fifthMap.begin());
	CHECK_STATUS(fifthMap);
	fifthMap.erase(--fifthMap.end());
	CHECK_STATUS(fifthMap);

	std::cout << "end of main" << std::endl;

	return (0);
}
