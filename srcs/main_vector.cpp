/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_vector.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesoeuv <mdesoeuv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 14:33:31 by mdesoeuv          #+#    #+#             */
/*   Updated: 2022/04/29 10:31:45 by mdesoeuv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <memory>
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
	iter += 3;
	std::cout << *iter << std::endl;
	iter -= 1;
	std::cout << *iter << std::endl;
	iter = test_vector.begin() + 1;
	std::cout << *iter << std::endl;
	iter = 1 + test_vector.begin();
	std::cout << *iter << std::endl;
	std::cout << *iter++ << std::endl;
	std::cout << *--iter << std::endl;
	std::cout << *iter-- << std::endl;
	std::cout << *iter << std::endl;
	std::cout << iter[3] << std::endl;
	
	const ft::vector<int>	const_vect(test_vector);
	ft::vector<int>::Const_Iterator	const_iter = const_vect.begin();
	std::cout << std::endl << "testing const iterator :" << std::endl;
	std::cout << *const_iter << std::endl;
	++const_iter;
	//*const_iter = 1000; does not compile because const_iterator returns const value_type when dereferenced
	std::cout << *const_iter << std::endl;

	std::cout << std::endl << "erasing element at index 5 :" << std::endl;
	ft::vector<int>::Iterator	iter_five(test_vector, 5);
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
	
	
	std::cout << std::endl << "testing insertion at index 3 :" << std::endl;
	ft::vector<int>::Iterator	iter_three(test_vector, 3);
	test_vector.insert(iter_three, 1000);
	for (size_t i = 0; i < test_vector.size(); ++i)
	{
		std::cout << test_vector[i] << std::endl;
	}
	std::cout << "vector size : " << test_vector.size() << ", vector capacity : " << test_vector.capacity() << std::endl;
	
	std::cout << std::endl << "testing vector swap :" << std::endl;
	ft::vector<std::string>	vs1;
	ft::vector<std::string>	vs2;
	vs1.reserve(15);
	vs1.push_back("coucou");
	vs1.push_back("hello");
	vs2.push_back("bye");
	std::cout << "s1 = " << vs1[0] << std::endl;
	std::cout << "vector size : " << vs1.size() << ", vector capacity : " << vs1.capacity() << std::endl;
	std::cout << "s2 = " << vs2[0] << std::endl;
	std::cout << "vector size : " << vs2.size() << ", vector capacity : " << vs2.capacity() << std::endl;
	std::cout << "--- swapping ---" << std::endl;
	vs1.swap(vs2);
	std::cout << "s1 = " << vs1[0] << std::endl;
	std::cout << "vector size : " << vs1.size() << ", vector capacity : " << vs1.capacity() << std::endl;
	std::cout << "s2 = " << vs2[0] << std::endl;
	std::cout << "vector size : " << vs2.size() << ", vector capacity : " << vs2.capacity() << std::endl;
	ft::vector<std::string>::Iterator	stringIter = vs1.begin();
	stringIter->push_back('t');
	std::cout << "s1 = " << stringIter[0] << std::endl;
	ft::vector<std::string>::Iterator	iterBegin;
	iterBegin = vs2.begin();
	ft::vector<std::string>::Iterator	iterEnd = vs2.end();
	std::cout << "testing if begin iterator < end iterator : ";
	if (iterBegin < iterEnd)
		std::cout << "true" << std::endl;
	else
		std::cout << "false" << std::endl;
	std::cout << "testing if end iterator > begin iterator : ";
	if (iterEnd > iterBegin)
		std::cout << "true" << std::endl;
	else
		std::cout << "false" << std::endl;
	std::cout << "testing if end iterator == begin iterator : ";
	if (iterEnd == iterBegin)
		std::cout << "true" << std::endl;
	else
		std::cout << "false" << std::endl;
	std::cout << "testing if end iterator != begin iterator : ";
	if (iterEnd != iterBegin)
		std::cout << "true" << std::endl;
	else
		std::cout << "false" << std::endl;

	std::cout << std::endl << "testing constructors :" << std::endl;
	ft::vector<std::string>		strVect(5, "lol");
	for (size_t i = 0; i < 5; ++i)
	{
		std::cout << strVect[i] << std::endl;
	}
	ft::vector<std::string>		strVect2(3);
	for (size_t i = 0; i < 3; ++i)
	{
		std::cout << strVect2[i] << std::endl;
	}

	ft::vector<std::string>		strVect3(strVect.begin(), strVect.end());
	for (ft::vector<std::string>::Iterator iter = strVect3.begin(); iter != strVect3.end(); ++iter)
		std::cout << *iter << std::endl;

	std::cout << std::endl << "comparing two identical vectors, is it equal ? " << std::endl;
	if (strVect == strVect3)
		std::cout << "true" << std::endl;
	else
		std::cout << "false" << std::endl;

	std::cout << std::endl << "is it different ? " << std::endl;
	if (strVect != strVect3)
		std::cout << "true" << std::endl;
	else
		std::cout << "false" << std::endl;

	std::cout << std::endl << "is it inferior ? " << std::endl;
	if (strVect < strVect3)
		std::cout << "true" << std::endl;
	else
		std::cout << "false" << std::endl;

	std::cout << std::endl << "is it inferior or equal ? " << std::endl;
	if (strVect <= strVect3)
		std::cout << "true" << std::endl;
	else
		std::cout << "false" << std::endl;
	std::cout << std::endl << "removing last element of copy and comparing, is it equal ? " << std::endl;
	strVect3.pop_back();
	
	if (strVect == strVect3)
		std::cout << "true" << std::endl;
	else
		std::cout << "false" << std::endl;

	std::cout << std::endl << "is it different ? " << std::endl;
	if (strVect != strVect3)
		std::cout << "true" << std::endl;
	else
		std::cout << "false" << std::endl;
	
	std::cout << std::endl << "is it inferior ? " << std::endl;
	if (strVect < strVect3)
		std::cout << "true" << std::endl;
	else
		std::cout << "false" << std::endl;
	
	std::cout << std::endl << "is it inferior or equal ? " << std::endl;
	if (strVect <= strVect3)
		std::cout << "true" << std::endl;
	else
		std::cout << "false" << std::endl;

	std::cout << std::endl << "testing reverse iterator incrementation:" << std::endl;
	ft::vector<int>	vectInt;
	for (int i = 0; i < 5; ++i)
		vectInt.push_back(i);
	ft::vector<int>::Reverse_Iterator r_iter = vectInt.rbegin();
	while (r_iter != vectInt.rend())
	{
		std::cout << *r_iter++ << std::endl;
	}
	std::cout << std::endl << "testing reverse iterator decrementation:" << std::endl;
	while (r_iter != vectInt.rbegin())
	{
		std::cout << *--r_iter << std::endl;
	}
	std::cout << "distance between rbegin() and rend(): " << vectInt.rend() - vectInt.rbegin() << std::endl;
	std::cout << "accessing element at index 1 : " << r_iter[1] << std::endl;

	std::cout << std::endl << "testing operator=, displaying copy :" << std::endl;
	ft::vector<int>	copyInt;
	copyInt = vectInt;
	std::cout << "vector size : " << vectInt.size() << ", vector capacity : " << vectInt.capacity() << std::endl;
	std::cout << "vector size : " << copyInt.size() << ", vector capacity : " << copyInt.capacity() << std::endl;
	for (ft::vector<int>::Iterator iter = copyInt.begin(); iter != copyInt.end(); ++iter)
		std::cout << *iter << std::endl;
	std::cout << "assigning a smaller vector without reallocation :" << std::endl;
	ft::vector<int> smallInt;
	smallInt.push_back(1000);
	copyInt = smallInt;
	std::cout << "vector size : " << smallInt.size() << ", vector capacity : " << smallInt.capacity() << std::endl;
	std::cout << "vector size : " << copyInt.size() << ", vector capacity : " << copyInt.capacity() << std::endl;
	for (ft::vector<int>::Iterator iter = copyInt.begin(); iter != copyInt.end(); ++iter)
		std::cout << *iter << std::endl;
	
	return (0);
}