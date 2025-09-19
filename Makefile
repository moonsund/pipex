NAME = pipex
NAME_BNS = pipex_bonus

CC = cc
CFLAGS = -g -Wall -Wextra -Werror

HEADER = pipex.h

LIBFT_DIR = libft
LIBFT_A = $(LIBFT_DIR)/libft.a

INCLUDES = -I. -I$(LIBFT_DIR)
LIBS = -Llibft -lft

SRCS = srcs/pipex.c srcs/utils.c
OBJS = $(SRCS:.c=.o)

SRCS_BNS = srcs/pipex_bonus.c srcs/utils_bonus.c srcs/pipex.c srcs/utils.c
OBJS_BNS = $(SRCS_BNS:.c=.o)

all: $(NAME) 

bonus: $(NAME)
bonus: SRCS := SRCS_BNS
bonus: OBJS := OBJS_BNS

$(NAME): $(OBJS) $(LIBFT_A) $(HEADER)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME) $(OBJS) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

$(LIBFT_A):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -f $(OBJS) $(OBJS_BNS)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME) $(NAME_BNS)

re: fclean all
	$(MAKE) all

rebonus: fclean bonus
	$(MAKE) bonus

.PHONY: all bonus clean fclean re rebonus