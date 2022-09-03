NAME := lc3vm
CFLAGS := -Wall -Wextra -Werror
SRCS := main.c

all: $(NAME)

$(NAME):
	$(CC) $(CFLAGS) $(SRCS) -o $@

clean:
	/bin/rm *.o

fclean: clean
	/bin/rm $(NAME)

re: fclean all
