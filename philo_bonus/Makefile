NAME = philo_bonus

SRC_DIR = ./src/

SRC = 	$(SRC_DIR)main.c				\

OBJS = $(SRC:.c=.o)

.c.o:
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

CFLAGS = -Wextra -Wall -Werror $(RACE_CHECK)

INCLUDE = -Iinclude

THREADS_LIB = -lpthread

CC = gcc
RACE_CHECK = -g3 -fsanitize=thread

CFLAGS += $(RACE_CHECK)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDE) $(OBJS) -o $(NAME)

all: $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
