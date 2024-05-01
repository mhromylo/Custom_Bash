/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_chil.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochurko <ochurko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 12:55:06 by ochurko           #+#    #+#             */
/*   Updated: 2024/04/26 17:10:14 by mhromylo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	make_fd(char *com, char *file)
{
	int		fd;

	if (com[0] == '>' || com[0] == '|')
	{
		if (com[0] == '|')
			fd = open(file, O_WRONLY | O_CREAT | O_TRUNC | O_NOFOLLOW, 0644);
		else
			fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	}
	else
	{
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	return (fd);
}

char	find_redirect(char *str, int *i)
{
	*i = 0;
	while (str[*i])
	{
		if (str[*i] == '\'')
		{
			(*i)++;
			while (str[*i] != '\'')
				(*i)++;
		}
		if (str[*i] == '"')
		{
			(*i)++;
			while (str[*i] != '"')
				(*i)++;
		}
		if (str[*i] == '<' || str[*i] == '>')
			return (str[*i]);
		(*i)++;
	}
	return (0);
}

int	redirect_output(char *com)
{
	char	*file;
	int		fd;

	if (com[0] == '>' || com[0] == '|')
		file = ft_file_name(ft_move_space(com + 1));
	else
		file = ft_file_name(ft_move_space(com));
	fd = make_fd(com, file);
	if (fd == -1)
	{
		print_perror_msg("open", file);
		free(file);
		return (0);
	}
	else
	{
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	free(file);
	return (1);
}

void	quit_child(char **comms, t_envp **envp_vars)
{
	rl_clear_history();
	free_t_envp(envp_vars);
	free_arr(comms);
	close_all_fds();
	exit(EXIT_FAILURE);
}

void	red_chil(char *com, char **comms, t_envp **envp_vars)
{
	char	red;
	int		i;

	i = 0;
	red = find_redirect(com, &i);
	while (red)
	{
		if (red == '<' && com[i + 1] != '<')
		{
			if (redirect_input(com + (i + 1), envp_vars) == 0)
				quit_child(comms, envp_vars);
		}
		if (red == '>')
		{
			if (redirect_output(com + (i + 1)) == 0)
				quit_child(comms, envp_vars);
		}
		if (red == '<' && com[i + 1] == '<')
		{
			heredoc(com + (i + 2));
		}
		com = ft_move_command(com, red, 0, 0);
		red = find_redirect(com, &i);
	}
}
