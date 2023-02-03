# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mzblah <mehdi.zblah@gmail.com>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/22 14:40:05 by Mzblah            #+#    #+#              #
#    Updated: 2021/03/16 16:55:31 by mzblah           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

BONUS = bonusse

PATH_SRC = ./

HEADER = ./

CFLAGS = -Wall -Wextra -Werror

OPTION = -c -I $(HEADER)

SRCS =	$(PATH_SRC)ft_putchar.c 	\
		$(PATH_SRC)ft_putstr.c		\
		$(PATH_SRC)ft_putnbr.c		\
		$(PATH_SRC)ft_isalpha.c		\
		$(PATH_SRC)ft_isdigit.c		\
		$(PATH_SRC)ft_isalnum.c		\
		$(PATH_SRC)ft_isascii.c		\
		$(PATH_SRC)ft_isprint.c		\
		$(PATH_SRC)ft_isspace.c		\
		$(PATH_SRC)ft_toupper.c		\
		$(PATH_SRC)ft_tolower.c		\
		$(PATH_SRC)ft_bzero.c		\
		$(PATH_SRC)ft_strnew.c		\
		$(PATH_SRC)ft_strlen.c		\
		$(PATH_SRC)ft_strdup.c		\
		$(PATH_SRC)ft_strcpy.c		\
		$(PATH_SRC)ft_strncpy.c		\
		$(PATH_SRC)ft_strcat.c		\
		$(PATH_SRC)ft_strncat.c		\
		$(PATH_SRC)ft_atoi.c		\
		$(PATH_SRC)ft_strdup.c		\
		$(PATH_SRC)ft_putchar_fd.c	\
		$(PATH_SRC)ft_putstr_fd.c	\
		$(PATH_SRC)ft_putendl_fd.c	\
		$(PATH_SRC)ft_putnbr_fd.c	\
		$(PATH_SRC)ft_chr_in_str.c	\
		$(PATH_SRC)ft_strncmp.c		\
		$(PATH_SRC)ft_strcmp.c		\
		$(PATH_SRC)ft_calloc.c

OBJS = $(SRCS:.c=.o)

.c.o:
	cc $(CFLAGS) -c $< -o $@ -I $(HEADER)

all:	$(NAME)

$(NAME): $(OBJS)
	ar rc $(NAME) $(OBJS)
	ranlib $(NAME)

clean:
	/bin/rm -f $(OBJS)
fclean: clean
	/bin/rm -f $(NAME)

re: clean fclean all re bonus
