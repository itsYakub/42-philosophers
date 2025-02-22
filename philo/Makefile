CC= \
	cc
CFLAGS= \
	-Wall \
	-Wextra \
	-Werror \
	-g
SRCS= \
	./philo.c \
	./philo-utils0.c \
	./philo-utils1.c \
	./philo-parse.c \
	./philo-sim0.c \
	./philo-sim1.c
OBJS= \
	$(SRCS:.c=.o)
NAME= \
	./philo

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
