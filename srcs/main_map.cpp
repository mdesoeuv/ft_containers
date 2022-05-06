/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_map.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesoeuv <mdesoeuv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 16:35:49 by mdesoeuv          #+#    #+#             */
/*   Updated: 2022/05/06 11:29:50 by mdesoeuv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "../inc/map.hpp"

#include <map>

int	main(void)
{
	ft::map<int, std::string>	myMap;
	myMap.insert(myMap.root(), ft::make_pair<int, std::string>(10, "first"));
	std::cout << "there" << std::endl;
	myMap.insert(myMap.root(), ft::make_pair<int, std::string>(15, "second"));
	
	// myMap->clear(myMap);

	return (0);
}
