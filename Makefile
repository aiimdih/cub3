NAME = cub3D
CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS = PARSE/main.c \
       PARSE/cleanup.c \
       PARSE/checks.c \
       PARSE/core_help.c \
       PARSE/core_parse.c \
       PARSE/map_config.c \
       PARSE/parse_validators.c \
       PARSE/parse_walls.c \
       PARSE/parser_utils.c \
       PARSE/config_help.c \
       PARSE/validators_help.c \
       get_next_line/get_next_line.c \
       get_next_line/get_next_line_utils.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) libft/libft.a
	$(CC) $(CFLAGS) $(OBJS) libft/libft.a -o $(NAME)

libft/libft.a:
	make -C libft

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	make -C libft clean

fclean: clean
	rm -f $(NAME)
	make -C libft fclean

re: fclean all

.PHONY: all clean fclean re
