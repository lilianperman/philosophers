##add 42 header

CC = cc
FLAGS = -Wall -Wextra -Werror
PTHREADS = -pthread
NAME = philo
SRC = routine.c time_manipulation.c build_and_check.c utils.c main.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(PTHREADS) $(SRC) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean:
	rm -f $(NAME) $(OBJ)

re: fclean all

.PHONY: all clean fclean re
