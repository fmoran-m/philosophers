# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fmoran-m <fmoran-m@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/10 18:09:40 by fmoran-m          #+#    #+#              #
#    Updated: 2024/06/10 18:09:41 by fmoran-m         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

LIBFT = ./libft/libft.a

LIBFTDIR = ./libft

CC = cc

LM = make -C

INCLUDES = philo.h

CFLAGS = -Wall -Wextra -Werror

SRC = main.c

OBJS = ${SRC:.c=.o}

$(NAME): $(OBJS) $(INCLUDES)
		$(LM) $(LIBFTDIR)
		$(CC) -o $(NAME) $(CFLAGS) $(OBJS) $(LIBFT) $(RLIB)

all: $(NAME)

clean:
		$(RM) $(OBJS)
		cd $(LIBFTDIR) && make clean

fclean: clean
		$(RM) $(NAME)
		cd $(LIBFTDIR) && make fclean

re: fclean all

.PHONY = all clean fclean re
