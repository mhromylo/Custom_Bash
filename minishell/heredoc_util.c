/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhromylo <mhromylo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 11:50:19 by mhromylo          #+#    #+#             */
/*   Updated: 2024/04/30 11:55:17 by mhromylo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_symb_env(char red, char *command, t_envp **envp_vars)
{
	if ((red == '<' && command[1] == '<') && ft_issymb("<<", *envp_vars))
		return (1);
	if ((red == '>' && command[1] == '>') && ft_issymb(">>", *envp_vars))
		return (1);
	return (0);
}

char	*ft_pos_heredoc(char *str)
{
	while (*str && str[1])
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
		if (*str == '<' && str[1] == '<')
			return (str);
		str++;
	}
	return (NULL);
}

int	exec_heredoc(char *delimiter, char *file_name,
		int *exit_status, t_envp *envp_vars)
{
	int	child_pid;

	child_pid = fork();
	define_execute_signals(child_pid);
	if (child_pid == -1)
		print_perror_msg("fork - heredoc_prompt", delimiter);
	else if (child_pid == 0)
		read_heredoc(exit_status, envp_vars, delimiter, file_name);
	else
	{
		*exit_status = wait_for_child(child_pid, 1);
		define_main_signals();
		if (*exit_status != 0)
			return (0);
	}
	return (1);
}

int	make_heredoc(char *input, t_envp *envp_vars, int *exit_status)
{
	static int	i_file;
	char		*pos_heredoc;
	char		*file_name;
	char		*delimiter;

	i_file = 0;
	pos_heredoc = ft_pos_heredoc(input);
	if (!pos_heredoc)
		return (1);
	delimiter = ft_file_name(ft_move_space(pos_heredoc + 2));
	file_name = file_name_heredoc(i_file);
	i_file++;
	if (!exec_heredoc(delimiter, file_name, exit_status, envp_vars))
	{
		free(delimiter);
		return (0);
	}
	free(delimiter);
	free(file_name);
	return (make_heredoc(pos_heredoc + 2, envp_vars, exit_status));
}

int	redirect_one_com(char *com, int orig_fds[2], t_envp **envp_vars, int i)
{
	char	red;

	orig_fds[0] = -1;
	orig_fds[1] = -1;
	red = find_redirect(com, &i);
	while (!ft_symb_env(red, com, envp_vars) && red)
	{
		if (red == '<' && com[i + 1] != '<')
		{
			if (redirect_input_one(com + (i + 1), orig_fds, envp_vars) == 0)
				return (0);
		}
		else if (red == '>')
		{
			if (redirect_output_one(com + (i + 1), orig_fds) == 0)
				return (0);
		}
		if (red == '<' && com[i + 1] == '<')
			ft_redir_heredoc(com, orig_fds, i);
		com = ft_move_command(com, red, 0, 0);
		red = find_redirect(com, &i);
	}
	return (1);
}
