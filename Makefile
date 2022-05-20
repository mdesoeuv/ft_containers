# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdesoeuv <mdesoeuv@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/22 12:05:49 by mdesoeuv          #+#    #+#              #
#    Updated: 2022/05/20 15:00:38 by mdesoeuv         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME	:=	ft_containers

CXX		:=	c++

# DEBUG		:=	-fsanitize=address
CXXFLAGS	:=	 -g3 -O3 -Wall -Werror -Wextra -std=c++98 $(DEBUG)

SRCS	:=	test_map.cpp \
			test_vector.cpp \
			test_stack.cpp \
			main.cpp

SRCS_DIR	:=	srcs/

SRCS_FILES	:=	$(addprefix $(SRCS_DIR), $(SRCS))

OBJS			:=	$(SRCS:.cpp=.o)

OBJS_DIR		:=	objs/

FT_DIR			:= ft/

STL_DIR			:= stl/

OBJS_FILES		:=	$(addprefix $(OBJS_DIR), $(OBJS))

OBJS_FILES_STL	:=	$(addprefix $(OBJS_DIR)$(STL_DIR), $(OBJS))

OBJS_FILES_FT	:=	$(addprefix $(OBJS_DIR)$(FT_DIR), $(OBJS))

HEADERS			:=	stack.hpp \
					vector.hpp \
					map.hpp \
					enable_if.hpp \
					equal.hpp \
					is_integral.hpp \
					iterator_traits.hpp \
					lexicographical_compare.hpp \
					pair.hpp \
					Reverse_Iterator.hpp \
					tests.hpp

INC_DIR			:= inc/

$(OBJS_DIR)%.o:				$(SRCS_DIR)%.cpp Makefile $(addprefix $(INC_DIR), $(HEADERS))
							mkdir -p $(OBJS_DIR)
							$(CXX) $(CXXFLAGS) $(DEBUG) -DCHOICE=0  -c $< -o $@

$(OBJS_DIR)$(STL_DIR)%.o:	$(SRCS_DIR)%.cpp Makefile $(addprefix $(INC_DIR), $(HEADERS))
							mkdir -p $(OBJS_DIR)
							mkdir -p $(OBJS_DIR)$(STL_DIR)
							$(CXX) $(CXXFLAGS) $(DEBUG) -DCHOICE=1  -c $< -o $@

$(OBJS_DIR)$(FT_DIR)%.o:	$(SRCS_DIR)%.cpp Makefile $(addprefix $(INC_DIR), $(HEADERS))
							mkdir -p $(OBJS_DIR)
							mkdir -p $(OBJS_DIR)$(FT_DIR)
							$(CXX) $(CXXFLAGS) $(DEBUG) -DCHOICE=0  -c $< -o $@

all			:	ft stl $(NAME)

stl			:	$(OBJS_FILES_STL)
				$(CXX) $(CXXFLAGS) $(DEBUG) -I$(INC_DIR)  $(OBJS_FILES_STL) -o $(NAME)_STL

ft			:	$(OBJS_FILES_FT)
				$(CXX) $(CXXFLAGS) $(DEBUG) -I$(INC_DIR) $(OBJS_FILES_FT) -o $(NAME)_FT

$(NAME)		:	$(OBJS_FILES)
				$(CXX) $(CXXFLAGS) $(DEBUG) -I$(INC_DIR) $(OBJS_FILES) -o $(NAME)

clean		:
				rm -rf $(OBJS_DIR)

fclean		:	clean
				rm -f $(NAME) $(NAME)_FT $(NAME)_STL

re			:	fclean all

.PHONY		:	all re clean fclean ft stl
