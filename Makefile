# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chulee <chulee@nstek.com>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/21 14:04:03 by chulee            #+#    #+#              #
#    Updated: 2023/03/30 18:29:53 by chulee           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=md5
SRCS=$(wildcard srcs/*.c)
OBJS = $(addprefix objs/, $(notdir $(SRCS:.c=.o)))
CC = gcc
INCLUDE= -I./includes
CFLAGS = -O3 -g
LDFLAGS = 
OBJ_FILES = $(OBJS)

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
