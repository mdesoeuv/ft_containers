/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_map.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesoeuv <mdesoeuv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 16:35:49 by mdesoeuv          #+#    #+#             */
/*   Updated: 2022/05/05 17:37:10 by mdesoeuv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "../inc/map.hpp"

int	main(void)
{
	ft::map<int, std::string>::TreeNode*	myMap = NULL;
	myMap->insert(myMap, ft::make_pair<int, std::string>(10, "first"));
	std::cout << "there" << std::endl;
	myMap->insert(myMap, ft::make_pair<int, std::string>(15, "second"));
	
	// myMap->clear(myMap);

	return (0);
}
