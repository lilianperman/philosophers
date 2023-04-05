##add 42 header!

CC = cc
FLAGS = -Wall -Wextra -Werror
PTHREADS = -pthread
NAME = philo
SRC = checker.c philo_init.c routine.c utils.c main.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(PTHREADS) $(SRC) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean:
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
