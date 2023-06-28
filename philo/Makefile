NAME = philo

SRC_DIR = ./src/

SRC = 	$(SRC_DIR)main.c				\
		$(SRC_DIR)list_handler.c		\
		$(SRC_DIR)philo_behaviour.c		\
		$(SRC_DIR)utils.c				\
		$(SRC_DIR)cleanup.c				\
		$(SRC_DIR)creation.c			\
		$(SRC_DIR)init_params.c			\
		$(SRC_DIR)philo_time.c			\
		$(SRC_DIR)philo_print.c			\
		$(SRC_DIR)philo_actions.c		\

OBJS = $(SRC:.c=.o)

.c.o:
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

CFLAGS = -Wextra -Wall -Werror

INCLUDE = -Iinclude

THREADS_LIB = -lpthread

CC = gcc

RACE_CHECK = -g3 -fsanitize=thread

# CFLAGS += $(RACE_CHECK)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDE) $(OBJS) -o $(NAME)

all: $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
