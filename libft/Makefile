# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/03 15:37:26 by gbiebuyc          #+#    #+#              #
#    Updated: 2019/06/06 19:42:55 by nallani          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = ft_atoi.c \
	  ft_bzero.c \
	  ft_isalnum.c \
	  ft_isalpha.c \
	  ft_isascii.c \
	  ft_isdigit.c \
	  ft_isprint.c \
	  ft_itoa.c \
	  ft_lstadd.c \
	  ft_lstdel.c \
	  ft_lstdelone.c \
	  ft_lstiter.c \
	  ft_lstmap.c \
	  ft_lstnew.c \
	  ft_memalloc.c \
	  ft_memccpy.c \
	  ft_memchr.c \
	  ft_memcmp.c \
	  ft_memcpy.c \
	  ft_memdel.c \
	  ft_memmove.c \
	  ft_memset.c \
	  ft_putchar.c \
	  ft_putchar_fd.c \
	  ft_putendl.c \
	  ft_putendl_fd.c \
	  ft_putnbr.c \
	  ft_putnbr_fd.c \
	  ft_putstr.c \
	  ft_putstr_fd.c \
	  ft_putstrn_fd.c \
	  ft_strcat.c \
	  ft_strchr.c \
	  ft_strclr.c \
	  ft_strcmp.c \
	  ft_strcpy.c \
	  ft_strdel.c \
	  ft_strdup.c \
	  ft_strequ.c \
	  ft_striter.c \
	  ft_striteri.c \
	  ft_strjoin.c \
	  ft_strlcat.c \
	  ft_strlen.c \
	  ft_strmap.c \
	  ft_strmapi.c \
	  ft_strncat.c \
	  ft_strncmp.c \
	  ft_strncpy.c \
	  ft_strnequ.c \
	  ft_strnew.c \
	  ft_strnstr.c \
	  ft_strrchr.c \
	  ft_strsplit.c \
	  ft_strstr.c \
	  ft_strsub.c \
	  ft_strtrim.c \
	  ft_tolower.c \
	  ft_toupper.c \
	  ft_wordcount.c \
	  get_next_line.c \
	  ft_atof.c \
	  ft_itoa_static.c \
	  ft_min.c \
	  ft_max.c \
	  ft_abs.c \
	  ft_pow.c \
	  ft_printf.c \
	  ft_printf_bignum.c \
	  ft_printf_widechar.c \
	  ft_printf_parse.c \
	  ft_printf_conv_signed.c \
	  ft_printf_conv_unsigned.c \
	  ft_printf_conv_char.c \
	  ft_printf_conv_str.c \
	  ft_printf_conv_non_printable_str.c \
	  ft_printf_conv_float.c \
	  ft_printf_conv_misc.c \
	  ft_printf_get_args.c \
	  ft_printf_dispatch.c

OBJ = $(SRC:.c=.o)
NAME = libft.a
CFLAGS = -Wall -Wextra -Werror -O3
.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	ar rs $(NAME) $(OBJ)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all
