
SRCS		= main.c lst_lists.c utils.c init.c forks.c
HEADER		= -I includes.h

OBJS		=	${SRCS:.c=.o}

CFLAGS		= -Wall -Wextra -Werror

CC			= gcc

RM			= rm -rf

NAME		= philo_one

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
#valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -s ./miniRT tests/work.rt
