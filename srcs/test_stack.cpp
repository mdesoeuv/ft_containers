/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_stack.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesoeuv <mdesoeuv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 14:33:31 by mdesoeuv          #+#    #+#             */
/*   Updated: 2022/05/20 15:05:14 by mdesoeuv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/tests.hpp"

int test_stack(void)
{

	lib::stack<int> test_stack;

	std::cout << "testing stack implementation :" << std::endl << std::endl;
	for (int i = 0; i < 10; ++i)
	{
		test_stack.push(i);
	}

	lib::stack<int> copy_stack(test_stack);

	std::cout << "is the copy identical ?" << std::endl;
	if (copy_stack == test_stack)
		std::cout << "yes" << std::endl;
	else
		std::cout << "no" << std::endl;

	std::cout << "is the copy different ?" << std::endl;
	if (copy_stack != test_stack)
		std::cout << "yes" << std::endl;
	else
		std::cout << "no" << std::endl;

	std::cout << "is the copy superior ?" << std::endl;
	if (copy_stack > test_stack)
		std::cout << "yes" << std::endl;
	else
		std::cout << "no" << std::endl;

	std::cout << "is the copy inferior ?" << std::endl;
	if (copy_stack < test_stack)
		std::cout << "yes" << std::endl;
	else
		std::cout << "no" << std::endl;

	std::cout << "is the copy superior or equal ?" << std::endl;
	if (copy_stack >= test_stack)
		std::cout << "yes" << std::endl;
	else
		std::cout << "no" << std::endl;

	std::cout << "is the copy inferior or equal ?" << std::endl;
	if (copy_stack <= test_stack)
		std::cout << "yes" << std::endl;
	else
		std::cout << "no" << std::endl;
	
	std::cout << std::endl << "testing stack :" << std::endl;
	for (int i = 0; i < 10; ++i)
	{
		std::cout << "top = " << test_stack.top() << std::endl;
		std::cout << "size = " << test_stack.size() << std::endl << std::endl;
		test_stack.pop();
	}

	std::cout << std::endl << "testing copy constructed stack :" << std::endl;
	for (int i = 0; i < 10; ++i)
	{
		std::cout << "top = " << copy_stack.top() << std::endl;
		std::cout << "size = " << copy_stack.size() << std::endl << std::endl;
		copy_stack.pop();
	}
	return (0);
}