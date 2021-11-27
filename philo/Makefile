# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pdewitt <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/05 19:46:58 by pdewitt           #+#    #+#              #
#    Updated: 2021/08/07 09:38:36 by pdewitt          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =		philo

CC =		gcc
RM =		/bin/rm -f
CFLAGS =	-Wall -Wextra -Werror
INCLUDES =	.

SRCS =		main.c \
			get_args.c \
			ft_isnumber.c \
			init_philos.c \
			simulation.c \
			put_status.c \
			ft_itoa.c


OBJS =		$(SRCS:.c=.o)


.c.o :
			$(CC) $(CFLAGS) -I $(INCLUDES) -c $< -o $(<:.c=.o)


$(NAME) :	$(OBJS)	$(INCLUDES)/philo.h
			$(CC) -o $(NAME) $(OBJS) -I$(INCLUDES) -pthread


all :		$(NAME)

clean :
			$(RM) $(OBJS)

fclean :	clean
			$(RM) $(NAME)

re :		fclean \
			all

.PHONY :	all clean fclean re
