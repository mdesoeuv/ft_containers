/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_map.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesoeuv <mdesoeuv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 16:35:49 by mdesoeuv          #+#    #+#             */
/*   Updated: 2022/05/06 16:44:24 by mdesoeuv         ###   ########lyon.fr   */
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
	
	myMap.display(myMap.root(), 0);
	
	myMap.clear();

	return (0);
}
