# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gborne <gborne@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/10 03:22:08 by gborne            #+#    #+#              #
#    Updated: 2022/07/11 13:42:49 by gborne           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SHELL=/bin/bash
UNAME = $(shell uname -s)

# Properties for MacOS
CDEBUG = #-fsanitize=address
CHECKER = tests/checker_Mac

ifeq ($(UNAME), Linux)
	#Properties for Linux
	LEAKS = valgrind --leak-check=full --track-fds=yes --trace-children=yes -s -q
endif

SRCS			= main.c utils.c init.c routine.c utils_bis.c
OBJS			= $(SRCS:.c=.o)

CC				= gcc
RM				= rm -f
CFLAGS			= -Wall -Wextra -Werror
PTHREAD			= -lpthread

NAME			= philo

all:			$(NAME)

$(NAME):		$(OBJS)
				gcc -g -fsanitize=address ${CFLAGS} -o ${NAME} ${OBJS} ${PTHREAD}

run: all
	@$(LEAKS)./$(NAME)

clean:
				$(RM) $(OBJS) $(BONUS_OBJS)

fclean:			clean
				$(RM) $(NAME)

re:				fclean $(NAME)

test:			all
				@./philo "5" "500000" "500000" "500000" "5000"

.PHONY:			all clean fclean re
