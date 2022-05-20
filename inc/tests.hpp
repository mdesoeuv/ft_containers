/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesoeuv <mdesoeuv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 11:19:01 by mdesoeuv          #+#    #+#             */
/*   Updated: 2022/05/20 15:05:27 by mdesoeuv         ###   ########lyon.fr   */
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

int	test_stack(void);
int	test_vector(void);
int	test_map(void);
