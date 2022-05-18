# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdesoeuv <mdesoeuv@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/22 12:05:49 by mdesoeuv          #+#    #+#              #
#    Updated: 2022/05/18 08:58:45 by mdesoeuv         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME	:=	ft_containers

CXX		:=	c++

DEBUG		:=	-fsanitize=address -g3
CXXFLAGS	:=	-Wall -Werror -Wextra -std=c++98 $(DEBUG)

SRCS	:=	test_map.cpp \
			test_vector.cpp \
			test_stack.cpp \
			main.cpp

SRCS_DIR	:=	srcs/

SRCS_FILES	:=	$(addprefix $(SRCS_DIR), $(SRCS))

OBJS	:=	$(SRCS:.cpp=.o)

OBJS_DIR	:=	objs/

OBJS_FILES	:=	$(addprefix $(OBJS_DIR), $(OBJS))

HEADERS	:= stack.hpp vector.hpp map.hpp

INC_DIR		:= inc/

$(OBJS_DIR)%.o:	$(SRCS_DIR)%.cpp Makefile $(addprefix $(INC_DIR), $(HEADERS))
				mkdir -p $(OBJS_DIR)
				$(CXX) $(CXXFLAGS) $(DEBUG) -c $< -o $@

all			:	$(NAME)

stl			:	$(OBJS_FILES)
				$(CXX) $(CXXFLAGS) $(DEBUG) -I$(INC_DIR) -DCHOICE=1 $(OBJS_FILES) -o $(NAME)_STL

ft			:	$(OBJS_FILES)
				$(CXX) $(CXXFLAGS) $(DEBUG) -I$(INC_DIR) -DCHOICE=0 $(OBJS_FILES) -o $(NAME)_FT

$(NAME)		:	$(OBJS_FILES)
				$(CXX) $(CXXFLAGS) $(DEBUG) -I$(INC_DIR) $(OBJS_FILES) -o $(NAME)

clean		:
				rm -rf $(OBJS_DIR)

fclean		:	clean
				rm -f $(NAME)

re			:	fclean all

.PHONY		:	all re clean fclean
