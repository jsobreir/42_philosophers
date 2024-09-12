
SRC = philo.c parser.c utils.c init.c

OBJ = $(SRC:.c=.o)

HEADER = philo.h

NAME = philo

CC = gcc

FLAGS = -Wall -Wextra -Werror -g -lpthread

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(FLAGS)

%.o: %.c $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm $(OBJ)

fclean: clean
	rm $(NAME)

re:	fclean all

.PHONY: all re clean fclean
