# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vico <vico@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/27 22:14:59 by vico              #+#    #+#              #
#    Updated: 2022/02/28 03:44:55 by vico             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

BLUE = 		\033[0;34m
GREEN = 	\033[0;32m
LIGHTBLUE = \033[1;34m
RED = 		\033[0;31m
YELLOW = 	\033[1;33m
ORANGE = 	\033[0;33m
MAGENTA = 	\033[0;35m
RESET = 	\033[0m

SRCS_V		= $(wildcard srcs/vector_main.cpp)

OBJS_V		= ${SRCS_V:.cpp=.o}

NAME_V		= vector

SRCS_M		= $(wildcard srcs/map_main.cpp)

OBJS_M		= ${SRCS_M:.cpp=.o}

NAME_M		= map

SRCS_S		= $(wildcard srcs/stack_main.cpp)

OBJS_S		= ${SRCS_S:.cpp=.o}

NAME_S		= stack

SRCS_FT		= $(wildcard tests/ft_map_test.cpp tests/ft_pair_test.cpp tests/ft_stack_test.cpp tests/ft_vector_test.cpp tests/main_ft_tests.cpp)

SRCS_STD	= $(wildcard tests/std_map_test.cpp tests/std_pair_test.cpp tests/std_stack_test.cpp tests/std_vector_test.cpp tests/main_std_tests.cpp)

OBJS_FT		= ${SRCS_FT:.cpp=.o}

OBJS_STD	= ${SRCS_STD:.cpp=.o}

HEADERS		= -I ./includes/utils -I ./includes/vector -I ./includes/map -I ./includes/stack

CXXFLAGS	= -Wall -Wextra -Werror -std=c++98 -g3 -fsanitize=address

%.o: %.cpp
			@clang++ $(CXXFLAGS) $(HEADERS) -c -o $@ $<

all:		 ft_test std_test

ft_test:	${OBJS_FT}
			@printf "\n$(BLUE)"
			@printf "$(BLUE)Compiling files..."
			@clang++ ${CXXFLAGS} ${OBJS_FT} $(HEADERS) -o ft_test
			@./ft_test > ft.txt
			@sed -i -e 's/\(std\|ft\)//g' ft.txt
			@printf "$(GREEN)[ft_test done][✔]$(RESET)\n"

std_test:	${OBJS_STD}
			@printf "\n$(BLUE)"
			@printf "$(BLUE)Compiling files..."
			@clang++ ${CXXFLAGS} ${OBJS_STD} $(HEADERS) -o std_test
			@./std_test > std.txt
			@sed -i -e 's/\(std\|ft\)//g' std.txt
			@printf "$(GREEN)[std_test done][✔]$(RESET)\n"

${NAME_V}:	${OBJS_V}
			@printf "\n$(BLUE)"
			@printf "$(BLUE)Compiling files..."
			@clang++ ${CXXFLAGS} ${OBJS_V} $(HEADERS) -o $(NAME_V)
			@printf "$(GREEN)[$(NAME_V) done][✔]$(RESET)\n"

${NAME_M}:	${OBJS_M}
			@printf "\n$(BLUE)"
			@printf "$(BLUE)Compiling files..."
			@clang++ ${CXXFLAGS} ${OBJS_M} $(HEADERS) -o $(NAME_M)
			@printf "$(GREEN)[$(NAME_M) done][✔]$(RESET)\n"

${NAME_S}:	${OBJS_S}
			@printf "\n$(BLUE)"
			@printf "$(BLUE)Compiling files..."
			@clang++ ${CXXFLAGS} ${OBJS_S} $(HEADERS) -o $(NAME_S)
			@printf "$(GREEN)[$(NAME_S) done][✔]$(RESET)\n"

clean:
			@printf "\n"
			@printf "$(RED)Erase files '.o'\n"
			@rm -rf $(OBJS_V) $(OBJS_M) $(OBJS_S) $(OBJS_FT) $(OBJS_STD) ft.txt std.txt
			@printf "$(RESET)\n"

fclean:
			@printf "\n"
			@printf "$(RED)Erase files '.o'\n"
			@rm -rf $(OBJS_V) $(OBJS_M) $(OBJS_S) $(OBJS_FT) $(OBJS_STD) ft.txt std.txt
			@printf "$(RED)Delete executable file and libft\n"
			@rm -rf $(NAME_V) $(NAME_M) $(NAME_S) $(NAME_T) std_test ft_test
			@printf "$(RESET)\n"

re:			fclean all

.PHONY:		clean fclean re all