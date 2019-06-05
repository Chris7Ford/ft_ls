# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chford <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/17 17:57:13 by chford            #+#    #+#              #
#    Updated: 2019/06/04 17:13:06 by chford           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
FLAGS = -Wall -Werror -Wextra
SRC = ft_lstmap.c ft_putendl_fd.c ft_striter.c ft_strrchr.c ft_atoi.c ft_lstnew.c ft_putnbr.c ft_striteri.c ft_strsplit.c ft_bzero.c ft_memalloc.c ft_putnbr_fd.c ft_strjoin.c ft_strstr.c ft_isalnum.c ft_memccpy.c ft_putstr.c ft_strlcat.c ft_strsub.c ft_isalpha.c ft_memchr.c ft_putstr_fd.c ft_strlen.c ft_strtrim.c ft_isascii.c ft_memcmp.c ft_strcat.c ft_strmap.c ft_tolower.c ft_isdigit.c ft_memcpy.c ft_strchr.c ft_strmapi.c ft_toupper.c ft_isprint.c ft_memdel.c ft_strclr.c ft_strncat.c ft_itoa.c ft_memmove.c ft_strcmp.c ft_strncmp.c ft_lstadd.c ft_memset.c ft_strcpy.c ft_strncpy.c ft_lstdel.c ft_putchar.c ft_strdel.c ft_strnequ.c ft_lstdelone.c ft_putchar_fd.c ft_strdup.c ft_strnew.c ft_lstiter.c ft_putendl.c ft_strequ.c ft_strnstr.c ft_lstpush.c ft_absval.c ft_isspace.c ft_max.c ft_min.c print_hex_ulong_fd.c ft_putstr_constrain_fd.c print_hex_ulong_length.c ft_strjoin_free.c ft_prepend_char.c ft_islower.c ft_isupper.c get_char_array_len.c ft_join_str_array.c free_string_array.c

all: $(NAME)

$(NAME):
	gcc -c $(FLAGS) $(SRC)
	ar rc libft.a *.o
	ranlib libft.a
clean:
	/bin/rm -f *.o
fclean: clean
	/bin/rm -f $(NAME)
re: fclean all
