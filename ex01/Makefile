# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pdrettas <pdrettas@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/05/05 21:47:05 by pdrettas          #+#    #+#              #
#    Updated: 2026/05/05 21:47:08 by pdrettas         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = RPN

SRC			=	./main.cpp ./RPN.cpp
				
OBJ			=	$(SRC:.cpp=.o)
			
CXX			=	c++

CXXFLAGS	=	-Wall -Wextra -Werror -std=c++17

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(NAME)

all: $(NAME)

clean:	
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re:		fclean all

leaks: re
	valgrind --leak-check=full ./$(NAME)
	$(MAKE) fclean

.PHONY: all clean fclean re leaks