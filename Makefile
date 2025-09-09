NAME = pipex

CC = cc
CFLAGS = -g

LIBFT_DIR = libft
LIBFT_A = $(LIBFT_DIR)/libft.a

HEADER = pipex.h

INCLUDES = -I. -I$(LIBFT_DIR)
LIBS = -Llibft -lft

SRCS = main.c check_files.c check_commands.c
OBJS = $(SRCS:.c=.o)


all: $(NAME)

$(NAME): $(OBJS) $(LIBFT_A) $(HEADER)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME) $(OBJS) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

$(LIBFT_A):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -f $(OBJS)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all
