MAKEFLAGS += --quiet
SRC	= $(shell find src -type f -name "*.c")
LIB = $(shell find libft -type f -name "*.a")
INCLUDE	= $(addprefix -I, include)
OBJS	=$(SRC:.c=.o)
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address
NAME = philosophers

all: libft $(NAME)

libft:
	@$(MAKE) -C libft/

$(NAME):	libft $(OBJS)
	@$(CC) -o $(NAME) $(CFLAGS) $(INCLUDE) $(LIB) $(OBJS)

.c.o:
	@echo "Creating object: $@"
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	@rm -f $(OBJS)
	@$(MAKE) -C libft/ clean

fclean:
	@$(MAKE) -C libft/ fclean
	@rm -f $(OBJS)
	@rm -f $(NAME)

re:			fclean all

.PHONY:		all clean fclean re libft $(NAME)