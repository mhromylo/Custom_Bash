/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhromylo <mhromylo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 16:56:02 by mhromylo          #+#    #+#             */
/*   Updated: 2024/04/30 13:56:09 by mhromylo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	has_pipe(char *str)
{
	if (*str == '|')
		return (0);
	while (*str)
	{
		if (*str == '\'')
		{
			str++;
			while (*str != '\'')
				str++;
		}
		if (*str == '"')
		{
			str++;
			while (*str != '"')
				str++;
		}
		if (*str == '>' && str[1] == '|')
			str = str + 2;
		if (*str == '|')
			return (1);
		str++;
	}
	return (0);
}

static int	plus_last_name(char *key_pair)
{
	int	i;

	i = 0;
	while (key_pair[i] != '=' && key_pair[i])
		i++;
	if (i != 0 && key_pair[i - 1] == '+')
		return (1);
	return (0);
}

int	exp_rout(char *only_name, t_envp **envp_vars, char *str, int exit_status)
{
	char	*value;

	value = get_value(str);
	if (!value)
	{
		free(only_name);
		return (EXIT_SUCCESS);
	}
	if (!is_valid_varname(only_name) || str_equal(str, "="))
	{
		print_varname_err_msg("export", str);
		exit_status = 1;
	}
	else if (node_exist(only_name, *envp_vars))
	{
		if (plus_last_name(str))
			value = ft_strjoin(envp_val(only_name, *envp_vars), value);
		envp_update(only_name, value, *envp_vars);
	}
	else
		init_list(only_name, value, envp_vars);
	free(only_name);
	return (exit_status);
}

void	handle_pipe(int or_fd_out, char *cur_com, char **commands, int len)
{
	int			is_first_command;
	int			has_next_command;
	char		*last_command;
	static int	pipe_fds[2];

	last_command = commands[len - 1];
	is_first_command = (cur_com == commands[0]);
	has_next_command = (cur_com != last_command);
	if (!is_first_command)
		redirect_fd(pipe_fds[0], STDIN_FILENO);
	if (has_next_command)
	{
		if (pipe(pipe_fds) == -1)
			print_perror_msg("pipe", cur_com);
		redirect_fd(pipe_fds[1], STDOUT_FILENO);
	}
	else
		redirect_fd(or_fd_out, STDOUT_FILENO);
}

void	save_fd_parent(int fd[2])
{
	fd[0] = dup(STDIN_FILENO);
	fd[1] = dup(STDOUT_FILENO);
}
