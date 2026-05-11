NAME = philo
CC = cc
RM = rm -rf
CFLAGS = -Wall -Wextra -Werror -g #-fsanitize=thread -pthread

FILES = philo.c init.c routine.c death.c utils.c libft_utils.c

OBJ =$(FILES:.c=.o)

all:  ${NAME}

${NAME}: ${OBJ}
		${CC} ${CFLAGS} ${OBJ} -o ${NAME}

%.o: %.c
	${CC} ${CFLAGS} -c $< -o $@ 

clean:
		${RM} ${OBJ}

fclean: clean
		${RM} ${NAME}

re: fclean all

.PHONY = all clean fclean re
