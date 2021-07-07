
SRCS		= main.c lst_lists.c utils.c utils2.c init.c one_live.c print_mess.c
HEADER		= -I includes.h functions.h types.h

OBJS		=	${SRCS:.c=.o}

CFLAGS		= -Wall -Wextra -Werror

CC			= gcc

RM			= rm -f

NAME		= philo

.c.o:		${HEADER}
			${CC} ${CFLAGS} ${SHDRS} -c $< -o $@

${NAME}:	${OBJS}
			${CC} ${CFLAGS} ${OBJS} ${SFLS} -pthread -o ${NAME}

all:		${NAME}

clean:
			${RM} ${OBJS} *.gch

fclean:		clean
			${RM} ${NAME}

re:			fclean all

.PHONY: 	all clean fclean re

#number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]

#valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -s ./miniRT tests/work.rt
