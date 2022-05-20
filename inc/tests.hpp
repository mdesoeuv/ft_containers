/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesoeuv <mdesoeuv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 11:19:01 by mdesoeuv          #+#    #+#             */
/*   Updated: 2022/05/20 16:17:39 by mdesoeuv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <string>
#include <deque>
#include <stdlib.h>

#define STL 1
#define FT 0

#if CHOICE == STL
	#include <map>
	#include <stack>
	#include <vector>
	namespace lib = std;
#else
	#include "../inc/map.hpp"
	#include "../inc/stack.hpp"
	#include "../inc/vector.hpp"
	namespace lib = ft;
#endif

typedef lib::map<int, std::string> Map;

#ifdef CHECK_STATUS_ON
# if CHOICE == STL
#  define CHECK_STATUS(fuckMap) std::cout << std::endl << "map validity status : " << 1 << std::endl;					\
							for (Map::iterator iter = fuckMap.begin(); iter != fuckMap.end(); ++iter)				\
							{																						\
								std::cout << "key : " << iter->first << ", value :" << iter->second << std::endl;	\
							}																						\
							std::cout << "size : " << fuckMap.size() << std::endl << std::endl;							\

# else 
#  define CHECK_STATUS(map) map.status();
# endif
#else
# define CHECK_STATUS(map)
#endif


int	test_stack(void);
int	test_vector(void);
int	test_map(void);
