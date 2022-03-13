# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aisraely <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/01 18:55:02 by aisraely          #+#    #+#              #
#    Updated: 2021/11/03 17:32:14 by aisraely         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= containers

SRCS	= ${wildcard *.cpp}
OBJS	= ${SRCS:.cpp=.o}
ifeq ($(OS), Windows_NT)
	CC		= /c/msys64/mingw64/bin/clang++
	CFLAGS	= -Wall -Wextra -Werror -std=c++98 --target=x86_64-w64-windows-gnu
else
	CC		= clang++
	CFLAGS	= -Wall -Wextra -Werror -std=c++98
endif
RM		= rm -rf

all: ${NAME}

.cpp.o:
	@$(CC) $(CFLAGS) -c $< -o $(<:.cpp=.o)

${NAME}: ${OBJS}
	@${CC} ${OBJS} ${CFLAGS} -o ${NAME}

clean:
	@${RM} ${OBJS}

fclean: clean
	@${RM} ${NAME}

re: fclean all

.PHONY: clean fclean re all