/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhromylo <mhromylo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 11:46:57 by mhromylo          #+#    #+#             */
/*   Updated: 2024/04/30 11:49:00 by mhromylo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_redir_heredoc(char *command, int orig_fds[2], int i)
{
	if (orig_fds[0] == -1)
		orig_fds[0] = dup(0);
	heredoc(command + (i + 2));
}

int	execute_forked_external_one(char **args, t_envp *minienv)
{
	int		child_pid;
	char	*command;

	command = args[0];
	child_pid = fork();
	define_execute_signals(child_pid);
	if (child_pid == -1)
		print_perror_msg("fork", command);
	else if (child_pid == 0)
		execute_external(args, minienv);
	else
		return (wait_for_child(child_pid, 1));
	exit(1);
}

void	redirect_fd(int fd_to_redirect, int fd_location)
{
	dup2(fd_to_redirect, fd_location);
	close(fd_to_redirect);
}

void	ft_multiple_fork(char *input, int numb_commands,
		int *child_pid, t_envp **envp_vars)
{
	char	**commands;
	int		i;
	int		pipe_fd[2];

	i = 0;
	commands = split_commands(input, 0);
	save_fd_parent(pipe_fd);
	while (i < numb_commands)
	{
		handle_pipe(pipe_fd[1], commands[i], commands, numb_commands);
		child_pid[i] = fork();
		define_execute_signals(child_pid[i]);
		if (child_pid[i] == -1)
			print_perror_msg("fork", commands[i]);
		else if (child_pid[i] == 0)
		{
			red_chil(commands[i], commands, envp_vars);
			execute_command(commands[i], commands, envp_vars);
		}
		i++;
	}
	restore_original_fds(pipe_fd);
	free_arr(commands);
}

int	execute_multiple_command(char *input, t_envp **envp_vars)
{
	int		*child_pid;
	int		numb_commands;
	size_t	size;

	numb_commands = numb_com(input);
	size = sizeof(int) * (numb_commands + 1);
	child_pid = malloc(size);
	if (!child_pid)
		return (0);
	ft_bzero(child_pid, size);
	ft_multiple_fork(input, numb_commands, child_pid, envp_vars);
	free(input);
	return (wait_for_children(child_pid));
}
