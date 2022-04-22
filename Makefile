# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdesoeuv <mdesoeuv@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/22 12:05:49 by mdesoeuv          #+#    #+#              #
#    Updated: 2022/04/22 14:35:37 by mdesoeuv         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME	:=	ft_containers

CXX		:=	c++

CXXFLAGS	:=	-Wall -Werror -Wextra -std=c++98

SRCS	:=	main.cpp

SRCS_DIR	:=	srcs/

SRCS_FILES	:=	$(addprefix $(SRCS_DIR), $(SRCS))

OBJS	:=	$(SRCS:.cpp=.o)

OBJS_DIR	:=	objs/

OBJS_FILES	:=	$(addprefix $(OBJS_DIR), $(OBJS))

$(OBJS_DIR)%.o:	$(SRCS_DIR)%.cpp Makefile
				mkdir -p $(OBJS_DIR)
				$(CXX) $(CXXFLAGS) -c $< -o $@

all			:	$(NAME)

$(NAME)		:	$(OBJS_FILES)
				$(CXX) $(CXXFLAGS) $(OBJS_FILES) -o $(NAME)
				
				