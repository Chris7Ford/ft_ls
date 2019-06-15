# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chford <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/09 12:12:47 by chford            #+#    #+#              #
#    Updated: 2019/06/14 21:26:53 by chford           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls
FLAGS = -Wall -Werror -Wextra
LIB = libftprintf.a
SRC = directory.c \
	  file_node.c \
	  file_node2.c \
	  flag.c \
	  free.c \
	  get_info.c \
	  get_info2.c \
	  helpers.c \
	  helpers2.c \
	  init.c \
	  init2.c \
	  input.c \
	  main.c \
	  print.c \
	  print2.c \
	  print3.c \
	  print4.c \
	  queue.c \
	  sort.c \
	  sort2.c \
	  sort3.c \
	  string.c \
	  traversal.c \

all: $(NAME)

$(NAME):
	gcc $(FLAGS) $(SRC) $(LIB) -o $(NAME)
clean:
	/bin/rm -f *.o
fclean: clean
	/bin/rm -f $(NAME)
re: fclean all
