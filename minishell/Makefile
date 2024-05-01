SRCS = \
minishell.c envp_help.c envp.c env.c variables.c input_valid.c\
redirect.c check_input.c builtin.c args.c free_arr.c pipe.c\
export.c echo.c exit_status.c split_com.c cd.c unset.c exit.c\
redirect_child.c execute_command.c error.c signals.c fds.c\
path.c heredoc.c help.c wait.c exec.c heredoc_util.c\


OBJ = $(SRCS:.c=.o)

CC = cc

CFLAGS = -Wall -Werror -Wextra

NAME = minishell

LIBFTDIR = ./libft/

LIBFT = $(LIBFTDIR)/libft.a

all: $(NAME)

$(NAME): $(OBJ)
	$(MAKE) -C $(LIBFTDIR)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT) -lreadline

clean:
			rm -f *.o
			rm -f $(LIBFTDIR)*.o
fclean: clean
			rm -f $(NAME)
			rm -f $(LIBFTDIR)*.o $(LIBFT)
re: fclean all