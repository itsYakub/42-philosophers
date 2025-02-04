CC= \
	cc
CFLAGS= \
	-Wall \
	-Wextra \
	-Werror \
	-g
SRCS= \
	./philo/philo.c \
	./philo/philo-utils.c \
	./philo/philo-parse.c \
	./philo/philo-sim0.c \
	./philo/philo-sim1.c
OBJS= \
	$(SRCS:.c=.o)
NAME= \
	./philo/philo

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ 

$(OBJS): %.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean fclean re

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
