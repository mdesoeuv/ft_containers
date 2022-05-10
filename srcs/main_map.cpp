/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_map.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesoeuv <mdesoeuv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 16:35:49 by mdesoeuv          #+#    #+#             */
/*   Updated: 2022/05/10 16:23:03 by mdesoeuv         ###   ########lyon.fr   */
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
	
	Map::iterator	it = myMap.begin();
	std::cout << std::endl << "testing iterators :" << std::endl;
	std::cout << "dereferencing begin: " << "key=" << (*it).first << ", value=" << it->second << std::endl;
	Map::iterator	itEnd = myMap.end();
	std::cout << 
	
	
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
