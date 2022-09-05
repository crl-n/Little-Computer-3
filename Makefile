NAME := lc3
CFLAGS := -Wall -Wextra -Werror -g -I./includes

SRCDIR = src/
SRCS := $(addprefix $(SRCDIR), main.c \
		add_instr.c branch_instr.c cond_instr.c load_instr.c store_instr.c rti_instr.c\
		trap.c \
		mem_read.c sign_extend.c update_cond.c read_image.c)

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
