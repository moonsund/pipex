NAME       = pipex
NAME_BNS   = pipex_bonus

CC         = cc
CFLAGS     = -g -Wall -Wextra -Werror

LIBFT_DIR  = libft
LIBFT_A    = $(LIBFT_DIR)/libft.a

HEADER     = pipex.h

INCLUDES   = -I. -I$(LIBFT_DIR)
LIBS       = -L$(LIBFT_DIR) -lft

SRCS       = srcs/main.c srcs/pipex.c srcs/utils.c
OBJS       = $(SRCS:.c=.o)

SRCS_BNS   = srcs/main_bonus.c srcs/pipex_bonus.c srcs/utils_bonus.c srcs/pipex.c srcs/utils.c
OBJS_BNS   = $(SRCS_BNS:.c=.o)

.PHONY: all bonus clean fclean re rebonus

all: $(NAME)
bonus: $(NAME_BNS)

$(NAME): $(OBJS) $(LIBFT_A)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $(OBJS) $(LIBS)

$(NAME_BNS): $(OBJS_BNS) $(LIBFT_A)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $(OBJS_BNS) $(LIBS)

$(OBJS) $(OBJS_BNS): $(HEADER)

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
rebonus: fclean bonus