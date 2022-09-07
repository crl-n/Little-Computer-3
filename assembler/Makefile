NAME := little-assembler
CFLAGS := -Wall -Wextra -Werror -g -I./includes

SRCDIR = src/
SRCS := $(addprefix $(SRCDIR), main.c)

OBJDIR := obj/
OBJS := $(SRCS:$(SRCDIR)%.c=obj/%.o)
$(info $(OBJS))

all: $(OBJDIR) $(OBJS) $(NAME) 

$(OBJDIR):
	mkdir $(OBJDIR)

$(NAME):
	$(CC) $(CFLAGS) $(OBJS) -o $@

$(OBJS): $(OBJDIR)%.o: $(SRCDIR)%.c
	$(CC) -c $(CFLAGS) -o $@ $<

clean:
	-/bin/rm -rf $(OBJDIR)

fclean: clean
	-/bin/rm $(NAME)

re: fclean all
