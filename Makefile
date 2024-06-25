# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fmoran-m <fmoran-m@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/10 18:09:40 by fmoran-m          #+#    #+#              #
#    Updated: 2024/06/25 21:17:52 by fmoran-m         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = cc

INCLUDES = philo.h

CFLAGS = -Wall -Wextra -Werror

SRC = main.c \
		init.c \
		lists_func.c \
		control_argv.c \
		libft_functions.c \
		philo_routine.c \
		ft_putnbr.c \
		start_threads.c \
		init_forks.c \
		monitor.c \
		routine_actions.c

OBJS = ${SRC:.c=.o}

$(NAME): $(OBJS) $(INCLUDES)
		$(LM) $(LIBFTDIR)
		$(CC) -o $(NAME) $(CFLAGS) $(OBJS)

all: $(NAME)

clean:
		$(RM) $(OBJS)

fclean: clean
		$(RM) $(NAME)

re: fclean all

.PHONY = all clean fclean re
