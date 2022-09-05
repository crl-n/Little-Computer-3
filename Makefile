NAME := lc3
CFLAGS := -Wall -Wextra -Werror -g -I./includes

SRCDIR = src/
SRCS := $(addprefix $(SRCDIR), main.c add.c branch.c load.c ldr.c ldi.c \
		lea.c st.c sti.c str.c trap.c mem_read.c sign_extend.c rti.c \
		update_cond.c jump.c jsr.c and.c not.c)

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
