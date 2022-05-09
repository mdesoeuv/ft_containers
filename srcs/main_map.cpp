/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_map.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesoeuv <mdesoeuv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 16:35:49 by mdesoeuv          #+#    #+#             */
/*   Updated: 2022/05/09 17:17:48 by mdesoeuv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "../inc/map.hpp" 

#include <map>

int	main(void)
{
	typedef ft::map<int, std::string> Map;
	Map	myMap;
	std::cout << "ici" << std::endl;
	myMap.insert(ft::make_pair<int, std::string>(10, "first"));
	std::cout << "there" << std::endl;
	myMap.insert(ft::make_pair<int, std::string>(15, "second"));
	myMap.insert(ft::make_pair<int, std::string>(5, "third"));
	myMap.insert(ft::make_pair<int, std::string>(0, "fourth"));
	
	myMap.display(myMap.root(), 0);
	
	std::cout << std::endl << "creating a second map :" << std::endl;
	Map secondMap;
	secondMap.insert(ft::make_pair<int, std::string>(-1000, "minus thousand"));
	secondMap.display(secondMap.root(), 0);

	std::cout << std::endl << "--- swaping maps ---" << std::endl;
	myMap.swap(secondMap);
	std::cout << "displaying first map :" << std::endl;
	myMap.display(myMap.root(), 0);
	std::cout << "displaying second map :" << std::endl;
	secondMap.display(secondMap.root(), 0);
	
	std::cout << std::endl << "--- clearing maps ---" << std::endl;
	myMap.clear();
	secondMap.clear();
	std::cout << "displaying first map :" << std::endl;
	myMap.display(myMap.root(), 0);
	std::cout << "displaying second map :" << std::endl;
	secondMap.display(secondMap.root(), 0);
	std::cout << "end of main" << std::endl;
	return (0);
}
