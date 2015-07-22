# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gwells <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/11/19 16:35:04 by gwells            #+#    #+#              #
#    Updated: 2015/01/30 08:38:59 by gwells           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= ft_ls
SRC		= main.c \
		  flag.c \
		  list.c \
		  dir.c \
		  opt.c \
		  trie.c \
		  print.c \
		  insertion.c \
		  misc.c \
		  print_l.c \
		  print_l2.c \
		  print_l3.c

OBJ		= $(SRC:.c=.o)
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror

# *************************************************************************** #

all: $(NAME)

$(NAME): $(OBJ) 	
	git submodule init my_libc
	git submodule update --remote my_libc
	cp my_libc/libft.a .
	$(CC) $(OBJ) $(CFLAGS) -L. -lft -o ft_ls

clean:
	rm -rf $(OBJ)

fclean: clean 
	rm -rf $(NAME)

re: fclean $(NAME) 

.PHONY: clean re fclean all
