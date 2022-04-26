/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_vector.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesoeuv <mdesoeuv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 14:33:31 by mdesoeuv          #+#    #+#             */
/*   Updated: 2022/04/26 17:30:15 by mdesoeuv         ###   ########lyon.fr   */
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
		std::cout << "vector size : " << test_vector.size() << ", vector capacity : " << test_vector.capacity() << std::endl;
		test_vector.push_back(i);
	}

	std::cout << std::endl;

	for (size_t i = 0; i < test_vector.size(); ++i)
	{
		std::cout << test_vector[i] << std::endl;
	}
	std::cout << "vector size : " << test_vector.size() << ", vector capacity : " << test_vector.capacity() << std::endl;


	std::cout << std::endl << "vector pop_back :" << std::endl;
	test_vector.pop_back();
	for (size_t i = 0; i < test_vector.size(); ++i)
	{
		std::cout << test_vector[i] << std::endl;
	}
	std::cout << "vector size : " << test_vector.size() << ", vector capacity : " << test_vector.capacity() << std::endl;

	std::cout << "vector front element :" << test_vector.front() << std::endl;
	std::cout << "vector back element :" << test_vector.back() << std::endl;
	
	std::cout << "vector is empty : " << test_vector.empty() << std::endl;
	std::cout << "vector max_size : " << test_vector.max_size() << std::endl;
	std::cout << "--clearing vector--" << std::endl;
	test_vector.clear();
	std::cout << "vector is empty : " << test_vector.empty() << std::endl;
	std::cout << "vector contents :" << std::endl;
	for (size_t i = 0; i < test_vector.size(); ++i)
	{
		std::cout << test_vector[i] << std::endl;
	}
	std::cout << "vector size : " << test_vector.size() << ", vector capacity : " << test_vector.capacity() << std::endl << std::endl;

	std::cout << "filling vector to test insertions :" << std::endl;
	for (int i = 0; i < 5; ++i)
	{
		std::cout << test_vector[i] << std::endl;
		test_vector.push_back(i);
	}
	std::cout << "vector size : " << test_vector.size() << ", vector capacity : " << test_vector.capacity() << std::endl;

	std::cout << std::endl << "resizing vector (6, 0) :" << std::endl;
	test_vector.resize(6, 0);
	std::cout << "vector size : " << test_vector.size() << ", vector capacity : " << test_vector.capacity() << std::endl;
	for (size_t i = 0; i < test_vector.size(); ++i)
	{
		std::cout << test_vector[i] << std::endl;
	}
	
	std::cout << std::endl << "resizing vector (18, 100) :" << std::endl;
	test_vector.resize(18, 100);
	std::cout << "vector size : " << test_vector.size() << ", vector capacity : " << test_vector.capacity() << std::endl;
	for (size_t i = 0; i < test_vector.size(); ++i)
	{
		std::cout << test_vector[i] << std::endl;
	}
	
	ft::vector<int>::Iterator	iter = test_vector.begin();
	std::cout << std::endl << "testing basic iterator :" << std::endl;
	std::cout << *iter << std::endl;
	++iter;
	std::cout << *iter << std::endl;

	std::cout << std::endl << "erasing element at index 5 :" << std::endl;
	ft::vector<int>::Iterator	iter_five(test_vector, test_vector.size(), 5);
	test_vector.erase(iter_five);
	for (size_t i = 0; i < test_vector.size(); ++i)
	{
		std::cout << test_vector[i] << std::endl;
	}
	std::cout << "vector size : " << test_vector.size() << ", vector capacity : " << test_vector.capacity() << std::endl;
	
	std::cout << std::endl << std::endl << "erasing element from index 5 to end() :" << std::endl;
	test_vector.erase(iter_five, test_vector.end());
	for (size_t i = 0; i < test_vector.size(); ++i)
	{
		std::cout << test_vector[i] << std::endl;
	}
	std::cout << "vector size : " << test_vector.size() << ", vector capacity : " << test_vector.capacity() << std::endl;
	
	
	return (0);
}