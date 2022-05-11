/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_map.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesoeuv <mdesoeuv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 16:35:49 by mdesoeuv          #+#    #+#             */
/*   Updated: 2022/05/11 13:40:38 by mdesoeuv         ###   ########lyon.fr   */
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
	for (Map::const_iterator	const_it = secondMap.constbegin(); const_it != secondMap.constend(); ++const_it)
		std::cout << "key=" << (*const_it).first << ", value=" << const_it->second << std::endl;
	std::cout << std::endl << "backward display :" << std::endl;
	for (Map::const_iterator	const_it = secondMap.constend(); const_it != secondMap.constbegin();)
		std::cout << "key=" << (*--const_it).first << ", value=" << const_it->second << std::endl;
	// Map::const_iterator	const_itEnd = secondMap.end();
	
	std::cout << std::endl << "testing reverse iterator decrementation :" << std::endl;
	for (Map::reverse_iterator it = secondMap.rend(); it != secondMap.rbegin();)
	{
		it++;
		std::cout << "key=" << (*it).first << ", value=" << it->second << std::endl;
	}
	
	std::cout << std::endl << "testing reverse iterator incrementation :" << std::endl;
	for (Map::reverse_iterator it = secondMap.rbegin(); it != secondMap.rend(); ++it)
		std::cout << "key=" << (*it).first << ", value=" << it->second << std::endl;

	
	std::cout << std::endl << "--- clearing maps ---" << std::endl;
	myMap.clear();
	secondMap.clear();
	std::cout << "displaying first map :" << std::endl;
	myMap.display(myMap.root(), 0);
	std::cout << "size : " << myMap.size() << std::endl;
	std::cout << "displaying second map :" << std::endl;
	secondMap.display(secondMap.root(), 0);
	std::cout << "size : " << secondMap.size() << std::endl;
	std::cout << "is the first map empty ? " << myMap.empty() << std::endl;
	std::cout << "end of main" << std::endl;

	return (0);
}
