/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhromylo <mhromylo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 14:50:29 by mhromylo          #+#    #+#             */
/*   Updated: 2024/04/30 11:56:06 by mhromylo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_envp
{
	char			*name_env;
	char			*val_env;
	struct s_envp	*next;
}				t_envp;

t_envp	*node_exist(char *name, t_envp *env_vars);
void	init_list(char *name, char *value, t_envp **list);
t_envp	*init_envp(char **envp);
char	*get_value(char *key_pair);
char	*get_name(char *key_pair);
int		env(t_envp *envp_vars, char **args);
char	*envp_val(char *name, t_envp *env_vars);
void	variables(char **input, t_envp *envp_vars);
int		is_empty(char *str);
int		open_quotes(char *str);
char	get_next_redir(char *str);
int		redir_empty(char *input);
int		start_pipe(char *input);
char	*get_next_pipe(char *str);
int		empty_pipe(char *input);
int		open_quotes(char *str);
int		chek_input(char *input);
int		invalid_input(char *input, int *exit_status, t_envp *envp_vars);
int		invalid_token(char c);
int		str_equal(const char *s1, const char *s2);
int		builtin(char **args, t_envp **envp_vars, int exit_status);
char	**split_args(char *comand);
int		is_builtin(char *command);
void	free_arr(char **arr);
int		execute_one_command(char *command, t_envp **envp_vars);
int		has_pipe(char *str);
int		is_varname(char c);
void	print_varname_err_msg(char *command, char *name);
int		export(char **args, t_envp **envp_vars);
void	envp_update(char *name, char *value, t_envp *envp_vars);
int		echo(char **args);
void	get_last_exit_status(char **input, int exit_status);
void	print_err_msg(char *command, char *msg);
int		cd_error(void);
int		cd(char **args, t_envp *envp_vars);
int		pwd(void);
int		unset(char **args, t_envp **envp_vars);
int		is_valid_varname(char *name);
void	free_t_envp(t_envp **envp_vars);
int		built_exit(char **args, int exit_status);
char	**split_commands(char *str, int len);
int		numb_com(char *str);
void	redirect_child(char *command, char **commands, t_envp **envp_vars);
void	execute_command(char *command, char **commands, t_envp **envp_vars);
void	print_error_msg(char *command, char *msg);
void	exit_with_error(char *command, char *msg, int error);
void	print_perror_msg(char *command, char *perror_msg);
void	exit_with_perror(char *command, char *perror_msg, int error);
void	print_varname_error_msg(char *command, char *varname);
void	close_all_fds(void);
void	clean_after_execute(int *children_pid);
void	close_extra_fds(void);
int		execute_external(char **args, t_envp *envp_vars);
void	redirect_fd(int fd_to_redirect, int fd_location);
int		redirect_input(char *command, t_envp **envp_vars);
int		redirect_output(char *command);
char	find_redirect(char *str, int *i);
char	*ft_move_command(char *command, char red, int i, int j);
int		wait_for_child(int child_pid, int is_last_child);
void	define_main_signals(void);
void	heredoc(char *command);
void	read_heredoc(int *exit_status, t_envp *envp_vars,
			char *delimiter, char *file_name);
char	*ft_file_name(char *str);
char	*file_name_heredoc(int file_heredoc);
int		make_heredoc(char *input, t_envp *envp_vars, int *exit_status);
char	*ft_move_space(char *command);
char	*minienv_value(char *name, t_envp *envp_vars);
void	ft_replace_t(char *str);
int		is_folder(char *command);
void	close_extra_fds(void);
void	close_all_fds(void);
void	clean_after_execute(int *children_pid);
void	external_exit(char **args, t_envp *envp_vars, int exit_status);
int		is_path(char *command);
int		execute_forked_builtin(char **args, t_envp **envp_vars);
void	define_execute_signals(int child_pid);
void	define_heredoc_signals(int child_pid);
void	create_path(char *base, char *part1, char *part2, char *part3);
char	*local_path(char *command, t_envp *envp_vars);
char	*get_path(char *command, t_envp *envp_vars);
int		envp_has_path(t_envp *envp_vars);
int		exp_rout(char *only_name, t_envp **envp_vars, char *str,
			int exit_status);
void	make_filename(char *src, char *dst, int i, int k);
char	*ft_file_name(char *str);
char	*file_name_heredoc(int file_heredoc);
char	*ft_move_space(char *command);
void	read_heredoc(int *exit_status, t_envp *envp_vars,
			char *delimiter, char *file_name);
int		redirect_input(char *command, t_envp **envp_vars);
char	find_redirect(char *str, int *i);
int		redirect_output(char *command);
void	quit_child(char **commands, t_envp **envp_vars);
char	*ft_move_command(char *command, char red, int i, int j);
void	red_chil(char *command, char **commands, t_envp **envp_vars);
void	restore_original_fds(int original_fds[2]);
void	restore_original_fds_one(int orig_fds[2]);
int		redirect_input_one(char *command, int orig_fds[2], t_envp **envp_vars);
int		redirect_output_one(char *command, int orig_fds[2]);
int		ft_issymb(char *name, t_envp *envp_vars);
int		wait_for_child(int child_pid, int is_last_child);
int		wait_for_children(int *children_pid);
void	handle_pipe(int or_fd_out, char *cur_com, char **commands, int len);
void	save_fd_parent(int fd[2]);
void	ft_redir_heredoc(char *command, int orig_fds[2], int i);
int		execute_forked_external_one(char **args, t_envp *minienv);
void	redirect_fd(int fd_to_redirect, int fd_location);
void	ft_multiple_fork(char *input, int numb_commands,
			int *child_pid, t_envp **envp_vars);
int		execute_multiple_command(char *input, t_envp **envp_vars);
int		ft_symb_env(char red, char *command, t_envp **envp_vars);
char	*ft_pos_heredoc(char *str);
int		exec_heredoc(char *delimiter, char *file_name,
			int *exit_status, t_envp *envp_vars);
int		make_heredoc(char *input, t_envp *envp_vars, int *exit_status);
int		redirect_one_com(char *com, int orig_fds[2], t_envp **envp_vars, int i);

#endif