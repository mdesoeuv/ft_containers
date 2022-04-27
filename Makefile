# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdesoeuv <mdesoeuv@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/22 12:05:49 by mdesoeuv          #+#    #+#              #
#    Updated: 2022/04/27 16:10:06 by mdesoeuv         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME	:=	ft_containers

CXX		:=	c++

CXXFLAGS	:=	-Wall -Werror -Wextra -std=c++98

DEBUG		:=	-fsanitize=address -g3

SRCS	:=	main_vector.cpp

SRCS_DIR	:=	srcs/

SRCS_FILES	:=	$(addprefix $(SRCS_DIR), $(SRCS))

OBJS	:=	$(SRCS:.cpp=.o)

OBJS_DIR	:=	objs/

OBJS_FILES	:=	$(addprefix $(OBJS_DIR), $(OBJS))

HEADERS	:= stack.hpp vector.hpp

INC_DIR		:= inc/

$(OBJS_DIR)%.o:	$(SRCS_DIR)%.cpp Makefile $(addprefix $(INC_DIR), $(HEADERS))
				mkdir -p $(OBJS_DIR)
				$(CXX) $(CXXFLAGS) $(DEBUG) -c $< -o $@

all			:	$(NAME)

$(NAME)		:	$(OBJS_FILES)
				$(CXX) $(CXXFLAGS) $(DEBUG) -I$(INC_DIR) $(OBJS_FILES) -o $(NAME)

clean		:
				rm -rf $(OBJS_DIR)

fclean		:	clean
				rm -f $(NAME)

re			:	fclean all

.PHONY		:	all re clean fclean
