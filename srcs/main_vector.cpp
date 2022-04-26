/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_vector.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesoeuv <mdesoeuv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 14:33:31 by mdesoeuv          #+#    #+#             */
/*   Updated: 2022/04/26 09:22:54 by mdesoeuv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "../inc/stack.hpp"
#include "../inc/vector.hpp"

int main(void)
{

	ft::vector<int> test_vector;

	std::cout << "testing vector implementation :" << std::endl << std::endl;
	for (int i = 0; i < 10; ++i)
	{
		test_vector.push_back(i);
	}

	return (0);
}