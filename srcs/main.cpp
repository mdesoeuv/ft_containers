/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesoeuv <mdesoeuv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 14:33:31 by mdesoeuv          #+#    #+#             */
/*   Updated: 2022/04/25 11:01:47 by mdesoeuv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "../inc/stack.hpp"

int main(void)
{

	ft::stack<int> test_stack;

	for (int i = 0; i < 10; ++i)
	{
		test_stack.push(i);
	}
	for (int i = 0; i < 10; ++i)
	{
		std::cout << "top = " << test_stack.top() << std::endl;
		std::cout << "size = " << test_stack.size() << std::endl << std::endl;
		test_stack.pop();
	}
	return (0);
}