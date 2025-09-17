NAME = pipex

CC = cc
CFLAGS = -g -Wall -Wextra -Werror

LIBFT_DIR = libft
LIBFT_A = $(LIBFT_DIR)/libft.a

HEADER = pipex.h

INCLUDES = -I. -I$(LIBFT_DIR)
LIBS = -Llibft -lft

SRCS = srcs/main.c srcs/utils.c
OBJS = $(SRCS:.c=.o)

SRCS_BNS = main_bonus.c utils_bonus.c
OBJS_BNS = $(SRCS:.c=.o)


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
