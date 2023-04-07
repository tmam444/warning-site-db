# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chulee <chulee@nstek.com>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/21 14:04:03 by chulee            #+#    #+#              #
#    Updated: 2023/04/07 15:03:25 by chulee           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=db
SRCS=$(wildcard srcs/*.c)
OBJS=$(addprefix objs/, $(notdir $(SRCS:.c=.o)))
CC=gcc
INCLUDE=-O3 -I./includes
CFLAGS=-Wall -Wextra -Werror
LDFLAGS=-lm
OBJ_FILES=$(OBJS)

$(NAME) : $(OBJ_FILES)
		$(CC) $(CFLAGS) $(INCLUDE) -o $(NAME) $(OBJ_FILES) $(LDFLAGS)

objs/%.o : srcs/%.c
		$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@ $(LDFLAGS)

clean :
		rm -f $(OBJS)

fclean : clean
		rm -f $(NAME)

all : $(NAME)

re : fclean all

.PHONY: clean fclean all re
